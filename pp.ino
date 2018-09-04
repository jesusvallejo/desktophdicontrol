#include "HID-Project.h"




const int pinLed = LED_BUILTIN;
const int pinButton1 = 9;
const int pinButton2 = 10;
const int pinButton3 = 14;
const int pinButton4 = 16;
const int pinButton5 = 15;
const int pinButtonProfile = 6;
// pines Estado////////////////
const int profileLed1 = 7;
const int profileLed2 = 8;
//////////////////////////////

// Declaracion de Estados///////
const int bootState = 2; //////Estado predeterminado
const int firstState=0;
const int secondState=1;
const int thirdState=2;

int currentState = bootState;// Cuando bootea selecciona el modo predeterminado
///////////////////////////////

bool muted= false; //------------------> En construccion

///////////////////////////////
//char ctrlKey = KEY_LEFT_CTRL;
//char shiftKey = KEY_LEFT_SHIFT;
//char altKey = KEY_LEFT_ALT;
//char altgrKey = KEY_RIGHT_ALT;
////////////////////////////////
// declare surface dial ///////

// input pins for encoder channel A and channel B
int pinA = 4;
int pinB = 3;
// input pin for pushbutton
int pinButton = 5;

volatile bool previousButtonValue = false;
volatile int previous = 0;
volatile int counter = 0;

///////////////////////////////



void setup() {
  // hid setup ////////////////
  pinMode(pinLed, OUTPUT);
  pinMode(profileLed1, OUTPUT);
  pinMode(profileLed2, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(pinButtonProfile, INPUT_PULLUP);
  pinMode(pinButton1, INPUT_PULLUP);
  pinMode(pinButton2, INPUT_PULLUP);
  pinMode(pinButton3, INPUT_PULLUP);
  pinMode(pinButton4, INPUT_PULLUP);
  pinMode(pinButton5, INPUT_PULLUP);
  
  // Sends a clean report to the host. This is important on any Arduino type.
  Consumer.begin();
  Keyboard.begin();
  
  ////////////////////////////

  // surface dial setup //////

  pinMode(pinA, INPUT_PULLUP); 
  pinMode(pinB, INPUT_PULLUP);

  pinMode(pinButton, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), changed, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(pinB), changed, CHANGE);
  
  SurfaceDial.begin();

  ////////////////////////////
}

void ledControl(){
  if (muted){
  ////////////////////////////////////////////////// blink without delay  
  }
  else{
  switch(currentState){
     case firstState :
     digitalWrite(profileLed1,LOW);
     digitalWrite(profileLed2, LOW);
     break;
     case secondState :
     digitalWrite(profileLed1, HIGH);
     digitalWrite(profileLed2, LOW);
     break;
    
     case thirdState :
     digitalWrite(profileLed1, HIGH);
     digitalWrite(profileLed2, HIGH);
     break;

     default :
     if (currentState != firstState && currentState != secondState && currentState != thirdState ){
        digitalWrite(profileLed1,LOW);
        digitalWrite(profileLed2, LOW);
    currentState= bootState;
      }
    }
  }
  
}


// ESTADOS -- Estados predeterminados /////////////

