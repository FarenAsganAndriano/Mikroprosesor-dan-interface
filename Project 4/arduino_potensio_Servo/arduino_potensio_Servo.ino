#include <Servo.h>  // Library Servo

int potPin = A0;  // Potensiometer terhubung ke pin analog A0
int potValue = 0; // Variabel untuk menyimpan nilai dari potensiometer
int servoPin = 9; // Pin digital 9 untuk sinyal servo

Servo myServo;    // Buat objek Servo

void setup() {
  // Inisialisasi servo
  myServo.attach(servoPin);  
}

void loop() {
  // Baca nilai dari potensiometer (0 hingga 1023)
  potValue = analogRead(potPin);
  
  // Konversi nilai potensiometer (0-1023) menjadi sudut servo (0-180 derajat)
  int angle = map(potValue, 0, 1023, 0, 180);
  
  // Gerakkan servo ke sudut yang dikonversi
  myServo.write(angle);
  
  // Tambahkan sedikit jeda
  delay(15);  // 15 ms delay untuk stabilitas gerakan servo
}