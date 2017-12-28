#include <SPI.h>        
#include <DMD.h>        
#include <TimerOne.h>   
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

int xPosition = 0;
int yPosition = 0;

int xPin = A4;
int yPin = A3;
int buttonPin = 1;
int pos  = 9;
int EnemyPosX = 0;
int canMove = 0;
int EnemyPosX2 = -1;
int EnemyPosX3 = -1;
int ded = 0;
int BardurPos = 0;
int buttonState = 0;
int place = 1; //позиция 1 врага
int place2 = 1; //сторона появления врага
int place3 = 9; //позиция 2 врага
  int canRand = 1; 
  float speed = 100;

  DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void ScanDMD() { 
  dmd.scanDisplayBySPI();
}

void setup(void) {
   Timer1.initialize( 1000 );          
   Timer1.attachInterrupt( ScanDMD );  
   dmd.clearScreen( true );   
   pinMode(xPin, INPUT);
   pinMode(yPin, INPUT);
   Serial.begin(9600);
   pinMode(buttonPin, INPUT);

   digitalWrite(buttonPin, HIGH);
}

void loop(void) {

  if(ded == 0){
   xPosition = analogRead(xPin);
   yPosition = analogRead(yPin);
   Logik();  
   delay(speed);
   noTone(3);
   speed = speed - 0.01;
   Serial.println(speed);
  }

}

