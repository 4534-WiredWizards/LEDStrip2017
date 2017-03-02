// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------





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
#include "NewPing.h" //This through Newping setup is for ultrasonic sensors

#define TRIGGER_RIGHT_PIN  10   // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_RIGHT_PIN     9  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_LEFT_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_LEFT_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200    // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define WIDTH 14          // The distance between the two sensors.

NewPing sonar(TRIGGER_RIGHT_PIN, ECHO_RIGHT_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_LEFT_PIN, ECHO_LEFT_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


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
    void fade(int r, int g, int b, int wait);
    void alternatingFade(int r,int g,int b, int wait, int wavelength);
    void wave (int r, int g, int b, int wait, int quantity, int magnitude);
    void bounce(int r, int g, int b, int wait);
    void carnival(int r,int g,int b, int wait);
    void ripple(int r, int g, int b, byte magnitude, byte wait);
    void groupScroll(int r, int g, int b, int wait, int numGroups, int groupSize);
    void stillRainbow(byte brightness);
    void rainbowFade(byte maxBrightness, int wait);
    void rainbowCycle(byte brightness, int wait);
    void rainbowGroupScroll(byte brightness, int wait, int numGroups, int groupSize);
    void rainbowAlternatingFade(byte maxBrightness, int wait, int wavelength);
    //add more fun here
};

enum class AnimationType 
{ 
  blackout,
  solidColor,
  blink, 
  fade,
  alternatingFade,
  wave,
  bounce,
  carnival,
  ripple,
  groupScroll,
  stillRainbow,
  rainbowFade,
  rainbowCycle,
  rainbowGroupScroll,
  rainbowAlternatingFade
}; //Creates a list of our animations.
AnimationType animationID = AnimationType::rainbowGroupScroll; //creates animationID, which will store what animation we are running, and sets it to solidColor.


LedStrip inky = LedStrip(92, 3, NEO_GRB + NEO_KHZ800); // climber front.
LedStrip blinky = LedStrip(83, 4, NEO_GRB + NEO_KHZ800); // shooter front.
LedStrip pinky = LedStrip(41, 5, NEO_GRB + NEO_KHZ800); // climber back.
LedStrip clyde = LedStrip(40, 6, NEO_GRB + NEO_KHZ800); // shooter back.

int red = 126; //global color values. Passed to most animations.
int green = 42; // these values go from 0 to 255, 0 being off and 255 being full power: Full Power is Very Bright!
int blue = 0; //the colors combine to create a single, RGB color.
unsigned long startTime = 0;

char incoming; // a single character. will store the information on the serial port to be processed.
float sonarLeft;
float sonarRight;


