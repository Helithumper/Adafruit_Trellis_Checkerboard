#include <Wire.h>
#include "Adafruit_Trellis.h"

Adafruit_Trellis matrix0 = Adafruit_Trellis();



Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);


#define NUMTRELLIS 1

#define numKeys (NUMTRELLIS * 16)


#define INTPIN A2


int board[4][4]= {
  {0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}};

int checkerBoard[4][4]={
  {1,0,1,0},
  {0,1,0,1},
  {1,0,1,0},
  {0,1,0,1}
};

void setup() {
  Serial.begin(9600);
  Serial.println("Trellis Demo");

  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  
  trellis.begin(0x70); 

  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
}


void loop() {
  delay(30); // 30ms delay is required, dont remove me!
  checker();
}

void pulse(){
  int top  = 255;
  for(int i = 0; i < numKeys; i++){
    
    trellis.setLED(i);
    trellis.setBrightness(top);
    top=top-12;
    trellis.writeDisplay();
  }
  delay(50);
  trellis.clear();
  trellis.writeDisplay();
  trellis.setBrightness(255);
}

void checker(){
  for(int i = 0; i < 4; i ++){
    for(int j = 0; j < 4; j++){
      if(checkerBoard[i][j]==1){
        trellis.setLED(board[i][j]);
      }
    }
  }
  trellis.writeDisplay();
  delay(200);
  clearDisplay();
  for(int i = 0; i < 4; i ++){
    for(int j = 0; j < 4; j++){
      if(checkerBoard[i][j]==0){
        trellis.setLED(board[i][j]);
      }
    }
  }
  trellis.writeDisplay();
  delay(200);
  clearDisplay();
}

void clearDisplay(){
  for(int i = 0; i < 16; i++){
    trellis.clrLED(i);
    trellis.writeDisplay();
  }
}

