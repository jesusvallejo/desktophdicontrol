#include "HID-Project.h"

// declare hid  /////////////

const int pinLed = LED_BUILTIN;
const int pinButton1 = 9;
const int pinButton2 = 10;
const int pinButton3 = 14;
const int pinButton4 = 16;
const int pinButton5 = 15;
const int pinButtonProfile = 6;

const int profileLed1 = 7;
const int profileLed2 = 8;


const int bootState = 2;
const int firstState=0;
const int secondState=1;
const int thirdState=2;
int currentState = bootState;



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
      }
    }
  
}

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
    SurfaceDial.rotate(10);
    counter -= 4;
  } else if(counter <= -4) {
    SurfaceDial.rotate(-10);
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
  
void thirdStatefunction(){
  
  bool buttonValue = digitalRead(pinButton);
  
  if(counter >= 6) {
    Consumer.write(MEDIA_VOLUME_UP);
    delay(50);
    counter -= 6;
  
  } else if(counter <= -6) {
   Consumer.write(MEDIA_VOLUME_DOWN);
   delay(50);
    counter += 6;
  
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
  ledControl();
    
  }


// funcion changed ///////////

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

//////////////////////////////

void loop() {
  
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








