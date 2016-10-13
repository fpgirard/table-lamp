#include <EEPROM.h>

/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 */
#define RED 0xFF0000
#define WHITE 0xFFFFF
#define RED 0x0000FF
#define PURPLE 0x8B008B

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6 

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 3; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pixels.begin();  //start neopixels
  for(int i=0;i<NUMPIXELS;i++){
       pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
       pixels.show(); // This sends the updated pixel color to the hardware.
  }
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  //outputValue = map(sensorValue, 0, 1023, 0, 255);
  
  // change the analog out value:
  if (sensorValue < 512) { 
     outputValue = 255-(sensorValue/2);
     Serial.print("sensor = ");
     Serial.print(sensorValue);
     Serial.print("\t output = ");
     Serial.println(outputValue); 
     analogWrite(analogOutPin, outputValue); 
     for(int i=0;i<NUMPIXELS;i++){
       pixels.setPixelColor(i, pixels.Color(0,0,0)); // Turn off neopixels.
       pixels.show(); 
     }
  }
  else {
    Serial.print("light LED: "); Serial.println(outputValue);
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    outputValue = sensorValue/2 - 256;
    analogWrite(analogOutPin, 0); // turn off main white light
    holidayColor(outputValue);
    
  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
  }
}
void holidayColor(int outputValue) {
    int color = outputValue;
    int colors = NUMPIXELS/3;
    for(int i=0;i<5;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(color,0,0)); // white.
    pixels.setPixelColor(i+6, pixels.Color(color,color,color)); // white.
      pixels.setPixelColor(i+12, pixels.Color(0,0,color)); // white.
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
