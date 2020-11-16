void callback_mqtt_anzled(char* topic, byte* payload, unsigned int length) {
  DebugPrintln("CallbackAnzahl LEDs");


  float lv_numpix = payload_to_float( payload, length);
  fire.NUMFirePIXELS = lv_numpix;

  gv_mqtt_pup_stat = true;
}

void init_mqtt_local() {

  mqtt_pubtopic_status_s += gv_clientname;
  mqtt_pubtopic_status_s += '/';
  mqtt_pubtopic_status_s += mqtt_pubtopic_status_suff;
  mqtt_pubtopic_status = (char*) mqtt_pubtopic_status_s.c_str();
  DebugPrintln(mqtt_pubtopic_status);


  mqtt_subtopic_anzled_s += gv_clientname;
  mqtt_subtopic_anzled_s += '/';
  mqtt_subtopic_anzled_s += mqtt_subtopic_anzled_suff;
  mqtt_subtopic_anzled = (char*) mqtt_subtopic_anzled_s.c_str();
  DebugPrintln(mqtt_subtopic_anzled);


  //init_mqtt(callback_mqtt);
  init_mqtt(gv_clientname);

  add_subtopic(mqtt_subtopic_anzled, callback_mqtt_anzled);

  gv_mqtt_pup_stat = true;
}


void pub_stat() {

  char buffer[256];
  //dtostrf(fire.NUMFirePIXELS, 0, 0, buffer);

  // Allocate the JSON document
  //
  // Inside the brackets, 200 is the RAM allocated to this document.
  // Don't forget to change this value to match your requirement.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<200> jsondoc;

  // StaticJsonObject allocates memory on the stack, it can be
  // replaced by DynamicJsonDocument which allocates in the heap.
  //
  // DynamicJsonDocument  doc(200);

  // Add values in the document
  //
  jsondoc["anzled"] = fire.NUMFirePIXELS;
  int n  = serializeJson(jsondoc, buffer);

  client.publish(mqtt_pubtopic_status, buffer, true);

}

void check_mqtt_local() {

  if (gv_mqtt_pup_stat == true && gv_mqtt_conn_ok == true) {
    pub_stat();
    gv_mqtt_pup_stat = false;
  }

  check_mqtt();

}

float payload_to_float( byte* payload, unsigned int length) {
  float lv_float = 0;
  float lv_fact = 0;
  float lv_sign = 1;

  for (int i = 0; i < length; i++) {
    DebugPrint((char)payload[i]);
  }
  DebugPrintln("");

  for (int i = 0; i < length; i++) {

    switch (payload[i]) {
      case 45: //"-"
        lv_sign = -1;
        break;

      case 46: // "."
        lv_fact = 1;
        break;

      default:
        lv_float = (lv_float * 10) + payload[i] - 48;
        lv_fact = lv_fact * 10;
        break;
    }

  }

  if (lv_fact > 0) {
    lv_float = lv_float / lv_fact;
  }

  lv_float = lv_float * lv_sign;

  DebugPrintln(lv_float);

  return lv_float;
}
