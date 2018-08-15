////////////////////////////////////////////

//Set an led color
void setLed(int led, int hue, int sat, int val) {
  leds[led] = CHSV(hue, sat, val);
}

void setLed(int col, int row, int hue, int sat, int val) {
  setLed(col + (row * 10), hue, sat, val);
}

//Get an led from a given postion
CRGB getLed(int col, int row){
  return leds[col + (row * 10)];
}

void setLed(int col, int row, CRGB led){
  leds[col + (row * 10)] = led;
}

void setColumn(int col, int hue, int sat, int val) {
  setLed(col, 0, hue, sat, val);
  setLed(col, 1, hue, sat, val);
  setLed(col, 2, hue, sat, val);
}

void setRow(int row, int from, int too, int hue, int sat, int val) {
  do{
    if(from != -1){
      setLed(from, row, hue, sat, val);
    }
    from++;
  } while(from <= too);
}

void setRow(int row, int hue, int sat, int val) {
  setRow(row, 0, LED_COLS-1, hue, sat, val);
}

void animateRow(int row, int current, int new_count, int update_time, int hue, int sat, int val) {
  while (current <= new_count) {
    for (int i = (LED_COLS-1); i > current; i--) {
      setRow(row, 0, 0, 0);
      setLed(i, row, hue, sat, val);
      setRow(row, -1, current, hue, sat, val);
      FastLED.show();
      delay(update_time);
    }
    current++;
  }
}

void shiftRow(int row, bool continueous){
  CRGB overflowLed;
  for(int i = 0; i < LED_COLS; i++){
    if(i == 0) overflowLed = getLed(i, row);
    else {
      setLed(i-1, row, getLed(i, row));
    }
  }
  if(continueous){
    setLed(LED_COLS -1, row, overflowLed);
  } else {
    setLed(LED_COLS -1, row, 0, 0, 0);
  }
}

void clearAll(){
  for(int i = 0; i < LED_ROWS; i++){
    setRow(i, 0, 0, 0);
  }
}

void showPlay(){
  clearAll();
  setLed(5,1,180,255,brightness);
  setLed(4,1,180,255,brightness);
  setLed(5,0,180,255,brightness);
  setLed(5,2,180,255,brightness);
}

void showStop(){
  clearAll();
  setLed(5,1,180,255,brightness);
  setLed(5,0,180,255,brightness);
  setLed(5,2,180,255,brightness);
  setLed(6,1,180,255,brightness);
  setLed(6,0,180,255,brightness);
  setLed(6,2,180,255,brightness);
  setLed(4,1,180,255,brightness);
  setLed(4,0,180,255,brightness);
  setLed(4,2,180,255,brightness);
}

void showTorch(){
  clearAll();
  setLed(5,1,180,255,brightness);
  setLed(4,1,180,255,brightness);
  setLed(6,1,180,255,brightness);
  setLed(4,0,180,255,brightness);
  setLed(4,2,180,255,brightness);
}

void torch(uint8_t level){
  clearAll();
  setColumn(4, 1, 0, 255);
  setColumn(5, 1, 0, 255);
  if(level > 1){
    setColumn(3, 1, 0, 255);
    setColumn(6, 1, 0, 255);
  }
  if(level > 2){
    setColumn(2, 1, 0, 255);
    setColumn(7, 1, 0, 255);
  }
  if(level > 3){
    setColumn(1, 1, 0, 255);
    setColumn(8, 1, 0, 255);
  }
  if(level > 4){
    setColumn(0, 1, 0, 255);
    setColumn(9, 1, 0, 255);
  }
}

