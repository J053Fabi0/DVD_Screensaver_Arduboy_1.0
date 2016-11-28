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
  
  #include <Arduboy.h>
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
  int volumeImage = 1; //1 = off   2 = on
  
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
  
  void moveDVD(){
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
  }
  
  void buttons(){
      if(arduboy.pressed(DOWN_BUTTON)  && delai <= 60){ //60÷5 == 12
        delai++;
        drawVolume(delai);
      }
      
      if(arduboy.pressed(UP_BUTTON) && delai >= 1){
        delai--;
        drawVolume(delai);
      }
      
      if(arduboy.pressed(LEFT_BUTTON)){
        delai = 30;
        drawVolume(delai);
      }
      
      if(arduboy.pressed(RIGHT_BUTTON)){
        x = (rand()%X_MAX)+1;
        y = (rand()%Y_MAX)+1;
        state = (rand()%4)+1;
        
        while(arduboy.pressed(RIGHT_BUTTON)){}
        
        if(sound == true){
          arduboy.tunes.tone(440, 40);
        }
      }
      
      if(arduboy.pressed(A_BUTTON)){
        sound = false;
        volumeImage = 1;
      }
      if(arduboy.pressed(B_BUTTON)){
        sound = true;
        volumeImage = 2;
      }
  }

  void drawVolume(int delai){ //0 - 10 - 20 - 30 - 40 - 50 - 60
    if(delai <= 10){
      arduboy.drawBitmap(82, 0, speedMark, 11, 15, 1);
      arduboy.drawBitmap(95, 5, oneHundredP, 29, 6, 1);
    }else if(delai >= 11 && delai <= 20){
      arduboy.drawBitmap(82, 0, speedMark, 11, 15, 1);
      arduboy.drawBitmap(95, 5, eightyP, 29, 6, 1);
    }else if(delai >= 21 && delai <= 30){
      arduboy.drawBitmap(82, 0, speedMark, 11, 15, 1);
      arduboy.drawBitmap(95, 5, sixtyP, 29, 6, 1);
    }else if(delai >= 31 && delai <= 40){
      arduboy.drawBitmap(82, 0, speedMark, 11, 15, 1);
      arduboy.drawBitmap(95, 5, fortyP, 29, 6, 1);
    }else if(delai >= 41 && delai <= 50){
      arduboy.drawBitmap(82, 0, speedMark, 11, 15, 1);
      arduboy.drawBitmap(95, 5, twentyP, 29, 6, 1);
    }else if(delai >= 51){
      arduboy.drawBitmap(82, 0, speedMark, 11, 15, 1);
      arduboy.drawBitmap(95, 5, oneP, 29, 6, 1);
    }
  }
  
  void drawImage(int image, int volume){
    if(image == 1){
      arduboy.drawBitmap(x, y, dvdImage, WIDTH, HEIGHT, 1);
    }else if(image == 2){
      arduboy.drawBitmap(120/2 - 32/2 +4, 64/2 - 40/2, youWin, 32, 40, 1);
    }
  
    if(volumeImage == 1){
      arduboy.drawBitmap(0, 0, volumeOff, 11, 11, 1);
    }else if(volumeImage == 2){
      arduboy.drawBitmap(0, 0, volumeOn, 11, 11, 1);
    }
    
  }
  
  
  void loop() {
    if (!(arduboy.nextFrame()))
      return;
  
    arduboy.clear();

    buttons();
  
    delay(delai); //delai is the time it´ll wait until the next frame, is used to slow the dvd
      
    if(y >= 47){
      drawImage(2, volumeImage);
    }else{
      moveDVD();
      drawImage(1, volumeImage);
    }

    arduboy.display();
  }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
