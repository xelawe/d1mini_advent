#include "cy_mqtt_v1.h"
#include <ArduinoJson.h>

const char* mqtt_pubtopic_status_suff = "tele/status";
String mqtt_pubtopic_status_s;
const char* mqtt_pubtopic_status;

const char* mqtt_pubtopic_anzled_suff = "tele/anzled";
String mqtt_pubtopic_anzled_s;
const char* mqtt_pubtopic_anzled;

const char* mqtt_subtopic_anzled_suff = "cmnd/anzled";
String mqtt_subtopic_anzled_s;
const char* mqtt_subtopic_anzled;

boolean gv_mqtt_pup_stat;
