#include <FastLED.h>

// TODO eventually make all of these adjustable on the app settings side
#define NUM_LEDS 900
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define DATA_PIN 7
#define DEFAULT_BRIGHTNESS 100

#define MAX_INPUT 24        // The max number specified by communication protocol I set up ie. 24 bytes encased by < >
#define MAX_TIME 10000000   // ~2.6 hours before it auto-shuts down the pattern that's been holding
#define TIMEOUT 3000        // 3 seconds before it no longer waits to receive the current pattern info


CRGBArray<NUM_LEDS> leds;   // led array
int input[MAX_INPUT];      // parse data one byte at a time
unsigned long timeNoComm;   // long timeout if no communication is received
bool validInput;

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
    // TODO set the currentPattern to be OFF or blank
  }

  /* Communication is either received as 24 bytes encased by <> or a communication receive error message
   * is sent and instruction is disregarded */
  if(Serial.available() > 0) {
    if(Serial.available() == MAX_INPUT + 2) {
      if(Serial.read() == 60) {    // '<' was read as first character
        for(int i = 0; i < MAX_INPUT; ++i) {   // read 24 instruction parameter bytes into input array
          input[i] = Serial.read();
        }
        if(Serial.read() == 62) { // '>' was read as last character
          validInput = true;  // All parameters have been met for serial-read input; assume to be a valid instruction
        } else {
          Serial.println("Error: last delimiter");
          clearBuffer();
        }
      } else {
        Serial.println("Error: first delimiter");
        clearBuffer();
      }
    } else { // Something is in the buffer but it's not the right length, clear buffer
      Serial.println("Error: wrong buffer length");
      clearBuffer(); 
    }
  }

  if(validInput) {
    validInput = false;
    // TODO PARSE INPUT AND DO SOMETHING W PATTERN OBJECT
  }
}


/* Function to clear the entire pattern buffer, setting it to default '-' values */
void clearInputArray() {
  for(int i = 0; i < MAX_INPUT; ++i) {
    input[i] = 45;
  }
}


/* Function to clear the entire serial buffer */
void clearBuffer() {
  while(Serial.available() > 0) {
    Serial.read();
  }
}
