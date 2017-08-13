#if !(defined(NOTE_A5))
  #include "pitch.h"  
#endif

static const unsigned int PROGMEM fail[] = {
  NOTE_A5, NOTE_B5,  NOTE_C5, NOTE_B5,  NOTE_C5, NOTE_D5, 
  NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_D5, NOTE_E5, NOTE_E5
};
static const unsigned int PROGMEM failDuration[] = {
 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4
}

static const unsigned int PROGMEM flapTone[] = {
  NOTE_G4, NOTE_C4
};

static const unsigned int PROGMEM flapDuration[] = {
 4, 4
};