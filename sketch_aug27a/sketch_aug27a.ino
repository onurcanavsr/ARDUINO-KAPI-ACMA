#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "buzzr.h"

const int trigPin = 7;
const int echoPin = 6;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD adresine dikkat edin

int IN1 = 11;  // Motor sürücüye bağlanan pinleri tanımlıyoruz
int IN2 = 10;
int IN3 = 9;
int IN4 = 8;

int tamtur = 512;  // 28BYJ-48 motoru tam turunu 2048 adımda tamamlıyor
long duration = pulseIn(echoPin, HIGH);
int distance = duration * 0.034 / 2;
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Mesafe:");
  pinMode(IN1, OUTPUT);  // Pinleri çıkış olarak ayarlıyoruz
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  lcd.setCursor(8, 1);
  lcd.print("   ");  // Eski mesafeyi temizle
  lcd.setCursor(8, 1);
  lcd.print(distance);
  lcd.print(" cm");

  /*  Serial.print("Mesafe: ");
  Serial.print(distance);
  Serial.println(" cm");
  */
  if (distance < 20) {
    cal();
    sag(2);
        cal();
    delay(5000);
        cal();
    sol(2);
        cal();
  }

  delay(1000);
}
void sag(int bekle) {  // Sağa dönüş fonksiyonu
  int i = 0;
  while (i < tamtur / 4) {
    gonder(1, 0, 0, 1);  // Pinleri sola dönüşün tam tersine ayarlıyoruz
    delay(bekle);
    gonder(0, 0, 0, 1);
    delay(bekle);
    gonder(0, 0, 1, 1);
    delay(bekle);
    gonder(0, 0, 1, 0);
    delay(bekle);
    gonder(0, 1, 1, 0);
    delay(bekle);
    gonder(0, 1, 0, 0);
    delay(bekle);
    gonder(1, 1, 0, 0);
    delay(bekle);
    gonder(1, 0, 0, 0);
    delay(bekle);
    i++;
    lcd.setCursor(0, 0);
    lcd.print("   ");  // Eski mesafeyi temizle
    lcd.setCursor(0, 0);
    lcd.print("kapi aciliyor");
  }
}
void sol(int bekle) {  // Sola dönüş fonksiyonu
  int i = 0;
  while (i < tamtur / 4) {
    gonder(1, 0, 0, 0);  // Pinleri belirli bir sırayla ayarlıyoruz
    delay(bekle);
    gonder(1, 1, 0, 0);
    delay(bekle);
    gonder(0, 1, 0, 0);
    delay(bekle);
    gonder(0, 1, 1, 0);
    delay(bekle);
    gonder(0, 0, 1, 0);
    delay(bekle);
    gonder(0, 0, 1, 1);
    delay(bekle);
    gonder(0, 0, 0, 1);
    delay(bekle);
    gonder(1, 0, 0, 1);
    delay(bekle);
    i++;
    lcd.setCursor(0, 0);
    lcd.print("   ");  // Eski mesafeyi temizle
    lcd.setCursor(0, 0);
    lcd.print("kapi kapaliyor");
    lcd.setCursor(0, 0);
    lcd.print("                ");  // Eski mesafeyi temizle
    lcd.setCursor(0, 0);
    lcd.print("mesafe :");
    lcd.print(distance);
  }
}
void gonder(int a, int b, int c, int d) {  // Ayarlanan pin değerleri tek seferde gönderiliyor
  digitalWrite(IN1, a);
  digitalWrite(IN2, b);
  digitalWrite(IN3, c);
  digitalWrite(IN4, d);
}
