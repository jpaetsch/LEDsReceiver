#ifndef PATTERNOFF_H
#define PATTERNOFF_H

#include "pattern.h"

class PatternOff: public Pattern {
  private:      
  
  public:
    PatternOff(CRGB* inLeds, uint16_t inNumLeds): Pattern(inLeds, inNumLeds) {

    }

    ~PatternOff() {
    
    }

    bool updateNeeded();
    void initPattern();
    void updatePattern();
};


bool PatternOff::updateNeeded() {
  return false;
}

void PatternOff::initPattern() {
  FastLED.clear();
}

void PatternOff::updatePattern() {
  
}


#endif
