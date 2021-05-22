#include <FastLED.h>
#include "pattern.h"
#include "patternOff.h"
#include "patternSolid.h"


// TODO possibly make all of these adjustable on the app settings side
#define NUM_LEDS 900
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define DATA_PIN 7

#define MAX_INPUT 24        // The max number specified by communication protocol I set up ie. 24 bytes encased by < >
#define MAX_TIME 10000000   // ~2.78 hours before it auto-shuts down the pattern that's been holding
#define TIMEOUT 2000        // 2 seconds before it no longer waits to receive the current pattern info


CRGBArray<NUM_LEDS> leds;   // led array
Pattern *pattern;           // current pattern
byte input[MAX_INPUT];      // parse data one byte at a time
unsigned long timeNoComm;   // longer overall timeout if no successful pattern change communication is received
unsigned long timeWaiting;  // short timeout for filling the instruction buffer


// Explanation Notes
// 1) Communication protocol is   <----------------------->   ie. 24 bytes encased by 2 <> delimiters
// 2) Two different types of serial messages sent to the app - Error: | Status:   the first letter is stripped
//    by the controller app to set severity, display, etc.


void setup() {
  delay(3000);    // safety startup delay
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS);
  
  Serial.begin(9600);

  /* Initialize elements */
  pattern = new PatternOff(leds, NUM_LEDS);
  clearInputArray();
  timeNoComm = millis();
  
}


void loop() {
  
  /* No new pattern for a long time */
  if((millis()-timeNoComm) > MAX_TIME && pattern->getPatternID() != 0) {
    Serial.println("Error: no communication timeout");
    delete pattern;
    pattern = new PatternOff(leds, NUM_LEDS);
    pattern->initPattern();
  }
  
  if(readPattern()) {
    Serial.println("Status: read in the pattern and its parameters");
    if(setupPattern()) {
      Serial.println("Status: identified the pattern");
      timeNoComm = millis();
      pattern->initPattern();
    }
  }


  // Framerate will be controlled within each pattern classes update function
  pattern->updatePattern();
}


/* Handle serial input by monitoring the available buffer and reading it in when a full instruction is received */
bool readPattern() {
  /* Communication is either received as 24 bytes encased by <> or a communication receive error message
   * is sent and instruction is disregarded */
   
  if(Serial.available() > 0) {
    timeWaiting = millis();
    clearInputArray();
    
    while(Serial.available() != MAX_INPUT + 2) {  // wait for full pattern instruction within timeout bounds
      if((millis() - timeWaiting) > TIMEOUT) {
        Serial.println("Error: pattern wait timeout");
        clearBuffer();
        return false;
      }
    }
    /* At this point the full instruction is in the available buffer so test first delimiter */
    
    if((char) Serial.read() != '<') {
      Serial.println("Error: first delimiter");
      clearBuffer();
      return false;
    }
    /* At this point the first character is the proper < delimiter so read in the available buffer values */

    for(int i = 0; i < MAX_INPUT; ++i) {   // read 24 instruction parameter bytes into input array
      input[i] = Serial.read();
    }
    /* At this point the characters have been read into the input array so test final delimiter*/
   
    if((char) Serial.read() != '>') {
      Serial.println("Error: last delimiter");
      clearBuffer();
      return false;
    }
    /* At this point the final character is the proper > delimiter so assume everything is good to go */
    return true;
  }
  return false;
}


/* Function to parse the entire pattern buffer, and set up the global pattern object */
bool setupPattern() {  
  switch(input[0]) {
    case 0:
      Serial.println("Status: pattern id matches off pattern");
      delete pattern;
      pattern = new PatternOff(leds, NUM_LEDS);
      return true;
      
    case 1:
      Serial.println("Status: pattern id matches solid pattern");
      delete pattern;
      pattern = new PatternSolid(leds, NUM_LEDS, input[1], input[2], input[3]);
      return true;

    default:
      Serial.println("Error: pattern id not found");
      return false;
  }
}


/* Function to clear the entire pattern buffer, setting it to default '-' values */
void clearInputArray() {
  Serial.println("Status: cleared input array");
  for(int i = 0; i < MAX_INPUT; ++i) {
    input[i] = byte('-');
  }
}

/* Function to clear the entire serial buffer */
void clearBuffer() {
  Serial.println("Status: cleared serial buffer");
  do {
    Serial.read();
  } while(Serial.available() > 0);
}
