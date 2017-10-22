
void initGPS() {
//  ************* Turn on the GPS power************
  if ( sim808.attachGPS())
    Serial.println(F("Open the GPS power success"));
  else
    Serial.println(F("Open the GPS power failure"));


}

void visGPS() {
  //************** Get GPS data *******************
  if (sim808.getGPS()) {
    Serial.print(sim808.GPSdata.year);
    Serial.print("/");
    Serial.print(sim808.GPSdata.month);
    Serial.print("/");
    Serial.print(sim808.GPSdata.day);
    Serial.print(" ");
    Serial.print(sim808.GPSdata.hour);
    Serial.print(":");
    Serial.print(sim808.GPSdata.minute);
    Serial.print(":");
    Serial.print(sim808.GPSdata.second);
    Serial.print(":");
    Serial.println(sim808.GPSdata.centisecond);
    Serial.print(F("latitude :"));
    Serial.println(sim808.GPSdata.lat);
    Serial.print(F("longitude :"));
    Serial.println(sim808.GPSdata.lon);
    Serial.print(F("speed_kph :"));
    Serial.println(sim808.GPSdata.speed_kph);
    Serial.print(("heading :"));
    Serial.println(sim808.GPSdata.heading);
    Serial.println();

    //************* Turn off the GPS power ************
    sim808.detachGPS();
  }
}
