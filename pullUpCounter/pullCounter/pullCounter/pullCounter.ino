#include "HX711.h"

HX711 scale;

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
unsigned long startMillis100;
unsigned long currentMillis100;
unsigned long startMillis1000;  
unsigned long currentMillis1000;
const unsigned long period100 = 100;  //the value is a number of milliseconds
const unsigned long period1000 = 1000;

const byte ledPin = 13;    //using the built in LED
uint8_t dataPin = 6;
uint8_t clockPin = 7;

float w1, w2, previous = 0;

void setup()
{
  startMillis = millis();
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION); // posle verzi knihovny HX711
  Serial.println();

  pinMode(ledPin, OUTPUT);
  scale.begin(dataPin, clockPin);

  Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));

  scale.set_scale(200); //muj odhat na 10kg
  scale.tare();

  //Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));
}

int timeDelay(int ms){
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= ms)  //test whether the period has elapsed
  {
    Serial.println(">=");
    return 1;
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  } else {
    return 0;
  }
}

void measureWeight()
{

  currentMillis100 = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis100 - startMillis100 >= period100){
    w1 = scale.get_units(10); // read until stable
    startMillis100 = currentMillis100;  //IMPORTANT to save the start time of the current LED state.
  } 

}





void blinkDemo()
{
  /*
    currentMillis1000 = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis1000 - startMillis1000 >= period1000)  //test whether the period has elapsed
  {
    //Serial.print("1000: ");
    //Serial.println(currentMillis1000);
    digitalWrite(ledPin, !digitalRead(ledPin));  //if so, change the state of the LED.  Uses a neat trick to change the state
    startMillis1000 = currentMillis1000;  //IMPORTANT to save the start time of the current LED state.
  } */
  if (timeDelay(500) == 1){
    digitalWrite(ledPin, !digitalRead(ledPin));  //if so, change the state of the LED.  Uses a neat trick to change the state
  }
}

void loop()
{
  //measureWeight();
  blinkDemo();
}

// END OF FILE
