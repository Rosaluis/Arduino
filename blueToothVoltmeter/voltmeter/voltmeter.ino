/*
 * DC voltmeter with bluetooht 
 */

const int analogInput1ch = 0;
const int analogInput2ch = 0;

float vout1ch = 0.0;
float vin1ch = 0.0;
float R11ch = 100000.0;
float R21ch = 10000.0;
int value1ch = 0;

unsigned long previousMillis = 0;       // will store last time LED was updated
const long interval = 1000; 
int sekundy = 0;



void setup() {
  Serial.begin(115200);
  pinMode(analogInput1ch, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    sekundy += 1;
  }
  
  value1ch = analogRead(analogInput1ch);
  vout1ch = (value1ch * 5.0) / 1024.0;
  vin1ch = vout1ch / (R21ch/(R11ch+R21ch));
  if (vin1ch < 0.09) {
    vin1ch = 0.0;
  }

  
}