void setup() {
  // put your setup code here, to run once:
  blinky.begin(); // starts the strip running.
  blinky.show(); //displays the default color, all black.
  blinky.clear();
  inky.begin(); // starts the strip running.
  inky.show(); //displays the default color, all black.
  inky.clear();
  pinky.begin(); // starts the strip running.
  pinky.show(); //displays the default color, all black.
  pinky.clear();
  clyde.begin(); // starts the strip running.
  clyde.show(); //displays the default color, all black.
  clyde.clear();
  Serial.begin(115200); //sets up the serial port, at a baud rate of 115200.
  randomSeed(analogRead(A0));
  startTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) { //checks if there is anything waiting on the serial port
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

      case 'a': //will run if incoming = 'a'
        animationID = AnimationType::alternatingFade; //do not confuse with capital B, which stands for the color blue.
      break; //ends the case.

      case 'c': //will run if incoming = 'c'
        animationID = AnimationType::carnival; //do not confuse with capital B, which stands for the color blue.
      break; //ends the case.

      case 'r': //will run if incoming = 'r'
        animationID = AnimationType::ripple; //do not confuse with capital B, which stands for the color blue.
      break; //ends the case.

      case 'w': //will run if incoming = 'w'
        animationID = AnimationType::wave; //do not confuse with capital B, which stands for the color blue.
      break; //ends the case.

      case 'n': //will run if incoming = 'n'
        animationID = AnimationType::bounce; //do not confuse with capital B, which stands for the color blue.
      break; //ends the case.

      case 'g': 
        animationID = AnimationType::groupScroll;
      break;

      case 'R': //will run if incoming = 'R'
        red = 255; //red alliance colors
        blue = 0;
        green = 0;
      break; //ends the case.

      case 'B': //will run if incoming = 'B'
        red = 0; //blue alliance colors
        green = 0;
        blue = 255;
      break; //ends the case.

      case 'Y':
        red = 126;
        green = 84;
        blue = 0;
        break;

      case 'G':
        red = 0;
        green = 255;
        blue = 0;
        break;

      case 'O':
        red = 158;
        green = 63;
        blue = 0;
        break;

      case 'T':
        red = 0;
        green = 127;
        blue = 127;
        break;

      case 'V':
        red = 127;
        green = 0;
        blue = 127;
        break;

      case '1': 
        animationID = AnimationType::stillRainbow;
      break;

      case '2': 
        animationID = AnimationType::rainbowFade;
      break;

      case '3': 
        animationID = AnimationType::rainbowCycle;
      break;

      case '4': 
        animationID = AnimationType::rainbowGroupScroll;
      break;

      case '5': 
        animationID = AnimationType::rainbowAlternatingFade;
      break;

      case '?':
        sonarLeft = sonar2.ping_cm() /2.54;
        sonarRight = sonar.ping_cm() /2.54;
        if (sonarLeft == 0 && sonarRight == 0) {
          Serial.println("-555 -555 -555");
        } else {
          bool hasBrokenSensor = false;
          if (sonarLeft == 0) {
            sonarLeft = sonarRight;
            hasBrokenSensor = true;
          }
          if (sonarRight == 0) {
            sonarRight = sonarLeft;
            hasBrokenSensor = true;
          }
          //Serial.print("Ping:\t");
          Serial.print(sonarRight); // Send ping, get distance in cm and print result (0 = outside set distance range)
          Serial.print(" ");
          Serial.print(sonarLeft);
          Serial.print(" ");
          if (hasBrokenSensor == true) {
            Serial.println("-777");
          } else {
            float y = (sonarRight - sonarLeft);
            float theta = atan2(y,WIDTH) *(180.0/3.14159265359); 
            if (theta == 90) {
              Serial.println("-999");
            } else {
              Serial.println(theta);
            }
          }
        }
        break;

      default: // will run if incoming matches none of the above.
        //you don't need a default, but it is here when wanted.
        break;
      
    }
  }
  
  switch (animationID){
    
    case AnimationType::blackout:
      inky.blackout();
      blinky.blackout();
      pinky.blackout();
      clyde.blackout();
    break;

    case AnimationType::solidColor:
      inky.solidColor(red, green, blue);
      blinky.solidColor(red, green, blue);
      pinky.solidColor(red, green, blue);
      clyde.solidColor(red, green, blue);
      break;

    case AnimationType::fade:
      inky.fade(red, green, blue, 4);
      blinky.fade(red, green, blue, 4);
      pinky.fade(red, green, blue, 4);
      clyde.fade(red, green, blue, 4);
      break;

    case AnimationType::alternatingFade:
      inky.alternatingFade(red, green, blue, 3, 3);
      blinky.alternatingFade(red, green, blue, 3, 3);
      pinky.alternatingFade(red, green, blue, 3, 3);
      clyde.alternatingFade(red, green, blue, 3, 3);
      break;

    case AnimationType::wave:
      inky.wave(red, green, blue, 20, 5, 10);
      blinky.wave(red, green, blue, 20, 5, 10);
      pinky.wave(red, green, blue, 20, 5, 7);
      clyde.wave(red, green, blue, 20, 5, 7);
      break;

    case AnimationType::bounce:
      inky.bounce(red, green, blue, 20);
      blinky.bounce(red, green, blue, 20);
      pinky.bounce(red, green, blue, 20);
      clyde.bounce(red, green, blue, 20);
      break;

    case AnimationType::ripple:
      inky.ripple(red, green, blue, 8, 25);
      blinky.ripple(red, green, blue, 8, 25);
      pinky.ripple(red, green, blue, 8, 25);
      clyde.ripple(red, green, blue, 8, 25);
      break;

    case AnimationType::carnival:
      inky.carnival(red, green, blue, 40);
      blinky.carnival(red, green, blue, 40);
      pinky.carnival(red, green, blue, 40);
      clyde.carnival(red, green, blue, 40);
      break;

    case AnimationType::blink:
      inky.blink(red, green, blue, 500);
      blinky.blink(red, green, blue, 500);
      pinky.blink(red, green, blue, 500);
      clyde.blink(red, green, blue, 500);
      break;

    case AnimationType::groupScroll:
      inky.groupScroll(red, green, blue, 30, 10, 5);
      blinky.groupScroll(red, green, blue, 30, 10, 5);
      pinky.groupScroll(red, green, blue, 30, 6, 5);
      clyde.groupScroll(red, green, blue, 30, 6, 5);
      break;

    case AnimationType::stillRainbow:
      inky.stillRainbow(255);
      blinky.stillRainbow(255);
      pinky.stillRainbow(255);
      clyde.stillRainbow(255);
      break;
    
    case AnimationType::rainbowFade:
      inky.rainbowFade(255, 20);
      blinky.rainbowFade(255, 20);
      pinky.rainbowFade(255, 20);
      clyde.rainbowFade(255, 20);
      break;
    
    case AnimationType::rainbowCycle:
      inky.rainbowCycle(255, 10);
      blinky.rainbowCycle(255, 10);
      pinky.rainbowCycle(255, 10);
      clyde.rainbowCycle(255, 10);
      break;
    
    case AnimationType::rainbowGroupScroll:
      inky.rainbowGroupScroll(255, 20, 10, 5);
      blinky.rainbowGroupScroll(255, 20, 10, 5);
      pinky.rainbowGroupScroll(255, 20, 6, 5);
      clyde.rainbowGroupScroll(255, 20, 6, 5);
      break;

    case AnimationType::rainbowAlternatingFade:
      inky.rainbowAlternatingFade(255, 2, 4);
      blinky.rainbowAlternatingFade(255, 2, 4);
      pinky.rainbowAlternatingFade(255, 2, 4);
      clyde.rainbowAlternatingFade(255, 2, 4);
      break;
    
    default: // will run if icoming matches none of the above.
      //you don't need a default, but it is here when wanted.
      break;
  }
  inky.show();
  blinky.show();
  pinky.show();
  clyde.show();
  
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

