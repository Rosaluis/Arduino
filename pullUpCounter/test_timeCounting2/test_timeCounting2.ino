
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 1000;  //the value is a number of milliseconds
const byte ledPin = 13;    //using the built in LED

void setup()
{
  Serial.begin(115200);  //start Serial in case we need to print debugging info
  pinMode(ledPin, OUTPUT);
  startMillis = millis();  //initial start time
}

int timeDelay(int ms) {
  currentMillis = millis();
  if (currentMillis - startMillis >= ms)
    {
      startMillis = currentMillis;
      return 1;
    } else {
      return 0;
    }
}

void loop()
{
  if (timeDelay(500) == 1){
    digitalWrite(ledPin, !digitalRead(ledPin));  //if so, change the state of the LED.  Uses a neat trick to change the state
  }
  
}
