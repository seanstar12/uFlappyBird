#if !(defined(GAPHEIGHT))
  #define GAPHEIGHT 26
#endif
#if !(defined(PIPEW))
  #define PIPEW 8
#endif

// TUBE structure
class Tube {
  public:
    Tube(int _pipeW, int _height, int _gapHeight);
    unsigned int gap, col, width, height;
    int x;

    bool isVisible(void);
    void setX(int dist);
};


Tube::Tube(int _pipeW, int _height, int _gapHeight) {
  width = PIPEW;
  gap = random(6, 63-(16+GAPHEIGHT));
  //gap = 22;
}

bool Tube::isVisible(void) {
  return (x + width) > 0;
}

void Tube::setX(int dist) {
  x =  x + dist;
}