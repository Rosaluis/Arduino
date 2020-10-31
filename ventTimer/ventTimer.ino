#include <OneWire.h>
#include <DallasTemperature.h>


// constants won't change. Used here to set a pin number:
const int ledGreenPin   = 9;            // Green LED = Arduino is working
const int ledYellowPin  = 10;           // Yellow LED = Fan is turning high speed
const int ledBluePin    = 11;           // Blue LED = Fan is turning low speed (<5°C)
const int fanPin        = 12;           // Fan MOSFET output
const int tempInPin     = 3;            // Internal (on board) temperature 
const int tempBoxPin    = 6;            // Bee frames box temperature

// Variables will change:
int ledGreenState       = LOW;          // ledStates used to set the LED
int ledYellowState      = LOW;
int ledBlueState        = LOW;
int fanState            = LOW;
float calibDSIn           = -3.0;
float calibDSBox          = -1.8;
int tempLimit           = 10;           // if temp < limit, than run fan slowly
int tempFreeze          = -1;           // if temp < limit, than dont run

unsigned long previousMillis = 0;       // will store last time LED was updated
int sekundy = 0;
int minuty = 0;
int hodiny = 0;


// constants won't change:
const long interval = 1000;    

// vytvoreni instance oneWireDS z knihovny OneWire
OneWire oneWireDSIn(tempInPin);
OneWire oneWireDSBox(tempBoxPin);
DallasTemperature senzorDSIn(&oneWireDSIn);
DallasTemperature senzorDSBox(&oneWireDSBox);

void setup() {
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  Serial.begin(115200);
  senzorDSIn.begin();
  senzorDSBox.begin();
  Serial.println("...reset - run");
  sendTemperature();
}


void sendTime() {
  Serial.print("Time of run: ");
  Serial.print(minuty);
  Serial.print(":");
  Serial.println(sekundy);
}


void sendTemperature() {
  Serial.print("Teploty (box / pcb): ");
  Serial.print(senzorDSIn.getTempCByIndex(0) + calibDSIn);
  Serial.print(" / ");
  Serial.println(senzorDSBox.getTempCByIndex(0) + calibDSBox);
}


// fan speed 
void setPWMToFan(int speed) {
  switch (speed) {
  case 1: // slow if cold
    analogWrite(fanPin, 200);
    break;
    
  case 2: // high if not cold
    analogWrite(fanPin, 255);
    break;
  
  case 3: // fan stopped
    analogWrite(fanPin, 0);
    break;
    
      
  default: // fan is switch-off
    analogWrite(fanPin, 0);
    break;
  }
}

// arduino is alive
void blinkGreenLed() {
  if (sekundy %1 == 0) {
    if (ledGreenState == LOW) {
      ledGreenState = HIGH;
    } else {
      ledGreenState = LOW;
    }
  }
}


void blinkBlueLed() {
  if (sekundy %1 == 0) {
    if (ledBlueState == LOW) {
      ledBlueState = HIGH;
    } else {
      ledBlueState = LOW;
    }
  }
}

void onBlueLed() {
  ledBlueState = HIGH;
}

int checkTimeLimit(int maxTime) {
  if ((minuty >= 0) && (minuty < maxTime)) { 
    return (HIGH);
  } else {
    return (LOW);
  }
}

// timing for fan running
void switchFanOnOff() {
  /*
  if ((minuty >= 0) && (minuty < 10)) { //ventilator at bezi prvnich deset minut v kazde hodine
    ledYellowState = HIGH;
    fanState = HIGH;

  } else {
    ledYellowState = LOW;
    fanState = LOW; 
    //Serial.println("fanState = LOW");
  }
  */  
  if ((((senzorDSBox.getTempCByIndex(0) + calibDSBox) <= tempLimit) && 
      ((senzorDSBox.getTempCByIndex(0) + calibDSBox) > tempFreeze)) &&
      checkTimeLimit(10)) 
    {
      setPWMToFan(2);
      ledYellowState = LOW;
      blinkBlueLed();
      Serial.println("low speed of fan - cold (< 8dgr. of C.)");
    }
    else if (((senzorDSBox.getTempCByIndex(0) + calibDSBox) <= tempFreeze) &&
    checkTimeLimit(5))
  {
      setPWMToFan(2);
      ledYellowState = LOW;
      onBlueLed();
      Serial.println("low speed of fan - freeze");
  } 
    else if (((senzorDSBox.getTempCByIndex(0) + calibDSBox) > tempLimit) &&
    checkTimeLimit(15))
  {
      setPWMToFan(2);
      ledYellowState = HIGH;
      ledBlueState = LOW;
      Serial.println("high speed of fan");
  }
    else {
      setPWMToFan(3);
      Serial.println("fan off");
    }
  
}

void loop() {
  unsigned long currentMillis = millis();
  senzorDSIn.requestTemperatures();
  senzorDSBox.requestTemperatures();
  blinkGreenLed();
  switchFanOnOff();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    sekundy += 1;
  }

  if (sekundy %3 == 0) {
    sendTime();
    sendTemperature();
  }
  
  if (sekundy == 59) {
    minuty += 1;
    sekundy = 0;
  }

  if (minuty == 59) {                                    
    minuty = 0;
  }

  //snizení jasu diod
  //digitalWrite(ledGreenPin, ledGreenState);
  if (ledGreenState == HIGH) {
    analogWrite(ledGreenPin, 25);  
  } else {
    analogWrite(ledGreenPin, 0); 
  }

  
  //digitalWrite(ledYellowPin, ledYellowState);
  if (ledYellowState == HIGH) {
    analogWrite(ledYellowPin, 100);  
  } else {
    analogWrite(ledYellowPin, 0); 
  }

  
  //digitalWrite(ledBluePin, ledBlueState);
  if (ledBlueState == HIGH) {
    analogWrite(ledBluePin, 30);  
  } else {
    analogWrite(ledBluePin, 0); 
  }
}
