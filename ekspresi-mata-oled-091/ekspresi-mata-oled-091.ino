#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
}

void loop() {
  ekspresiMelihatKiri();
  delay(1500);
  mataBerkedip();
  delay(150);
  ekspresiMelihatKanan();
  delay(1500);
  mataBerkedip();
  delay(150);
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
  mataBerkedip();
  delay(150);
}

void ekspresiMelihatKiri() {
  // Melihat ke kiri (kedua mata memenuhi layar dan berada di tengah)
  display.clearDisplay();
  display.fillRoundRect(0, 0, 50, 32, 8, SSD1306_WHITE); // Mata kiri berada di tengah layar dengan rounded lebih kecil
  display.fillRoundRect(58, 4, 45, 24, 6, SSD1306_WHITE); // Mata kanan lebih kecil dan posisinya sedikit lebih ke atas
  display.display();
}

void ekspresiMelihatKanan() {
  // Melihat ke kanan (kedua mata memenuhi layar dan berada di tengah)
  display.clearDisplay();
  display.fillRoundRect(24, 4, 45, 24, 6, SSD1306_WHITE); // Mata kiri lebih kecil dan posisinya sedikit lebih ke atas
  display.fillRoundRect(76, 0, 50, 32, 8, SSD1306_WHITE); // Mata kanan berada di tengah layar dengan rounded lebih kecil
  display.display();
}

void ekspresiDatar() {
  // Ekspresi Datar (kedua mata memenuhi layar dan berada di tengah)
  display.clearDisplay();
  display.fillRoundRect(9, 0, 50, 32, 8, SSD1306_WHITE); // Mata kiri berada di tengah layar dengan rounded lebih kecil
  display.fillRoundRect(69, 0, 50, 32, 8, SSD1306_WHITE); // Mata kanan berada di tengah layar dengan rounded lebih kecil
  display.display();
}

void ekspresiMarah() {
  // Ekspresi Marah (kedua mata memenuhi layar dan berada di tengah)
  display.clearDisplay();
  display.fillRoundRect(9, 0, 50, 32, 8, SSD1306_WHITE); // Mata kiri berada di tengah dengan rounded lebih kecil
  display.fillRoundRect(69, 0, 50, 32, 8, SSD1306_WHITE); // Mata kanan berada di tengah dengan rounded lebih kecil
  display.fillTriangle(9, 0, 59, 0, 59, 16, SSD1306_BLACK); // Potongan kiri: kiri atas ke kanan bawah
  display.fillTriangle(69, 0, 69, 16, 119, 0, SSD1306_BLACK); // Potongan kanan: kanan atas ke kiri bawah
  display.display();
}

void ekspresiSedih() {
  // Ekspresi Sedih (kedua mata memenuhi layar dan berada di tengah)
  display.clearDisplay();
  display.fillRoundRect(9, 0, 50, 32, 8, SSD1306_WHITE); // Mata kiri berada di tengah dengan rounded lebih kecil
  display.fillRoundRect(69, 0, 50, 32, 8, SSD1306_WHITE); // Mata kanan berada di tengah dengan rounded lebih kecil
  display.fillTriangle(59, 0, 9, 0, 9, 16, SSD1306_BLACK); // Potongan kiri: kanan atas ke kiri bawah
  display.fillTriangle(69, 0, 119, 16, 119, 0, SSD1306_BLACK); // Potongan kanan: kiri atas ke kanan bawah
  display.display();
}

void ekspresiSenang() {
  // Ekspresi Senang (kedua mata memenuhi layar dan berada di tengah)
  display.clearDisplay();
  display.fillRoundRect(9, 0, 50, 32, 8, SSD1306_WHITE); // Mata kiri berada di tengah dengan rounded lebih kecil
  display.fillRoundRect(69, 0, 50, 32, 8, SSD1306_WHITE); // Mata kanan berada di tengah dengan rounded lebih kecil
  display.fillTriangle(59, 32, 9, 32, 9, 16, SSD1306_BLACK); // Potongan kiri: kanan bawah ke kiri atas
  display.fillTriangle(69, 32, 119, 32, 119, 16, SSD1306_BLACK); // Potongan kanan: kiri bawah ke kanan atas
  display.display();
}

void mataBerkedip() {
  // Mata Berkedip (kedua mata tertutup memenuhi layar dan berada di tengah)
  display.clearDisplay();
  display.fillRoundRect(9, 14, 50, 4, 2, SSD1306_WHITE); // Mata kiri tertutup
  display.fillRoundRect(69, 14, 50, 4, 2, SSD1306_WHITE); // Mata kanan tertutup
  display.display();
}
