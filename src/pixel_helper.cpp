#include <NeoPixelBus.h>
#include <iostream>
#include "pixel_helper.h"
#include "BlendRGB.h"
#include "CustomPattern.h"

using namespace std;

PIXEL_HELPER_CLASS* pixel_helper;

void PIXEL_HELPER_CLASS::ExceptionHandler(void){
	throw new string "String Exceptions";	
return;
}


RgbColor PIXEL_HELPER_CLASS::RGBStringToRGB(String input) {
  int index = 0;
	try{
  int R = input.substring(0, input.indexOf('.')).toInt();
	pixel_helper->ExceptionHandler();
	}catch(const char* msg){
        cout << "We caught a message: " << msg << endl;
    }

  index = input.indexOf('.');
	try{
  int G = input.substring(index + 1, input.indexOf('.', index + 1)).toInt();
  pixel_helper->ExceptionHandler();
	}catch(const char* msg){
        cout << "We caught a message: " << msg << endl;
    }
	
  index = input.indexOf('.', index + 1);
	try{
  int B = input.substring(index + 1).toInt();
  pixel_helper->ExceptionHandler();
	}catch(const char* msg){
        cout << "We caught a message: " << msg << endl;
    }
  return RgbColor( R,G,B);
}

void PIXEL_HELPER_CLASS::SetAll(RgbColor colour) {
  for (int K = 0; K < pixelCount; K++) {
    strip.SetPixelColor(K, colour);
  }
}

PIXEL_HELPER_CLASS::PIXEL_HELPER_CLASS() {
  // Clear LEDS
  SetAll(RgbColor(0,0,0));
  strip.Show();

  // Turn onboard led off
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
}





// RGBBLEND,0.0.0,0.20.0,0,3
void PIXEL_HELPER_CLASS::ProcessCommand(String input) {
  Serial.print("ProcessCommand:");
  Serial.println(input);
	if (input.startsWith("RGBBLEND")) {
		ParseRGBBLEND(input,pixel_helper);
	}
	if (input.startsWith("CUSTOMPATTERN")) {
		ParseCustomPattern(input,pixel_helper);
	}

}

String SerialInput = "";

void PIXEL_HELPER_CLASS::pixelLoop() {
  if (LEDMode == RGBMode_BLEND) {
    DoBlendMode(pixel_helper);
  } else if(LEDMode == RGBMode_BLEND){
	DoCustomPatternMode(pixel_helper);  
  }
  
  if(ProcessSerial){
    while (Serial.available() > 0)
    {
        char recieved = Serial.read();
        SerialInput += recieved; 

        // Process message when new line character is recieved
        if (recieved == '\n')
        {
            ProcessCommand(SerialInput);
            SerialInput = "";
        }
    }
  }
 
}

