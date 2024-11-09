#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIG_PIN A0
#define ECHO_PIN A1

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  long duration, distance;
  
  // Mengukur jarak
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // Menampilkan ekspresi dan jarak berdasarkan jarak yang terdeteksi
  if (distance < 5) {
    ekspresiSenang(distance);
  } else if (distance < 10) {
    ekspresiDatar(distance);
  } else if (distance < 15) {
    ekspresiSedih(distance);
  } else {
    ekspresiMarah(distance);
  }
  delay(1500); // Beri jeda sebelum berkedip
  mataBerkedip(distance);
  delay(100);
}

void mataBerkedip(long distance) {
  display.clearDisplay();
  display.fillRoundRect(20, 38, 40, 4, 2, SSD1306_WHITE); // Mata kiri tertutup
  display.fillRoundRect(70, 38, 40, 4, 2, SSD1306_WHITE); // Mata kanan tertutup
  tampilkanJarak(distance);
  display.display();
}

void ekspresiDatar(long distance) {
  display.clearDisplay();
  display.fillRoundRect(20, 20, 40, 40, 8, SSD1306_WHITE); // Mata kiri
  display.fillRoundRect(70, 20, 40, 40, 8, SSD1306_WHITE); // Mata kanan
  tampilkanJarak(distance);
  display.display();
}

void ekspresiSenang(long distance) {
  display.clearDisplay();
  display.fillRoundRect(20, 20, 40, 40, 8, SSD1306_WHITE); // Mata kiri penuh
  display.fillRoundRect(70, 20, 40, 40, 8, SSD1306_WHITE); // Mata kanan penuh
  display.fillTriangle(60, 60, 20, 60, 20, 40, SSD1306_BLACK); // Potongan kiri: kanan bawah ke kiri atas
  display.fillTriangle(70, 60, 110, 60, 110, 40, SSD1306_BLACK); // Potongan kanan: kiri bawah ke kanan atas
  tampilkanJarak(distance);
  display.display();
}

void ekspresiSedih(long distance) {
  display.clearDisplay();
  display.fillRoundRect(20, 20, 40, 40, 8, SSD1306_WHITE); // Mata kiri penuh
  display.fillRoundRect(70, 20, 40, 40, 8, SSD1306_WHITE); // Mata kanan penuh
  display.fillTriangle(60, 20, 20, 20, 20, 40, SSD1306_BLACK); // Potongan kiri: kanan atas ke kiri bawah
  display.fillTriangle(70, 20, 110, 40, 110, 20, SSD1306_BLACK); // Potongan kanan: kiri atas ke kanan bawah
  tampilkanJarak(distance);
  display.display();
}

void ekspresiMarah(long distance) {
  display.clearDisplay();
  display.fillRoundRect(20, 20, 40, 40, 8, SSD1306_WHITE); // Mata kiri penuh
  display.fillRoundRect(70, 20, 40, 40, 8, SSD1306_WHITE); // Mata kanan penuh
  display.fillTriangle(20, 20, 60, 20, 60, 40, SSD1306_BLACK); // Potongan kiri: kiri atas ke kanan bawah
  display.fillTriangle(70, 20, 70, 40, 110, 20, SSD1306_BLACK); // Potongan kanan: kanan atas ke kiri bawah
  tampilkanJarak(distance);
  display.display();
}

void tampilkanJarak(long distance) {
  display.setCursor(43, 0); // Menampilkan jarak di bagian atas layar
  display.print(distance);
  display.print("cm");
}
