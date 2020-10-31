/*
 * DC voltmeter with bluetooht 
 */


// na hornim PC je to arduino NANO na COM6

const int analogInput_1ch = 0;
const int analogInput_2ch = 0;

float vout_1ch = 0.0;      //z bit. prevedene napeti 1. kanalu 
float vin_1ch = 0.0;       //spocitane napeti 1. kanalu z delice napeti
float R1_1ch = 98800.0;    //hodnota 100kOhm odporu delice napeti
float R2_1ch = 9920.0;     //hodnota 10kOhm odporu delice napeti
int value_1ch = 0;         //bit. hodnota napeti z analogoveho vstupu arduino z 1. kanalu

unsigned long previousMillis = 0;       
const long interval = 100; 
int setiny = 0;



void setup() {
  Serial.begin(115200);
  pinMode(analogInput_1ch, INPUT);
}


void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    setiny += 1;
  }

  if (setiny == 10) {

  }
    
    value_1ch = analogRead(analogInput_1ch);
    vout_1ch = (value_1ch * 5.0) / 1024.0;
    vin_1ch = vout_1ch / (R2_1ch/(R1_1ch+R2_1ch));
    if (vin_1ch < 0.09) {
      vin_1ch = 0.0;
    }
    Serial.println(vin_1ch);
    setiny = 0;
  
  
  
}
