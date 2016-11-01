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

// Make an instance of arduboy used for many functions
Arduboy arduboy;

// Variables for your game go here.
const unsigned char image[] PROGMEM = {
  0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
  0xfc, 0xfc, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
  0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
  0xfc, 0xfc, 0x3f, 0x3f, 0x30, 0xb0, 0x30, 0x30, 
  0x30, 0xb0, 0x0f, 0x8f, 0x80, 0x80, 0x03, 0x83, 
  0x8c, 0x8c, 0xb0, 0x30, 0x0c, 0x8c, 0x83, 0x83, 
  0x80, 0x80, 0x3f, 0x3f, 0xb0, 0xb0, 0xb0, 0x30, 
  0x30, 0x30, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0f, 
  0x10, 0x20, 0x10, 0x0f, 0x00, 0x20, 0x3f, 0x20, 
  0x00, 0x3f, 0x20, 0x20, 0x20, 0x1f, 0x00, 0x3f, 
  0x24, 0x24, 0x24, 0x20, 0x00, 0x1f, 0x20, 0x20, 
  0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 
};
byte x;
byte y;
int speed = 1;
int state = 1;

// Width of each charcter including inter-character space
#define WIDTH 34
#define HEIGHT 22

#define X_MAX (128 - WIDTH - 1)
#define Y_MAX (64 - HEIGHT - 1)

#define X_MIN (0)
#define Y_MIN (0)

bool isInverted = false;

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  //initiate arduboy instance
  arduboy.beginNoLogo();

  // here we set the framerate to 30, we do not need to run at default 60 and
  // it saves us battery life.
  arduboy.setFrameRate(60);
  
  // set x and y to the middle of the screen
  x = (64 - (WIDTH/2));
  y = (32 - (HEIGHT / 2));
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
         }
         else if (x < X_MAX && y >= Y_MAX) {
             state = 4;
         } 
         else if (x >= X_MAX && y >= Y_MAX) {
             state = 3;
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
         }
         else if ( y < Y_MAX && x <= X_MIN) {
             state = 1;
         }
         else if ( y >= Y_MAX && x <= X_MIN) {
             state = 4;
         }
         break;
      case(3):
         x-=speed;
         y-=speed;
         if (x <= X_MIN && y > Y_MIN && y < Y_MAX) {
             state = 4;
         } 
         else if (x <= X_MIN && y <= Y_MIN) {
             state = 1;
         }
         else if (x > X_MIN && y <= Y_MIN && x < X_MAX) {
             state = 2;
         }
         break;
      case(4):
         x+=speed;
         y-=speed;
         if (x >= X_MAX && y <= Y_MIN) {
             state = 2;
         }
         else if (x >= X_MAX && y < Y_MAX && y > Y_MIN) {
             state = 3;
         }
         else if (x < X_MAX && x > X_MIN && y <= Y_MIN) {
             state = 1;
         }
         break;
      
    }

    if (arduboy.pressed(A_BUTTON)) {
        arduboy.invert(true);
    } else if (arduboy.pressed(B_BUTTON)) {
        arduboy.invert(false);
    }


  // we clear our screen to black
  arduboy.clear();

  // then we print to screen what is stored in our image variable we declared earlier
  arduboy.drawBitmap(x, y, image, WIDTH, HEIGHT, 1);

  // then we finaly we tell the arduboy to display what we just wrote to the display.
  arduboy.display();
}
