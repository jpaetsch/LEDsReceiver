#ifndef PATTERNSOLID_H
#define PATTERNSOLID_H

#include "pattern.h"

class PatternSolid: public Pattern {
  private:      
    uint8_t hue;
    uint8_t sat;
    uint8_t val;
  
  public:
    PatternSolid(CRGB* inLeds, uint16_t inNumLeds, uint8_t inHue, uint8_t inSat, uint8_t inVal): Pattern(inLeds, inNumLeds) {
      hue = inHue;
      sat = inSat;
      val = inVal;
    }

    ~PatternSolid() {
    
    }

    bool updateNeeded();
    void initPattern();
    void updatePattern();
};


bool PatternSolid::updateNeeded() {
  return false;
}

void PatternSolid::initPattern() {
  CHSV color = CHSV(hue, sat, val);
  fill_solid(leds, numLeds, color);
}

void PatternSolid::updatePattern() {
  
}


#endif
