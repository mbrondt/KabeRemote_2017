float getTemp() {
  byte i;
  byte present = 0;
  //byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;

  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    //return -1;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return -1;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
  celsius = (float)raw / 16.0;
  return celsius;
}
