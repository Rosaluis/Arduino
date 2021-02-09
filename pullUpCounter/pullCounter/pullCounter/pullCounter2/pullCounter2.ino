#include "HX711.h"
#include <EEPROM.h>
#include "pitches.h"                          // vysky tomu pro piezo
#include "melodies.h"                         // melodie pisnicek
#include "U8glib.h"                           // knihovna pro displaj
HX711 scale;

unsigned long startMillis100;                 //some global variables available anywhere in the program
unsigned long startMillis500;
unsigned long startMillis1000;
unsigned long currentMillis;
const unsigned long period = 1000;            //the value is a number of milliseconds
const byte rstBtnPin = 2;                     // tlacitko na reset pocitadla v eeprom
int rstBtnState = 0;
const byte piezoPin = 3;
U8GLIB_SH1106_128X64_2X mujOled(U8G_I2C_OPT_NO_ACK);    // inicializace OLED displeje z knihovny U8glib
long int prepis = 0;                          // proměnná pro uchování času poslední obnovy displeje

/* Definice struktur ********************************************************************************************* */

typedef struct
{
  unsigned long maxT = 0;
  unsigned long actT = 0;
  unsigned long eepromMaxT = 0;
} timeVars;


typedef struct
{
  const byte ledPin = 13;           //using the built in LED
  const byte ledBlue = 11;          // blue LED
} ledsVars;

typedef struct
  {
  uint8_t dataPin = 6;              // tenzometr
  uint8_t clockPin = 7;             // tenzometr
  float w1, w2, previous = 0;  
} tenzometerVars;

/* Definice struktur - konec ************************************************************************************* */

/* Deklarace promennych struktur ********************************************************************************* */
ledsVars ldsV;
tenzometerVars tzmV;
timeVars tmV;
/* Deklarace promennych struktur - konec ************************************************************************* */


void setup()
{
  Serial.begin(115200);                                 //start Serial in case we need to print debugging info
  pinMode(ldsV.ledPin, OUTPUT);
  pinMode(ldsV.ledBlue, OUTPUT);
  pinMode(rstBtnPin, INPUT);
  startMillis100 = millis();                            //100ms pauza pres counter
  startMillis500 = millis();                            //500ms
  startMillis1000 = millis();                           //1s
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION);                    // posle verzi knihovny HX711
  scale.begin(tzmV.dataPin, tzmV.clockPin);             // aktivovana vaha
  Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));
  scale.set_scale(200);                                 //muj odhat na 10kg
  scale.tare();
  pinMode(piezoPin, OUTPUT);
  // mujOled.setRot180();                               //otoceni displeje o 180 stupnu
  
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

int checkWeight() {
  if (timeDelay100()) {
    tzmV.w1 = abs(scale.get_units(2)); 
    //Serial.println(tzmV.w1);   
  }
  if (tzmV.w1 > 500) {                     // tohle pred nasazenim zvednout alespon na 2000
   Serial.print("w1: ");
   Serial.println(tzmV.w1);    
    return 1;
  } else {
    return 0;
  }
}

void melodyMaker(int melodyNr) {
  //melody_tetris - 1
  //melody_vampireKiller - 2
  //melody_godfather - 3
  //melody_newRecord - 4
  //melody_reset
  
  int wholenote = 0;
  int divider = 0, noteDuration = 0;
  int notes = 0, tempo = 0;
    
  switch (melodyNr) {
    case 1:
      tempo=144;
      wholenote = (60000 * 4) / tempo;
      notes = sizeof(melody_tetris)/sizeof(melody_tetris[0])/2;
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = melody_tetris[thisNote + 1];
        if (divider > 0) {
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }
        tone(piezoPin, melody_tetris[thisNote], noteDuration*0.9);
        delay(noteDuration);
      }
    break;

    case 2:
      tempo=130;
      wholenote = (60000 * 4) / tempo;
      notes = sizeof(melody_vampireKiller)/sizeof(melody_vampireKiller[0])/2;
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = melody_vampireKiller[thisNote + 1];
        if (divider > 0) {
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }
        tone(piezoPin, melody_vampireKiller[thisNote], noteDuration*0.9);
        delay(noteDuration);
      }
    break;

    case 3:
     tempo = 80;
     wholenote = (60000 * 4) / tempo;
     notes = sizeof(melody_godfather)/sizeof(melody_godfather[0])/2;
     for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
      divider = melody_godfather[thisNote + 1];
      if (divider > 0) {
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }
      tone(piezoPin, melody_godfather[thisNote], noteDuration*0.9);
      delay(noteDuration);
    }
    break;

    case 4:
     tempo = 120;
     wholenote = (60000 * 4) / tempo;
     notes = sizeof(melody_newRecord)/sizeof(melody_newRecord[0])/2;
     for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
      divider = melody_newRecord[thisNote + 1];
      if (divider > 0) {
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }
      tone(piezoPin, melody_newRecord[thisNote], noteDuration*0.9);
      delay(noteDuration);
    }
    break;

    case 5:
     tempo = 120;
     wholenote = (60000 * 4) / tempo;
     notes = sizeof(melody_reset)/sizeof(melody_reset[0])/2;
     for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
      divider = melody_reset[thisNote + 1];
      if (divider > 0) {
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }
      tone(piezoPin, melody_reset[thisNote], noteDuration*0.9);
      delay(noteDuration);
    }
    break;
  
  noTone(piezoPin);
  }
}

