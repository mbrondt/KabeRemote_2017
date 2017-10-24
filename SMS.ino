void sendWelcomeSMS() {
  String text = "\r\nSim808 started up";
  int onOff = (digitalRead(RELAY_PIN));
  if (onOff == 0) {
    text += "\r\nAlde ON\r\n";
  } else {
    text += "\r\nAlde OFF\r\n";
  }
  //text += "\r\nTemp i vogn: ";
  //Her er getTemp() fordi vi ikke er nået ned i loop()
  //text += getTemp();
  text.toCharArray(tekst, text.length() + 1);
  Serial.print(tekst);
  //indtil prod  sim808.sendSMS(phone, tekst);

}
//MAngler resten !!!
void synchTimeSMS() {
  strcpy(phone, "+45????");
  strcpy(tekst, "Init time");
  sim808.sendSMS(phone, tekst);

  while (sim808.isSMSunread() == 0) {
    Serial.print(F("Venter på initSMS \r\n"));
    delay(1000);
  }

  sim808.readSMS(messageIndex, tekst, TEKST_LENGTH, phone, datetime);
  Serial.print("\r\n");
  Serial.print(datetime);
  delay(3000);
  sim808.deleteSMS(messageIndex);


}
void getTempPartSMS(char* phone) {
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
  String timeText = "\r\nGSM net tid: ";
  timeText += getTime();
  timeText += "\r\nTicks since boot ";
  timeText += ticksSinceBoot;
  Serial.println(timeText);
  delay(3000);
  char cTimeText[160];
  timeText.toCharArray(cTimeText, timeText.length()+1);
  sim808.sendSMS(phone, cTimeText);

}

