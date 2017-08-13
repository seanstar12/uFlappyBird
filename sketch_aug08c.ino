#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

#include "font.h"
#include "nyan.h"

#define DEBUG 0
#define OLED_MOSI  18   //D1
#define OLED_CLK   19   //D0
#define OLED_DC    9
#define OLED_CS    8
#define OLED_RESET 10

#define TFTW            128     // screen width
#define TFTH            64     // screen height
#define TFTW2            64     // half screen width
#define TFTH2            32     // half screen height
// game constant
#define SPEED             1
#define GRAVITY         9.8
//#define JUMP_FORCE     2.15
#define JUMP_FORCE     1.95

#define SKIP_TICKS     20.0
#define MAX_FRAMESKIP     6
// bird size
#define BIRDW             14     // bird width
#define BIRDH             8     // bird height
#define BIRDW2            7     // half width
#define BIRDH2            4     // half height
// pipe size
#define PIPEW            16     // pipe width
#define GAPHEIGHT        26     // pipe gap height
// floor size
#define FLOORH           1     // floor height (from bottom of the screen)
// grass size
#define GRASSH            1     // grass height (inside floor, starts at floor y)


Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
IntervalTimer sound;

const unsigned char GAMEH = TFTH - FLOORH;
const unsigned int BKG = BLACK;
const unsigned int FG = WHITE;

// bird structure
static struct BIRD {
  int8_t x, y;
  float vel;
  uint8_t pos;
} bird;

// TUBE structure
class Tube {
  public:
    Tube(int _pipeW, int _dist, int _gapHeight);
    char active, window;
    int tail;
    int gap, width, height;
    int x, pos, dist;

    bool isVisible(void);
    void setGap(void);
    void move(int speed);
    void reset(int screenWidth);
    void drawPipe(void);
};


Tube::Tube(int _pipeW, int _dist, int _gapHeight) {
  active = 0;
  dist = _dist;
  pos = 0;
  
  x = TFTW + dist;
  this->setGap();
}

void Tube::reset(int screenWidth) {
  this->setGap();
  x = screenWidth;
  tail = 0;
  window = 1;
  active = 0;
}

void Tube::setGap(void) {
  gap = random(6, GAMEH-(6+GAPHEIGHT));
}

void Tube::move(int speed) {
  x -= speed;
}

void Tube::drawPipe(void) {
  unsigned int _gap = gap - 5;
  unsigned int _height = 6;
  
  // top pipe
  display.drawFastVLine(x + 1, 0, _gap, WHITE);
  display.drawFastVLine(x + PIPEW - 1, 0, _gap, WHITE);
  // accent
  display.drawFastVLine(x + PIPEW - 3, 0, _gap, WHITE);

  // cap verticals
  display.drawFastVLine(x, _gap, _height, WHITE);
  display.drawFastVLine(x + PIPEW, _gap, _height, WHITE);
  // accent
  display.drawFastVLine(x + PIPEW - 2, _gap, _height, WHITE);

  // cap horizontals
  display.drawFastHLine(x, gap, PIPEW, WHITE);
  display.drawFastHLine(x, _gap, PIPEW, WHITE);

  _gap = GAPHEIGHT + gap;
  // @TODO: possible bug here where pipe is 1px longer than it should
  //        be causing it to overlap the grass/ground area
  // bottom pipe
  display.drawFastVLine(x + 1, _gap + 5, GAMEH - _gap, WHITE);
  display.drawFastVLine(x + PIPEW - 1, _gap + 5, GAMEH - _gap, WHITE);
  // accent
  display.drawFastVLine(x + PIPEW - 3, _gap + 5, GAMEH - _gap, WHITE);

  // bottom cap verticals
  display.drawFastVLine(x, _gap, _height, WHITE);
  display.drawFastVLine(x + PIPEW, _gap, _height, WHITE);
  // accent
  display.drawFastVLine(x + PIPEW - 2, _gap, _height, WHITE);

  // bottom cap horizontals
  display.drawFastHLine(x, _gap, PIPEW, WHITE);
  display.drawFastHLine(x, _gap + 5, PIPEW, WHITE);

  if (DEBUG) {
    display.setCursor(x, gap + GAPHEIGHT/2);
    display.print(pos);
  }
}

bool Tube::isVisible(void) {
  return (x + width) > 0;
}

// score
static short score;
// temporary x and y var
static short tmpx, tmpy;
bool btn = false;

volatile unsigned long toneTime = 0;
volatile const unsigned int *toneDuration;
volatile const unsigned int *toneTone;
volatile unsigned int tonePos = 0;
volatile unsigned int toneSize = 0;

// @TODO: I don't like this, but b/c array initialization
//        and my lack of C++ skills...
unsigned int tubesCount = 4;

Tube tubes[4] = {
  Tube(PIPEW, 0, GAPHEIGHT),
  Tube(PIPEW, 0, GAPHEIGHT),
  Tube(PIPEW, 0, GAPHEIGHT),
  Tube(PIPEW, 0, GAPHEIGHT)
};

