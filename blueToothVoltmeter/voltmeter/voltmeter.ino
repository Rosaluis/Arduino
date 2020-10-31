/*
 * DC voltmeter with bluetooht 
 */


// na hornim PC je to arduino NANO na COM6

const int analogInput_1ch = 0;      //cislo analogoveho vstupu 1. kanalu
const int analogInput_2ch = 1;      //cislo analogoveho vstupu 2. kanalu

float vout_1ch = 0.0;               //z bit. prevedene napeti 1. kanalu 
float vin_1ch = 0.0;                //spocitane napeti 1. kanalu z delice napeti
float R1_1ch = 98800.0;             //hodnota 100kOhm odporu delice napeti 1. kanalu
float R2_1ch = 9920.0;              //hodnota 10kOhm odporu delice napeti 1. kanalu
int value_1ch = 0;                  //bit. hodnota napeti z analogoveho vstupu arduino z 1. kanalu
float offset_1ch = -0.21;           //offset 1. kanalu dany merenim napeti multimetrem

unsigned long previousMillis = 0;   //promenna pro cas
const long interval = 1;            //promenna pro cas
int setiny = 0;                     //promenna pro cas




void setup() {
  Serial.begin(115200);
  Serial.println("Run ..."); 
  pinMode(analogInput_1ch, INPUT);
}

void readChannel1() {
  value_1ch = analogRead(analogInput_1ch);
  vout_1ch = (value_1ch * 5.0) / 1024.0;
  vin_1ch = vout_1ch / (R2_1ch/(R1_1ch+R2_1ch));
  /*if (vin_1ch < 0.09) {
    vin_1ch = 0.0;
  }*/
  vin_1ch += offset_1ch;
  
  Serial.println(vin_1ch);
}

void loop() {
  unsigned long currentMillis = millis(); //milisekundy od spusteni arduina
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    setiny += 1;
  }

  if (setiny == 100) {
    setiny = 0;
    readChannel1();  
    Serial.println("+");
  }
  

  
  
}
