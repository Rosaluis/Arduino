// OLED displej přes I2C
// řadič SSD1306
/* https://navody.dratek.cz/navody-k-produktum/oled-displej-ssd1306.html */
/* https://github.com/olikraus/u8glib/wiki/fontsize */

// připojení knihovny U8glib
#include "U8glib.h"

// inicializace OLED displeje z knihovny U8glib
U8GLIB_SH1106_128X64_2X mujOled(U8G_I2C_OPT_NO_ACK);
// proměnná pro uchování času poslední obnovy displeje
long int prepis = 0;

void setup(void) {
  // pro otočení displeje o 180 stupňů
  // stačí odkomentovat řádek níže
  // mujOled.setRot180();
}

void loop(void) {
  // porovnání uloženého a aktuálního času
  // při rozdílu větším než 100 ms se provede
  // obnovení displeje, čas můžeme nastavit dle potřeby
  if (millis()-prepis > 100) {
    // následující skupina příkazů
    // obnoví obsah OLED displeje
    mujOled.firstPage();
    do {
      // funkce vykresli vykreslí žádaný obsah
      vykresli();
    } while( mujOled.nextPage() );
    // uložení posledního času obnovení
    prepis = millis();
  }
  
  // zde je místo pro další příkazy pro Arduino
  
  // volitelná pauza 10 ms pro demonstraci
  // vykonání dalších příkazů
  delay(10);
}
// funkce vykresli pro nastavení výpisu informací na OLED
void vykresli(void) {
  // nastavení písma, toto písmo umožní vypsat
  // přibližně 15x4 znaků
  //mujOled.setFont(u8g_font_unifont);
  mujOled.setFont(u8g_font_ncenB18);       /* jiny font */
  // nastavení pozice výpisu v pixelech
  // souřadnice jsou ve tvaru x, y
  // souřadnice 0, 0 je v levém horní rohu
  // OLED displeje, maximum je 128, 64
  //mujOled.setPrintPos(5, 10);
  // výpis textu na zadanou souřadnici
  /*
  mujOled.print("Arduino navody");
  mujOled.setPrintPos(5, 25);
  mujOled.print("dratek.cz");
  mujOled.setPrintPos(5, 40);
  mujOled.print("Cas od zapnuti:");
  mujOled.setPrintPos(40, 55);
  mujOled.print(millis()/1000);
  mujOled.print(" vterin");
  */

  mujOled.setPrintPos(10, 25);
  mujOled.print("max: ");
  mujOled.setPrintPos(80, 25);
  mujOled.print("999");
  mujOled.setPrintPos(45, 55);
  mujOled.print("999");

  
}
