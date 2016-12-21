/*
 * This is the final version of the LED code for 2016. 
 * Use this as a reference for animations, or run it and try to figure it out.
 * It is designed to work with Susan/Su. 
 */




#include <Adafruit_NeoPixel.h>

#define PIN 6 // the Data Pin for the strip.
#define NUMPIXELS 34 // how many pixels are on the strip
#define LIMITSWITCH 2


class NewNeoPixel:public Adafruit_NeoPixel  {

  public:
   NewNeoPixel(int pixels, int pin, int options);
   void fade(int r,int g,int b, int wait);
   void alternatingFade(int r,int g,int b, int wait, int wavelength);
   void wave (int r, int g, int b, int wait, int quantity, int magnitude);
   void bounce(int r, int g, int b, int wait);
   void carnival(int r,int g,int b, int wait);
   void solidColor(int r, int g, int b);
   void ripple(int r, int g, int b, byte magnitude, byte wait);
   void blink(int r, int g, int b, int wait);
   void easter(int r,int g,int b);
   void rainbowBounce(int wait);
};


NewNeoPixel strip1 = NewNeoPixel(153, 6, NEO_GRB + NEO_KHZ800);
NewNeoPixel strip2 = NewNeoPixel(34, 5, NEO_GRB + NEO_KHZ800);
NewNeoPixel strip3 = NewNeoPixel(17, 3, NEO_GRB + NEO_KHZ800);

int incoming;

int animationID = 1;
int red = 0;
int green = 0;
int blue = 32;
unsigned long lastTick = 0;
unsigned long timeSince = 0;

boolean willReset = true;

boolean redAlliance = true;
boolean endGame = false;


void setup() {
  // put your setup code here, to run once:
  strip1.begin();
  strip1.show();
  strip2.begin();
  strip2.show();
  strip3.begin();
  strip3.show();
  Serial.begin(115200);
  pinMode(LIMITSWITCH, INPUT);

}

void loop() {
  lastTick = micros();
  redo:
  if (Serial.available() > 0) {
    timeSince = millis();
    incoming = Serial.read(); // reads the next thing sent on the serial line.
    switch (incoming) {
      case 'f':
        Serial.println ("Fade");
        animationID = 1;
        strip1.solidColor(0,0,0);
        strip2.solidColor(0,0,0);
        strip3.solidColor(0,0,0);
        
        break;
      case 'b':
        Serial.println ("Bounce");
        animationID = 2;
        strip1.solidColor(0,0,0);
        strip2.solidColor(0,0,0);
        strip3.solidColor(0,0,0);
        
        break;
      case 'i':
        Serial.println ("Teleop");
        animationID = 3;
        strip1.solidColor(0,0,0);
        strip2.solidColor(0,0,0);
        strip3.solidColor(0,0,0);
        
        break;
      case 'e':
        Serial.println ("Easter");
        animationID = 4;
        strip1.solidColor(0,0,0);
        strip2.solidColor(0,0,0);
        strip3.solidColor(0,0,0);
        
        break;
      case 'l':
        Serial.println ("Intake Running");
        animationID = 2;
        strip1.solidColor(0,0,0);
        strip2.solidColor(0,0,0);
        strip3.solidColor(0,0,0);
        
        break;
      case 's':
        Serial.println ("Shoot");
        animationID = 6;
        strip1.solidColor(0,0,0);
        strip2.solidColor(0,0,0);
        strip3.solidColor(0,0,0);
        
        break;
      case 'c':
        Serial.println ("Autonomous");
        animationID = 7;
        strip1.solidColor(0,0,0);
        strip2.solidColor(0,0,0);
        strip3.solidColor(0,0,0);
        
        break;
      case 'n':
        Serial.println ("Blue");
        red = 0;
        green = 0;
        blue = 64;
        break;
      case 'r':
        Serial.println ("Red");
        red = 64;
        green = 0;
        blue = 0;
        break;
      case 'v':
      Serial.println ("Violet");
        red = 30;
        green = 0;
        blue = 54;
        break;
      case 'g':
      Serial.println ("Green");
        red = 0;
        green = 64;
        blue = 0;
        break;
      case 't':
      Serial.println ("Teal");
        red = 0;
        green = 84;
        blue = 44;
        break;
      case 'z':
        Serial.println ("Final 20 Seconds");
        red = 64;
        green = 48;
        blue = 0;
        break;
       case 'w':
        Serial.println ("White");
        red = 32;
        green = 32;
        blue = 32;
        break;
      case '~':
        Serial.println ("Alive");
        //keeps the lights awake. Leave blank unless you've got something to do nearly every active frame.
        goto redo;
        break;
    }
  } 
  /* 
    else if (millis() - timeSince > 5000) {
    animationID = 1;
    strip1.solidColor(0,0,0);
    strip2.solidColor(0,0,0);
    strip3.solidColor(0,0,0);
        
  }
  */
  /*
  if (digitalRead(LIMITSWITCH == true)) {
    animationID = 5;
    red = 32;
    green = 32;
    blue = 32;
  }
  */
  switch (animationID){
      case 1:
         strip1.alternatingFade (red, green, blue, 5, 3);
         strip2.alternatingFade (red, green, blue, 5, 3);
         strip3.alternatingFade (red, green, blue, 5, 3);
         
        break;
      case 2:
        strip1.bounce (red, green, blue, 10);
        strip2.bounce (red, green, blue, 10);
        strip3.bounce (red, green, blue, 10);
        
        break;
      case 3:
         strip1.ripple (red, green, blue, 8, 25);
         strip2.ripple (red, green, blue, 8, 25);
         strip3.ripple (red, green, blue, 8, 25);
         
        break;
      case 4:
         strip1.easter (red, green, blue);
         strip2.easter (red, green, blue);
         strip3.easter (red, green, blue);
         
        break;
      case 5:
         strip1.blink (red, green, blue, 100);
         strip2.blink (red, green, blue, 100);
         strip3.blink (red, green, blue, 100);
         
        break;
      case 6:
         strip1.solidColor (red, green, blue);
         strip2.solidColor (red, green, blue);
         strip3.solidColor (red, green, blue);
         
        break;
      case 7:
         strip1.carnival (red, green, blue, 40);
         strip2.carnival (red, green, blue, 40);
         strip3.carnival (red, green, blue, 40);
         
        break;
      case 8:
         strip1.rainbowBounce (50);
         strip2.rainbowBounce (50);
         strip3.rainbowBounce (50);
         
        break;
      default:
        strip1.solidColor (16, 16, 16);
        strip2.solidColor (16, 16, 16);
        strip3.solidColor (16, 16, 16);
  }
  
  strip1.show();
  strip2.show();
  strip3.show();
  
  while(micros() - lastTick < 1000){
    delayMicroseconds(1);
  }
  Serial.println(micros()-lastTick);
}



