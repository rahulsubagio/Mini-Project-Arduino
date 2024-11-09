#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
}

void loop() {
  mataBerkedip();
  delay(300);  
  ekspresiDatar();
  delay(1500);
  mataBerkedip();
  delay(150);
  ekspresiMarah();
  delay(1500);
  mataBerkedip();
  delay(150);
  ekspresiSedih();
  delay(1500);
  mataBerkedip();
  delay(150);
  ekspresiSenang();
  delay(1500);
}

void mataBerkedip() {
  // Mata Berkedip (tertutup dengan garis horizontal)
  display.clearDisplay();
  display.fillRoundRect(20, 38, 40, 4, 2, SSD1306_WHITE); // Mata kiri tertutup
  display.fillRoundRect(70, 38, 40, 4, 2, SSD1306_WHITE); // Mata kanan tertutup
  display.display();
}

void ekspresiDatar() {
  // Ekspresi Datar
  display.clearDisplay();
  display.fillRoundRect(20, 20, 40, 40, 8, SSD1306_WHITE); // Mata kiri
  display.fillRoundRect(70, 20, 40, 40, 8, SSD1306_WHITE); // Mata kanan
  display.display();
}

void ekspresiMarah() {
  // Ekspresi Marah
  display.clearDisplay();
  display.fillRoundRect(20, 20, 40, 40, 8, SSD1306_WHITE); // Mata kiri penuh
  display.fillRoundRect(70, 20, 40, 40, 8, SSD1306_WHITE); // Mata kanan penuh
  display.fillTriangle(20, 20, 60, 20, 60, 40, SSD1306_BLACK); // Potongan kiri: kiri atas ke kanan bawah
  display.fillTriangle(70, 20, 70, 40, 110, 20, SSD1306_BLACK); // Potongan kanan: kanan atas ke kiri bawah
  display.display();
}

void ekspresiSedih() {
  // Ekspreasi Sedih
  display.clearDisplay();
  display.fillRoundRect(20, 20, 40, 40, 8, SSD1306_WHITE); // Mata kiri penuh
  display.fillRoundRect(70, 20, 40, 40, 8, SSD1306_WHITE); // Mata kanan penuh
  display.fillTriangle(60, 20, 20, 20, 20, 40, SSD1306_BLACK); // Potongan kiri: kanan atas ke kiri bawah
  display.fillTriangle(70, 20, 110, 40, 110, 20, SSD1306_BLACK); // Potongan kanan: kiri atas ke kanan bawah
  display.display();
}

void ekspresiSenang() {
  // Ekspresi Senang
  display.clearDisplay();
  display.fillRoundRect(20, 20, 40, 40, 8, SSD1306_WHITE); // Mata kiri penuh
  display.fillRoundRect(70, 20, 40, 40, 8, SSD1306_WHITE); // Mata kanan penuh
  display.fillTriangle(60, 60, 20, 60, 20, 40, SSD1306_BLACK); // Potongan kiri: kanan bawah ke kiri atas
  display.fillTriangle(70, 60, 110, 60, 110, 40, SSD1306_BLACK); // Potongan kanan: kiri bawah ke kanan atas
  display.display();
}