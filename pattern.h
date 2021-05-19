#ifndef PATTERN_H
#define PATTERN_H

#include <FastLED.h>

class Pattern {
  protected:
    CRGB *leds;
    int numLeds;
  public:
    Pattern(CRGB *inLeds, uint16_t inNumLeds) {
      leds = inLeds;
      numLeds = inNumLeds;
    }

    virtual ~Pattern() {
      
    }
    
    virtual bool updateNeeded() = 0;
    virtual void initPattern() = 0;
    virtual void updatePattern() = 0;
};


#endif
