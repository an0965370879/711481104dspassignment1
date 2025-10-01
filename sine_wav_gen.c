#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h> 

#define PI 3.14159265359

// 定義 WAV 檔案的標頭結構
typedef struct {
    char chunkId[4];        // "RIFF"
    uint32_t chunkSize;     // File size - 8 bytes
    char format[4];         // "WAVE"
    char subchunk1Id[4];    // "fmt "
    uint32_t subchunk1Size;   // Size of subchunk1, usually 16
    uint16_t audioFormat;     // 1 for PCM
    uint16_t numChannels;     // 聲道數 (更改為 2)
    uint32_t sampleRate;      // Sample rate
    uint32_t byteRate;        // Bytes per second
    uint16_t blockAlign;      // Bytes per sample block
    uint16_t bitsPerSample;   // 16 bits per sample
    char subchunk2Id[4];    // "data"
    uint32_t subchunk2Size;   // Size of data chunk
} WAVHeader;

int main(int argc, char *argv[]) {
    // 檢查命令列參數數量
    if (argc != 5) {
        printf("Usage: %s <sample_rate> <signal_freq> <duration_sec> <output_filename.wav>\n", argv[0]);
        return 1;
    }

    // 從命令列參數中讀取數值
    double fs = atof(argv[1]); // 取樣頻率
    double f = atof(argv[2]);  // 訊號頻率
    double L = atof(argv[3]);  // 訊號時長
    char *filename = argv[4];  // 輸出檔名

    // 參數有效性檢查 (保持不變)
    if (fs <= 0 || f <= 0 || L <= 0) {
        printf("Error: Sampling rate, signal frequency, and duration must be positive numbers.\n");
        return 1;
    }
    
    // 計算音訊數據的相關參數
    double T = 1.0 / fs;
    size_t N_mono = (size_t)(L * fs); // 單聲道的樣本總數
    
    // !!! 關鍵改變 1: 雙聲道，總樣本數加倍 !!!
    size_t N_stereo = N_mono * 2; 
    
    const int BITS_PER_SAMPLE = 16;
    const int NUM_CHANNELS = 2; // !!! 關鍵改變 2: 聲道數設為 2 !!!

    // 動態分配記憶體給音訊數據陣列 (大小為單聲道總數的兩倍)
    short *x = (short *)malloc(sizeof(short) * N_stereo);
    if (x == NULL) {
        perror("malloc failed");
        return 1;
    }

    // !!! 關鍵改變 3: 生成雙聲道交錯數據 (Interleaved Data) !!!
    // x[2*n] 是左聲道 (Sine), x[2*n + 1] 是右聲道 (Cosine)
    for (size_t n = 0; n < N_mono; n++) {
        // 時間點 t = n * T
        double time = (double)n * T;
        
        // 左聲道 (L): Sine wave (正弦波)
        double sine_amplitude = 10000.0 * sin(2.0 * PI * f * time);
        
        // 右聲道 (R): Cosine wave (餘弦波)
        double cosine_amplitude = 10000.0 * cos(2.0 * PI * f * time);
        
        // 交錯寫入陣列: L R L R L R ...
        x[2 * n]     = (short)floor(sine_amplitude + 0.5);   // 左聲道 (Left Channel)
        x[2 * n + 1] = (short)floor(cosine_amplitude + 0.5); // 右聲道 (Right Channel)
    }
    
    // 填充 WAV 標頭 (需要更新所有與聲道數相關的欄位)
    WAVHeader header;
    memcpy(header.chunkId, "RIFF", 4);
    
    // chunkSize = 36 + DataSize = 36 + (N_stereo * 2 bytes/sample)
    header.chunkSize = 36 + (N_stereo * sizeof(short)); 
    
    memcpy(header.format, "WAVE", 4);
    memcpy(header.subchunk1Id, "fmt ", 4);
    header.subchunk1Size = 16;
    header.audioFormat = 1;
    header.numChannels = NUM_CHANNELS; // 2
    header.sampleRate = (uint32_t)fs;
    
    // byteRate = SampleRate * NumChannels * (BitsPerSample / 8)
    header.byteRate = fs * NUM_CHANNELS * (BITS_PER_SAMPLE / 8); 
    
    // blockAlign = NumChannels * (BitsPerSample / 8) = 2 * 2 = 4 bytes
    header.blockAlign = NUM_CHANNELS * (BITS_PER_SAMPLE / 8); 
    
    header.bitsPerSample = BITS_PER_SAMPLE;
    memcpy(header.subchunk2Id, "data", 4);
    
    // subchunk2Size = N_stereo * 2 bytes/sample
    header.subchunk2Size = N_stereo * sizeof(short); 

    // 寫入 WAV 檔案 (保持不變，但寫入 N_stereo 個樣本)
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("fopen failed");
        free(x);
        return 1;
    }

    // 依序寫入 WAV 標頭和音訊數據
    fwrite(&header, sizeof(WAVHeader), 1, fp);
    fwrite(x, sizeof(short), N_stereo, fp); // 寫入 N_stereo 個樣本

    // 清理並結束
    fclose(fp);
    free(x);

    printf("Successfully generated Stereo WAV file (L:Sine, R:Cosine) ：%s\n", filename);

    return 0;
}