void setup() {
  randomSeed(analogRead(0));
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.invertDisplay(false);
  display.display();

  pinMode(23, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(12, INPUT);
  attachInterrupt(12, buttonPushed, FALLING);

  game_start();
}

// interrupt for maximum accuracy
void buttonPushed() {
  btn = true;
}

// ---------------
// main loop
// ---------------
void loop() {
  game_init();
  game_loop();
  game_over();
}

// ---------------
// game loop
// ---------------
void game_loop() {
  Tube *currentTube;
  
  // game loop time variables
  double prev_time, next_game_tick, current_time;
  double btnPress = 0;
  int loops;
  bool passed_pipe = false;
  unsigned char px;
  
  // Amount of pixes bird can pass through before causing game end
  // Needed due to bouncing of button/enjoyable factor
  int grace = 6; 
  next_game_tick = current_time = millis();


  // @TODO: is this the best way to handle tubes?
  //setup tubes
  for (uint8_t j=0; j < tubesCount; j++) {
    if (!j) tubes[j].active = 1;

    tubes[j].reset(TFTW);
    tubes[j].pos = j + 1;
    currentTube = &tubes[j];
  }

  
  while (1) {
    loops = 0;
    while( millis() > next_game_tick && loops < MAX_FRAMESKIP) {
      // @TODO: different game modes?
      // can change tube distance on the fly.
      int TUBEDIST = 60;

      prev_time = current_time;
      current_time = millis();

      // slight debounding for the buttons
      // delay(XXX) causes performance issues at 8MHz
      if ( btn && btnPress + 50 < current_time) {
        btnPress = current_time;
        btn = false;
        
        // Allow bird to partially go above screen; give them hope 
        // of being able to skip the pipes even though the collision 
        // detection is windowed in between pipes.
        if (bird.y > -BIRDH) bird.vel = -JUMP_FORCE;
        else bird.vel = 0;

        startTone(flapTone, flapDuration, sizeof(flapTone));
      }

      bird.vel += GRAVITY * (current_time-prev_time)/1000;
      bird.y += bird.vel;


      // @TODO: Not my best work here, but it gets the job done.
      //        find better way to manage pipes.
      //        sets active, tail, and currentPipe.
      int count = 0;
      for (uint8_t j=0; j < tubesCount; j++) {
        if (tubes[j].active == 1) {
          if (!tubes[j].tail && (tubes[j].x + TUBEDIST < TFTW)) {
            for (uint8_t k=0; k < tubesCount; k++) {
              if (tubes[k].active == 0) {
                tubes[j].tail = 1;
                tubes[k].active = 1;
                break;
              }
            }            
          }
          tubes[j].x -= SPEED;
          if (tubes[j].x < bird.x + BIRDW + 20 && tubes[j].x > bird.x) {
            currentTube = &tubes[j];
          }
          if (tubes[j].x < -(PIPEW + 5)) {
            tubes[j].reset(TFTW);
          }
          count++;
        }
      }

      // ensures we always have an active pipe.
      if (count == 0) tubes[0].active = 1;
      
      next_game_tick += SKIP_TICKS;
      loops++;
    }
    
    // draw grass
    display.drawFastHLine(0, GAMEH, TFTW, WHITE);

    // draw pipes
    for (uint8_t i = 0; i < tubesCount; i++) {
      if (tubes[i].x < TFTW && (tubes[i].x + PIPEW >0)) {
        tubes[i].drawPipe();
      }
    }

    // Draw Bird
    tmpx = BIRDW-1;
    do {
      px = bird.x + tmpx + BIRDW;
      tmpy = BIRDH - 1;
      
      do {
         // only draw pixels that have color
        if (bird01[tmpx + (tmpy * BIRDW)])
          display.drawPixel(px, bird.y + tmpy, bird01[tmpx + (tmpy * BIRDW)]);
        } while (tmpy--);
    } while (tmpx--);
    
    // @TODO: remove comment, but for developing, bird can hit the ground
    //if (bird.y > GAMEH-BIRDH) break;

    // without this, during debug, bird goes warp speed
    if (bird.y >= GAMEH - BIRDH) {
      bird.vel = 0;
      bird.y = GAMEH - BIRDH;
    }

    // DEBUGGING: GOOD WINDOW
    //if (DEBUG){
    //  display.drawRect(currentTube->x +2, currentTube->gap +2, PIPEW-4, GAPHEIGHT - 4, WHITE);
    //}
    if (bird.x+BIRDW >= currentTube->x - BIRDW + grace && bird.x <= currentTube->x + PIPEW-BIRDW - grace) {
      if (bird.y < currentTube->gap || bird.y + BIRDH > currentTube->gap + GAPHEIGHT) {

        // render to show where person failed.
        display.display();
        startTone(failTone, failDuration, sizeof(failTone));
        break;
      }
      else {
        passed_pipe = true;
      }
    }
    // checking for bird collision with pipe

    // if bird has passed the pipe increase score
    else if (bird.x > currentTube->x+PIPEW-BIRDW && passed_pipe) {
      startTone(pipeTone, pipeDuration, sizeof(pipeTone));
      passed_pipe = false;
      score++;
    }
    
    if (DEBUG) {
      display.setCursor(65, 10);
      display.print(tubes[0].x);
      display.print(" ");
      display.print(tubes[0].gap); 
      display.setCursor(65,20); 
      display.print(tubes[1].x);
      display.print(" ");
      display.print(tubes[1].gap);
      display.setCursor(65, 30); 
      display.print(tubes[2].x);
      display.print(" ");
      display.print(tubes[2].gap);
      display.setCursor(65, 40); 
      display.print(tubes[3].x);
      display.print(" ");
      display.print(tubes[3].gap);
    }

    // ---------------
    // Update Score
    // ---------------

    tmpx = 7;
    int yloc = 4;
    int xloc = 60;
    int mod = 0;
    int _score = score;

    // @TODO: do maths here.
    //        this will allow for flappy bird font to show score
    //        works with single digits, need to remember how to
    //        modulos/divide with C++ to make it multi-digit
    //if (_score > 9) {
    //  _score = score % 10;
    //  mod++;
    //}

    /*
    do {
      xloc += 8;
      
      do {
        px = xloc+ tmpx + 7;
        tmpy = 8;
        do {
          // only draw pixels that have color
          if (num[_score][tmpx + (tmpy * 7)] < 2) {
            display.drawPixel(px, yloc + tmpy, num[_score][tmpx + (tmpy * 7)]);
          }
        } while (tmpy--);
      } while (tmpx--);
    } while(mod--);
    */
    
    display.setCursor( TFTW2, 4);
    display.print(score);
    display.display();

    // Clear buffer for next frame
    display.clearDisplay();
  }

  // reflection time
  delay(1200);
}

// ---------------
// game start
// ---------------
void game_start() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);

  display.setCursor( TFTW2-(6*6), 0);
  display.println("FLAPPY");
  display.drawFastHLine(20, 7, 80, WHITE);
  display.setCursor( TFTW2-(6*6), 20);
  display.println(" BIRD ");
  display.setTextSize(1);
  display.setCursor( TFTW2 - (12*3) - 1, 54);
  display.println("press button");
  display.display();
  
  while (1) {
    // wait for push button
    if ( btn ) {
      btn = false;
      break;
    }
    
    delay(20);
  }
  
  // init game settings
  game_init();
}

