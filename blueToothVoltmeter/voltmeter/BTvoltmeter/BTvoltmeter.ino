/*
 * DC voltmeter with bluetooht 
 */


// na hornim PC je to arduino NANO na COM6

const int analogInput_1ch = 0;      //cislo analogoveho vstupu 1. kanalu
const int analogInput_2ch = 1;      //cislo analogoveho vstupu 2. kanalu

float vout = 0.0;                   //z bit. prevedene napeti
float vin = 0.0;                    //spocitane napeti z delice napeti
float vin_1ch = 0.0;                //spocitane napeti z delice napeti 1. kanalu
float R1_1ch = 98800.0;             //hodnota 100kOhm odporu delice napeti 1. kanalu
float R2_1ch = 9920.0;              //hodnota 10kOhm odporu delice napeti 1. kanalu
int value_1ch = 0;                  //bit. hodnota napeti z analogoveho vstupu arduino z 1. kanalu
float offset_1ch = 0.946;           //offset 1. kanalu dany merenim napeti multimetrem
int arr_value_1ch[] = {0,0,0,0,0,0,0,0,0,0}; //pole na prumerovani vysledku mereni z deseti vzorku
long sum;                           //suma ze souctu hodnot ve vzorkach 
int shiftNo = 0;                    //pomocna promenna pro postupne vycitani z pole

unsigned long previousMillis = 0;   //promenna pro cas
const long interval = 1;            //promenna pro cas
int setiny = 0;                     //promenna pro cas
int setiny_x10 = 0;                 //promenna pro cas



void setup() {
  Serial.begin(115200);
  Serial.println("Run ..."); 
  pinMode(analogInput_1ch, INPUT);
}

float countVolage(int sumOfSamples) {
  vout = (((sumOfSamples / 10.0) * 5.0) / 1024.0);
  vin = vout / (R2_1ch/(R1_1ch+R2_1ch));
  /*if (vin_1ch < 0.09) {
    vin_1ch = 0.0;
  }*/
  //vin += offset_1ch;
  vin *= offset_1ch;
  return(vin);
}

void loop() {
  unsigned long currentMillis = millis(); //milisekundy od spusteni arduina
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    setiny += 1;
    setiny_x10 += 1;
  }

  if (setiny == 10) {   //ziskani deseti vzorku a ulozeni do pole na zprumerovani
    arr_value_1ch[shiftNo] = analogRead(analogInput_1ch);
    shiftNo += 1;
    if (shiftNo == 10) {
      shiftNo = 0;
    }
    setiny = 0;
  }


  if (setiny_x10 == 100) { //vypocet napeti z prumeru sumy a 
    Serial.print("Channel No. 1: ");
    for (int i = 0; i<10; i++) {
      sum += arr_value_1ch[i];
    }
    //value_1ch /= 10.0;
    vin_1ch = countVolage(sum);
    Serial.println(vin_1ch);
    setiny_x10 = 0;
    sum = 0;
  }


  
  
}
