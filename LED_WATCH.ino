#include <FastLED.h>

#define LED_PIN 7
#define NEXT_PIN 2
#define PREV_PIN 3
#define MODE_PIN 4

#define NUM_LED 30
#define BRIGHTNESS 100
#define UPDATE_SPEED 20
#define LED_ROWS 3
#define LED_COLS 10
#define CHAMBER_COUNT = 9;//Not including 8

#define DEBUG

////// Button states \\\\\\\\\/
boolean NEXT_LAST_STATE = LOW;
boolean PREV_LAST_STATE = LOW;
boolean MODE_LAST_STATE = LOW;
uint16_t NEXT_HOLD_TIME = 0;
uint16_t PREV_HOLD_TIME = 0;
uint16_t MODE_HOLD_TIME = 0;

///Main Menu 
uint8_t currentSelection = 0;

//Touch settings
uint8_t torch_intensity = 0;


CRGB leds[NUM_LED];
uint8_t brightness = 101;
uint8_t targetBrightness = 100;
uint8_t brightnessTimeStep = 5;
uint8_t brightnessAge = 0;

uint8_t currentChamber = 0;

uint8_t mode = 0;


void setup() {
  init_watch();  

  
  
  /*animateRow(0,-1,LED_COLS,10,155,200,100); 
  //animateRow(1,-1,LED_COLS,10,60,200,100);
  //animateRow(2,-1,LED_COLS,10,0,200,100);

  for(int i = 0; i < NUM_LED; i++){
    shiftRow(0, false);
    shiftRow(1, false);
    shiftRow(2, false);
    FastLED.show();
    delay(100);
  }*/
}

void loop() {
  static uint8_t hue = 0;
  uint8_t deltaTime = 0;
  while(true){
    unsigned long startTime = millis();
    
    updateBrightness(deltaTime);
    if(mode == 0){
      //Standard chamber clock startup
      //loadChamberLine();
      //loadChamberTimerLine();
      //loadTourTimerLine();
      mode = 1;
    }

    if(mode == 1) mode1();
    if(mode == 2) torch(torch_intensity);

    buttonCheck(deltaTime);
    
    hue++;
    delay(5);
    FastLED.show();
    deltaTime = millis() - startTime;
  }
}


//////////////////////////////////////////////

void updateBrightness(int deltaTime){
  brightnessAge += deltaTime;
  while(brightnessAge >= brightnessTimeStep){
    if(targetBrightness > brightness) brightness++;
    if(targetBrightness < brightness) brightness--;
    FastLED.setBrightness(brightness);
    brightnessAge -= brightnessTimeStep;
  }
}

void loadChamberLine(){
  animateRow(0, -1, LED_COLS, 10, 70, 200, 255);
}

void loadChamberTimerLine(){
  animateRow(1, -1, LED_COLS, 10, 155, 255, 255);
}

void loadTourTimerLine(){
  animateRow(2, -1, LED_COLS, 10, 0, 200, 255);
}

//Check the state of the buttons and react accordingly
void buttonCheck(uint8_t delta_time){
  if(digitalRead(NEXT_PIN) == HIGH){
    if(NEXT_LAST_STATE == LOW){
      buttonNext(false, delta_time);
    }
  }
  if(digitalRead(PREV_PIN) == HIGH){
    if(PREV_LAST_STATE == LOW){
      buttonPrev(false, delta_time);
    }
  }
  if(digitalRead(MODE_PIN) == HIGH){
    if(MODE_LAST_STATE == LOW){
      buttonMode(false, delta_time);
    }
  }

  MODE_LAST_STATE = digitalRead(MODE_PIN);
  PREV_LAST_STATE = digitalRead(PREV_PIN);
  NEXT_LAST_STATE = digitalRead(NEXT_PIN);
}

void buttonNext(boolean held, uint8_t delta_time){
  #ifdef DEBUG
  Serial.println("Button Next");
  #endif

  //MENU CONTROLES:
  if(mode == 1){
    currentSelection += 1;
    currentSelection = currentSelection % 3;
  }

  if(mode == 2){
    torch_intensity += 1;
    torch_intensity = torch_intensity % 6;
  }

}

void buttonPrev(boolean held, uint8_t delta_time){
  #ifdef DEBUG
  Serial.println("Button Prev");
  #endif

  if(mode == 1){
    currentSelection -= 1;
    if(currentSelection > 2) currentSelection = 2;
  }

  if(mode == 2){
    torch_intensity -= 1;
    if(torch_intensity > 5) torch_intensity = 5;
  }
}

void buttonMode(boolean held, uint8_t delta_time){
  #ifdef DEBUG
  Serial.println("Button Mode");
  #endif

  if(mode == 1){
    select();
  }

}


