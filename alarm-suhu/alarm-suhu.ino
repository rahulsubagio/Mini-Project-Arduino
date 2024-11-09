#include <DHT.h>

#define DHTPIN 2        // Pin data untuk sensor DHT21
#define DHTTYPE DHT21   // Tipe sensor DHT21
#define BUZZER_PIN 9    // Pin untuk buzzer

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);   // Mengaktifkan Serial Monitor dengan baud rate 9600
  dht.begin();          // Inisialisasi sensor DHT21
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Membaca suhu dari sensor
  float t = dht.readTemperature(); // Membaca suhu dalam Celsius

  // Periksa apakah pembacaan dari sensor berhasil
  if (isnan(t)) {
    Serial.println("Gagal membaca data dari sensor DHT22!");
    return;
  }

  // Menampilkan data suhu dan kelembapan di Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.println("*C");

  // Logika untuk mengaktifkan buzzer jika suhu melebihi ambang batas
  if (t > 30) {    // Sesuaikan batas sesuai kebutuhan
    digitalWrite(BUZZER_PIN, HIGH);  // Nyalakan buzzer
    Serial.println("Peringatan! Suhu Melebihi Batas!");
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);   // Matikan buzzer
  } else {
    digitalWrite(BUZZER_PIN, LOW);   // Matikan buzzer
  }

  delay(500); // Baca setiap 2 detik
}
