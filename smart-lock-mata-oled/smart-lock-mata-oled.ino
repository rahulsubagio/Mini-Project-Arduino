#include <Keypad.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SERVO_PIN 18
#define BUZZER_PIN 19

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Servo lockServo;

// Konfigurasi Keypad
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {32, 33, 25, 26};  // Konektor baris keypad dimulai dari pin 32
byte colPins[COLS] = {27, 14, 12, 13};  // Konektor kolom keypad dimulai dari pin 27 hingga 13
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Password untuk membuka kunci
String password = "1234";
String inputPassword = "";

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);

  // Inisialisasi LCD OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();

  // Inisialisasi Servo
  lockServo.attach(SERVO_PIN);
  lockServo.write(0);  // Servo pada posisi terkunci

  // Inisialisasi Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  static bool isLocked = true;
  if (isLocked) {
    // Menampilkan animasi mata saat pintu terkunci
    mataBerkedip();
    delay(150);
    ekspresiMelihatKiri();
    delay(1500);
    mataBerkedip();
    delay(150);
    ekspresiDatar();
    delay(1500);
    mataBerkedip();
    delay(150);
    ekspresiMelihatKanan();
    delay(1500);
  }

  char key = keypad.getKey();

  if (key) {
    // Membunyikan buzzer setiap kali tombol ditekan
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);

    if (key == '#') {
      // Cek apakah password benar
      if (inputPassword == password) {
        unlockDoor();
        isLocked = false;
      } else {
        incorrectPassword();
      }
      inputPassword = "";  // Reset input password
    } else if (key == '*') {
      // Reset input jika ditekan tombol '*'
      inputPassword = "";
      mataBerkedip();
      delay(150);
      ekspresiSedih();
      delay(1500);
      isLocked = true;
    } else {
      // Menambahkan karakter yang ditekan ke inputPassword
      inputPassword += key;
      displayMaskedPassword();
    }
  }
}

void unlockDoor() {
  mataBerkedip();
  delay(150);
  ekspresiSenang();
  delay(1500);
  mataBerkedip();
  delay(150);
  ekspresiSenang();
  delay(1500);

  display.clearDisplay();
  display.setTextSize(2);
  int16_t x, y;
  uint16_t width, height;
  display.getTextBounds("Unlocked", 0, 0, &x, &y, &width, &height);
  display.setCursor((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2);
  display.print("Unlocked");
  display.display();
  lockServo.write(180);  // Servo membuka kunci

  // Bunyi buzzer saat password benar
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(i == 1 ? 300 : 100);  // Bunyi kedua lebih panjang
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }

  delay(3000);  // Biarkan pintu terbuka selama 3 detik
  lockServo.write(0);  // Servo kembali ke posisi terkunci
}

void incorrectPassword() {
  mataBerkedip();
  delay(150);
  ekspresiMarah();
  delay(1500);
  mataBerkedip();
  delay(150);
  ekspresiDatar();

  display.clearDisplay();
  display.setTextSize(2);
  int16_t x, y;
  uint16_t width, height;
  display.getTextBounds("Incorrect", 0, 0, &x, &y, &width, &height);
  display.setCursor((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2);
  display.print("Incorrect");
  display.display();

  // Bunyi buzzer saat password salah
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

void displayPasswordPrompt() {
  display.clearDisplay();
  display.setTextSize(2);
  int16_t x, y;
  uint16_t width, height;
  display.getTextBounds("DoorLocked", 0, 0, &x, &y, &width, &height);
  display.setCursor((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2);
  display.print("DoorLocked");
  display.display();
}

void displayMaskedPassword() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("Password: ");
  for (int i = 0; i < inputPassword.length(); i++) {
    display.print('*');
  }
  display.display();
}

void ekspresiMelihatKiri() {
  display.clearDisplay();
  display.fillRoundRect(0, 0, 50, 32, 8, SSD1306_WHITE); // Mata kiri berada di tengah layar dengan rounded lebih kecil
  display.fillRoundRect(58, 4, 45, 24, 6, SSD1306_WHITE); // Mata kanan lebih kecil dan posisinya sedikit lebih ke atas
  display.display();
}

void ekspresiMelihatKanan() {
  display.clearDisplay();
  display.fillRoundRect(24, 4, 45, 24, 6, SSD1306_WHITE); // Mata kiri lebih kecil dan posisinya sedikit lebih ke atas
  display.fillRoundRect(76, 0, 50, 32, 8, SSD1306_WHITE); // Mata kanan berada di tengah layar dengan rounded lebih kecil
  display.display();
}

void ekspresiDatar() {
  display.clearDisplay();
  display.fillRoundRect(9, 0, 50, 32, 8, SSD1306_WHITE); // Mata kiri berada di tengah layar dengan rounded lebih kecil
  display.fillRoundRect(69, 0, 50, 32, 8, SSD1306_WHITE); // Mata kanan berada di tengah layar dengan rounded lebih kecil
  display.display();
}

void ekspresiMarah() {
  display.clearDisplay();
  display.fillRoundRect(9, 0, 50, 32, 8, SSD1306_WHITE); // Mata kiri berada di tengah dengan rounded lebih kecil
  display.fillRoundRect(69, 0, 50, 32, 8, SSD1306_WHITE); // Mata kanan berada di tengah dengan rounded lebih kecil
  display.fillTriangle(9, 0, 59, 0, 59, 16, SSD1306_BLACK); // Potongan kiri: kiri atas ke kanan bawah
  display.fillTriangle(69, 0, 69, 16, 119, 0, SSD1306_BLACK); // Potongan kanan: kanan atas ke kiri bawah
  display.display();
}

void ekspresiSedih() {
  display.clearDisplay();
  display.fillRoundRect(9, 0, 50, 32, 8, SSD1306_WHITE); // Mata kiri berada di tengah dengan rounded lebih kecil
  display.fillRoundRect(69, 0, 50, 32, 8, SSD1306_WHITE); // Mata kanan berada di tengah dengan rounded lebih kecil
  display.fillTriangle(59, 0, 9, 0, 9, 16, SSD1306_BLACK); // Potongan kiri: kanan atas ke kiri bawah
  display.fillTriangle(69, 0, 119, 16, 119, 0, SSD1306_BLACK); // Potongan kanan: kiri atas ke kanan bawah
  display.display();
}

void ekspresiSenang() {
  display.clearDisplay();
  display.fillRoundRect(9, 0, 50, 32, 8, SSD1306_WHITE); // Mata kiri berada di tengah dengan rounded lebih kecil
  display.fillRoundRect(69, 0, 50, 32, 8, SSD1306_WHITE); // Mata kanan berada di tengah dengan rounded lebih kecil
  display.fillTriangle(59, 32, 9, 32, 9, 16, SSD1306_BLACK); // Potongan kiri: kanan bawah ke kiri atas
  display.fillTriangle(69, 32, 119, 32, 119, 16, SSD1306_BLACK); // Potongan kanan: kiri bawah ke kanan atas
  display.display();
}

void mataBerkedip() {
  display.clearDisplay();
  display.fillRoundRect(9, 14, 50, 4, 2, SSD1306_WHITE); // Mata kiri tertutup
  display.fillRoundRect(69, 14, 50, 4, 2, SSD1306_WHITE); // Mata kanan tertutup
  display.display();
}
