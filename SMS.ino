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
  Serial.print("\r\n                        Temp i vogn: ");
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
  strcpy(tekst, "\r\nSystem tid: ");
  char tid[10] = "bum";
  getTime().toCharArray(tid, 6);
//  strcat(tekst, tid);
  char const lTekst[] = "\r\nTicks since boot ";
  strcat(tekst, lTekst);
  char ticks[7];
  itoa(ticksSinceBoot, ticks, 6);
  strcat(tekst, ticks);
  Serial.print(tekst);
  Serial.println(ticks);
  delay(3000);
  sim808.sendSMS(phone, tekst);

}

