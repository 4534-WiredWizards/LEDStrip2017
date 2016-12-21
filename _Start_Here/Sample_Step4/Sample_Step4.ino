/*
   Wired Wizards 2017 LED example code level 4: Classes!
   by Benjamin Davis

   This version is intended to be the fifth step into the Arduino/NeoPixel environment.

   Why:
   Each strip needs to handle its own animations. Classes give each strip their own copy of each function. Classes are not found in Regular C, so now we are getting into C++ territory.

   The NeoPixel library is critical to this code. This can be installed following the instructions at https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation.

*/



#include <Adafruit_NeoPixel.h> //adds the neopixel library to the code. This library handles the data going to the strip.

class LedStrip: public Adafruit_NeoPixel { //A class is a group of other data and functions. Adafruit_NeoPixel is already a class, we are extending the class (hence the :public Adafruit_NeoPixel) to include animations.
  private:
    // private members can only be accessed by the members of the class.
  protected:
    // protected members can only be accessed by this class or other classes that inherit it.
  public: //public members are accessible by the whole code.
    LedStrip (int pixels, int pin, int options); //this function sets up the led strip accoring to the NeoPixel library.
    void solidColor (int r, int g, int b); // these are functions for animations.
    void blink (int r, int g, int b, int wait); //Notice how the prototype is part of the class. It is not optional anymore.
    void carnival (int r, int g, int b, int wait, int period); // the more animations the merrier, right? (Even though this one isn't defined yet.)
}; // this semicolon belongs here.


LedStrip blinky = LedStrip(32, 6, NEO_GRB + NEO_KHZ800); // creates an LedStrip named "blinky" 32 pixels long, on pin 6. The NEO_GRB + NEO_KHZ800 is magical stuff that the Neopixels library needs to operate.

int red = 48; //these values determine the color being used.
int green = 0; // these values go from 0 to 255, 0 being off and 255 being full power: Full Power is Very Bright!
int blue = 64; //the colors combine to create a single, RGB color.
char incoming; // a single character. will store the information on the serial port to be processed.

void setup() {
  // put your setup code here, to run once:
  blinky.begin(); // starts the strip running.
  blinky.show(); //displays the default color, all black.
  Serial.begin(115200); //sets up serial communications, at 115200 bits/second.
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) { //checks if there is anything waiting on the serial port, keeps repeating until clear.
    incoming = Serial.read(); //reads the next thing in the serial buffer.
    switch (incoming) { // switches are a good way to handle many different cases based on the value of a variable. in this case, we wnat to do different things based on what data we received on the serial port.
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

      // we can add more cases for other things, like changing animations.

      default: // will run if incoming matches none of the above.
        //you don't need a default, but it is here when wanted.
        break;
    }
  }

  blinky.blink (red, green, blue, 1000); //because blink() is a member of the LedStrip class, and blinky is an LedStrip, blinky.blink() makes blinky blink. 
  
  blinky.show();
}

LedStrip::LedStrip(int pixels, int pin, int options): Adafruit_NeoPixel(pixels, pin, options) //initializes the ledStrip.
{ // this function sets up the LedStrip to be an Adafruit_Neopixel. It uses the same input, but now we can also use the functions in the LedStrip class we made.
}

void LedStrip::blink (int r, int g, int b, int wait)
{
  static unsigned long startTime = millis(); //gets the current processor time, in milliseconds, and makes it static, meaning the value will stay not reset every time we call the function.
  int frame = (millis() - startTime) / wait; //Calculates which frame of the animation we are on by taking the time elapsed and dividing by how long each frame should be.
  frame %= 2; //evaluates the remainder of frame / 2, then saves that value to frame. This means that odd numbers will return 1, and even numbers will return 0.
  if (frame == 0) { // the "==" means is egual to, and is used as a comparison. A single "=" would set the value of frame to 0. Not what you want!
    for (int i = 0; i < blinky.numPixels(); i++) { //starts at pixel 0, then adds one until you reach the end of the strip.
      this->setPixelColor(i, r, g, b); // the this-> means that whichever LedStrip calls this function will be animated.
    }
  } else { // if (frame != 0). this runs if the above condition is not satisfied. Becuase frame will either be equal to
    this->solidColor(0, 0, 0); // because we have a solidColor function, we call on that instead of writing out the code.
  }
}

void LedStrip::solidColor(int r, int g, int b)
{
   for(int i = 0; i < this->numPixels(); i++){ //steps through each pixel on the strip
    this->setPixelColor(i, r, g, b); //and paints them in the color you told it to.
  }
}