// read double word from EEPROM, give starting address
unsigned long EEPROM_readlong(int address)  {
  //use word read function for reading upper part
  unsigned long dword = EEPROM_readint(address);
  //shift read word up
  dword = dword << 16;
  // read lower word from EEPROM and OR it into double word
  dword = dword | EEPROM_readint(address+2);
  return dword;
}

//write word to EEPROM
void EEPROM_writeint(int address, int value) {
  EEPROM.write(address,highByte(value));
  EEPROM.write(address+1 ,lowByte(value));
}
 
 //write long integer into EEPROM
void EEPROM_writelong(int address, unsigned long value) {
  //truncate upper part and write lower part into EEPROM
  EEPROM_writeint(address+2, word(value));
  //shift upper part down
  value = value >> 16;
  //truncate and write
  EEPROM_writeint(address, word(value));
}

unsigned int EEPROM_readint(int address) {
  unsigned int word = word(EEPROM.read(address), EEPROM.read(address+1));
  return word;
}


int vykresli(int maxT, int actT) {                     // funkce vykresli pro nastavení výpisu informací na OLED
  mujOled.setFont(u8g_font_ncenB18); 
  mujOled.setPrintPos(10, 25);
  mujOled.print("max: ");
  mujOled.setPrintPos(80, 25);
  mujOled.print(maxT);
  mujOled.setPrintPos(45, 55);
  mujOled.print(actT);
}
  
void loop()
{
  /*
  if (timeDelay500()){
    digitalWrite(lds.ledPin, !digitalRead(lds.ledPin));  //if so, change the state of the LED.  Uses a neat trick to change the state
  */

/*
 * EEPROM_writelong(0x00, 4294967295); //write unsigned long number u want

storage = EEPROM_readlong(0x00); //read it and put it in our newly created unsigned long variable

 */
  rstBtnState = digitalRead(rstBtnPin);
  tmV.maxT = EEPROM_readlong(0x00);

  if(rstBtnState == HIGH) {
    melodyMaker(5);
    digitalWrite(ldsV.ledPin, HIGH);
    if(timeDelay500()) {
     EEPROM_writelong(0x00, 0);
     vykresli(0, tmV.actT);
    }
  } else {
    digitalWrite(ldsV.ledPin, LOW);
  }

   if (millis()-prepis > 100) {                           // porovnání uloženého a aktuálního času pro prepis displeje
    mujOled.firstPage();
    do {
      vykresli(tmV.maxT, tmV.actT);                      // funkce vykresli vykreslí žádaný obsah
    } while( mujOled.nextPage() );
    prepis = millis();                                    // uložení posledního času obnovení
  }

  
  if (checkWeight()) {
    digitalWrite(ldsV.ledBlue, HIGH);
    //tmV.maxT = EEPROM_readlong(0x00);
    Serial.print("saved maxT: ");
    Serial.println(tmV.maxT);
    
    if (timeDelay1000()) {
      tmV.actT += 1;
      Serial.println(tmV.actT);
      vykresli(tmV.maxT, tmV.actT);
    }

    if (tmV.actT > tmV.maxT) {
      Serial.print("new max time: ");
      Serial.println(tmV.actT);
      tmV.maxT = tmV.actT;
      EEPROM_writelong(0x00, tmV.maxT);
      melodyMaker(4);
    }

    
  } else {
    digitalWrite(ldsV.ledBlue, LOW);
    tmV.actT = 0;
  }
}
