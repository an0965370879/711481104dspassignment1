# 數位訊號處理 作業專案 
### 學號 : 711481104 姓名 : 洪子軒
---
本專案包含手寫作業的掃描檔與數位版本，以及針對指定問題的程式碼實現與分析。

---

## **手寫作業 (Problems 1-6)**

這部分包含手寫的解答內容，並以圖檔形式嵌入。為了方便閱讀與搜尋，手寫內容也以 LaTeX 格式進行了數位化。

### **Problem 1**
![S__5816358_0](https://hackmd.io/_uploads/BJBwGu53ee.jpg)


### **Problem 1 - LaTeX 數位化**

---

若 $$x(t)=e^{j\Omega t}$$

求 $$y(t)（RC 低通，輸出在電容）$$

$RC電路公式:$

$$x(t)=RI(t)+y(t)$$
$$I(t)=\frac{dQ(t)}{dt}=C\frac{dy(t)}{dt}$$

$微分方程：(I(t)代入)$

$$x(t)=C\frac{dy(t)}{dt}R+y(t)$$ 
$$=RC\frac{dy(t)}{dt}+y(t)$$

$傅立葉轉換$

$$X(j\Omega)=RC(j\Omega)Y(j\Omega)+Y(j\Omega)$$

$同除以Y(j\omega)$

$$\frac{X(j\Omega)}{Y(j\Omega)}=RC(j\Omega)+1$$

$整理一下$

$$\frac{Y(j\Omega)}{X(j\Omega)}=\frac{1}{RC(j\Omega)+1} \equiv H(j\Omega)$$

$結果 :$

$$y(t)=H(j\Omega)\,e^{j\Omega t}=\frac{1}{1+j\Omega RC}\,e^{j\Omega t}$$

---

### **Problem 2**
![S__5816360_0](https://hackmd.io/_uploads/BkPKfuc2lg.jpg)
![S__5816361_0](https://hackmd.io/_uploads/r1wKfO9nxl.jpg)

### **Problem 2 - LaTeX 數位化**

若 $$x(t)=e^{j\Omega t}u(t)$$

求 $$y(t)（初始電容電壓假設為 0）$$

微分方程：

$$x(t)=RC\frac{dy(t)}{dt}+y(t)$$

代入$x(t)=e^{j\Omega t}u(t)$

$$e^{j\Omega t}u(t)=RC\frac{dy(t)}{dt}+y(t)$$

解為特解加齊次解：

$$y(t)=y_h(t)+y_p(t)$$

$y_h(t)(暫態響應):$

$$x(t)=RC\frac{dy}{dt}+y$$

$x(t)=0代入$

$$0=RC\frac{dy}{dt}+y$$

$同除以RC$

$$\frac{dy}{dt}=\frac{-1}{RC}y$$

$移項整理$

$$\frac{dy}{y}=\frac{-1}{RC}dt$$

$兩邊積分$

$$ln|y|=\frac{-t}{RC}+C$$

$兩邊取指數$

$$|y|=C_1e^{\frac{-t}{RC}}=y_h(t),(C_1=e^{c}為常數)$$

---

$y_p(t)(穩態響應):$

$$y_p(t)=Ke^{j\Omega t}$$

$代入e^{j\Omega t}u(t)=RC\frac{dy(t)}{dt}+y(t)$

$$e^{j\Omega t}=RC (j\Omega K e^{j\Omega t})+K e^{j\Omega t}$$

$同除e^{j\Omega t}$

$$1=RCj\Omega K+K$$

$提出K且做整理$

$$K=\frac{1}{1+RCj\Omega}$$

$代回y_p(t)=Ke^{j\Omega t}$

$$y_p(t)=\frac{1}{1+RCj\Omega}e^{j\Omega t}$$

---
暫態部分： $$y_h(t)=C_1e^{\frac{-t}{RC}},(C_1=e^{c}為常數)$$（隨時間衰減）

穩態部分： $$y_p(t)=\frac{1}{1+RCj\Omega}e^{j\Omega t}$$  

---

$$y(t)=y_h(t)+y_p(t)$$

$代入y_h(t),y_p(t)$

$$y(t)=C_1e^{\frac{-t}{RC}}+\frac{1}{1+RCj\Omega}e^{j\Omega t},t\ge0$$

$乘上u(t)$

$$y(t)=(C_1e^{\frac{-t}{RC}}+\frac{1}{1+RCj\Omega}e^{j\Omega t})u(t)$$

$假設輸入t<0為0,則輸出在t=0^{-}會為0 :$ 

$令t=0時$

$$y(0)=C_1+\frac{1}{1+j\Omega RC}=0$$

$整理一下$

$$C_1=\frac{-1}{1+j\Omega RC}$$

$將C_1代回y(t)$

$$y(t)=(\frac{1}{1+RCj\Omega}e^{j\Omega t}-\frac{1}{1+j\Omega RC}e^{\frac{-t}{RC}})u(t)$$

---

$結果 :$

$$y(t)=(\frac{1}{1+RCj\Omega}e^{j\Omega t}-\frac{1}{1+j\Omega RC}e^{\frac{-t}{RC}})u(t)$$

### **Problem 3**
![S__5816362_0](https://hackmd.io/_uploads/HJfjGu92ll.jpg)
![S__5816363_0](https://hackmd.io/_uploads/Bymif_9nge.jpg)

### **Problem 3 - LaTeX 數位化**
若 $$x(t)=e^{j\Omega t}$$

求 $$y(t)$$

$從Problem 1 得$

$$H(\Omega)=\frac{1}{1+j \Omega RC},y(t)=\frac{1}{1+j \Omega RC}e^{j\Omega t}$$

$題目給的參數$

$$R=1000\Omega , C=\frac{1}{2\pi\times400\times1000},\Omega=2\pi f$$
$代入$

$$j\Omega RC=\frac{f}{400}j$$

$example :$ $f=100Hz$

$$H(\Omega)=\frac{1}{1+\frac{100}{400}j}=\frac{1}{1+0.25j}$$

$$|H(\Omega)|=\frac{1}{\sqrt{1^2+0.25^2}}\approx0.9701$$

$$\angle H(\Omega)=-arctan(\frac{0.25}{1})\approx-14.04$$

$So:$

$$H(\Omega)=\approx0.9701e^{-j14.04^\circ}$$

$y(t):$

$$\Omega=2\pi\times10=200\pi\      rad/s$$

$$y(t)=(0.9701e^{-j14.04^\circ})e^{j(200\pi t)}$$

$$ =0.9701e^{j(200\pi t-14.04^\circ)}$$

$$ 以此類推f = 400,3000Hz照著上述的運算邏輯便能得到結果 $$

### **Problem 4**
![S__5816364_0](https://hackmd.io/_uploads/H1B2M_53ge.jpg)

### **Problem 4 - LaTeX 數位化**
若 $$x(t)=e^{j\Omega t}u(t)$$

求 $$y(t)$$

$從Problem 2 得:$

$$y(t)=(\frac{1}{1+RCj\Omega}e^{j\Omega t}-\frac{1}{1+j\Omega RC}e^{\frac{-t}{RC}})u(t)$$

$題目給的參數$

$$R=1000\Omega , C=\frac{1}{2\pi\times400\times1000},\Omega=2\pi f$$

$將參數代入y(t)$

$$y(t)=(\frac{1}{1+j\frac{f}{400}}e^{2\pi f tj}-\frac{1}{1+j\frac{f}{400}}e^{-800\pi t})u(t)$$

$$=\frac{1}{1+j\frac{f}{400}}(e^{2\pi ftj}-e^{-800\pi t})u(t)$$

$example :$ $f=100Hz代入y(t)$

$$y(t)=0.9701e^{-j14.04^\circ}(e^{2\pi ftj}-e^{-800\pi t})u(t)$$

$$ 以此類推f = 400,3000Hz代入y(t)便能得到結果 $$

### **Problem 5**
![S__5816365_0](https://hackmd.io/_uploads/BJ7pzO52ll.jpg)
![S__5816366_0](https://hackmd.io/_uploads/SkLpfOc3gx.jpg)
![S__5816367_0](https://hackmd.io/_uploads/Hk86fO92ge.jpg)

### **Problem 5 - LaTeX 數位化**
若 $$x[n]=exp(j\omega n)$$

求 $$y[n]=H(\Omega)exp(j\omega n)$$

$一階差分方程:$

$$y[n]=\frac{RC}{RC+\tau}y[n-1]+\frac{\tau}{\tau+RC}x[n],\tau=\frac{1}{f_s}$$

$DTFT:$

$$Y(e^{j\omega})=\frac{RC}{RC+\tau}Y(e^{j\omega})e^{-j\omega}+\frac{\tau}{RC+\tau}X(e^{j\omega})$$

$移項整理$

$$Y(e^{j\omega})(1-\frac{RC}{RC+\tau}e^{-j\omega})=\frac{\tau}{RC+\tau}X(e^{j\omega})$$
$移項整理$

$$\frac{Y(e^{j\omega})}{X(e^{j\omega})}=\frac{\frac{\tau}{RC+\tau}}{1-\frac{RC}{RC+\tau}e^{-j\omega}}=\frac{\tau}{RC+\tau-RCe^{-j\omega}}=H(j\omega)$$

$結果:$

 $$y[n]=H(\Omega)exp(j\omega n)=\frac{\tau}{RC+\tau-RCe^{-j\omega}}exp(j\omega n)$$
 $$=\frac{\frac{1}{f_s}}{RC+\frac{1}{f_s}-RCe^{-j\frac{2\pi f}{f_s}}}exp(j\frac{2\pi f}{f_s}n)$$

$$將f_s=4000,8000,16000Hz以及f=100,400,3000Hz分別代入後總共會有9種答案$$

### **Problem 6**
![S__5816368_0](https://hackmd.io/_uploads/HkACfdq2gx.jpg)
![S__5816369_0](https://hackmd.io/_uploads/Hk0AMOchxx.jpg)
![S__5816371_0](https://hackmd.io/_uploads/rJ0Cfu93ll.jpg)

### **Problem 6 - LaTeX 數位化**
若 $$x[n]=u[n]exp(j\omega n)$$
求 $$y[n]$$
$一階差分方程:$

$$ y[n] = \frac{RC}{RC+\tau}y[n-1] + \frac{\tau}{RC+\tau}x[n],\tau= 1/f_s $$
$轉換為 Z 域:$
$$ Y(z) = \frac{RC}{RC+\tau} z^{-1}Y(z) + \frac{\tau}{RC+\tau}X(z) $$
$找出轉移函數 H(z):$
$$ Y(z) \left(1 - \frac{RC}{RC+\tau} z^{-1}\right) = \frac{\tau}{RC+\tau}X(z) $$
$$ H(z) = \frac{Y(z)}{X(z)} = \frac{\frac{\tau}{RC+\tau}}{1 - \frac{RC}{RC+\tau} z^{-1}} $$

找出輸入訊號 $X(z):$

$$ X(z) = \sum_{n=-\infty}^{\infty} (e^{j\omega n}u[n])z^{-n} = \sum_{n=0}^{\infty} (e^{j\omega n})z^{-n} $$
利用等比級數公式 $\sum_{n=0}^{\infty} r^n = \frac{1}{1-r}$，當 $|r|<1$。
將 $r = e^{j\omega}z^{-1}$ 代入，得到：
$$ X(z) = \frac{1}{1-e^{j\omega}z^{-1}}, \quad |z|>1 $$

$計算輸出訊號 Y(z):$

$$ Y(z) =H(z)X(z)= \left( \frac{\frac{\tau}{RC+\tau}}{1 - \frac{RC}{RC+\tau} z^{-1}} \right) \left( \frac{1}{1-e^{j\omega}z^{-1}} \right) $$

$部分分式展開$


$$ Y(z) = \frac{A}{1 - \frac{RC}{RC+\tau}z^{-1}} + \frac{B}{1-e^{j\omega}z^{-1}} $$
其中：
$$ A = \frac{\frac{\tau}{RC+\tau}}{1-e^{j\omega}\left(\frac{RC+\tau}{RC}\right)^{-1}} = \frac{\frac{\tau}{RC+\tau}}{1-e^{j\omega}\frac{RC}{RC+\tau}} $$
$$ B = \frac{\frac{\tau}{RC+\tau}}{1-\frac{RC}{RC+\tau}e^{-j\omega}} $$

反 Z 變換得到 $y[n]:$

將 $A$ 和 $B$ 代入 $Y(z)$ 並進行反 Z 變換，得到時域訊號 $y[n]$。
* 第一項為**暫態響應 (Transient Response)**，其係數與極點 $\frac{RC}{RC+\tau}$ 有關。
* 第二項為**穩態響應 (Steady-State Response)**，其係數與輸入訊號的頻率有關。

$$ y[n] = \underbrace{A \left(\frac{RC}{RC+\tau}\right)^n u[n]}_{\text{暫態響應}} + \underbrace{B e^{j\omega n} u[n]}_{\text{穩態響應}} $$
$結果:(將A,B代入)$
$$ = \underbrace{\frac{\frac{\tau}{RC+\tau}}{1-e^{j\omega}\frac{RC}{RC+\tau}} \left(\frac{RC}{RC+\tau}\right)^n u[n]}_{\text{暫態響應}} + \underbrace{\frac{\frac{\tau}{RC+\tau}}{1-\frac{RC}{RC+\tau}e^{-j\omega}} e^{j\omega n} u[n]}_{\text{穩態響應}} $$


---

## **Problem 7：RC 濾波器分析**

## 程式碼詳解：WAV 一階 RC 數位濾波程式

> 原始程式為使用後向歐拉（backward Euler）離散化的一階低通濾波器，並同時對 WAV 檔做理論分析（複數指數訊號）與實際濾波處理。

---

## 目錄

1. 檔案與包含檔（`#include`）
2. 宏與常數定義（`#define`）
3. `WAVHeader` 結構（注意事項）
4. `extract_frequency_from_filename`：從檔名擷取測試頻率
5. `print_simulation_analysis`：理論與模擬分析逐行說明
6. `filter_audio`：濾波核心（單聲道 / 雙聲道）逐行說明
7. `main`：整體流程與重要檢查點
8. 理論推導與數學關係（為什麼 a, b 如此）
9. 常見問題、潛在 bug 與改善建議
10. 編譯、執行範例
11. 輸出結果
---

## 1. 檔案與包含檔（`#include`）

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <complex.h> // 核心：用於理論分析
```

**說明：**

* `stdio.h`, `stdlib.h`, `string.h`：基本 I/O、動態記憶體、字串處理。
* `math.h`：用到 `PI`、`acos()`、`round()` 等數學函數（連結時常需加 `-lm`）。
* `stdint.h`：提供明確大小型別（如 `uint32_t`、`int16_t`）。
* `complex.h`：使用 C99 複數型別與函數（`cexp`, `cabs`, `carg`），只在理論/模擬分析段使用。

> 注意：某些系統或編譯器需要在連結時指定 `-lm`（數學函式庫）。

---

## 2. 變數與常數定義（`#define`）

```c
#define PI 3.14159265358979323846
#define R_VALUE 1000.0
#define FC_ANALOG 400.0
#define C_VALUE (1.0 / (2.0 * PI * R_VALUE * FC_ANALOG))
#define NUM_SAMPLES 2000 // 模擬點數，用於理論分析

#ifndef I
#define I _Complex_I
#endif
```

**說明：**

* `R_VALUE` 與 `FC_ANALOG` 是用來求模擬的電路元件值（模擬一個 1kΩ 與 400 Hz 的 RC）。
* `C_VALUE` 根據類比 RC 截止頻率公式：
  $f_c = \frac{1}{2\pi R C} \Rightarrow C = \frac{1}{2\pi R f_c}$
* `NUM_SAMPLES`：理論模擬中使用的樣本數（複數指數輸入的長度）。
* `_Complex_I`：確保 `I` 被定義為複數單位。

---

## 3. `WAVHeader` 結構（注意事項）

```c
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
```

**說明與風險：**

* 這是常見的 WAV（RIFF）標頭欄位集合，通常總長是 44 bytes（對 PCM）。
* **注意對齊（struct padding）與 endianness**：直接用 `fread(&header, sizeof(WAVHeader), 1, fp)` 偶爾會因為 compiler 對 `struct` 的對齊（padding）導致讀取錯誤或與檔案位元順序不符。更穩妥的作法是讀 44 個位元組到 `unsigned char buf[44]`，再用 `memcpy` / 位移解析欄位或使用 `#pragma pack(1)`（但 pragma 亦有可攜性問題）。
* 驗證 `chunkId`（應該是 "RIFF"）、`format`（"WAVE"）、`subchunk1Id`（"fmt "）、以及 `subchunk2Id`（"data"）是好習慣。
* `audioFormat` == 1 表示 PCM。

---

## 4. `extract_frequency_from_filename`：從檔名擷取測試頻率

```c
double extract_frequency_from_filename(const char* filename) { ... }
```

**行為說明（演算法）：**

1. 使用 `strchr(filename, 'f')` 找出字串中第一個字母 `f`。
2. 每次找到 `f` 後，檢查 `f` 後面第一個字元是否為數字（`'0'..'9'`）。
3. 如果是數字，呼叫 `strtod` 從該位置解析浮點數；若解析成功（pointer 前進），並且數值 > 1 Hz，則回傳這個值。
4. 若失敗就尋找下一個 `f`，直到沒有更多 `f`。

**範例：**

* `sincos_fs4000_f3000_L1.0.wav`：第一個 `f` 在 "fs4000"，因為 `f` 後面是 `s`（非數字），會跳過，下一個 `f3000` 會成功解析為 `3000`（Hz）。

**注意：** 如果檔名格式不穩定或使用大寫 `F`，此函數會失敗（只有小寫 `f` 被搜尋）。如果你期望更多容錯性，可以改為同時搜尋 `'f'` 與 `'F'`，或使用正規表達式匹配 `f\s*([0-9]+(\.[0-9]+)?)`。

---

## 5. `print_simulation_analysis`：理論與模擬分析逐行說明

函數簽章：

```c
void print_simulation_analysis(double fs, double f_in) { ... }
```

**流程重點：**

1. `tau = 1.0 / fs;`：樣本週期（秒）。
2. `a = (R*C) / (R*C + tau);`、`b = tau / (tau + R*C);`：濾波器係數（由後向歐拉離散化得到，稍後會推導）。
3. `normalized_omega = 2.0 * PI * f_in / fs;`：數位角頻率 ω（rad/sample）。

**輸入訊號：**

* `x[n] = exp(j * normalized_omega * n)`：複數單位旋轉（複數指數）用來測試頻率響應（理想情況下，系統對這個複數正弦的穩態輸出就是 H(e^{jω}) 的乘積）。

**差分方程模擬：**

```c
y[0] = b * x[0];
for (int n = 1; n < NUM_SAMPLES; n++) {
    y[n] = a * y[n-1] + b * x[n];
}
```

* 這直接套用：`y[n] = a*y[n-1] + b*x[n]`。
* `y_steady_state = y[NUM_SAMPLES - 1];`：把最後一個樣本當作穩態值（實務上建議取最後 N 個樣本的平均以降低瞬態振盪影響）。

**解析解（理論）：**

* 差分方程的頻率響應：

  $$ H(e^{j\omega}) = \frac{b}{1 - a e^{-j\omega}}. $$

* 在程式中用 `h_theoretical = b / (1.0 - a * cexp(-I * normalized_omega));` 計算理論幅度與相位，並與模擬值比較。

**小技巧／注意：**

* 如果 `f_in` 超過 Nyquist（`fs/2`），`normalized_omega` 仍能被計算，但其實是對折後的頻率（aliasing）--- 也就是模擬與理論比較時要注意輸入檔案的實際內容是否已被採樣折疊。
* `NUM_SAMPLES` 必須足夠大使系統進入穩態；2000 對某些情況足夠，但若時間常數 RC 很大（比 `NUM_SAMPLES * tau` 大），則需要更長的模擬時間。

---

## 6. `filter_audio`：濾波核心（單聲道 / 雙聲道）逐行說明

函數簽章：

```c
void filter_audio(short* input, short* output, size_t num_samples, uint32_t fs, uint16_t num_channels, double a, double b) { ... }
```

**重點說明：**

* `num_samples` 在主程式被計算為 `header.subchunk2Size / sizeof(short)`，也就是 **樣本數（short 數量）**，而不是「frame 數」；對 stereo 而言，`num_samples` 包含左右聲道交錯的 short 數（例如：若原始音訊是 1000 frames stereo，則 `num_samples` = 2000）。

### Mono 分支

```c
for (size_t n = 0; n < num_samples; n++) {
    double y_current = a * y_prev_L + b * input[n];
    output[n] = (short)round(y_current);
    y_prev_L = y_current;
}
```

* 以 1 個狀態 `y_prev_L` 處理整串 samples（注意：input 用 `short` 整數直接參與運算）。

### Stereo 分支

```c
for (size_t i = 0; i < num_samples; i += 2) {
    // Left channel at input[i], Right channel at input[i+1]
}
```

* 對左右通道獨立維護 `y_prev_L` 與 `y_prev_R`，逐樣本更新。

**注意事項與改進建議：**

1. **溢位（clipping）**：`(short)round(y_current)` 可能超出 `int16_t` 的範圍 `[-32768,32767]`，應該先剪裁。
2. **正規化（Normalization）**：`input` 是原始的 PCM short（例如 -32768..32767）。常見做法是先把樣本轉為浮點範圍 `[-1.0, +1.0)`，做濾波，再乘回 `32767` 並剪裁，這能保持數值穩定且減少溢位。
3. **效率**：目前一次分配整個檔案到記憶體，對大型 WAV（幾百 MB）會吃大量 RAM。建議改成分塊（chunk）讀/寫並保持狀態 `y_prev`，即可線上處理長檔案。
4. **多聲道**：若要支援大於 2 個通道，改用迭代通道數而非硬編碼雙聲道。

---

## 7. `main`：整體流程與重要檢查點

### 主要步驟（依序）

1. 解析 `argv`，期望兩個參數：輸入與輸出 WAV 檔案。
2. `test_f_in = extract_frequency_from_filename(input_filename);`：從檔名擷取測試頻率（失敗則返回錯誤）。
3. 開啟輸入檔案並 `fread` WAV 標頭（`WAVHeader`）。
4. 檢查 `sampleRate` 與 `bitsPerSample == 16`。
5. 計算數位濾波器係數 `a`, `b`（基於 `fs`），並印出 `fc_digital`（程式中採 `acos(a)` 的近似式，見 §8）。
6. 呼叫 `print_simulation_analysis(fs, test_f_in);` 做理論與數值模擬比較。
7. 以 `subchunk2Size` 計算 `num_samples`，分配 `input_data` / `output_data`，`fread` 樣本資料（一次讀完）。
8. 呼叫 `filter_audio(...)`，將結果寫回 `output_filename`（先寫 header，再寫 data）。

**檢查點與風險：**

* `header.bitsPerSample` 只允許 16-bit，其他位深（24/32）會導致錯誤。
* `header.sampleRate == 0` 或 `subchunk2Size == 0` 都需報錯處理。
* `malloc` 可能失敗應該處理（程式已有部分處理）。

---

## 8. 理論推導與數學關係（為什麼 `a`, `b` 如此）

### 類比系統

一階 RC 低通之類比傳遞函數：

[ H_{analog}(s) = \frac{1}{1 + RC s}. ]

時間常數 ( \tau_{RC} = R C )。

微分方程（類比）：

$$\frac{dy(t)}{dt} = -\frac{1}{RC} y(t) + \frac{1}{RC} x(t)$$

### 後向歐拉（Backward Euler）離散化

以採樣週期 (T_s = \tau) 來離散化，後向歐拉代表示：

$$\frac{y[n] - y[n-1]}{T_s} \approx \frac{dy(t_n)}{dt} $$

將微分方程替換：

$$\frac{y[n] - y[n-1]}{T_s} = -\frac{1}{RC} y[n] + \frac{1}{RC} x[n]$$

整理：

$$y[n] (1 + \frac{T_s}{RC}) = y[n-1] + \frac{T_s}{RC} x[n]$$

乘上常數得：

$$ y[n] = \underbrace{\frac{RC}{RC + T_s}}*{a} ; y[n-1] + \underbrace{\frac{T_s}{RC + T_s}}*{b} ; x[n] $$

因此程式中 `a = RC/(RC + tau)`、`b = tau/(RC + tau)` 即為後向歐拉離散化結果。

> 與前向歐拉（forward Euler）或精確 ZOH（zero‑order hold）差異：ZOH 的精確對應係數為 `a = exp(-T_s/(RC))`、`b = 1 - exp(-T_s/(RC))`。後向歐拉是穩定但有數值阻尼的近似。

### 頻率響應

差分方程的系統函數：

$$H(z) = \frac{Y(z)}{X(z)} = \frac{b}{1 - a z^{-1}}$$

令 $z = e^{j\omega}$，就得

$$H(e^{j\omega}) = \frac{b}{1 - a e^{-j\omega}}$$

$在 DC（(\omega=0)）時：$

$$H(1) = \frac{b}{1 - a} = 1$$

代表直流增益為 1（不衰減），這與理想 RC 低通直流為 1 的特性符合。

### `fc_digital` 的計算（程式中的 `acos(a)`）

程式中使用：

```c
double fc_digital = (fs / (2.0 * PI)) * acos(a);
```

這是一個近似或啟發式的映射（把 `a` 映射到一個角頻率 `acos(a)`）。更嚴謹的做法是數值求解使得  $|H(e^{j\omega_c})| = 1/\sqrt{2}$  的 $(\omega_c)$（再換算成 Hz），或者直接使用 ZOH 的對應公式（若使用 $a = exp(-T_s/(RC)$)的話，可用 $f_c = -(1/(2\pi T_s)) ln(a)$）。

---

## 9. 常見問題、潛在 bug 與改善建議（逐條）

1. **WAV 標頭讀取的可攜性**：如前述，使用 `fread(&header, ...)` 可能遇到 struct packing 問題。改以讀 44 bytes 到緩衝區並手動解析會更穩。
2. **Endianness**：WAV 是 little-endian；在 big-endian 平台需轉換字節序。
3. **預防溢位**：對 `round(y_current)` 結果進行剪裁：

   ```c
   if (y_current > 32767) y_current = 32767;
   if (y_current < -32768) y_current = -32768;
   ```
4. **數值尺度**：建議把 short 轉換為浮點 `double x = input[n] / 32768.0;` 做濾波，再乘回 `32767.0` 寫回 short，這樣不容易 overflow 且保留振幅資訊。
5. **檢查 `audioFormat`**：應確保 `header.audioFormat == 1`（PCM）。
6. **支援不同位深與通道**：24-bit PCM 與浮點 WAV 需額外支援。
7. **大檔案的記憶體**：改成分塊讀寫並保留 `y_prev` 狀態以線上處理（streaming）。
8. **釋放資源**：遇錯要在每個失敗分支保證 `fclose`, `free` 被呼叫，避免記憶體或檔案 handle 泄漏。
9. **檔名解析的容錯**：支援 `F`、空白或 `f=` 等情形。
10. **輸出 header 校正**：目前直接把原始 header 寫回，但若你改變資料位元或樣本數、或想保留某些 metadata，需更新 `subchunk2Size`、`chunkSize` 等欄位。

---

## 10. 編譯、執行範例

**編譯**：

```bash
gcc -std=c11 -O2 -Wall -Wextra RC_filtering.c -o RC_filtering -lm
```

**執行**（範例檔名必須包含 `fXXXX`，例如 `f3000`）：

```bash
.\RC_filtering sincos_fs4000_f3000_L1.0.wav filtered_sincos_fs4000_f3000_L1.0.wav
```

程式會：

* 從 `sincos_fs4000_f3000_L1.0.wav` 擷取 `f_in = 3000`。
* 輸出濾波後結果到 `filtered_sincos_fs4000_f3000_L1.0.wav`（保留原 header，直接覆寫 sample data）。

---
## 11. 輸出結果
![螢幕擷取畫面 2025-10-01 125013](https://hackmd.io/_uploads/Bk3GQVc3lg.png)
**第一部分 WAV File Processing & Filtering**
* 輸出內容: 檔案資訊和濾波器係數計算
* 主要目的: 顯示程式讀取的檔案參數，並根據這些參數計算出數位濾波器所需的係數 a 和 b


**第二部分 Theoretical Steady-State Analysis**
* 輸出內容: 使用複數分析和模擬計算理論上的頻率響應 H(ω)
* 主要目的: 驗證此數位濾波器在輸入特定頻率 f_in 時，應有的理論輸出幅度和相位

**第三部分 輸出濾波音檔**
* 輸出內容:如果中間讀檔名或是濾波沒什麼問題會顯示成功且輸出檔名會是一開始輸出的期望檔名，**ex:** filtered_sincos_fs4000_f3000_L1.0.wav
---

### **濾波結果與頻率響應討論**

#### **1. 繪圖與波形分析**
以下圖表展示了輸入的 sine/cosine wave（濾波前）和經過 RC 濾波器處理後（濾波後）的波形。我們將觀察振幅和相位的變化。
#### fs:4000Hz f:100Hz
| 濾波前波形圖 | 濾波後波形圖 |
| :---: | :---: |
|![scf4000f100](https://hackmd.io/_uploads/S1FuEdq2ge.png)|![fscf4000f100](https://hackmd.io/_uploads/S1I3Edcngx.png)|

---

#### fs:4000Hz f:400Hz
| 濾波前波形圖 | 濾波後波形圖 |
| :---: | :---: |
|![scf4000f400](https://hackmd.io/_uploads/rkYkH_q3eg.png)|![fsc4000f400](https://hackmd.io/_uploads/BkjxSu5hll.png)|
---

#### fs:4000Hz f:3000Hz
| 濾波前波形圖 | 濾波後波形圖 |
| :---: | :---: |
| ![scf4000f3000](https://hackmd.io/_uploads/HyYQr_93ge.png)| ![fscf4000f3000](https://hackmd.io/_uploads/SkcNSuchgx.png)|
---

#### fs:8000Hz f:100Hz
| 濾波前波形圖 | 濾波後波形圖 |
| :---: | :---: |
| ![scf8000f100](https://hackmd.io/_uploads/HJXhBuqngx.png)| ![fscf8000f100](https://hackmd.io/_uploads/SJVpBd53el.png)|
---

#### fs:8000Hz f:400Hz
| 濾波前波形圖 | 濾波後波形圖 |
| :---: | :---: |
| ![scf8000f400](https://hackmd.io/_uploads/ryecrO93gl.png)| ![fscf8000f400](https://hackmd.io/_uploads/Syq5HOq2xe.png)|
---

#### fs:8000Hz f:3000Hz
| 濾波前波形圖 | 濾波後波形圖 |
| :---: | :---: |
| ![scf8000f3000](https://hackmd.io/_uploads/By50r_c2xx.png)| ![fscf8000f3000](https://hackmd.io/_uploads/Hk3JIuqnlg.png)|
---

#### fs:16000Hz f:100Hz
| 濾波前波形圖 | 濾波後波形圖 |
| :---: | :---: |
| ![scf16000f100](https://hackmd.io/_uploads/S1qLI_52ll.png)| ![fscf16000f100](https://hackmd.io/_uploads/rJ_PUd9hex.png)|
---

#### fs:16000Hz f:400Hz
| 濾波前波形圖 | 濾波後波形圖 |
| :---: | :---: |
| ![scf16000f400](https://hackmd.io/_uploads/ByUdI_93xg.png)| ![fsf16000f400](https://hackmd.io/_uploads/SydtUd5hel.png)|
---

#### fs:16000Hz f:3000Hz
| 濾波前波形圖 | 濾波後波形圖 |
| :---: | :---: |
| ![scf16000f3000](https://hackmd.io/_uploads/HyccIOc3ge.png)| ![fscf16000f3000](https://hackmd.io/_uploads/Sy5j8uqnll.png)|

**觀察與討論：**
### 1. 濾波前後比較
在將輸入信號通過設計的濾波器後，可以明顯觀察到以下現象：  
- **幅度響應**：低於截止頻率的訊號幾乎沒有衰減，高於截止頻率的成分則逐漸被抑制。  
- **相位響應**：隨著頻率增加，輸出信號相對於輸入信號會產生相位延遲，且延遲量在高頻段更為顯著。

### 2. 理論與實驗比較
根據理論，一階低通濾波器在截止頻率 $( f_c )$ 附近，輸入與輸出之間應該有約 $(-45^\circ)$ 的相位差，且輸出振幅為輸入的$(\frac{1}{\sqrt{2}})$（約為 −3 dB）。  
- 在本次實驗結果中，於 $( f \approx f_c )$ 的位置，測得的輸出振幅與相位變化與理論大致吻合。  
- 在低頻區域，輸入與輸出幾乎同相位，延遲接近零。  
- 在高頻區域，輸出不僅被大幅衰減，還伴隨更大的相位延遲。

### 3. 誤差來源
雖然整體結果符合預期，但仍存在些許偏差，可能的原因包括：  
- **取樣頻率限制**：若接近奈奎斯特頻率，數位化後的相位與幅度會有誤差。  
- **暫態響應影響**：若在輸入剛開始時觀察，可能會包含尚未消退的暫態成分。  
- **數值誤差**：由於程式中採用浮點運算與有限精度，計算結果可能與理論有微小差距。  

### 4. 總結
整體而言，濾波結果符合低通濾波器的理論特性：  
- **低頻保持、通過順暢**  
- **高頻被抑制並伴隨明顯相位延遲**  
這樣的設計在實際應用中能有效濾除高頻雜訊，但若應用對相位線性有嚴格需求，可能需要進一步考慮 **線性相位濾波器（如 FIR）** 或 **相位補償方法**。

#### **2. 與類比訊號計算的差異**

在 Problems 1-6 中，我們針對類比訊號計算了其頻率響應。這些計算結果應該與數位濾波器的結果非常接近。

* **-3dB 概念：**
  * -3dB 點表示訊號振幅衰減到**原始振幅的 $1/\sqrt{2}$**（約 0.707 倍）時的頻率。
  * 根據類比計算，這個 RC 濾波器的截止頻率為 400 Hz。請將你在手寫作業中的計算結果與數位濾波的實際觀察進行比較。
  * 請討論你的數位濾波結果是否在 400 Hz 附近也呈現約 0.707 倍的振幅衰減。

---

## **參考資料**
* [GitHub Markdown 指南](https://docs.github.com/zh/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
* [LaTeX 數學公式語法](https://en.wikibooks.org/wiki/LaTeX/Mathematics)