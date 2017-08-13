#include "pitch.h"

static const unsigned int PROGMEM flapTone[] = {
  NOTE_A3, NOTE_GS3
};

static const unsigned int PROGMEM flapDuration[] = {
 16, 16
};

static const unsigned int PROGMEM pipeTone[] = {
  NOTE_B5, NOTE_E6, NOTE_0
};

static const unsigned int PROGMEM pipeDuration[] = {
 32, 8, 8
};

static const unsigned int PROGMEM failTone[] = {
   NOTE_B3, NOTE_C4, NOTE_C7, NOTE_B6, NOTE_A6, NOTE_G6, NOTE_F6,
   NOTE_E6, NOTE_D6, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_0
};

static const unsigned int PROGMEM failDuration[] = {
 16, 16, 16, 64, 64, 64, 64, 64, 64, 64, 64, 64, 8
};

static const unsigned int PROGMEM nyanChord[] = {
  NOTE_DS4, NOTE_E4,  NOTE_FS4, NOTE_B4,  NOTE_DS4, NOTE_E4, 
  NOTE_FS4, NOTE_B4,  NOTE_CS5, NOTE_DS5, NOTE_CS5, NOTE_AS4, 
  NOTE_B5
};

static const unsigned int PROGMEM nyanChordDuration[] = {
  8, 8, 4, 4, 8, 8, 
  8, 8, 8, 8, 8, 8, 
  4
};

static const unsigned int PROGMEM nyanChord1[] = {
  NOTE_DS5, NOTE_E5,  NOTE_FS5, NOTE_B5,  NOTE_DS5, NOTE_E5, 
  NOTE_FS5, NOTE_B5,  NOTE_CS6, NOTE_DS6, NOTE_CS6, NOTE_AS5, 
  NOTE_B5
};

