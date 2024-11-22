// Libraries yang diperlukan
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Mengganti library Ultrasonic.h dengan logika manual menggunakan pulseIn
#define TRIGGER_PIN_1 10
#define ECHO_PIN_1 11
#define TRIGGER_PIN_2 8
#define ECHO_PIN_2 9

// Konfigurasi komponen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define BUZZER_PIN 3
#define OLED_RESET 4

// Inisialisasi objek

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variabel untuk menghitung orang
int count = 0;
int distanceIn = 0;
int distanceOut = 0;

long getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

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
  pinMode(TRIGGER_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);

  // Mulai komunikasi serial
  Serial.begin(9600);
}

void loop() {
  kembali:
  delay(1000);
  distanceIn = getDistance(TRIGGER_PIN_1, ECHO_PIN_1);
  distanceOut = getDistance(TRIGGER_PIN_2, ECHO_PIN_2);

  Serial.print("Ping1: ");
  Serial.print(distanceIn);
  Serial.println("cm");
  Serial.print("Ping2: ");
  Serial.print(distanceOut);
  Serial.println("cm");
  Serial.println(count);

  // Logika untuk mendeteksi orang masuk
  if (distanceIn < 7 && distanceOut > 7 && distanceIn != 0) {
    do {
      distanceIn = getDistance(TRIGGER_PIN_1, ECHO_PIN_1);
      distanceOut = getDistance(TRIGGER_PIN_2, ECHO_PIN_2);
      Serial.print("Ping(+)1: ");
      Serial.print(distanceIn);
      Serial.println("cm");
      Serial.print("Ping(+)2: ");
      Serial.print(distanceOut);
      Serial.println("cm");
      Serial.println(count);
      delay(500);

      if (distanceOut < 7 && distanceIn >= 7 && distanceOut != 0) {
        count++;
        tone(BUZZER_PIN, 1000, 200); // Bunyikan buzzer saat orang masuk
        updateDisplay();
        Serial.print("Jumlah orang (masuk): ");
        Serial.println(count);
        goto kembali;
      }
    } while (distanceOut > 7);
  }

  // Logika untuk mendeteksi orang keluar
  else if (distanceOut < 7 && distanceIn > 7 && distanceOut != 0) {
    do {
      distanceIn = getDistance(TRIGGER_PIN_1, ECHO_PIN_1);
      distanceOut = getDistance(TRIGGER_PIN_2, ECHO_PIN_2);
      Serial.print("Ping(-)1: ");
      Serial.print(distanceIn);
      Serial.println("cm");
      Serial.print("Ping(-)2: ");
      Serial.print(distanceOut);
      Serial.println("cm");
      Serial.println(count);
      delay(500);

      if (distanceIn < 7 && distanceOut >= 7 && distanceIn != 0) {
        count--;
        tone(BUZZER_PIN, 800, 200); // Bunyikan buzzer saat orang keluar
        updateDisplay();
        Serial.print("Jumlah orang (keluar): ");
        Serial.println(count);
        goto kembali;
      }
    } while (distanceIn > 7);
  }

  // Update tampilan LCD
  updateDisplay();
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
