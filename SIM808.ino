void powerOn() {
  Serial.println("\r\nTaender sim ");
  digitalWrite(SIM808_PIN, HIGH);
  delay(1000);
  digitalWrite(SIM808_PIN, LOW);
  Serial.println("Sim808 on");
  while (!sim808.init()) {
    Serial.print(F("Initialize Sim808, waiting \r\n"));
    delay(1000);
  }
  Serial.println(F("Sim808 initialized, ready to receive SMS messages"));
}

void powerOff() {
  Serial.println(F("\r\nSlukker sim"));

  digitalWrite(SIM808_PIN, HIGH);
  delay(3000);
  digitalWrite(SIM808_PIN, LOW);
  Serial.println("Sim808 off");
  delay(5000);
}

void restartSim() {

  powerOff();
  Serial.println(F("Pause 20000"));
  for (int i = 0; i < 20; i++) {
    delay(2000);
    Serial.print(".");
  }
  powerOn();
  strcpy(tekst, "Sim808 re-started");
  int onOff = (digitalRead(RELAY_PIN));
  if (onOff == 0) {
    strcat(tekst, "\r\nAlde ON");
  } else {
    strcat(tekst, "\r\nAlde OFF");
  }
  getTempPartSMS(phone);
}

void shutdownSim() {
  //Virker som designet
  char const test[] = "Sim808 & Arduino will be dead";
  //strcpy(tekst, test);
  boolean rc = sim808.sendSMS(phone, test);
  delay(1000);
  powerOff();
  Serial.print(F("Sim808 shut down, end of life rc="));
  Serial.println(rc);
  do {} while (1);

}

String getTime() {
  String test;
  sim808.getDateTime(tekst); //Snyd med besked feltet fra SMS'en
  test = tekst;
  Serial.println(test);
  int komma = test.indexOf(',');
  String hour = test.substring(komma + 1, komma +3);
  int iHour = hour.toInt() + 14; //convert til tidszone
  hour = String(iHour);
  String minute = test.substring(komma + 4, komma + 6);
  int iMin = minute.toInt() + 12; //Den mærkelige tid fra GSM
  minute = String(iMin);
  test = hour + ":" + minute;
  Serial.print("Kl: ");
  Serial.println(test);
  return test;
}

void cleanUp() {
  //********* housekeeping? *************************//
  if (sim808.readable()) {
    sim808_read_buffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
    //Serial.print(gprsBuffer);

    //************** Detect the current state of the telephone or SMS ************************
    if (NULL != strstr(gprsBuffer, "RING")) {
      sim808.answer();
    } else if (NULL != (s = strstr(gprsBuffer, "+CMTI: \"SM\""))) { //SMS: $$+CMTI: "SM",24$$
      char message[MESSAGE_LENGTH];
      int messageIndex = atoi(s + 12);
      sim808.readSMS(messageIndex, message, MESSAGE_LENGTH);
      Serial.print("Recv Message: ");
      Serial.println(message);
    }
    sim808_clean_buffer(gprsBuffer, 32);
  }

}

