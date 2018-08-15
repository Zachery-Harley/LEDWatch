

void mode1(){//MENU
    if(currentSelection == 0){
      showTorch();
    }

    if(currentSelection == 1){
      showPlay();
    }

    if(currentSelection == 2){
      showStop();
    }
}

void select(){
  if(mode == 1){
    if(currentSelection == 0){
      openTorch();
    }

    if(currentSelection == 1){
      openTour();
    }

    if(currentSelection == 2){
      closeTour();
    }
  }
}

void openTorch(){
  #ifdef DEBUG
  Serial.println("Selected Torch");
  #endif 
  mode = 2;
}

void openTour(){
  #ifdef DEBUG
  Serial.println("Selected Tour");
  #endif 
}

void closeTour(){
  #ifdef DEBUG
  Serial.println("Selected Close Tour");
  #endif 
}

