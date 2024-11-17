#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define BUZZER_PIN A2
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int count = 0;
bool personDetected = false;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pin modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Penghitung Orang");
  display.display();
  delay(2000);
}

void loop() {
  long duration, distance;

  // Send a 10us pulse to trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pin
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.034) / 2;

  // Check if someone is in range (less than 10 cm)
  if (distance < 7) {
    if (!personDetected) {
      count++;
      personDetected = true;

      // Update display
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 10);
      display.print("Jumlah : ");
      display.print(count);
      display.display();

      // Buzzer notification
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      delay(100);
    }
  } else {
    personDetected = false;
  }

  // Small delay to avoid too frequent checks
  delay(100);
}