static const unsigned int PROGMEM nyanTone[] = {
  NOTE_DS5, NOTE_E5,  NOTE_FS5, NOTE_B5,  NOTE_DS5, NOTE_E5, 
  NOTE_FS5, NOTE_B5,  NOTE_CS6, NOTE_DS6, NOTE_CS6, NOTE_AS5, 
  NOTE_B5,  
  NOTE_FS5, NOTE_DS5, NOTE_E5,  NOTE_FS5, NOTE_B5, 
  NOTE_CS6, NOTE_AS5, NOTE_B5,  NOTE_CS6, NOTE_E6,  
  NOTE_DS6, NOTE_E6,  NOTE_CS6,
  //Total of 26
  NOTE_FS5, NOTE_GS5, NOTE_DS5, NOTE_DS5,NOTE_0,NOTE_B4,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,NOTE_0,NOTE_B4,  NOTE_CS5,  NOTE_D5,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_DS5,  NOTE_FS5, NOTE_GS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_B4,  NOTE_CS5, 
  NOTE_B4,  NOTE_DS5, NOTE_FS5, NOTE_FS5,  NOTE_DS5, NOTE_FS5, 
  NOTE_CS5, NOTE_DS5, NOTE_B4,  NOTE_D5,   NOTE_DS5, NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_D5, NOTE_0,NOTE_B4,  NOTE_CS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_CS5, NOTE_B4, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5,
  //Total of 54
  NOTE_FS5, NOTE_GS5, NOTE_DS5, NOTE_DS5,NOTE_0,NOTE_B4,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,NOTE_0,NOTE_B4,  NOTE_CS5,  NOTE_D5,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_DS5,  NOTE_FS5, NOTE_GS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_B4,  NOTE_CS5, 
  NOTE_B4,  NOTE_DS5, NOTE_FS5, NOTE_FS5,  NOTE_DS5, NOTE_FS5, 
  NOTE_CS5, NOTE_DS5, NOTE_B4,  NOTE_D5,   NOTE_DS5, NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_D5, NOTE_0,NOTE_B4,  NOTE_CS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_CS5, NOTE_B4, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5,
  //Total of 54
  NOTE_B4, NOTE_FS4, NOTE_GS4, NOTE_B4, NOTE_FS4, NOTE_GS4, 
  NOTE_B4, NOTE_CS5, NOTE_DS5, NOTE_B4, NOTE_E5,  NOTE_DS5,
  NOTE_E5, NOTE_FS5, NOTE_B4,  NOTE_B4, NOTE_FS4, NOTE_GS4,
  NOTE_B4, NOTE_FS4, NOTE_E5,  NOTE_DS5,NOTE_CS5, NOTE_B4,
  NOTE_FS4,NOTE_DS4, NOTE_E4,  NOTE_FS4,NOTE_B4,  NOTE_FS4,
  NOTE_GS4,NOTE_B4,  NOTE_FS4, NOTE_GS4,NOTE_B4,  NOTE_B4,
  NOTE_CS5,NOTE_DS5, NOTE_B4,  NOTE_FS4,NOTE_GS4, NOTE_FS4,
  NOTE_B4, NOTE_B4,  NOTE_AS4, NOTE_B4, NOTE_FS4, NOTE_GS4,
  NOTE_B4, NOTE_E5,  NOTE_DS5, NOTE_E5, NOTE_FS6, NOTE_B4,
  NOTE_AS4,
  //Total of 55
  NOTE_B4, NOTE_FS4, NOTE_GS4, NOTE_B4, NOTE_FS4, NOTE_GS4, 
  NOTE_B4, NOTE_CS5, NOTE_DS5, NOTE_B4, NOTE_E5,  NOTE_DS5,
  NOTE_E5, NOTE_FS5, NOTE_B4,  NOTE_B4, NOTE_FS4, NOTE_GS4,
  NOTE_B4, NOTE_FS4, NOTE_E5,  NOTE_DS5,NOTE_CS5, NOTE_B4,
  NOTE_FS4,NOTE_DS4, NOTE_E4,  NOTE_FS4,NOTE_B4,  NOTE_FS4,
  NOTE_GS4,NOTE_B4,  NOTE_FS4, NOTE_GS4,NOTE_B4,  NOTE_B4,
  NOTE_CS5,NOTE_DS5, NOTE_B4,  NOTE_FS4,NOTE_GS4, NOTE_FS4,
  NOTE_B4, NOTE_B4,  NOTE_AS4, NOTE_B4, NOTE_FS4, NOTE_GS4,
  NOTE_B4, NOTE_E5,  NOTE_DS5, NOTE_E5, NOTE_FS6, NOTE_B4,
  NOTE_CS5,
  //Total of 55
  NOTE_FS5, NOTE_GS5, NOTE_DS5, NOTE_DS5,NOTE_0,NOTE_B4,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,NOTE_0,NOTE_B4,  NOTE_CS5,  NOTE_D5,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_DS5,  NOTE_FS5, NOTE_GS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_B4,  NOTE_CS5, 
  NOTE_B4,  NOTE_DS5, NOTE_FS5, NOTE_FS5,  NOTE_DS5, NOTE_FS5, 
  NOTE_CS5, NOTE_DS5, NOTE_B4,  NOTE_D5,   NOTE_DS5, NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_D5, NOTE_0,NOTE_B4,  NOTE_CS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_CS5, NOTE_B4, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5};

  

// note durations: 4 = quarter note, 8 = eighth note, etc.:
static const unsigned int PROGMEM nyanDuration[] = {
  8, 8, 4, 4, 8, 8, 
  8, 8, 8, 8, 8, 8, 
  4, 
  4, 8, 8, 4, 4, 
  8, 8, 8, 8, 8, 
  8, 8, 8,
  
  4, 4,  8, 8,8,8, 8, 
  8, 8,8,4, 4,  4, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,  8, 8,
  8, 4,  4, 8,  8, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,8,8, 8, 
  8, 8,  8, 8,  8, 8,
  4, 4,  4,
  
  4, 4,  8, 8,8,8, 8, 
  8, 8,8,4, 4,  4, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,  8, 8,
  8, 4,  4, 8,  8, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,8,8, 8, 
  8, 8,  8, 8,  8, 8,
  4, 4, 4,

  4, 8, 8, 4, 8, 8,
  8, 8, 8, 8, 8, 8,
  8, 8, 4, 4, 8, 8,
  8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 4, 8,
  8, 4, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 4,
  4,

  4, 8, 8, 4, 8, 8,
  8, 8, 8, 8, 8, 8,
  8, 8, 4, 4, 8, 8,
  8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 4, 8,
  8, 4, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 4,
  4,
  
  4, 4,  8, 8,8,8, 8, 
  8, 8,8,4, 4,  4, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,  8, 8,
  8, 4,  4, 8,  8, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,8,8, 8, 
  8, 8,  8, 8,  8, 8,
  4, 4,  4};
  
