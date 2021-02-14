#include <FastLED.h>

// TODO eventually make all of these adjustable on the app settings side
#define NUM_LEDS 900
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define DATA_PIN 7
#define DEFAULT_BRIGHTNESS 100

#define MAX_INPUT 24        // The max number specified by communication protocol I set up ie. 24 bytes encased by < >
#define MAX_TIME 10000000   // ~2.6 hours before it auto-shuts down the pattern that's been holding
#define TIMEOUT 2000        // 2 seconds before it no longer waits to receive the current pattern info


CRGBArray<NUM_LEDS> leds;   // led array
byte input[MAX_INPUT];      // parse data one byte at a time
unsigned long timeNoComm;   // long timeout if no communication is received
unsigned int timeWaiting;   // short timeout for filling the instruction buffer
bool validInput;

// Explanation Notes
// 1) Communication protocol is   <----------------------->   ie. 24 bytes encased by 2 <> delimiters
// 2) Three different types of serial messages sent to the app - Private: | Error: | Status:   the first letter is stripped
//    by the controller app to see the behaviour - Private ones are meant to be hidden, Error ones emphasized to the user, and
//    Status displayed to the user ... thinking about logging all of these eventually but right now they are just used to affect
//    UI elements


void setup() {
  delay(3000);    // safety startup delay
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS);    // look into if .setCorrection(TypicalLEDStrip) is necessary
  FastLED.setBrightness(DEFAULT_BRIGHTNESS);
  
  Serial.begin(9600);

  /* Initialize elements */
  clearInputArray();
  timeNoComm = millis();
  validInput = false;
}


void loop() {

  validInput = false;
  
  /* No new pattern for a long time */
  if((millis()-timeNoComm) > MAX_TIME) {
    Serial.println("Error: no communication timeout");
    // TODO set the currentPattern to be OFF or blank
  }
  

  if(readPattern()) {
    Serial.println("Status: received possibly valid input");
    setupPattern();
  }
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
// TODO turn into a boolean similar to readPattern()
void setupPattern() {  
  switch((char) input[0]) {
    case '0':
      Serial.println("Status: matches off pattern");
      FastLED.clear();
      FastLED.show();
      break;
      
    case '1':
      Serial.println("Status: matches solid pattern");
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      FastLED.show();
      break;

    default:
      Serial.println("Error: no pattern index found");
  }
}


/* Function to clear the entire pattern buffer, setting it to default '-' values */
void clearInputArray() {
  Serial.println("Private: cleared input array");
  for(int i = 0; i < MAX_INPUT; ++i) {
    input[i] = byte('-');
  }
}


/* Function to clear the entire serial buffer */
void clearBuffer() {
  Serial.println("Private: cleared serial buffer");
  while(Serial.available() > 0) {
    Serial.read();
  }
}
