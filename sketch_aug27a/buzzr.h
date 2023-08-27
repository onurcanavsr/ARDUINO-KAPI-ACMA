const int buzzerPin = 2;

void buzzr1() {
  pinMode(buzzerPin, OUTPUT);
}

void cal() {
  // Buzzer'ı 500 Hz frekansta 1 saniye çal
  tone(buzzerPin, 3000);  // Frekansı ayarlayın
  delay(1000);           // Süreyi ayarlayın
  noTone(buzzerPin);     // Buzzer'ı kapat
  delay(10);           // Bekleme süresi
}
