/*
 * DC voltmeter with bluetooht 
 */


// na hornim PC je to arduino NANO na COM6

const int analogInput_1ch = 0;      //cislo analogoveho vstupu 1. kanalu
const int analogInput_2ch = 1;      //cislo analogoveho vstupu 2. kanalu
const int btnCalibInput = 2;        //cislo digitalniho vstupu pro tlacitko na kalibraci 2. kanalu k 1. kanalu
const int ledBlue = 5;              //cislo digitalniho vystupu pro modrou LEDku

float vin_1ch = 0.0;                //spocitane napeti z delice napeti 1. kanalu
float R1_1ch = 98800.0;             //hodnota 100kOhm odporu delice napeti 1. kanalu
float R2_1ch = 9920.0;              //hodnota 10kOhm odporu delice napeti 1. kanalu
int value_1ch = 0;                  //bit. hodnota napeti z analogoveho vstupu arduino z 1. kanalu
float offset_1ch = 1.064;           //offset 1. kanalu dany merenim napeti multimetrem
int arr_value_1ch[] = {0,0,0,0,0,0,0,0,0,0}; //pole na prumerovani vysledku mereni z deseti vzorku

float vin_2ch = 0.0;                //spocitane napeti z delice napeti 2. kanalu
float R1_2ch = 99150.0;             //hodnota 100kOhm odporu delice napeti 2. kanalu
float R2_2ch = 9900.0;              //hodnota 10kOhm odporu delice napeti 2. kanalu
int value_2ch = 0;                  //bit. hodnota napeti z analogoveho vstupu arduino z 2. kanalu
float offset_2ch = 1.065;           //offset 2. kanalu dany merenim napeti multimetrem
int arr_value_2ch[] = {0,0,0,0,0,0,0,0,0,0}; //pole na prumerovani vysledku mereni z deseti vzorku

float vout = 0.0;                   //z bit. prevedene napeti
float vin = 0.0;                    //spocitane napeti z delice napeti
long sum;                           //suma ze souctu hodnot ve vzorkach 
int shiftNo = 0;                    //pomocna promenna pro postupne vycitani z pole

unsigned long previousMillis = 0;   //promenna pro cas
const long interval = 1;            //promenna pro cas
int setiny = 0;                     //promenna pro cas
int setiny_x10 = 0;                 //promenna pro cas

int btnCalibInputState = 0;         //status tlacitka

void setup() {
  Serial.begin(115200);
  Serial.println("Run ..."); 
  pinMode(analogInput_1ch, INPUT);
  pinMode(btnCalibInput, INPUT);
  pinMode(ledBlue, OUTPUT);
  analogReference(INTERNAL);        //interni reference 1.1V pro presnejsi mereni anal. vstupu
}

float countVolage(int sumOfSamples, int channel) {
  vout = ((sumOfSamples / 10.0) / 1024.0);
  if (channel == 1) {
    vin = vout / (R2_1ch/(R1_1ch+R2_1ch));
  } else if (channel == 2) {
    vin = vout / (R2_2ch/(R1_2ch+R2_2ch));
  } else {
    vin = 666;
  }
  return(vin);
}

void loop() {
  btnCalibInputState = digitalRead(btnCalibInput);
  
  unsigned long currentMillis = millis(); //milisekundy od spusteni arduina
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    setiny += 1;
    setiny_x10 += 1;
  }

  if (setiny == 10) {   //ziskani deseti vzorku a ulozeni do pole na zprumerovani
    arr_value_1ch[shiftNo] = analogRead(analogInput_1ch);
    arr_value_2ch[shiftNo] = analogRead(analogInput_2ch);
    shiftNo += 1;
    if (shiftNo == 10) {
      shiftNo = 0;
    }
    setiny = 0;
  }


  if (setiny_x10 == 1000) { //vypocet napeti z prumeru sumy a 
    Serial.print("Channel No. 1: ");
    for (int i = 0; i<10; i++) {
      sum += arr_value_1ch[i];
    }
    vin_1ch = countVolage(sum, 1) * offset_1ch;
    Serial.println(vin_1ch);
    sum = 0;

    Serial.print("Channel No. 2: ");
    for (int i = 0; i<10; i++) {
      sum += arr_value_2ch[i];
    }
    vin_2ch = countVolage(sum, 2) * offset_2ch;
    Serial.println(vin_2ch);
    sum = 0;
    
    setiny_x10 = 0;
  }

  if (btnCalibInputState == HIGH) {
    digitalWrite(ledBlue, HIGH);
  } else {
    digitalWrite(ledBlue, LOW);
  }

  
  
}