// ---------------
// game init
// ---------------
void game_init() {
  display.clearDisplay();
  score = 0;
  bird.x = 20;
  bird.y = (GAMEH/2) - BIRDH;
  bird.vel = -JUMP_FORCE;
  tmpx = tmpy = 0;
}

// ---------------
// game over
// ---------------
void game_over() {
  btn = false;
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor( TFTW2 - (9*6), TFTH2 - 4);
  display.println("GAME OVER");
  display.setTextSize(0);
  display.setCursor( 10, TFTH2 - 14);
  display.print("score: ");
  display.print(score);
  display.setCursor( TFTW2 - (12*3), TFTH2 + 12);
  display.println("press button");

  display.display();
  while (1) {
    // wait for push button
    if ( btn ) {
      btn = false;
      break;
    }
    delay(20);
  }
}


/*
 // intro music? seemed like too much during testing
void mus() {
    for (int thisNote = 0; thisNote < 27; thisNote++) {
      if (btn) break;
      // to calculate the note duration, take one second 
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000/noteDurations[thisNote];

      if (melody[thisNote] > 0) tone(23, melody[thisNote],noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 0.90;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      if (melody[thisNote] > 0) noTone(244);
      //if (thisNote == 27) thisNote = 0;
    }
    for (int thisNote = 27; thisNote < 244; thisNote++) {
      if (btn) break;
      
      int noteDuration = 1000/noteDurations[thisNote];
      if (melody[thisNote] > 0) tone(23, melody[thisNote],noteDuration);
      int pauseBetweenNotes = noteDuration * 0.90;
      delay(pauseBetweenNotes);
      if (melody[thisNote] > 0) noTone(244);

      if (thisNote == 243) thisNote = 26;
    }
}
*/

/*
 * Plays tones using timers. Prevents lockup when playing sounds.
 */
void doTone() {
  if (tonePos < toneSize) {
    unsigned int toneNote = *(toneTone + tonePos);
    unsigned int _duration = *(toneDuration + tonePos);
    int duration = 1;
    
    if (toneNote > 0) {
      duration = 1000/_duration;
      tone(23, toneNote, duration);
      sound.begin(stopTone, 1000*duration);
    }
    else {
      sound.end();
      noTone(23);
    }
    
  }
}
/*
 * Plays tones using timers. Prevents lockup when playing sounds.
 */
void stopTone() {
  noTone(23);
  sound.end();
    
  if (tonePos >= toneSize) {
    tonePos = 0;
  }
  else {
    tonePos++;
    doTone();
  }
}

/*
 * Plays tones using timers. Prevents lockup when playing sounds.
 */
void startTone(const unsigned int *arr, const unsigned int *dur, unsigned int size) {
  noTone(23);
  sound.end();
 
  tonePos = 0;
  toneSize = size;
  toneTone = arr;
  toneDuration = dur;
  
  doTone();
}


