
unsigned long startMillis100;  //some global variables available anywhere in the program
unsigned long startMillis500;
unsigned long startMillis1000;
unsigned long currentMillis;
const unsigned long period = 1000;  //the value is a number of milliseconds
const byte ledPin = 13;    //using the built in LED
const byte ledBlue = 11; // blue LED

void setup()
{
  Serial.begin(115200);  //start Serial in case we need to print debugging info
  pinMode(ledPin, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  startMillis100 = millis();  //100ms
  startMillis500 = millis();  //500ms
  startMillis1000 = millis();  //1s
}

int timeDelay100() {
  currentMillis = millis();
  if (currentMillis - startMillis100 >= 100){ 
      startMillis100 = currentMillis;
      return 1;
    } else {
      return 0;
    }
}

int timeDelay500() {
  currentMillis = millis();
  if (currentMillis - startMillis500 >= 500){ 
      startMillis500 = currentMillis;
      return 1;
    } else {
      return 0;
    }
}

int timeDelay1000() {
  currentMillis = millis();
  if (currentMillis - startMillis1000 >= 1000){ 
      startMillis1000 = currentMillis;
      return 1;
    } else {
      return 0;
    }
}

void loop()
{
  if (timeDelay500()){
    digitalWrite(ledPin, !digitalRead(ledPin));  //if so, change the state of the LED.  Uses a neat trick to change the state
  }

  if (timeDelay1000()){
    digitalWrite(ledBlue, !digitalRead(ledBlue));  
  }
}
