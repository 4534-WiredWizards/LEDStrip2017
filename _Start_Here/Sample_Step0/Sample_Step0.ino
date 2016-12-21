/*
 * Wired Wizards 2017 LED example code level 0: Blink! 
 * by Benjamin Davis
 * 
 * This version is intended to be the first step into the Arduino/NeoPixel environment.
 * 
 * 
 * The NeoPixel library is critical to this code. This can be installed following the instructions at https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation.
 * 
 */



#include <Adafruit_NeoPixel.h> //adds the neopixel library to the code. This library handles the data going to the strip.

Adafruit_NeoPixel blinky = Adafruit_NeoPixel(32, 6, NEO_GRB + NEO_KHZ800); // creates an LedStrip named "blinky" 32 pixels long, on pin 6. The NEO_GRB + NEO_KHZ800 is magical stuff that the Neopixels library needs to operate.

int red = 48; //these values determine the color being used.
int green = 0; // these values go from 0 to 255, 0 being off and 255 being full power: Full Power is Very Bright!
int blue = 64; //the colors combine to create a single, RGB color.

void setup() {
  // put your setup code here, to run once:
  blinky.begin(); // starts the strip running.
  blinky.show(); //displays the default color, all black.
}

void loop() {
  // put your main code here, to run repeatedly:

  /*
   * how to use a "for" loop:
   * 
   * for(type name = startingValue; name <comparator> endValue; name <operator> changeValue)
   * {
   *  commands;
   * } 
   */
  for(int i = 0; i < blinky.numPixels(); i++){ //starts at pixel 0, then adds one until you reach the end of the strip.
    blinky.setPixelColor(i, red, green, blue); //paints pixel "i" according the the color values (the last three parameters in setPixelColor).
  }
  blinky.show(); //displays the changes.
  delay(1000); //waits 1000 milliseconds.
  for(int i = 0; i < blinky.numPixels(); i++){ //steps through each pixel
    blinky.setPixelColor(i, 0, 0, 0); //and sets them to off (black).
  }
  blinky.show();
  delay(1000); //waits a second.
  
}


