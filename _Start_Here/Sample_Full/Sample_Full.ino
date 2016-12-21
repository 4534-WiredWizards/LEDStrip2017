/*
 * Wired Wizards 2017 LED example code FULL POWER!
 * by Benjamin Davis
 * 
 * This is similar to the final version of 2016's code, but designed for clarity and precision.
 * 
 * This uses many different aspects of C++ code, such as classes, enums, and switch case statements.
 * Please familiarize yourself with these concepts.
 * I have tried to comment heavily and explain what is going on, but anything not explained here can be explained by me or any of our excellent mentors.
 * 
 * The NeoPixel library is critical to this code. This can be installed following the instructions at https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation.
 * 
 */



#include <Adafruit_NeoPixel.h> //adds the neopixel library to the code. This library handles the data going to the strip.

class LedStrip:public Adafruit_NeoPixel { //A class is a group of other data and functions.
  private: 
    // private members can only be accessed by the members of the class.
  protected:
    // protected members can only be accessed by this class or other classes that inherit it.
  public: //public members are accessible by the whole code.
    LedStrip(int pixels, int pin, int options); //this function sets up the led strip accoring to the NeoPixel library.
    void solidColor(int r, int g, int b); // these are functions for animations. 
    void blink(int r, int g, int b, int wait);
    void blackout();
    void fade(int r, int g, int b, int wavelength);
    //add more fun here
};

enum class AnimationType 
{ 
  blackout,
  solidColor,
  blink, 
  fade
}; //Creates a list of our animations.
AnimationType animationID = AnimationType::solidColor; //creates animationID, which will store what animation we are running, and sets it to solidColor.

LedStrip blinky = LedStrip(153, 6, NEO_GRB + NEO_KHZ800); // creates an LedStrip named "blinky" 32 pixels long, on pin 6. The NEO_GRB + NEO_KHZ800 is magical stuff that the Neopixels library needs to operate.

int red = 48; //global color values. Passed to most animations.
int green = 0; // these values go from 0 to 255, 0 being off and 255 being full power: Full Power is Very Bright!
int blue = 64; //the colors combine to create a single, RGB color.

char incoming; // a single character. will store the information on the serial port to be processed.

void setup() {
  // put your setup code here, to run once:
  blinky.begin(); // starts the strip running.
  blinky.show(); //displays the default color, all black.
  blinky.clear();
  Serial.begin(115200); //sets up the serial port, at a baud rate of 115200.
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available() > 0) { //checks if there is anything waiting on the serial port
    incoming = Serial.read(); //reads the next thing in the serial buffer.
    switch (incoming) { 
      
      case 's': //will run if incoming = 's'
        animationID = AnimationType::solidColor;
      break; //ends the case.

      case 'o': //will run if incoming = 'o'
        animationID = AnimationType::blackout;
      break; //ends the case.

      case 'f': //will run if incoming = 'f'
        animationID = AnimationType::fade;
      break; //ends the case.

      case 'b': //will run if incoming = 'b'
        animationID = AnimationType::blink; //do not confuse with capital B, which stands for the color blue.
      break; //ends the case.

      case 'R': //will run if incoming = 'R'
        red = 64; //red alliance colors
        blue = 0;
        green = 0;
      break; //ends the case.

      case 'B': //will run if incoming = 'B'
        red = 0; //blue alliance colors
        green = 0;
        blue = 64;
      break; //ends the case.

      default: // will run if incoming matches none of the above.
        //you don't need a default, but it is here when wanted.
        break;
      
    }
  }
  
  switch (animationID){
    
    case AnimationType::blackout:
      blinky.blackout();
    break;

    case AnimationType::solidColor:
      blinky.solidColor(red, green, blue);
      break;

    case AnimationType::fade:
      blinky.fade(red, green, blue, 2000);
      break;

    case AnimationType::blink:
      blinky.blink(red, green, blue, 500);
      break;
    
    default: // will run if icoming matches none of the above.
      //you don't need a default, but it is here when wanted.
      break;
  }
  blinky.show();
}

LedStrip::LedStrip(int pixels, int pin, int options): Adafruit_NeoPixel(pixels, pin, options) //initializes the ledStrip.
{
}

void LedStrip::blackout(){ //clears all of the pixels on the strip. NOTE: the Neopixel library's strip.clear() function should do the same.
  for (int i = 0; i < this->numPixels(); i++){ //steps through each pixel on the strip
    this->setPixelColor(i, 0, 0, 0); //and clears each one.
  }
  this->show();//displays changes.
}

void LedStrip::solidColor(int r, int g, int b){
   for(int i = 0; i < this->numPixels(); i++){ //steps through each pixel on the strip
    this->setPixelColor(i, r, g, b); //and paints them in the color you told it to.
  }
  this->show(); //after all pixels have been told what to do, the strip displays the changes.
}

void LedStrip::fade(int r, int g, int b, int time){
  static unsigned long timer = millis(); // creates a variable equal to the current time in milliseconds tat will last between different callings of the function.

  float position = (millis() - timer)/(2 * time); //creates a variable equaling how far we are in the sequence, i.e. .66 means we are 66% through the animation.
  while (position >= 1) {
    position --; //decrements position so that the value is always between 1 and 0.
  }
  
  if(position < .5){
    this->solidColor(int (r * 2 * position),int (g * 2 * position),int (b * 2 * position)); // lights the strip, dimmed based on the value of position. 
  } else {
    this->solidColor(int (r * 2 *(1 - position)),int (g * 2 * (1 - position)),int (b * 2 * (1 - position))); // same as previous, but now increasing position decreases the brightness.
  }
}

void LedStrip::blink(int r, int g, int b, int wait) {
  static unsigned long timer = millis(); //creates a variable that will last between callings of the function equal to the time at the start of calling it.
  
  unsigned int f = (millis()-timer)/wait; // determines which frame of the animation we are on.
  f %= 2; //modulates f, so that the animation will reset when f >= 2
  
  if (f == 1) { //tests f. if f is equal to 1, the code in the block will run.
    this->solidColor(r,g,b); //paints the strip a solidColor based on what was passed into the function.
  } else {
    this->blackout(); //makes the lights turn off. Every light side needs a good dark side.
  }
}



