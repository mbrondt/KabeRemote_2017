String getTime() {
  String test;
  sim808.getDateTime(tekst); //Snyd med besked feltet fra SMS'en
  test = tekst;
  Serial.println(test);
  int komma = test.indexOf(',');
  String hour = test.substring(komma + 1, komma +3);
  int iHour = hour.toInt() + 15; //convert til tidszone
  hour = String(iHour);
  String minute = test.substring(komma + 4, komma + 6);
  test = hour + ":" + minute;
  Serial.print(F("Kl: "));
  Serial.println(test);
  return test;
}
