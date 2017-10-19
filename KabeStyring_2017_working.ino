#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
OneWire  ds(10);  // on pin 10 (a 4.7K resistor is necessary)
//
#define RELAY_PIN 6
#define SIM808_PIN 12
#define MESSAGE_LENGTH 20
#define TEKST_LENGTH 160

char message[MESSAGE_LENGTH];
char gprsBuffer[64];
char *s = NULL;
char const phone[16] = "+4522947000";
char tekst[TEKST_LENGTH];
char datetime[24];
int messageIndex = 0;
float temp;
int lowTemp = 100;
int highTemp = -100;
long ticksSinceBoot = 0;

//
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
      if (strcmp(tekst, "Alde on") == 0) {
        digitalWrite(RELAY_PIN, LOW);
      }
      if (strcmp(tekst, "Alde off") == 0) {
        digitalWrite(RELAY_PIN, HIGH);
      }

      int onOff = (digitalRead(RELAY_PIN));
      Serial.print("\r\n                        ALDE status: ");
      if (onOff == 0) {
        strcpy(tekst, "ALDE ON");
        Serial.print(F("Varme ON"));
      } else {
        strcpy(tekst, "ALDE OFF");
        Serial.print(F("Varme OFF"));
      }
      getTempPartSMS();
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
  String now = getTime();
  //********* er det ved at være boot time ****************
  if (ticksSinceBoot > 100000) {
    restartSim();
  }
  delay(3000);

}



