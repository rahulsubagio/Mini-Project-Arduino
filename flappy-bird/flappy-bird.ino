#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON_PIN A0

int birdY = SCREEN_HEIGHT / 2;
int birdVelocity = 0;
int gravity = 1;
int jump = -4; // Kurangi tinggi lompatan burung

int obstacleX = SCREEN_WIDTH;
int obstacleWidth = 10;
int obstacleGap = 20;
int score = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Tombol dengan internal pull-up
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
}

void loop() {
  // Tombol untuk naik
  if (digitalRead(BUTTON_PIN) == LOW) {
    birdVelocity = jump;
  }

  // Gerakan burung
  birdVelocity += gravity;
  birdY += birdVelocity;

  // Batas atas dan bawah burung
  if (birdY < 0) birdY = 0;
  if (birdY > SCREEN_HEIGHT - 5) birdY = SCREEN_HEIGHT - 5;

  // Gerakan rintangan
  obstacleX -= 2;
  if (obstacleX < 0) {
    obstacleX = SCREEN_WIDTH;
    obstacleGap = random(15, 40);
    score++;
  }

  // Pembersihan layar
  display.clearDisplay();

  // Gambar burung
  display.fillRect(15, birdY, 5, 5, SSD1306_WHITE);

  // Gambar rintangan
  display.fillRect(obstacleX, 0, obstacleWidth, obstacleGap, SSD1306_WHITE); // Rintangan atas
  display.fillRect(obstacleX, obstacleGap + 20, obstacleWidth, SCREEN_HEIGHT, SSD1306_WHITE); // Rintangan bawah

  // Cek tabrakan
  if ((10 + 5 > obstacleX && 10 < obstacleX + obstacleWidth) && 
      (birdY < obstacleGap || birdY + 5 > obstacleGap + 20)) {
    gameOver();
  }

  // Tampilkan skor
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("Score: ");
  display.print(score);

  display.display();
  delay(50);
}

void gameOver() {
  display.clearDisplay();
  // Menampilkan "Game Over!"
  display.setTextSize(1);
  display.setCursor(35, 10);
  display.print("Game Over!");

  // Menampilkan skor akhir
  display.setCursor(30, 30);
  display.print("Score: ");
  display.print(score);

  // Instruksi untuk restart
  display.setCursor(20, 50);
  display.print("Press Button");
  display.display();

  // Tunggu hingga tombol ditekan untuk restart
  while (digitalRead(BUTTON_PIN) == HIGH) {
    // Tunggu sampai tombol ditekan (LOW = ditekan)
    delay(10); // Hindari pembacaan terlalu cepat
  }

  // Reset variabel game
  birdY = SCREEN_HEIGHT / 2;
  birdVelocity = 0;
  obstacleX = SCREEN_WIDTH;
  score = 0;
  delay(200); // Tambah sedikit penundaan untuk menghindari bouncing tombol
}
