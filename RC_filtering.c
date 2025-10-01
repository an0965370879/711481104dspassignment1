#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <complex.h> // 核心：用於理論分析

// 定義常量
#define PI 3.14159265358979323846
#define R_VALUE 1000.0
#define FC_ANALOG 400.0 
#define C_VALUE (1.0 / (2.0 * PI * R_VALUE * FC_ANALOG)) 
#define NUM_SAMPLES 2000 // 模擬點數，用於理論分析

// 確保編譯器識別虛數單位
#ifndef I
#define I _Complex_I
#endif

// WAV 檔案標頭結構 (44 位元組)
typedef struct {
    char chunkId[4];
    uint32_t chunkSize;
    char format[4];
    char subchunk1Id[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char subchunk2Id[4];
    uint32_t subchunk2Size;
} WAVHeader;

// --- 新增：從檔名提取頻率的函數 ---
/**
 * @brief 嘗試從檔案名稱中提取測試頻率 (fXXXX 部分)。
 */
double extract_frequency_from_filename(const char* filename) {
    const char* start_f_marker = strchr(filename, 'f');
    
    while (start_f_marker) {
        const char* start_of_number = start_f_marker + 1;
        
        char* end_ptr;
        
        // 檢查 'f' 後面緊接著的字元是否為數字 (0-9)
        if (*start_of_number >= '0' && *start_of_number <= '9') {
            
            double f_value = strtod(start_of_number, &end_ptr);
            
            if (start_of_number != end_ptr) {
                // 要求提取到的頻率必須大於 1 Hz，以避免誤判
                if (f_value > 1.0) { 
                    return f_value;
                }
            }
        }
        
        // 如果這個 'f' 失敗了，繼續尋找下一個 'f'
        start_f_marker = strchr(start_f_marker + 1, 'f');
    }
    
    return 0.0; 
}


/**
 * @brief 執行理論穩態分析，輸出該 fs 下對指定 f_in 的響應。
 */
void print_simulation_analysis(double fs, double f_in) {
    // 檢查頻率有效性
    double tau = 1.0 / fs;
    double a = (R_VALUE * C_VALUE) / (R_VALUE * C_VALUE + tau); 
    double b = tau / (tau + R_VALUE * C_VALUE);                  
    double normalized_omega = 2.0 * PI * f_in / fs; // 這裡 f_in > fs/2 相當於計算頻率的折疊波

    printf("\n--- Theoretical Steady-State Analysis ---\n");
    printf("Test Parameters: fs = %.0f Hz, f_in = %.0f Hz\n", fs, f_in);
    printf("Filter coefficients: a = %f, b = %f\n", a, b);

    // 2. 生成輸入信號 (x[n] = exp(j * omega * n))
    double complex x[NUM_SAMPLES];
    double complex y[NUM_SAMPLES];
    for (int n = 0; n < NUM_SAMPLES; n++) {
        x[n] = cexp(I * normalized_omega * n);
    }

    // 3. 執行差分方程式模擬
    y[0] = b * x[0];
    for (int n = 1; n < NUM_SAMPLES; n++) {
        y[n] = a * y[n-1] + b * x[n];
    }
    
    // 4. 分析結果 (計算穩態響應)
    double complex y_steady_state = y[NUM_SAMPLES - 1]; 
    
    double magnitude_sim = cabs(y_steady_state);
    double phase_y_sim = carg(y_steady_state) * 180.0 / PI;
    
    // 5. 理論解析解比較 (H(omega) = b / (1 - a * e^(-j*omega)))
    double complex h_theoretical = b / (1.0 - a * cexp(-I * normalized_omega));
    double theoretical_mag = cabs(h_theoretical);
    double theoretical_phase = carg(h_theoretical) * 180.0 / PI;

    printf("Simulation Results (Steady-State):\n");
    printf("Magnitude: %.4f\n", magnitude_sim);
    printf("Phase: %.4f degrees\n", phase_y_sim); 

    printf("Theoretical H(omega) (Analytic Solution):\n");
    printf("Magnitude |H(W)|: %.4f\n", theoretical_mag);
    printf("Phase: %.4f degrees\n", theoretical_phase); 
}


/**
 * @brief 濾波核心函數：同時處理單聲道和雙聲道 (用於 WAV 檔案)
 */
void filter_audio(short* input, short* output, size_t num_samples, uint32_t fs, uint16_t num_channels, double a, double b) {
    // 聲道延遲狀態的定義
    double y_prev_L = 0.0;
    double y_prev_R = 0.0; 

    if (num_channels == 1) {
        for (size_t n = 0; n < num_samples; n++) {
            double y_current = a * y_prev_L + b * input[n];
            output[n] = (short)round(y_current);
            y_prev_L = y_current;
        }
        printf("Mode:(1 Channel) Filtered.\n");
    } 
    else if (num_channels == 2) {
        for (size_t i = 0; i < num_samples; i += 2) {
            
            double x_L = input[i];
            double y_current_L = a * y_prev_L + b * x_L;
            output[i] = (short)round(y_current_L);
            y_prev_L = y_current_L;

            double x_R = input[i + 1];
            double y_current_R = a * y_prev_R + b * x_R;
            output[i + 1] = (short)round(y_current_R);
            y_prev_R = y_current_R;
        }
        printf("Mode: Stereo (2 Channels) Filtered Independently.\n");
    }
    else {
        fprintf(stderr, "Warning: Unsupported channel count (%u). Only Mono (1) and Stereo (2) supported.\n", num_channels);
        memcpy(output, input, num_samples * sizeof(short));
    }
}


int main(int argc, char* argv[]) {
    
    char* input_filename = NULL;
    char* output_filename = NULL;
    double test_f_in = 0.0; 

    // 檢查參數數量：必須是 3 個 (程式名、輸入檔名、輸出檔名)
    if (argc == 3) {
        input_filename = argv[1];
        output_filename = argv[2];
    } else {
        printf("\n--- ERROR: Missing Parameters ---\n");
        printf("Usage: %s <input.wav> <output.wav>\n", argv[0]);
        printf("Example: %s sincos_fs4000_f3000_L1.0.wav filtered_output.wav\n", argv[0]);
        printf("Note: The test frequency (f_in) is now extracted from the input filename.\n");
        return 1;
    } 
    
    // *** 提取測試頻率 (f_in) ***
    test_f_in = extract_frequency_from_filename(input_filename);
    if (test_f_in == 0.0) {
        printf("\nERROR: Failed to extract test frequency (f_in) from filename: %s\n", input_filename);
        printf("Please ensure the filename contains 'fXXXX' (e.g., 'f3000').\n");
        return 1;
    }

    // 1. 讀取 WAV 檔案並讀取檔頭
    FILE* fp_in = fopen(input_filename, "rb");
    if (!fp_in) {
        perror("Error: Could not open input file");
        return 1;
    }

    WAVHeader header;
    fread(&header, sizeof(WAVHeader), 1, fp_in);
    
    uint32_t fs = header.sampleRate;
    uint16_t num_channels = header.numChannels;
    
    if (fs == 0 || header.bitsPerSample != 16) {
        fprintf(stderr, "Error: Invalid Sample Rate (0) or unsupported bit depth (must be 16-bit).\n");
        fclose(fp_in);
        return 1;
    }

    printf("\n--- WAV File Processing & Filtering ---\n");
    printf("Input File: %s\n", input_filename);
    printf("Sample Rate (fs) = %u Hz\n", fs);
    printf("Channels = %u\n", num_channels);
    printf("Extracted Test Frequency (f_in): %.0f Hz\n", test_f_in);

    // 2. 計算 WAV 檔案取樣率下的濾波器係數
    double tau = 1.0 / (double)fs;
    double a = (R_VALUE * C_VALUE) / (R_VALUE * C_VALUE + tau); 
    double b = tau / (tau + R_VALUE * C_VALUE);                  
    double fc_digital = (fs / (2.0 * PI)) * acos(a); 

    printf("Digital Filter Theory (based on WAV fs):\n");
    printf("  y[n] = a * y[n-1] + b * x[n]\n");
    printf("  a = %f\n", a);
    printf("  b = %f\n", b);
    printf("Digital Cutoff Freq (fc_digital): %.2f Hz\n", fc_digital);

    // *** 3. 執行理論分析 (使用從檔案提取的 fs 和 f_in) ***
    print_simulation_analysis(fs, test_f_in);

    // 計算總樣本數
    size_t num_samples = header.subchunk2Size / sizeof(short);
    short* input_data = (short*)malloc(num_samples * sizeof(short));
    short* output_data = (short*)malloc(num_samples * sizeof(short));
    
    if (!input_data || !output_data) {
        perror("Error: Memory allocation failed");
        free(input_data); free(output_data); fclose(fp_in);
        return 1;
    }

    fread(input_data, sizeof(short), num_samples, fp_in);
    fclose(fp_in);
    
    // 4. 執行 WAV 濾波
    filter_audio(input_data, output_data, num_samples, fs, num_channels, a, b);

    // 5. 寫入新的 WAV 檔案
    FILE* fp_out = fopen(output_filename, "wb");
    if (!fp_out) {
        perror("Error: Could not open output file");
        free(input_data); free(output_data);
        return 1;
    }
    
    fwrite(&header, sizeof(WAVHeader), 1, fp_out);
    fwrite(output_data, sizeof(short), num_samples, fp_out);
    
    fclose(fp_out);
    free(input_data);
    free(output_data);

    printf("Success: Filtered audio saved to '%s'.\n", output_filename);

    return 0;
}