void sendWelcomeSMS() {
  strcpy(tekst, "Sim808 started up");
  int onOff = (digitalRead(RELAY_PIN));
  if (onOff == 0) {
    strcat(tekst, "\r\nALDE ON");
  } else {
    strcat(tekst, "\r\nALDE OFF");
  }
  strcat(tekst, "\r\nTemp i vogn: ");
  char temperatur[10];
  //Her er getTemp() fordi vi ikke er nået ned i loop()
  dtostrf(getTemp(), 3, 2, temperatur);
  strcat(tekst, temperatur);
  //indtil prod  sim808.sendSMS(phone, tekst);

}

void getTempPartSMS() {
  Serial.print(F("\r\n                        Temp i vogn: "));
  Serial.println(temp, 2);

  strcat(tekst, "\r\nTemp i vogn: ");
  char temperatur[10];
  dtostrf(temp, 3, 2, temperatur);
  strcat(tekst, temperatur);

  strcat(tekst, "\r\nMin temp: ");
  dtostrf(lowTemp, 3, 0, temperatur);
  strcat(tekst, temperatur);

  strcat(tekst, "\r\nMax temp: ");
  dtostrf(highTemp, 3, 0, temperatur);
  strcat(tekst, temperatur);

  Serial.println(tekst);
  Serial.println(phone);
  delay(3000);
  sim808.sendSMS(phone, tekst);

}

void getTimeSMS() {
  String tid = "\r\nSystem tid: ";
  tid += getTime();
  tid += "\r\nTicks since boot ";
  tid += ticksSinceBoot;
  Serial.println(tid);
  char text[160];
  tid.toCharArray(text, tid.length());
  delay(3000);
  sim808.sendSMS(phone, text);

}

