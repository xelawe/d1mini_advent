// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Fill the dots one after the other with a color
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void colorWipe(uint32_t c, unsigned long wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    if (wait != 0) {
      strip.show();
      delay(wait);
    }
  }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void do_WS2812_newcol(  ) {
  fader_pos = 0;
  fire.Draw();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void fireshow() {

  fader_pos++;
  //Serial.print("Fader: ");
  //Serial.println(fader_pos );
  for (int i = 0; i < NUMPIXELS; i++)
  {
    strip.setPixelColor(i, fire.Fade(strip.getPixelColor(i), fire.fire_colors[i], fader_pos, i) );
  }

  strip.show();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void do_WS2812_step(  ) {


  if (gv_ws2812 == 0 ) {
    gv_ws2812 = 1;

    // colorWipe(strip.Color(255, 80, 0), 50);
    colorWipe(fire_color, 50);
  }
  fireshow();


  return;

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void do_WS2812_col_test( ) {
  colorWipe(strip.Color(255, 0, 0), 500); // Red
  delay(500);
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  delay(500);
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  delay(500);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void init_ws2812( ) {
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'

  do_WS2812_col_test( );

  do_WS2812_newcol( );

  gv_rainbow_state = 0;
  gv_ws2812 = 0; //1;

  do_WS2812_step(  );
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void do_WS2812_tick() {

  if (fader_pos >= fader_steps ) {
    do_WS2812_newcol();
  }

  do_WS2812_step(  );

  //Serial.println();
}
