/*
 * DC voltmeter with bluetooht 
 */
// na hornim PC je to arduino NANO na COM6

/* Definice struktur ********************************************************************************************* */
typedef struct 
{
  float vin;                          //spocitane napeti z delice napeti
  float R1;                           //hodnota 100kOhm odporu delice napeti
  float R2;                           //hodnota 10kOhm odporu delice napeti
  int value;                          //bit. hodnota napeti z analogoveho vstupu arduino
  float offset;                       //offset kanalu dany merenim napeti multimetrem
  int arr_value[10];                  //pole na prumerovani vysledku mereni z deseti vzorku
  long sum;                           //suma ze souctu hodnot ve vzorkach
  long sumKalib;                      //pomocna suma ze souctu hodnot ve vzorkach 1. kanalu pro porovnani s 2. kanalem
} channel;                            //struktura channel pro praci s analogovym okruhem zarizeni

typedef struct
{
  const int analogInput_1ch = 0;      //cislo analogoveho vstupu 1. kanalu
  const int analogInput_2ch = 1;      //cislo analogoveho vstupu 2. kanalu
  const int btnCalibInput = 2;        //cislo digitalniho vstupu pro tlacitko na kalibraci 2. kanalu k 1. kanalu
  const int ledBlue = 5;              //cislo digitalniho vystupu pro modrou LEDku
} pinOfArdu;

typedef struct
{
  int diffOfChannels;                 //rozdil 2. kanalu od 1. kanalu pro kalibraci
  float vout;                         //z bit. prevedene napeti
  float vin;                          //spocitane napeti z delice napeti
  int shiftNo;                        //pomocna promenna pro postupne vycitani z pole
  unsigned long previousMillis;       //promenna pro cas
  unsigned long  prevMls;
  int interval;                       //promenna pro cas
  int setiny;                         //promenna pro cas
  int setiny_x10;                     //promenna pro cas
  int setiny_x100;                    //promenna pro cas
  int btnCalibInputState;             //status tlacitka
} vars;
/* Definice struktur - konec ************************************************************************************* */


channel ch1;                          //vytvoreni promenne ch1, ktera je typ: struktura channel
channel ch2;                          //vytvoreni promenne ch1, ktera je typ: struktura channel
pinOfArdu pofa;                       //vytvoreni promenne pofa, ktera je typ: struktura pinOfArdu
vars var;                             //vytvoreni promenne var, ktera je typ: struktura vars

void setup() {
  ch1.R1 = 98800.0;                   //hodnota 100kOhm odporu delice napeti 1. kanalu
  ch1.R2 = 9920.0;                    //hodnota 10kOhm odporu delice napeti 1. kanalu
  ch1.offset = 1.064;                 //offset 1. kanalu dany merenim napeti multimetrem
  ch2.R1 = 99150.0;                   //hodnota 100kOhm odporu delice napeti 2. kanalu
  ch2.R2 = 9900.0;                    //hodnota 10kOhm odporu delice napeti 2. kanalu
  ch2.offset = 1.065;                 //offset 2. kanalu dany merenim napeti multimetrem
  var.diffOfChannels = 0;             //rozdil 2. kanalu od 1. kanalu pro kalibraci
  var.vout = 0.0;                     //z bit. prevedene napeti
  var.vin = 0.0;                      //spocitane napeti z delice napeti
  var.shiftNo = 0;                    //pomocna promenna pro postupne vycitani z pole
  var.previousMillis = 0;             //promenna pro cas cyklu mereni
  var.prevMls = 0;                    //promenna pro cas drzeni tlacitka
  var.interval = 1;                   //promenna pro cas tisicin sekund
  var.setiny = 0;                     //promenna pro cas cyklu jednoho mereni
  var.setiny_x10 = 0;                 //promenna pro cas cyklu zprumerovani deseti mereni
  var.setiny_x100 = 0;                //promenna pro cas cyklu drzeni tlacitka kalibrace
  var.btnCalibInputState = LOW;       //status tlacitka kalibrace

  
  Serial.begin(115200);
  Serial.println("Run ..."); 
  pinMode(pofa.analogInput_1ch, INPUT);
  pinMode(pofa.analogInput_2ch, INPUT);
  pinMode(pofa.btnCalibInput, INPUT);
  pinMode(pofa.ledBlue, OUTPUT);
  analogReference(INTERNAL);          //interni reference 1.1V pro presnejsi mereni anal. vstupu
}

float countVolage(int sumOfSamples, int channel) {
  var.vout = ((sumOfSamples / 10.0) / 1024.0);
  if (channel == 1) {
    var.vin = var.vout / (ch1.R2/(ch1.R1 + ch2.R2));
  } else if (channel == 2) {
    var.vin = var.vout / (ch2.R2/(ch2.R1 + ch2.R2));
  } else {
    var.vin = 666;
  }
  return(var.vin);
}

void kalibChannels() {
  
  digitalWrite(pofa.ledBlue, HIGH);
  Serial.println(ch1.sumKalib);
  Serial.println(ch2.sumKalib);
  var.diffOfChannels = ch1.sumKalib - ch2.sumKalib;
  Serial.println(var.diffOfChannels);
  Serial.println("kalibrovano");
  delay(1000);
  digitalWrite(pofa.ledBlue, LOW);
  
}

void loop() {
  var.btnCalibInputState = digitalRead(pofa.btnCalibInput);
  
  unsigned long currentMillis = millis();             //milisekundy od spusteni arduina
  if (currentMillis - var.previousMillis >= var.interval) {
    var.previousMillis = currentMillis;
    var.setiny += 1;
    var.setiny_x10 += 1;
    var.setiny_x100 += 1;
  }

  

  if (var.setiny == 10) {                 //ziskani deseti vzorku a ulozeni do pole na zprumerovani
    ch1.arr_value[var.shiftNo] = analogRead(pofa.analogInput_1ch);
    ch2.arr_value[var.shiftNo] = analogRead(pofa.analogInput_2ch);
    var.shiftNo += 1;
    if (var.shiftNo == 10) {
      var.shiftNo = 0;
    }
    var.setiny = 0;
  }


  if (var.setiny_x10 == 1000) { //vypocet napeti z prumeru sumy a 
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
    
    var.setiny_x10 = 0;
  }
  
  //pokud je tlacitko kalibrace 2. kanalu na 1. kanal drzeno > 1s.
  if (var.btnCalibInputState == HIGH) {
    if (var.setiny_x100 - var.prevMls >= 1000) {
      var.prevMls = var.setiny_x100;
      kalibChannels();                  //zavolej funkci na kalibraci  
    }
  } else {
    var.setiny_x100 = 0;                    //vynulovani promennych aby musela pred volanim fce kalibChannels()
    var.prevMls = 0;                        //zase tlacitko drzeno 
  }
}
