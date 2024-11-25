#define BLYNK_TEMPLATE_ID "TMPL6nzmazT8K"
#define BLYNK_TEMPLATE_NAME "robot obstacle avoiding"
#define BLYNK_AUTH_TOKEN "Sp3NTEmZ3SI3PMR_WBFz8ZCnM8MH3Di0" 

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NewPing.h>
#include <Servo.h>

// Blynk credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Loading..."; // Nama Wifi
char pass[] = "terserahlu"; // Password Wifi

// Motor pins
#define IN1 D2
#define IN2 D3
#define IN3 D5
#define IN4 D6
#define ENA D1
#define ENB D0

// Ultrasonic sensor pins
#define TRIG_PIN D7
#define ECHO_PIN D8
#define MAX_DISTANCE 200

// Servo pin
#define SERVO_PIN D4

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;

// Variables for motor speed
int speed = 800; // Default speed (PWM value 0-1023)

bool manualMode = false;
bool forwardButton = false;
bool backwardButton = false;
bool leftButton = false;
bool rightButton = false;

BLYNK_WRITE(V0) {
  manualMode = param.asInt();
}

BLYNK_WRITE(V1) {
  forwardButton = param.asInt();
}
  
BLYNK_WRITE(V2) {
  backwardButton = param.asInt();
}
  
BLYNK_WRITE(V3) {
  leftButton = param.asInt();
}

BLYNK_WRITE(V4) {
  rightButton = param.asInt();
}

void manual() {
  if (forwardButton) {
    forward();
  } else if (backwardButton) {
    backward();
  } else if (leftButton) {
    right();
  } else if (rightButton) {
    left();
  } else if (!forwardButton && !backwardButton && !leftButton && !rightButton) {
    stopMotor();
  }
}

void setup() {
  // Setup motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Setup servo
  myservo.attach(SERVO_PIN); // Attach servo to pin D4
  myservo.write(85); // Center position
  
  // Setup Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  if (manualMode) {
    obstacleAvoidingMode();
  } else {
    manual();
  }
}

void forward() {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotor() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void obstacleAvoidingMode() {
  myservo.write(85); // Center position
  delay(500);
  unsigned int distance = sonar.ping_cm();

  if (distance > 0 && distance < 30) {
    stopMotor();
    delay(1000);
    backward();
    delay(250);
    stopMotor();

    myservo.write(0); // Look left
    delay(500);
    unsigned int distanceLeft = sonar.ping_cm();

    myservo.write(180); // Look right
    delay(1000);
    unsigned int distanceRight = sonar.ping_cm();

    myservo.write(85); // Center position
    delay(500);

    if (distanceLeft > distanceRight) {
      left();
      delay(200);
    } else {
      right();
      delay(200);
    }
  } else {
    forward();
  }
}