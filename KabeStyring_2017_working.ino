#include <DFRobot_sim808.h>

#include <SoftwareSerial.h>
#include <OneWire.h>
OneWire  ds(10);  // on pin 10

#define RELAY_PIN 6
#define SIM808_PIN 12
#define MESSAGE_LENGTH 20
#define TEKST_LENGTH 160

char const on[] = "Alde on";
char const off[] = "Alde of";

char message[MESSAGE_LENGTH];
char gprsBuffer[64];
char *s = NULL;
char phone[16];
char tekst[TEKST_LENGTH];
char datetime[24];
int messageIndex = 0;
float temp;
int lowTemp = 100;
int highTemp = -100;
long ticksSinceBoot = 0;
char const admTlfNr[] = "+4522947000";


DFRobot_SIM808 sim808(&Serial);

void setup(void) {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SIM808_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(SIM808_PIN, HIGH);
  Serial.begin(9600);

  //******** Initialize sim808 module *************
  powerOn(); //inkl. timingsloop til connect
  sendWelcomeSMS();
  //initGPS();
  delay(3000);
  cleanUp();
  delay(2000);
  String test;
}


void loop(void) {
  ticksSinceBoot++;
  temp = getTemp();
  if ((int)temp <= lowTemp) lowTemp = (int)temp;
  if ((int)temp >= highTemp) highTemp = (int)temp;


  //*********** Detecting unread SMS ************************
  messageIndex = sim808.isSMSunread();

  if (messageIndex > 0) {
    sim808.readSMS(messageIndex, tekst, TEKST_LENGTH, phone, datetime);
    delay(3000);
    sim808.deleteSMS(messageIndex);
    if (strncmp(tekst, "Alde", 4) == 0) {
      if (strcmp(tekst, off) == 0) {
        digitalWrite(RELAY_PIN, LOW);
      }
      if (strcmp(tekst, on) == 0) {
        digitalWrite(RELAY_PIN, HIGH);
      }

      int onOff = (digitalRead(RELAY_PIN));
      Serial.print(F("\r\n                        ALDE status: "));
      if (onOff == 0) {
        strcpy(tekst, on);
        Serial.print(F("Varme ON"));
      } else {
        strcpy(tekst, off);
        Serial.print(F("Varme OFF"));
      }
      getTempPartSMS();
    } else if (ticksSinceBoot > 100000) {
      //********* er det ved at være boot time ****************
      ticksSinceBoot = 0;
      restartSim();
    }


    //************ teknik kommandoer ************************
    if (strcmp(tekst, "Restart sim808") == 0) {
      restartSim();
    }
    if (strcmp(tekst, "Shutdown sim808") == 0) {
      shutdownSim();
    }
    if (strcmp(tekst, "Time") == 0) {
      getTimeSMS();
    }
  }

  //visGPS();
  delay(3000);

}



