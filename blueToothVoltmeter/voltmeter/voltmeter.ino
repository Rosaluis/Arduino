/*
 * DC voltmeter with bluetooht 
 */
// na hornim PC je to arduino NANO na COM6

/* Definice struktur ********************************************************************************************* */
typedef struct 
{
  float vin;                        //spocitane napeti z delice napeti
  float R1;                         //hodnota 100kOhm odporu delice napeti
  float R2;                         //hodnota 10kOhm odporu delice napeti
  int value;                        //bit. hodnota napeti z analogoveho vstupu arduino
  float offset;                     //offset kanalu dany merenim napeti multimetrem
  int arr_value[10];                //pole na prumerovani vysledku mereni z deseti vzorku
  long sum;                         //suma ze souctu hodnot ve vzorkach
  long sumKalib;                    //pomocna suma ze souctu hodnot ve vzorkach 1. kanalu pro porovnani s 2. kanalem
} channel;                          //struktura channel pro praci s analogovym okruhem zarizeni



const int analogInput_1ch = 0;      //cislo analogoveho vstupu 1. kanalu
const int analogInput_2ch = 1;      //cislo analogoveho vstupu 2. kanalu
const int btnCalibInput = 2;        //cislo digitalniho vstupu pro tlacitko na kalibraci 2. kanalu k 1. kanalu
const int ledBlue = 5;              //cislo digitalniho vystupu pro modrou LEDku

int diffOfChannels = 0;             //rozdil 2. kanalu od 1. kanalu pro kalibraci

float vout = 0.0;                   //z bit. prevedene napeti
float vin = 0.0;                    //spocitane napeti z delice napeti
int shiftNo = 0;                    //pomocna promenna pro postupne vycitani z pole
unsigned long previousMillis = 0;   //promenna pro cas
unsigned long  prevMls = 0;
const long interval = 1;            //promenna pro cas
int setiny = 0;                     //promenna pro cas
int setiny_x10 = 0;                 //promenna pro cas
int setiny_x100 = 0;                 //promenna pro cas

int btnCalibInputState = LOW;         //status tlacitka

channel ch1;                        //vytvoreni promenne ch1, ktera je typ: struktura channel
channel ch2;                        //vytvoreni promenne ch1, ktera je typ: struktura channel

void setup() {
  ch1.R1 = 98800.0;                   //hodnota 100kOhm odporu delice napeti 1. kanalu
  ch1.R2 = 9920.0;                    //hodnota 10kOhm odporu delice napeti 1. kanalu
  ch1.offset = 1.064;             //offset 1. kanalu dany merenim napeti multimetrem
  
  ch2.R1 = 99150.0;                   //hodnota 100kOhm odporu delice napeti 2. kanalu
  ch2.R2 = 9900.0;                    //hodnota 10kOhm odporu delice napeti 2. kanalu
  ch2.offset = 1.065;                 //offset 2. kanalu dany merenim napeti multimetrem
  
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
    vin = vout / (ch1.R2/(ch1.R1 + ch2.R2));
  } else if (channel == 2) {
    vin = vout / (ch2.R2/(ch2.R1 + ch2.R2));
  } else {
    vin = 666;
  }
  return(vin);
}

void kalibChannels() {
  
  digitalWrite(ledBlue, HIGH);
  Serial.println(ch1.sumKalib);
  Serial.println(ch2.sumKalib);
  diffOfChannels = ch1.sumKalib - ch2.sumKalib;
  Serial.println(diffOfChannels);
  Serial.println("kalibrovano");
  delay(1000);
  digitalWrite(ledBlue, LOW);
  
}

void loop() {
  btnCalibInputState = digitalRead(btnCalibInput);
  
  unsigned long currentMillis = millis();             //milisekundy od spusteni arduina
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    setiny += 1;
    setiny_x10 += 1;
    setiny_x100 += 1;
  }

  

  if (setiny == 10) {                 //ziskani deseti vzorku a ulozeni do pole na zprumerovani
    ch1.arr_value[shiftNo] = analogRead(analogInput_1ch);
    ch2.arr_value[shiftNo] = analogRead(analogInput_2ch);
    shiftNo += 1;
    if (shiftNo == 10) {
      shiftNo = 0;
    }
    setiny = 0;
  }


  if (setiny_x10 == 1000) { //vypocet napeti z prumeru sumy a 
    Serial.print("Channel No. 1: ");
    for (int i = 0; i<10; i++) {
      ch1.sum += ch1.arr_value[i];
    }
    ch1.vin = countVolage(ch1.sum, 1) * ch1.offset;
    Serial.println(ch2.vin);
    ch1.sumKalib = ch1.sum;
    ch1.sum = 0;

    Serial.print("Channel No. 2: ");
    for (int i = 0; i<10; i++) {
      ch2.sum += ch2.arr_value[i];
    }
    ch2.vin = countVolage(ch2.sum, 2) * ch2.offset;
    Serial.println(ch2.vin);
    ch2.sumKalib = ch2.sum;
    ch2.sum = 0;
    
    setiny_x10 = 0;
  }
  
  //pokud je tlacitko kalibrace 2. kanalu na 1. kanal drzeno > 1s.
  if (btnCalibInputState == HIGH) {
    if (setiny_x100 - prevMls >= 1000) {
      prevMls = setiny_x100;
      kalibChannels();                  //zavolej funkci na kalibraci  
    }
  } else {
    setiny_x100 = 0;                    //vynulovani promennych aby musela pred volanim fce kalibChannels()
    prevMls = 0;                        //zase tlacitko drzeno 
  }
  
}
