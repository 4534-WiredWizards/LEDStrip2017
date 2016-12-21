/*
 * Wired Wizards 2017 LED example code level 1: Subroutines! 
 * by Benjamin Davis
 * 
 * This version is intended to be the second step into the Arduino/NeoPixel environment.
 * 
 * Why:
 * When you have multiple animations to switch between, formatting each one as a subroutine makes your code much cleaner.
 * 
 * The NeoPixel library is critical to this code. This can be installed following the instructions at https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation.
 * 
 */



#include <Adafruit_NeoPixel.h> //adds the neopixel library to the code. This library handles the data going to the strip.

void blink (int r, int g, int b, int wait); //this is called a prototype, it tells the code that somewhere else there is a function called "blink" that needs 4 integers. Arduino does not require these, but standard C++ code does.

Adafruit_NeoPixel blinky = Adafruit_NeoPixel(32, 6, NEO_GRB + NEO_KHZ800); // creates an Adafruit_NeoPixel named "blinky" 32 pixels long, on pin 6. The NEO_GRB + NEO_KHZ800 is magical stuff that the Neopixels library needs to operate.

int red = 48; //these values determine the color being used.
int green = 0; // these values go from 0 to 255, 0 being off and 255 being full power: Full Power is Very Bright!
int blue = 64; //the colors combine to create a single, RGB color.
int delayTime = 1000; //how long, in milliseconds, each frame of the animation will last.

void setup() {
  // put your setup code here, to run once:
  blinky.begin(); // starts the strip running.
  blinky.show(); //displays the default color, all black.
}

void loop() {
  // put your main code here, to run repeatedly:
  blink (red, green, blue, delayTime); //blinks the led once on and off.
  blink ((255 - red), (255 - green), (255 - blue), delayTime); //blinks in the opposite color.
  
}

void blink(int r, int g, int b, int wait)
{
  for(int i = 0; i < blinky.numPixels(); i++){ //starts at pixel 0, then adds one until you reach the end of the strip.
    blinky.setPixelColor(i, r, g, b); //paints pixel "i" according the the color values (the last three parameters in setPixelColor).
  }
  blinky.show();
  delay(wait); //waits based on the value of wait milliseconds.
  for(int i = 0; i < blinky.numPixels(); i++){ //steps through each pixel
    blinky.setPixelColor(i, 0, 0, 0); //and sets them to off (black).
  }
  blinky.show();
  delay(wait); //waits again.
}