static const unsigned int PROGMEM melody[] = {
  NOTE_DS5, NOTE_E5,  NOTE_FS5, NOTE_B5,  NOTE_DS5, NOTE_E5, 
  NOTE_FS5, NOTE_B5,  NOTE_CS6, NOTE_DS6, NOTE_CS6, NOTE_AS5, 
  NOTE_B5,  
  NOTE_FS5, NOTE_DS5, NOTE_E5,  NOTE_FS5, NOTE_B5, 
  NOTE_CS6, NOTE_AS5, NOTE_B5,  NOTE_CS6, NOTE_E6,  
  NOTE_DS6, NOTE_E6,  NOTE_CS6,
  //Total of 26
  NOTE_FS5, NOTE_GS5, NOTE_DS5, NOTE_DS5,NOTE_0,NOTE_B4,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,NOTE_0,NOTE_B4,  NOTE_CS5,  NOTE_D5,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_DS5,  NOTE_FS5, NOTE_GS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_B4,  NOTE_CS5, 
  NOTE_B4,  NOTE_DS5, NOTE_FS5, NOTE_FS5,  NOTE_DS5, NOTE_FS5, 
  NOTE_CS5, NOTE_DS5, NOTE_B4,  NOTE_D5,   NOTE_DS5, NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_D5, NOTE_0,NOTE_B4,  NOTE_CS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_CS5, NOTE_B4, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5,
  //Total of 54
  NOTE_FS5, NOTE_GS5, NOTE_DS5, NOTE_DS5,NOTE_0,NOTE_B4,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,NOTE_0,NOTE_B4,  NOTE_CS5,  NOTE_D5,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_DS5,  NOTE_FS5, NOTE_GS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_B4,  NOTE_CS5, 
  NOTE_B4,  NOTE_DS5, NOTE_FS5, NOTE_FS5,  NOTE_DS5, NOTE_FS5, 
  NOTE_CS5, NOTE_DS5, NOTE_B4,  NOTE_D5,   NOTE_DS5, NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_D5, NOTE_0,NOTE_B4,  NOTE_CS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_CS5, NOTE_B4, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5,
  //Total of 54
  NOTE_B4, NOTE_FS4, NOTE_GS4, NOTE_B4, NOTE_FS4, NOTE_GS4, 
  NOTE_B4, NOTE_CS5, NOTE_DS5, NOTE_B4, NOTE_E5,  NOTE_DS5,
  NOTE_E5, NOTE_FS5, NOTE_B4,  NOTE_B4, NOTE_FS4, NOTE_GS4,
  NOTE_B4, NOTE_FS4, NOTE_E5,  NOTE_DS5,NOTE_CS5, NOTE_B4,
  NOTE_FS4,NOTE_DS4, NOTE_E4,  NOTE_FS4,NOTE_B4,  NOTE_FS4,
  NOTE_GS4,NOTE_B4,  NOTE_FS4, NOTE_GS4,NOTE_B4,  NOTE_B4,
  NOTE_CS5,NOTE_DS5, NOTE_B4,  NOTE_FS4,NOTE_GS4, NOTE_FS4,
  NOTE_B4, NOTE_B4,  NOTE_AS4, NOTE_B4, NOTE_FS4, NOTE_GS4,
  NOTE_B4, NOTE_E5,  NOTE_DS5, NOTE_E5, NOTE_FS6, NOTE_B4,
  NOTE_AS4,
  //Total of 55
  NOTE_B4, NOTE_FS4, NOTE_GS4, NOTE_B4, NOTE_FS4, NOTE_GS4, 
  NOTE_B4, NOTE_CS5, NOTE_DS5, NOTE_B4, NOTE_E5,  NOTE_DS5,
  NOTE_E5, NOTE_FS5, NOTE_B4,  NOTE_B4, NOTE_FS4, NOTE_GS4,
  NOTE_B4, NOTE_FS4, NOTE_E5,  NOTE_DS5,NOTE_CS5, NOTE_B4,
  NOTE_FS4,NOTE_DS4, NOTE_E4,  NOTE_FS4,NOTE_B4,  NOTE_FS4,
  NOTE_GS4,NOTE_B4,  NOTE_FS4, NOTE_GS4,NOTE_B4,  NOTE_B4,
  NOTE_CS5,NOTE_DS5, NOTE_B4,  NOTE_FS4,NOTE_GS4, NOTE_FS4,
  NOTE_B4, NOTE_B4,  NOTE_AS4, NOTE_B4, NOTE_FS4, NOTE_GS4,
  NOTE_B4, NOTE_E5,  NOTE_DS5, NOTE_E5, NOTE_FS6, NOTE_B4,
  NOTE_CS5,
  //Total of 55
  NOTE_FS5, NOTE_GS5, NOTE_DS5, NOTE_DS5,NOTE_0,NOTE_B4,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,NOTE_0,NOTE_B4,  NOTE_CS5,  NOTE_D5,  NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_DS5,  NOTE_FS5, NOTE_GS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_B4,  NOTE_CS5, 
  NOTE_B4,  NOTE_DS5, NOTE_FS5, NOTE_FS5,  NOTE_DS5, NOTE_FS5, 
  NOTE_CS5, NOTE_DS5, NOTE_B4,  NOTE_D5,   NOTE_DS5, NOTE_D5, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5, NOTE_D5, NOTE_0,NOTE_B4,  NOTE_CS5, 
  NOTE_DS5, NOTE_FS5, NOTE_CS5, NOTE_DS5,  NOTE_CS5, NOTE_B4, 
  NOTE_CS5, NOTE_B4,  NOTE_CS5};

  

