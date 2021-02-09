int melody_tetris[] = {
  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,

  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,

  NOTE_E5,2,   NOTE_C5,2,
  NOTE_D5,2,   NOTE_B4,2,
  NOTE_C5,2,   NOTE_A4,2,
  NOTE_GS4,2,  NOTE_B4,4,  REST,8, 
  NOTE_E5,2,   NOTE_C5,2,
  NOTE_D5,2,   NOTE_B4,2,
  NOTE_C5,4,   NOTE_E5,4,  NOTE_A5,2,
  NOTE_GS5,2,
};
/*
 *vsechno je stazeno z: https://github.com/robsoncouto/arduino-songs 
*/

int melody_vampireKiller[] = {
  // Vamire Killer, from castlevania
  // Score available at https://musescore.com/user/28972071/scores/5425616
  // Theme starts at measure 6

  NOTE_E5,16, NOTE_E5,8, NOTE_D5,16, REST,16, NOTE_CS5,-4, NOTE_E4,8, NOTE_FS4,16, NOTE_G4,16, NOTE_A4,16,
  
  NOTE_B4,-8, NOTE_E4,-8, NOTE_B4,8, NOTE_A4,16, NOTE_D5,-4, //7
  NOTE_E5,16, NOTE_E5,8, NOTE_D5,16, REST,16, NOTE_CS5,-4, NOTE_E4,8, NOTE_FS4,16, NOTE_G4,16, NOTE_A4,16,
  NOTE_B4,-8, NOTE_E4,-8, NOTE_B4,8, NOTE_A4,16, NOTE_D4,-4,
  REST,8, NOTE_E5,8, REST,16, NOTE_B5,16, REST,8, NOTE_AS5,16, NOTE_B5,16, NOTE_AS5,16, NOTE_G5,16, REST,4,

  NOTE_B5,8, NOTE_B5,16, NOTE_AS5,16, REST,16, NOTE_AS5,16, NOTE_A5,16, REST,16, NOTE_B5,16, NOTE_G5,16, NOTE_B5,16, NOTE_AS5,16, REST,16, NOTE_B5,16, NOTE_A5,16, NOTE_G5,16,//11
  REST,8, NOTE_E5,8, REST,16, NOTE_B5,16, REST,8, NOTE_AS5,16, NOTE_B5,16, NOTE_AS5,16, NOTE_G5,16, REST,4,
  NOTE_B5,8, NOTE_B5,16, NOTE_AS5,16, REST,16, NOTE_AS5,16, NOTE_A5,16, REST,16, NOTE_B5,16, NOTE_G5,16, NOTE_B5,16, NOTE_AS5,16, REST,16, NOTE_B5,16, NOTE_A5,16, NOTE_G5,16,

  NOTE_DS4,-8, NOTE_FS4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_G4,-8, NOTE_E4,8, //14
  NOTE_DS4,-8, NOTE_FS4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_G4,-8, REST,8,
  NOTE_DS4,-8, NOTE_FS4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_G4,-8, NOTE_E4,8,
  NOTE_DS4,-8, NOTE_FS4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_CS5,-8, NOTE_DS5,8,

  NOTE_E5,16, NOTE_E5,16, NOTE_E4,16, NOTE_E4,-2,//18
  NOTE_C4,8, NOTE_C4,8, NOTE_E4,16, NOTE_G4,-8, NOTE_D4,8, NOTE_D4,8, NOTE_FS4,16, NOTE_A4,-8,
  NOTE_E5,16, NOTE_E5,16, NOTE_E4,16, NOTE_E4,-2,
  NOTE_C4,8, NOTE_C4,8, NOTE_E4,16, NOTE_G4,-8, NOTE_D4,8, NOTE_D4,8, NOTE_B3,16, NOTE_D4,-8,

  //repeats a second time

  NOTE_E5,16, NOTE_E5,8, NOTE_D5,16, REST,16, NOTE_CS5,-4, NOTE_E4,8, NOTE_FS4,16, NOTE_G4,16, NOTE_A4,16,
  
  NOTE_B4,-8, NOTE_E4,-8, NOTE_B4,8, NOTE_A4,16, NOTE_D5,-4, //7
  NOTE_E5,16, NOTE_E5,8, NOTE_D5,16, REST,16, NOTE_CS5,-4, NOTE_E4,8, NOTE_FS4,16, NOTE_G4,16, NOTE_A4,16,
  NOTE_B4,-8, NOTE_E4,-8, NOTE_B4,8, NOTE_A4,16, NOTE_D4,-4,
  REST,8, NOTE_E5,8, REST,16, NOTE_B5,16, REST,8, NOTE_AS5,16, NOTE_B5,16, NOTE_AS5,16, NOTE_G5,16, REST,4,

  NOTE_B5,8, NOTE_B5,16, NOTE_AS5,16, REST,16, NOTE_AS5,16, NOTE_A5,16, REST,16, NOTE_B5,16, NOTE_G5,16, NOTE_B5,16, NOTE_AS5,16, REST,16, NOTE_B5,16, NOTE_A5,16, NOTE_G5,16,//11
  REST,8, NOTE_E5,8, REST,16, NOTE_B5,16, REST,8, NOTE_AS5,16, NOTE_B5,16, NOTE_AS5,16, NOTE_G5,16, REST,4,
  NOTE_B5,8, NOTE_B5,16, NOTE_AS5,16, REST,16, NOTE_AS5,16, NOTE_A5,16, REST,16, NOTE_B5,16, NOTE_G5,16, NOTE_B5,16, NOTE_AS5,16, REST,16, NOTE_B5,16, NOTE_A5,16, NOTE_G5,16,

  NOTE_DS4,-8, NOTE_FS4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_G4,-8, NOTE_E4,8, //14
  NOTE_DS4,-8, NOTE_FS4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_G4,-8, REST,8,
  NOTE_DS4,-8, NOTE_FS4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_G4,-8, NOTE_E4,8,
  NOTE_DS4,-8, NOTE_FS4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_CS5,-8, NOTE_DS5,8,

  NOTE_E5,16, NOTE_E5,16, NOTE_E4,16, NOTE_E4,-2,//18
  NOTE_C4,8, NOTE_C4,8, NOTE_E4,16, NOTE_G4,-8, NOTE_D4,8, NOTE_D4,8, NOTE_FS4,16, NOTE_A4,-8,
  NOTE_E5,16, NOTE_E5,16, NOTE_E4,16, NOTE_E4,-2,
  NOTE_C4,8, NOTE_C4,8, NOTE_E4,16, NOTE_G4,-8, NOTE_D4,8, NOTE_D4,8, NOTE_B3,16, NOTE_D4,-8,
};

