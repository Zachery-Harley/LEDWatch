void init_watch(){
  //Start up delay
  delay(200);

  //Set pin modes
  pinMode(NEXT_PIN, INPUT);
  pinMode(PREV_PIN, INPUT);
  pinMode(MODE_PIN, INPUT);

  //Set the LED's up
  FastLED.addLeds<WS2811, LED_PIN>(leds, NUM_LED);

  #ifdef DEBUG
  Serial.begin(9600);
  #endif


  
}