// note durations: 4 = quarter note, 8 = eighth note, etc.:
static const unsigned int PROGMEM noteDurations[] = {
  8, 8, 4, 4, 8, 8, 
  8, 8, 8, 8, 8, 8, 
  4, 
  4, 8, 8, 4, 4, 
  8, 8, 8, 8, 8, 
  8, 8, 8,
  
  4, 4,  8, 8,8,8, 8, 
  8, 8,8,4, 4,  4, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,  8, 8,
  8, 4,  4, 8,  8, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,8,8, 8, 
  8, 8,  8, 8,  8, 8,
  4, 4,  4,
  
  4, 4,  8, 8,8,8, 8, 
  8, 8,8,4, 4,  4, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,  8, 8,
  8, 4,  4, 8,  8, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,8,8, 8, 
  8, 8,  8, 8,  8, 8,
  4, 4, 4,

  4, 8, 8, 4, 8, 8,
  8, 8, 8, 8, 8, 8,
  8, 8, 4, 4, 8, 8,
  8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 4, 8,
  8, 4, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 4,
  4,

  4, 8, 8, 4, 8, 8,
  8, 8, 8, 8, 8, 8,
  8, 8, 4, 4, 8, 8,
  8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 4, 8,
  8, 4, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 4,
  4,
  
  4, 4,  8, 8,8,8, 8, 
  8, 8,8,4, 4,  4, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,  8, 8,
  8, 4,  4, 8,  8, 8, 
  8, 8,  8, 8,  8, 8,
  8, 8,  8, 8,8,8, 8, 
  8, 8,  8, 8,  8, 8,
  4, 4,  4};