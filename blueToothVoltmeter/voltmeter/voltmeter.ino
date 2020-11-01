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
long sum_1ch = 0;                   //suma ze souctu hodnot ve vzorkach 1. kanalu
long sum_1chKalib = 0;              //pomocna suma ze souctu hodnot ve vzorkach 1. kanalu pro porovnani s 2. kanalem

float vin_2ch = 0.0;                //spocitane napeti z delice napeti 2. kanalu
float R1_2ch = 99150.0;             //hodnota 100kOhm odporu delice napeti 2. kanalu
float R2_2ch = 9900.0;              //hodnota 10kOhm odporu delice napeti 2. kanalu
int value_2ch = 0;                  //bit. hodnota napeti z analogoveho vstupu arduino z 2. kanalu
float offset_2ch = 1.065;           //offset 2. kanalu dany merenim napeti multimetrem
int arr_value_2ch[] = {0,0,0,0,0,0,0,0,0,0}; //pole na prumerovani vysledku mereni z deseti vzorku
long sum_2ch = 0;                   //suma ze souctu hodnot ve vzorkach 2. kanalu
long sum_2chKalib = 0;              //pomocna suma ze souctu hodnot ve vzorkach 2. kanalu pro porovnani s 1. kanalem

int diffOfChannels = 0;             //rozdil 2. kanalu od 1. kanalu pro kalibraci

float vout = 0.0;                   //z bit. prevedene napeti
float vin = 0.0;                    //spocitane napeti z delice napeti
int shiftNo = 0;                    //pomocna promenna pro postupne vycitani z pole
unsigned long previousMillis = 0;   //promenna pro cas
const long interval = 1;            //promenna pro cas
int setiny = 0;                     //promenna pro cas
int setiny_x10 = 0;                 //promenna pro cas
int current_x100 = 0;               //promenna pro cas stisknuteho tlacitka
int previous_x100 = 0;              //promenna pro cas stisknuteho tlacitka

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

void kalibChannels() {
  digitalWrite(ledBlue, HIGH);
  Serial.println(sum_1chKalib);
  Serial.println(sum_2chKalib);
}

void loop() {
  btnCalibInputState = digitalRead(btnCalibInput);
  
  unsigned long currentMillis = millis(); //milisekundy od spusteni arduina
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    setiny += 1;
    setiny_x10 += 1;
    current_x100 += 1;
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
      sum_1ch += arr_value_1ch[i];
    }
    vin_1ch = countVolage(sum_1ch, 1) * offset_1ch;
    Serial.println(vin_1ch);
    sum_1chKalib = sum_1ch;
    sum_1ch = 0;

    Serial.print("Channel No. 2: ");
    for (int i = 0; i<10; i++) {
      sum_2ch += arr_value_2ch[i];
    }
    vin_2ch = countVolage(sum_2ch, 2) * offset_2ch;
    Serial.println(vin_2ch);
    sum_2chKalib = sum_2ch;
    sum_2ch = 0;
    
    setiny_x10 = 0;
  }

  if (btnCalibInputState == HIGH) { //pokud je tlacitko kalibrace 2. kanalu na 1. kanal drzeno > 1s.
    if (current_x100 - previous_x100 >= 1000) {
      previous_x100 = current_x100;
      kalibChannels();              //zavolej funkci na kalibraci
    } 
  } else {
    current_x100 = 0;
  }

  
  
}
