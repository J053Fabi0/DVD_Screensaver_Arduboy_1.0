/*
Buttons example
June 11, 2015
Copyright (C) 2015 David Martinez
All rights reserved.
This code is the most basic barebones code for showing how to use buttons in
Arduboy.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
*/

#include "Arduboy.h"
#include "DVD_bitmaps.h"


// Make an instance of arduboy used for many functions
Arduboy arduboy;

// Variables for your game go here.


#define WIDTH 31
#define HEIGHT 19

#define X_MAX (128 - WIDTH)
#define Y_MAX (64 - HEIGHT)

#define X_MIN (0)
#define Y_MIN (0)

byte x = (rand()%X_MAX)+1;
byte y = (rand()%Y_MAX)+1;
int speed = 1;
int state = 1;

bool sound = false;
int delai = 30;

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  //initiate arduboy instance
  arduboy.beginNoLogo();

  // here we set the framerate to 30, we do not need to run at default 60 and
  // it saves us battery life.
  arduboy.setFrameRate(60);
  

}


void playSound(){
  if(sound == true){
    arduboy.tunes.tone(250, 150);
  }
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

    switch(state){
      case(1):
         x += speed;
         y += speed;
         
         if (x >= X_MAX && y < Y_MAX) {
             state = 2;
             playSound();
         }
         else if (x < X_MAX && y >= Y_MAX) {
             state = 4;
             playSound();
         } 
         else if (x >= X_MAX && y >= Y_MAX) {
             state = 3;
             playSound();
         }
//         switch(isInverted){
//            case(true){
//              arduboy.invert(false);
//              isInverted = true;
//            }
//         }
         break;
      case(2):
         x-=speed;
         y+=speed;
         if ( y >= Y_MAX && x >= X_MIN && x <= X_MAX) {
             state = 3;
             playSound();
         }
         else if ( y < Y_MAX && x <= X_MIN) {
             state = 1;
             playSound();
         }
         else if ( y >= Y_MAX && x <= X_MIN) {
             state = 4;
             playSound();
         }
         break;
      case(3):
         x-=speed;
         y-=speed;
         if (x <= X_MIN && y > Y_MIN && y < Y_MAX) {
             state = 4;
             playSound();
         } 
         else if (x <= X_MIN && y <= Y_MIN) {
             state = 1;
             playSound();
         }
         else if (x > X_MIN && y <= Y_MIN && x < X_MAX) {
             state = 2;
             playSound();
         }
         break;
      case(4):
         x+=speed;
         y-=speed;
         if (x >= X_MAX && y <= Y_MIN) {
             state = 2;
             playSound();
         }
         else if (x >= X_MAX && y < Y_MAX && y > Y_MIN) {
             state = 3;
             playSound();
         }
         else if (x < X_MAX && x > X_MIN && y <= Y_MIN) {
             state = 1;
             playSound();
         }
         break;
      
    }


    if(arduboy.pressed(DOWN_BUTTON)  && delai <= 60){
      delai++;
    }
    if(arduboy.pressed(UP_BUTTON) && delai >= 1){
      delai--;
    }
    if(arduboy.pressed(LEFT_BUTTON)){
      delai = 30;
    }
    if(arduboy.pressed(RIGHT_BUTTON)){
      x = (rand()%X_MAX)+1;
      y = (rand()%Y_MAX)+1;
    }
    
    if(arduboy.pressed(A_BUTTON)){
      sound = false;
    }
    if(arduboy.pressed(B_BUTTON)){
      sound = true;
    }


  // we clear our screen to black
  arduboy.clear();

  delay(delai);

  // then we print to screen what is stored in our image variable we declared earlier
  arduboy.drawBitmap(x, y, dvdImage, WIDTH, HEIGHT, 1);

  // then we finaly we tell the arduboy to display what we just wrote to the display.
  arduboy.display();
}