//ESTADO 1 -- Control general(Surface Dial) //
void firstStatefunction(){
  
  bool buttonValue = digitalRead(pinButton);
  if(buttonValue != previousButtonValue){
    if(buttonValue) {
      SurfaceDial.press();
    } else {
      SurfaceDial.release();
    }    
    previousButtonValue = buttonValue;
  }

  if(counter >= 4) {
    SurfaceDial.rotate(20);
    counter -= 4;
  } else if(counter <= -4) {
    SurfaceDial.rotate(-20);
    counter += 4;
  } 
  

  if (!digitalRead(pinButton1)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    Consumer.write(MEDIA_VOLUME_MUTE);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }


  if (!digitalRead(pinButton2)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    Consumer.write(MEDIA_PLAY_PAUSE);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }


  if (!digitalRead(pinButton3)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    Consumer.write(MEDIA_NEXT);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
  if (!digitalRead(pinButton4)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    Consumer.write(MEDIA_PREVIOUS);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
  if (!digitalRead(pinButton5)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    Consumer.write(CONSUMER_BROWSER_HOME);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }

  }
/////////////////////////////////////////////

//ESTADO 2 -- Control general(No Dial) ///////
void secondStatefunction(){
  
    if (!digitalRead(pinButton1)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
   Keyboard.press(KEY_LEFT_CTRL);
   Keyboard.press('c');
   
   Keyboard.releaseAll();
    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }


  if (!digitalRead(pinButton2)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
   Keyboard.press(KEY_LEFT_CTRL);
   Keyboard.press('v');
   Keyboard.releaseAll();

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }


  if (!digitalRead(pinButton3)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    //Keyboard.press(altgrKey);
  Keyboard.press('l');
    Keyboard.releaseAll();
    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
  if (!digitalRead(pinButton4)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    //Keyboard.press(altgrKey);
  Keyboard.press('l');
    Keyboard.releaseAll();
    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
  if (!digitalRead(pinButton5)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F4);
    Keyboard.releaseAll();

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
/////////////////////////////////////////////

//ESTADO 3 -- Control general(Vol  Dial) // ----------> predeterminado
void thirdStatefunction(){
  
  bool buttonValue = digitalRead(pinButton);
  
  if(counter >= 4) {
    Consumer.write(MEDIA_VOLUME_UP);
    
    
    counter -= 4;
  
  } else if(counter <= -4) {
   Consumer.write(MEDIA_VOLUME_DOWN);
   
   
    counter += 4;
  
  }

  
  if (!digitalRead(pinButton1)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
   Consumer.write(MEDIA_VOLUME_MUTE);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }


  if (!digitalRead(pinButton2)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    Consumer.write(MEDIA_PLAY_PAUSE);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }


  if (!digitalRead(pinButton3)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    Keyboard.press(KEY_RIGHT_ALT);
    Keyboard.press('P');
    
     Keyboard.releaseAll();
    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);

  }

  
  if (!digitalRead(pinButton4)) {
    
    digitalWrite(pinLed, HIGH);
    
    // See HID Project documentation for more Consumer keys
    Keyboard.press(KEY_RIGHT_ALT);
    delay(200);
   Keyboard.press('L');
    delay(200);
   Keyboard.release('LED_BUILTIN');
    delay(200);
Keyboard.releaseAll();
    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);

  }

  
  if (!digitalRead(pinButton5)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  delay(200);
  Keyboard.press(KEY_DELETE);
  delay(200);
  Keyboard.releaseAll();
    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }

  }
//////////////////////////////////////////

//////////////////////////////////////////////////

  
// State control -- Estado en función de botón ////
void statecontrolFunction(){   
  if (!digitalRead(pinButtonProfile)) {
    digitalWrite(pinLed, HIGH);
    if (currentState<2){// See HID Project documentation for more Consumer keys
    currentState++;
    }
  else{
    currentState =0;
  }
   digitalWrite(pinLed, LOW);//
    // Simple debounce
    delay(450);
    
  }
  if(!muted){
  ledControl();
  }
    
  }
//////////////////////////////////////////////////


// ROTATORY ENCODER -- Posicionamiento //////////// 
void changed() {
  int A = digitalRead(pinA); 
  int B = digitalRead(pinB);

  int current = (A << 1) | B;
  int combined  = (previous << 2) | current;
   
  if(combined == 0b0010 || 
     combined == 0b1011 ||
     combined == 0b1101 || 
     combined == 0b0100) {
    counter++;
  }
   
  if(combined == 0b0001 ||
     combined == 0b0111 ||
     combined == 0b1110 ||
     combined == 0b1000) {
    counter--;
  }
  previous = current;
}
//////////////////////////////////////////////////

// Non delay blink -- blinker for muted non delayed ////
// Credits : https://learn.adafruit.com/multi-tasking-the-arduino-part-1/a-classy-solution //////
class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time

  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated

  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  OnTime = on;
  OffTime = off;
  
  ledState = LOW; 
  previousMillis = 0;
  }

  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);   // Update the actual LED
    }
  }
};


Flasher led1(profileLed1, 100, 400);
Flasher led2(profileLed2, 100, 400);
///////////////////////////////////////////////

void loop() {
 led1.Update();
 led2.Update();  
statecontrolFunction();
  switch(currentState){
     case firstState :
     firstStatefunction();
     break;
     case secondState :
     secondStatefunction();
     break;
     case thirdState :
     thirdStatefunction();
     break;

    }
 
  
}