int melody_godfather[] = {
  // The Godfather theme
  // Score available at https://musescore.com/user/35463/scores/55160
  REST, 4, REST, 8, REST, 8, REST, 8, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8, //1
  NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, NOTE_G4, 8,
  NOTE_E4, 2, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8,
  NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_E4, 8, NOTE_DS4, 8,
  
  NOTE_D4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8, //5
  NOTE_B4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8,
  NOTE_A4, 2, NOTE_C4, 8, NOTE_C4, 8, NOTE_G4, 8, 
  NOTE_F4, 8, NOTE_E4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_E4, 8, NOTE_GS4, 8,

  NOTE_A4, 2, REST,8, NOTE_A4, 8, NOTE_A4, 8, NOTE_GS4, 8, //9
  NOTE_G4, 2, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, 
  NOTE_E4, 2, NOTE_E4, 8, NOTE_G4, 8, NOTE_E4, 8,
  NOTE_D4, 2, NOTE_D4, 8, NOTE_D4, 8, NOTE_F4, 8, NOTE_DS4, 8, 
   
  NOTE_E4, 2, REST, 8, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8, //13

  //repeats from 2
  NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, NOTE_G4, 8, //2
  NOTE_E4, 2, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8,
  NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_E4, 8, NOTE_DS4, 8,
  
  NOTE_D4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8, //5
  NOTE_B4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8,
  NOTE_A4, 2, NOTE_C4, 8, NOTE_C4, 8, NOTE_G4, 8, 
  NOTE_F4, 8, NOTE_E4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_E4, 8, NOTE_GS4, 8,

  NOTE_A4, 2, REST,8, NOTE_A4, 8, NOTE_A4, 8, NOTE_GS4, 8, //9
  NOTE_G4, 2, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, 
  NOTE_E4, 2, NOTE_E4, 8, NOTE_G4, 8, NOTE_E4, 8,
  NOTE_D4, 2, NOTE_D4, 8, NOTE_D4, 8, NOTE_F4, 8, NOTE_DS4, 8, 
   
  NOTE_E4, 2 //13
};

int melody_newRecord[] = {
  NOTE_E4, 8, NOTE_E4, 8, NOTE_G4, 4
};  

int melody_almost1[] = {
  NOTE_A4, 8
};  