void LedStrip::fade(int r,int g,int b, int wait)
{
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;
  
  int res = 64;
  int l = 0;
  f %= ((res * 2));
  
  
  if (f % (res * 2) < res) {
  l = f % (res);
  } else if (f % (res * 2) >= res) {
  l = res - (f % (res));
  }

  for (int i = 0; i < this->numPixels(); i ++){
    this->setPixelColor(i, this->Color((l*r)/res,(l*g)/res,(l*b)/res));
  }
  this->show();
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

void LedStrip::alternatingFade(int r,int g,int b, int wait, int wavelength)
{
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;
  int res = 64;
  int l = 0;
  f %= ((res * 2) * wavelength);
  int s = f / (res * 2);
  s %= wavelength;
  
  if (f % (res * 2) < res) {
  l = f % (res);
  } else if (f % (res * 2) >= res) {
  l = res - (f % (res));
  }

  for (int i = s; i < this->numPixels(); i += wavelength){
    this->setPixelColor(i, this->Color((l*r)/res,(l*g)/res,(l*b)/res));
  }
  this->show();
}

void LedStrip::wave (int r, int g, int b, int wait, int quantity, int magnitude)
{
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;
  
  int p = this->numPixels() / quantity;
  int o = this->numPixels() - (p * quantity);
  int s = (f % (this->numPixels() - o));
  
  for(int w = (s % p); w < (this->numPixels() + (magnitude * 2)); w += p){
    for (int i = 0; i <= magnitude; i++){
      
      this->setPixelColor(((i+w) - (magnitude * 2)), this->Color((i*r)/magnitude, (i*g)/magnitude, (i*b)/magnitude));
      
    }
    for (int i = magnitude; i >= 0; i--) {
      
      this->setPixelColor((w+((magnitude * 2) - i) - (magnitude * 2)), this->Color((i*r)/magnitude, (i*g)/magnitude, (i*b)/magnitude));
      
    }
  }
}

void LedStrip::bounce(int r, int g, int b, int wait)
{
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;
  f %= ((this->numPixels() * 2) - 1);

  if (f <= this->numPixels()) {
    this->setPixelColor(f,this->Color(r,g,b));
    this->setPixelColor(f - 1,this->Color(0,0,0));
    this->setPixelColor(f - 2,this->Color(0,0,0));
    
  }

  if (f > this->numPixels()){
    this->setPixelColor((this->numPixels() * 2) - f, this->Color(r,g,b));
    this->setPixelColor((this->numPixels() * 2) - f + 1, this->Color(0,0,0));
    this->setPixelColor((this->numPixels() * 2) - f + 2, this->Color(0,0,0));
  }
  if (f > (this->numPixels() * 2) - 1) {
    
  }
}

void LedStrip::carnival(int r,int g,int b, int wait)
{
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;
  int c = f % 3;
  for(int i = 0; i < this->numPixels() + 1; i+=3){
    this->setPixelColor(i+c, this->Color(r,g,b));
    this->setPixelColor(i+c-1, this->Color(0,0,0));
  }
}

void LedStrip::ripple(int r, int g, int b, byte magnitude, byte wait)
{
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;
  
  int s = ((f % (magnitude * 2)) - (magnitude * 2) + 2);
  
  for (int p = 0; p < this->numPixels() + (2 * magnitude) - 2; p += (2*magnitude)) {
    for (int i = 0; i < magnitude; i++){
      if ((p+i-s) >= 0 && p+i-s < this->numPixels()){
        this->setPixelColor(p+i-s, this->Color((i*r)/magnitude, (i*g)/magnitude, (i*b)/magnitude));
      }
    }
    for (int i = magnitude; i > 0; i--) {
      if ((p-s+((magnitude * 2) - i)) >= 0 && (p-s+((magnitude * 2) - i)) < this->numPixels()){
        this->setPixelColor((p-s+((magnitude * 2) - i)), this->Color((i*r)/magnitude, (i*g)/magnitude, (i*b)/magnitude));
      }
    }
  }
}

void LedStrip::groupScroll(int r, int g, int b, int wait, int numGroups, int groupSize) {
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;

  f %= this->numPixels();
  int sum = 0;
  int v = this->numPixels() / numGroups;
  
  for(uint16_t i=0; i<groupSize; i++) {
    for(uint16_t n = 0; n < numGroups; n++) {
      sum = (i + f) + (n * v);
      while (sum >= this->numPixels()) {
        sum = sum - this->numPixels();
      }
      this->setPixelColor(sum, r, g, b);
    }
  }
  
  for (int n = 0; n < numGroups; n++) {
    sum = f + (n * v);
    sum %= this->numPixels();
    this->setPixelColor(sum, 0, 0, 0);
  }
}

void LedStrip::stillRainbow(byte brightness)
{
  for (int i; i < this->numPixels(); i++) {
    this->setPixelColor(i, wheelBrightness((i * 256 / this->numPixels()) & 255, brightness));
  }
}

void LedStrip::rainbowFade(byte maxBrightness, int wait)
{
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;

  int res = 64;
  int l = 0;
  f %= ((res * 2));
  
  if (f % (res * 2) < res) {
  l = f % (res);
  } else if (f % (res * 2) >= res) {
  l = res - (f % (res));
  }
  
  for (int i; i < this->numPixels(); i++) {
    this->setPixelColor(i, wheelBrightness((i * 256 / this->numPixels()) & 255, (maxBrightness * l) / res));
  }
}

void LedStrip::rainbowCycle(byte brightness, int wait)
{
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;
  int s = f % 256;
  for (int i; i < this->numPixels(); i++) {
    this->setPixelColor(i, wheelBrightness(((i * 256 / this->numPixels()) + s) & 255, brightness));
  }
}

void LedStrip::rainbowGroupScroll(byte brightness, int wait, int numGroups, int groupSize)
{
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;

  f %= this->numPixels();
  int sum = 0;
  int v = this->numPixels() / numGroups;
  
  for(uint16_t i=0; i<groupSize; i++) {
    for(uint16_t n = 0; n < numGroups; n++) {
      sum = (i + f) + (n * v);
      while (sum >= this->numPixels()) {
        sum = sum - this->numPixels();
      }
      this->setPixelColor(sum, wheelBrightness((sum * 256 / this->numPixels()) & 255, brightness));
    }
  }
  
  for (int n = 0; n < numGroups; n++) {
    sum = f + (n * v);
    sum %= this->numPixels();
    this->setPixelColor(sum, 0, 0, 0);
  }
}

void LedStrip::rainbowAlternatingFade(byte maxBrightness, int wait, int wavelength)
{
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;
  int res = 64;
  int l = 0;
  f %= ((res * 2) * wavelength);
  int s = f / (res * 2);
  s %= wavelength;
  
  if (f % (res * 2) < res) {
  l = f % (res);
  } else if (f % (res * 2) >= res) {
  l = res - (f % (res));
  }

  for (int i = s; i < this->numPixels(); i += wavelength){
    this->setPixelColor(i, wheelBrightness((i * 256 / this->numPixels()) & 255, (maxBrightness * l) / res));
  }
  this->show();
}

// wheel gives an rgb color given a position on the color wheel. To use 
uint32_t wheel(byte position) {
  if(position < 85) {
   return Adafruit_NeoPixel::Color(position * 3, 255 - position * 3, 0);
  } else if(position < 170) {
   position -= 85;
   return Adafruit_NeoPixel::Color(255 - position * 3, 0, position * 3);
  } else {
   position -= 170;
   return Adafruit_NeoPixel::Color(0, position * 3, 255 - position * 3);
  }
}

uint32_t wheelBrightness(byte position, byte brightness) {
  if(position < 85) {
   return Adafruit_NeoPixel::Color((position * 3 * brightness) / 255, ((255 - position * 3) * brightness) / 255, 0);
  } else if(position < 170) {
   position -= 85;
   return Adafruit_NeoPixel::Color(((255 - position * 3) * brightness) / 255, 0, (position * 3 * brightness) / 255);
  } else {
   position -= 170;
   return Adafruit_NeoPixel::Color(0, (position * 3 * brightness) / 255, ((255 - position * 3) * brightness) / 255);
  }
}





