#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Ganti 0x3F ke 0x27 kalau LCD tidak muncul

#define SS_PIN 10
#define RST_PIN 9
#define LM35 A0          // Pin untuk sensor suhu LM35
#define RED 7            // LED merah
#define GREEN 6          // LED hijau (Anda bisa menambahkan ini ke hardware)
int powerPin = 3;        // Pin power
int sda = A4;
int scl = A5;            // untuk pengganti VCC/5vOLT

float lm_value;          // Variabel untuk membaca nilai dari LM35
float tempc;             // Variabel untuk menyimpan suhu dalam derajat Celsius

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Membuat instance untuk MFRC522

void setup() {
  pinMode(RED, OUTPUT);   // Set LED merah sebagai output
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);     // Memulai komunikasi serial
  SPI.begin();            // Memulai SPI bus
  mfrc522.PCD_Init();     // Memulai MFRC522
  
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  
}

void loop() {
  readTemperature();      // Memanggil fungsi untuk membaca suhu dari LM35
  
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
   readTemperature();      // Memanggil fungsi untuk membaca suhu dari LM35
  
  // Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "05 8F 6E 1A 0D F2 00") {  // UID kartu yang diizinkan
    Serial.println("Allow");
    digitalWrite(7, HIGH);
    delay(3000);
    digitalWrite(7, LOW);
  } else {
    Serial.println("Deny");
    blinkLED(7);           // Memanggil fungsi untuk memberi sinyal deny
  }
}

// Fungsi untuk membaca suhu dari LM35 dan mengatur kondisi LED
void readTemperature() {
  lm_value = analogRead(LM35);     // Membaca nilai analog dari LM35
  tempc = (lm_value * 500.0) / 1023.0;  // Menghitung suhu dalam Celsius

  Serial.print("Temperature: ");
  Serial.println(tempc);           // Menampilkan suhu di serial monitor

  // Menampilkan suhu pada LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempc);
  lcd.print((char)223);            // Menampilkan simbol derajat (°)
  lcd.print("C");

  // Kondisi berdasarkan suhu
  if (tempc > 35) {
    digitalWrite(RED, HIGH);      // Nyalakan LED merah jika suhu > 35°C
    digitalWrite(GREEN, LOW);     // Matikan LED hijau
  } else {
    digitalWrite(GREEN, HIGH);    // Nyalakan LED hijau jika suhu <= 35°C
    digitalWrite(RED, LOW);       // Matikan LED merah
  }

  delay(3000);                     // Delay untuk pembacaan selanjutnya
}

// Fungsi untuk memberi sinyal deny dengan berkedip
void blinkLED(int pin) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(pin, HIGH);
    delay(200);
    digitalWrite(pin, LOW);
    delay(200);
  }
}
