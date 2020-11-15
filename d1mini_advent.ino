/*
  Room Fountain control
*/
#include <cy_serdebug.h>
#include <cy_serial.h>

#include "cy_wifi.h"
#include "cy_ota.h"


//#define PIN_BUTTON 13
//#define PIN_RELAY 4
#define PIN_LED 2 //"BUILTIN_LED
//#define PIN_INPUT 12
//#define PIN_WS2812 12

//#define relStateOFF LOW
//#define relStateON HIGH
//#define LEDStateOFF HIGH
//#define LEDStateON LOW
//#define butStateOFF HIGH
//#define butStateON LOW
//#define inpStateLow LOW // Low Water state
//int relayState = relStateOFF;

const char *gc_hostname = "D1mAdvent";

//for LED status
#include <Ticker.h>
Ticker ticker;
Ticker WS2812_ticker;



void tick()
{
  int state = digitalRead(PIN_LED);  // get the current state of GPIO1 pin
  digitalWrite(PIN_LED, !state);     // set pin to the opposite state
}



void restart() {
  ESP.reset();
  delay(1000);
}

void reset() {
  //reset settings to defaults
  /*
    WMSettings defaults;
    settings = defaults;
    EEPROM.begin(512);
    EEPROM.put(0, settings);
    EEPROM.end();
  */
  //reset wifi credentials
  WiFi.disconnect();
  delay(1000);
  ESP.reset();
  delay(1000);
}

