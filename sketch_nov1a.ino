#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- 1. MUKA NORMAL (Mata Kapsul + Mulut Senyum Imut) ---
void drawFaceNormal() {
  display.clearDisplay();
  // Mata Kapsul Tebal
  display.fillRoundRect(20, 14, 28, 34, 8, SSD1306_WHITE);
  display.fillRoundRect(80, 14, 28, 34, 8, SSD1306_WHITE);
  // Mulut Senyum Mochi
  display.fillRoundRect(58, 44, 12, 4, 2, SSD1306_WHITE);
  display.display();
}

// --- 2. MUKA LOVE / BUCIN (Mata Bentuk Hati) ---
void drawFaceLove() {
  display.clearDisplay();
  
  // Hati Kiri
  display.fillCircle(28, 24, 7, SSD1306_WHITE);
  display.fillCircle(40, 24, 7, SSD1306_WHITE);
  display.fillTriangle(21, 26, 47, 26, 34, 42, SSD1306_WHITE);
  
  // Hati Kanan
  display.fillCircle(88, 24, 7, SSD1306_WHITE);
  display.fillCircle(100, 24, 7, SSD1306_WHITE);
  display.fillTriangle(81, 26, 107, 26, 94, 42, SSD1306_WHITE);
  
  // Mulut Senyum Lebar
  display.fillRoundRect(56, 42, 16, 6, 3, SSD1306_WHITE);
  display.display();
}

// --- 3. MUKA TIDUR + GELEMBUNG INGUS (Sleeping & Bubble) ---
void drawFaceSleepy(bool bubbleBig) {
  display.clearDisplay();
  
  // Mata Meram / Garis Lengkung Datar
  display.fillRoundRect(20, 32, 28, 5, 2, SSD1306_WHITE);
  display.fillRoundRect(80, 32, 28, 5, 2, SSD1306_WHITE);
  
  // Gelembung Ingus Mochi di dekat hidung/mata kanan
  int bSize = bubbleBig ? 7 : 4;
  display.drawCircle(74, 28, bSize, SSD1306_WHITE);
  display.fillCircle(74, 28, bSize - 2, SSD1306_BLACK); // Efek gelembung bening
  
  // Mulut Datar Kecil
  display.drawFastHLine(59, 44, 10, SSD1306_WHITE);
  display.display();
}

// --- 4. MUKA MARAH / KESEL (> < + Vektor Urat) ---
void drawFaceAngry() {
  display.clearDisplay();
  
  // Mata > (Kiri)
  display.drawLine(20, 20, 38, 30, SSD1306_WHITE);
  display.drawLine(20, 21, 38, 31, SSD1306_WHITE);
  display.drawLine(20, 40, 38, 30, SSD1306_WHITE);
  display.drawLine(20, 39, 38, 29, SSD1306_WHITE);
  
  // Mata < (Kanan)
  display.drawLine(108, 20, 90, 30, SSD1306_WHITE);
  display.drawLine(108, 21, 90, 31, SSD1306_WHITE);
  display.drawLine(108, 40, 90, 30, SSD1306_WHITE);
  display.drawLine(108, 39, 90, 29, SSD1306_WHITE);
  
  // Simbol Urat Marah di Jidat (Kanan Atas)
  display.drawFastHLine(102, 10, 8, SSD1306_WHITE);
  display.drawFastVLine(106, 6, 8, SSD1306_WHITE);
  display.drawFastHLine(100, 14, 8, SSD1306_WHITE);
  
  // Mulut Taring Marah
  display.fillTriangle(56, 42, 72, 42, 64, 52, SSD1306_WHITE);
  display.display();
}

// --- 5. MUKA KAGET / NGUAP LEBAR (Mata Bulat + Mulut O Besar) ---
void drawFaceShocked() {
  display.clearDisplay();
  
  // Mata Menyempit Agak Bulat
  display.fillRoundRect(24, 18, 22, 28, 6, SSD1306_WHITE);
  display.fillRoundRect(82, 18, 22, 28, 6, SSD1306_WHITE);
  
  // Mulut O Menganga Lebar
  display.fillRoundRect(56, 36, 16, 20, 6, SSD1306_WHITE);
  display.fillRoundRect(59, 39, 10, 14, 4, SSD1306_BLACK); // Lubang mulut hitam
  display.display();
}

// --- 6. ANIMASI KEDIP HALUS ---
void animBlink() {
  // Meram sebentar
  display.clearDisplay();
  display.fillRoundRect(20, 28, 28, 5, 2, SSD1306_WHITE);
  display.fillRoundRect(80, 28, 28, 5, 2, SSD1306_WHITE);
  display.fillRoundRect(58, 44, 12, 4, 2, SSD1306_WHITE);
  display.display();
  delay(100);
  
  // Melek lagi
  drawFaceNormal();
}

void setup() {
  Wire.begin(8, 9); // Pin I2C ESP32-C3 Super Mini
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }

  display.clearDisplay();
  drawFaceNormal();
}

void loop() {
  // --- ALUR SIMULASI EKSPRESI NIXON ANIMATION MOCHI ---
  
  // 1. Standby Biasa & Kedip
  drawFaceNormal();
  delay(2000);
  animBlink();
  delay(1000);
  
  // 2. Ekspresi Love / Bucin
  drawFaceLove();
  delay(2500);
  
  // 3. Ekspresi Marah (> <)
  drawFaceAngry();
  delay(2500);

  // 4. Ekspresi Kaget / Nguap Lebar
  drawFaceShocked();
  delay(2000);
  
  // 5. Tidur Ngorok (Gelembung ingus membesar & mengecil)
  for(int i = 0; i < 3; i++) {
    drawFaceSleepy(false); // Gelembung kecil
    delay(500);
    drawFaceSleepy(true);  // Gelembung membesar
    delay(700);
  }
}