NewNeoPixel::NewNeoPixel(int pixels, int pin, int options): Adafruit_NeoPixel(pixels, pin, options)
{
}


void NewNeoPixel::fade(int r,int g,int b, int wait){

  static unsigned long timer = millis();
  
  unsigned int f = (millis()-timer)/wait;
  int res = 64;
  int l = 0;
  f %= (res * 2);
  
  if (f % (res * 2) < res) {
  l = f % (res);
  } else if (f % (res * 2) >= res) {
  l = res - (f % (res));
  }

  for (int i = 0; i < this->numPixels(); i++){
    this->setPixelColor(i, this->Color((l*r)/res,(l*g)/res,(l*b)/res));
  }
  this->show();
  }

void NewNeoPixel::alternatingFade(int r,int g,int b, int wait, int wavelength){

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

void wave (int r, int g, int b, int wait, int quantity, int magnitude) {
  
}

void NewNeoPixel::bounce(int r, int g, int b, int wait){
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
  
void NewNeoPixel::carnival(int r,int g,int b, int wait){
  static unsigned long timer = millis();
  unsigned int f = (millis()-timer)/wait;
  int c = f % 3;
  for(int i = 0; i < this->numPixels() + 1; i+=3){
    this->setPixelColor(i+c, this->Color(r,g,b));
    this->setPixelColor(i+c-1, this->Color(0,0,0));
  }
  
}

void NewNeoPixel::solidColor(int r, int g, int b){
   for(int i = 0; i < this->numPixels(); i++){
    this->setPixelColor(i, this->Color(r,g,b));
  }
  this->show();
}

void NewNeoPixel::blink(int r, int g, int b, int wait) {
  static unsigned long timer = millis();
  
  unsigned int f = (millis()-timer)/wait;
  f %= 2;
  if (f % 2) {
  solidColor(0,0,0);
  } else {
  solidColor(r,g,b);
  }
}

void NewNeoPixel::easter(int r,int g,int b){
    int num = 0;
  
  for(int i = this->numPixels(); i > 0; i--){
    int R = random(r);
    int G = random(g);
    int B = random(b);
    for(int r = num + 1; r <= i; r++){
      this->setPixelColor(r, this->Color(R,G,B));
      this->show();
      delayMicroseconds(10);
      this->setPixelColor(r, this->Color(0,0,0));
      }
    this->setPixelColor(i, this->Color(R,G,B));

     for(int k = i - 1; k >= num; k--){
        this->setPixelColor(k, this->Color(R,G,B));
        this->show();
        delayMicroseconds(10);
        this->setPixelColor(k, this->Color(0,0,0));
      }
   
   this->setPixelColor(num, this->Color(R,G,B));
   num++;
   
  }
  this->show();
}

void NewNeoPixel::ripple(int r, int g, int b, byte magnitude, byte wait){
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
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
void NewNeoPixel::rainbowBounce(int wait) {
/*
  static unsigned long timer = millis();
  int r;
  int g;
  int b;
  
  unsigned int f = (millis()-timer)/wait;
  f %= ((this->numPixels() * 5) - 1);
  Serial.println(f);
  Serial.println(f / this->numPixels());
  
  switch (f / this->numPixels()){
    case 0:
      r = 32;
      g = 0;
      b = 0;
    break;
    case 1:
      r = 16;
      g = 16;
      b = 0;
    break;
    case 2:
      r = 0;
      g = 32;
      b = 0;
    break;
    case 3:
      r = 0;
      g = 16;
      b = 16;
    break;
    case 4:
      r = 0;
      g = 0;
      b = 32;
    break;
    case 5:
      r = 16;
      g = 0;
      b = 16;
    break;
  }
  
  if (f % ((this->numPixels() - 1) * 2) <= this->numPixels()) {
    this->setPixelColor(f,this->Color(r,g,b));
    this->setPixelColor(f - 1,this->Color(0,0,0));
    this->setPixelColor(f - 2,this->Color(0,0,0));
    
  }

  if (f % ((this->numPixels() - 1) * 2) > this->numPixels()){
    this->setPixelColor((this->numPixels() * 2) - f, this->Color(r,g,b));
    this->setPixelColor((this->numPixels() * 2) - f + 1, this->Color(0,0,0));
    this->setPixelColor((this->numPixels() * 2) - f + 2, this->Color(0,0,0));
  }
  */
  /*
  for (int i = 299; i > 0; i = i -1){
    this->setPixelColor(i,this->Color(255,0,0));
    this->setPixelColor(i + 1, this->Color(255,0,0));
    this->setPixelColor(i + 2, this->Color(255,0,0));
    this->show();
    delay(5);
    this->setPixelColor(i + 3,this->Color(0,0,0));

   //red
  }

  for (int i = 0; i < 299; i = i +1){
    this->setPixelColor(i,this->Color(255,65,0));
    this->setPixelColor(i - 1, this->Color(255,65,0));
    this->setPixelColor(i - 2, this->Color(255,65,0));
    this->show();
    delay(5);
    this->setPixelColor(i - 3,this->Color(0,0,0));

    //orange
  }

  
  for (int i = 299; i > 0; i = i -1){
    this->setPixelColor(i,this->Color(255,130,0));
    this->setPixelColor(i + 1, this->Color(255,130,0));
    this->setPixelColor(i + 2, this->Color(255,130,0));
    this->show();
    delay(5);
    this->setPixelColor(i + 3,this->Color(0,0,0));

    //yellow
  }

 for (int i = 0; i < 299; i = i +1){
    this->setPixelColor(i,this->Color(0,255,0));
    this->setPixelColor(i - 1, this->Color(0,255,0));
    this->setPixelColor(i - 2, this->Color(0,255,0));
    this->show();
    delay(5);
    this->setPixelColor(i - 3,this->Color(0,0,0));

    //green
  }
for (int i = 299; i > 0; i = i -1){
    this->setPixelColor(i,this->Color(0,0,230));
    this->setPixelColor(i + 1, this->Color(0,0,230));
    this->setPixelColor(i + 2, this->Color(0,0,230));
    this->show();
    delay(5);
    this->setPixelColor(i + 3,this->Color(0,0,0));

    //blue
  }
   for (int i = 0; i < 299; i = i +1){
    this->setPixelColor(i,this->Color(255,0,255));
    this->setPixelColor(i - 1, this->Color(255,0,255));
    this->setPixelColor(i - 2, this->Color(255,0,255));
    this->show();
    delay(5);
    this->setPixelColor(i - 3,this->Color(0,0,0));

    //violet
  }
  */
}