void Logik() {
   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16);
   Draw();
   collision();
   Move();
   POS();

           
}
void BardurDraw(){
  
    dmd.drawBox(  BardurPos + 24,  15, BardurPos + 28, 15, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos + 16,  15, BardurPos + 20, 15, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos + 8,  15, BardurPos + 12, 15, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos,  15, BardurPos+4, 15, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos - 28,  15, BardurPos - 24, 15, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos - 20,  15, BardurPos - 16, 15, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos - 12,  15, BardurPos - 8, 15, GRAPHICS_NORMAL);

    dmd.drawBox(  BardurPos + 24,  0, BardurPos + 28, 0, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos + 16,  0, BardurPos + 20, 0, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos + 8,  0, BardurPos + 12, 0, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos,  0, BardurPos+4, 0, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos - 28,  0, BardurPos - 24, 0, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos - 20,  0, BardurPos - 16, 0, GRAPHICS_NORMAL);
    dmd.drawBox(  BardurPos - 12,  0, BardurPos - 8, 0, GRAPHICS_NORMAL);
   
    BardurPos++;
    
      if (BardurPos == 31){
           BardurPos = 4;
      }
    }
  void collision(){
  
    int Mx[28] = {26,27,30,31,26,27,30,31,24,25,26,27,28,29,24,25,26,27,28,29,26,27,30,31,26,27,30,31} ;
  int My[28] = {pos,pos,pos,pos,pos+1,pos+1,pos+1,pos+1,pos+2,pos+2,pos+2,pos+2,pos+2,pos+2,pos+3,pos+3,pos+3,pos+3,pos+3,pos+3,pos+4,pos+4,pos+4,pos+4,pos+5,pos+5,pos+5,pos+5} ;
  int Vx[28] = {EnemyPosX-7,EnemyPosX-6,EnemyPosX-3,EnemyPosX-2,EnemyPosX-7,EnemyPosX-6,EnemyPosX-3,EnemyPosX-2,EnemyPosX-5,EnemyPosX-4,EnemyPosX-3,EnemyPosX-2,EnemyPosX-1,EnemyPosX,EnemyPosX-5,EnemyPosX-4,EnemyPosX-3,EnemyPosX-2,EnemyPosX-1,EnemyPosX,EnemyPosX-7,EnemyPosX-6,EnemyPosX-3,EnemyPosX-2,EnemyPosX-7,EnemyPosX-6,EnemyPosX-3,EnemyPosX-2};
  int Vy[28] = {9,9,9,9,10,10,10,10,11,11,11,11,11,11,12,12,12,12,12,12,13,13,13,13,14,14,14,14};
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
       if (Mx[i] == Vx[j] && My[i] == Vy[j]) {
       tone(3, 400);
       Dead();
    }
  }
 }
  int Vx2[28] = {EnemyPosX2-7,EnemyPosX2-6,EnemyPosX2-3,EnemyPosX2-2,EnemyPosX2-7,EnemyPosX2-6,EnemyPosX2-3,EnemyPosX2-2,EnemyPosX2-5,EnemyPosX2-4,EnemyPosX2-3,EnemyPosX2-2,EnemyPosX2-1,EnemyPosX2,EnemyPosX2-5,EnemyPosX2-4,EnemyPosX2-3,EnemyPosX2-2,EnemyPosX2-1,EnemyPosX2,EnemyPosX2-7,EnemyPosX2-6,EnemyPosX2-3,EnemyPosX2-2,EnemyPosX2-7,EnemyPosX2-6,EnemyPosX2-3,EnemyPosX2-2};
  int Vy2[28] = {place,place,place,place,place+1,place+1,place+1,place+1,place+2,place+2,place+2,place+2,place+2,place+2,place+3,place+3,place+3,place+3,place+3,place+3,place+4,place+4,place+4,place+4,place+5,place+5,place+5,place+5};
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
       if (Mx[i] == Vx2[j] && My[i] == Vy2[j]) {
       tone(3, 400);
       Dead();
    }
  }
 }

  int Vx3[28] = {EnemyPosX3-7,EnemyPosX3-6,EnemyPosX3-3,EnemyPosX3-2,EnemyPosX3-7,EnemyPosX3-6,EnemyPosX3-3,EnemyPosX3-2,EnemyPosX3-5,EnemyPosX3-4,EnemyPosX3-3,EnemyPosX3-2,EnemyPosX3-1,EnemyPosX3,EnemyPosX3-5,EnemyPosX3-4,EnemyPosX3-3,EnemyPosX3-2,EnemyPosX3-1,EnemyPosX3,EnemyPosX3-7,EnemyPosX3-6,EnemyPosX3-3,EnemyPosX3-2,EnemyPosX3-7,EnemyPosX3-6,EnemyPosX3-3,EnemyPosX3-2};
  int Vy3[28] = {place3,place3,place3,place3,place3+1,place3+1,place3+1,place3+1,place3+2,place3+2,place3+2,place3+2,place3+2,place3+2,place3+3,place3+3,place3+3,place3+3,place3+3,place3+3,place3+4,place3+4,place3+4,place3+4,place3+5,place3+5,place3+5,place3+5};
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
       if (Mx[i] == Vx3[j] && My[i] == Vy3[j]) {
       tone(3, 400);
       Dead();
    }
  }
 }  

}
void Move(){
   if(pos != 9){
    if(xPosition > 900){
      pos++;
    }
 }
 
 if( pos != 1){
    if(xPosition <100){
      pos--;
    }
 }
 if(canMove == 1){
 if(place2 == 0){
            EnemyPosX2 ++;
         if(EnemyPosX2 == 40) {
             EnemyPosX2 = -1;
          canRand = 1;
          canMove = 0;
       
 }
 }else{
           EnemyPosX3 ++;
         if(EnemyPosX3 == 40) {
             EnemyPosX3 = -1;
             canRand =1;
             canMove = 0;
}
}
 }
           EnemyPosX ++;
         if(EnemyPosX == 40) {
             EnemyPosX = -1;
}


}
void Draw(){
  PlayerDraw();
  EnemyDraw();
  BardurDraw();
}
void PlayerDraw(){

     dmd.drawBox(  30,  pos +4, 31, pos +5, GRAPHICS_NORMAL);
   dmd.drawBox(  28,  pos +2, 29, pos +3, GRAPHICS_NORMAL);
   dmd.drawBox(  30,  pos, 31, pos +1, GRAPHICS_NORMAL);
   dmd.drawBox(  26,  pos, 27, pos +5, GRAPHICS_NORMAL);
   dmd.drawBox(  24,  pos +2, 25, pos +3, GRAPHICS_NORMAL);
}
void EnemyDraw(){
   dmd.drawBox(  EnemyPosX,  11, EnemyPosX-1, 12, GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX-2, 9 , EnemyPosX-3,14 , GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX-4, 11 , EnemyPosX-5,12 , GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX-6, 9 , EnemyPosX-7,10 , GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX-6, 13 , EnemyPosX-7,14 , GRAPHICS_NORMAL);
   
    if(place2 == 0){ //еслипозиция врага = 0 то...
   dmd.drawBox(  EnemyPosX2,  place+2, EnemyPosX2-1, place+3, GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX2-2, place , EnemyPosX2-3,place+5 , GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX2-4, place+2 , EnemyPosX2-5,place+3 , GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX2-6, place , EnemyPosX2-7,place+1 , GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX2-6, place+4 , EnemyPosX2-7,place+5 , GRAPHICS_NORMAL);
    

    }else{
   dmd.drawBox(  EnemyPosX3,  place3+2, EnemyPosX3-1, place3+3, GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX3-2, place3 , EnemyPosX3-3,place3+5 , GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX3-4, place3+2 , EnemyPosX3-5,place3+3 , GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX3-6, place3 , EnemyPosX3-7,place3+1 , GRAPHICS_NORMAL);
   dmd.drawBox(  EnemyPosX3-6, place3+4 , EnemyPosX3-7,place3+5 , GRAPHICS_NORMAL);

}


}
void POS(){
      if(  canRand == 1){
        if(EnemyPosX == 20){
     place2 = random(0,2);
    canRand = 0;
    canMove = 1;
    
}
      }
}

void Dead(){
  dmd.clearScreen( true );
     dmd.drawMarquee("You are dead nooooob",20,(32*DISPLAYS_ACROSS)-1,0);
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret){
     if ((timer+15) < millis()) {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }

   EnemyPosX = 0;
   canMove = 0;
   EnemyPosX2 = -20;
   EnemyPosX3 = -15;
   place2 = 0; 
   canRand = 1;
     ded = 1;
     speed = 100;
  }
  
