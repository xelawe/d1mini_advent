void setup() {

  cy_serial::start(__FILE__);

  pinMode(PIN_LED, OUTPUT);  // initialize onboard LED as output
  digitalWrite(PIN_LED, 0);   // turn off LED with voltage LOW


  // start ticker with 0.5 because we start in AP mode and try to connect
  ticker.attach(0.2, tick);
  delay(500);
  
  wifi_init(gc_hostname);

  init_ota(gv_clientname);

  // init_time();

  ticker.detach();
  digitalWrite(PIN_LED, HIGH);

  init_ws2812( );

  init_mqtt_local();


  WS2812_ticker.attach_ms(20, do_WS2812_tick);

  DebugPrintln("done setup");
}

void loop() {

  check_ota();

  check_mqtt_local();

  //check_time();

  delay( 50 );

}
