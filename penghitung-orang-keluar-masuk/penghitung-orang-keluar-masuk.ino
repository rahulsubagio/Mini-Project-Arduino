// Libraries yang diperlukan
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Ultrasonic.h>

// Konfigurasi komponen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define TRIGGER_PIN_1 7
#define ECHO_PIN_1 6
#define TRIGGER_PIN_2 8
#define ECHO_PIN_2 9
#define BUZZER_PIN 3
#define OLED_RESET 4

// Inisialisasi objek
Ultrasonic ultrasonicIn(TRIGGER_PIN_1, ECHO_PIN_1);
Ultrasonic ultrasonicOut(TRIGGER_PIN_2, ECHO_PIN_2);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variabel untuk menghitung orang
int count = 0;
int distanceIn = 0;
int distanceOut = 0;
boolean sensorInTriggered = false;
boolean sensorOutTriggered = false;

void setup() {
  // Konfigurasi LCD OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Menggunakan alamat I2C 0x3C
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("People Counter");
  display.display();

  // Konfigurasi Buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  // Mulai komunikasi serial
  Serial.begin(9600);
}

void loop() {
  // Membaca jarak menggunakan sensor ultrasonik untuk masuk dan keluar
  distanceIn = ultrasonicIn.read();
  distanceOut = ultrasonicOut.read();

  // Logika untuk mendeteksi orang masuk (sensor pertama lalu sensor kedua)
  if (distanceIn < 7 && !sensorInTriggered && !sensorOutTriggered) {
    sensorInTriggered = true;
  }
  
  if (sensorInTriggered && distanceOut < 7) {
    personEntered();
  }

  // Logika untuk mendeteksi orang keluar (sensor kedua lalu sensor pertama)
  if (distanceOut < 7 && !sensorOutTriggered && !sensorInTriggered) {
    sensorOutTriggered = true;
  }
  
  if (sensorOutTriggered && distanceIn < 7) {
    personExited();
  }

  // Reset trigger jika tidak ada objek
  if (distanceIn >= 7) {
    sensorInTriggered = false;
  }
  if (distanceOut >= 7) {
    sensorOutTriggered = false;
  }

  delay(200); // Tambahkan delay untuk stabilitas sensor
}

void updateDisplay() {
  // Update tampilan LCD
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("People Counter");
  display.setCursor(0, 10);
  display.print("Count: ");
  display.print(count);
  display.display();
}

void personEntered() {
  count++;
  sensorInTriggered = false;
  tone(BUZZER_PIN, 1000, 200); // Bunyikan buzzer saat orang masuk
  
  updateDisplay();

  // Cetak jumlah orang di serial monitor
  Serial.print("Jumlah orang (masuk): ");
  Serial.println(count);
}

void personExited() {
  count--;
  sensorOutTriggered = false;
  tone(BUZZER_PIN, 800, 200); // Bunyikan buzzer dengan nada berbeda saat orang keluar
  
  updateDisplay();

  // Cetak jumlah orang di serial monitor
  Serial.print("Jumlah orang (keluar): ");
  Serial.println(count);
}
