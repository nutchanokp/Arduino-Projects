#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 4
#define CLK_PIN   D5 // or SCK
#define DATA_PIN  D7 // or MOSI
#define CS_PIN    D4 // or SS // you can set it to any pin


MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
 
  Display.begin();
  Display.setIntensity(7);
  Display.displayClear();
}

void loop() {
  // Display.setTextAlignment(PA_LEFT);
  // Display.print("ESP");
  // delay(2000);
  
  // Display.setTextAlignment(PA_CENTER);
  // Display.print("ESP");
  // delay(2000);

  // Display.setTextAlignment(PA_RIGHT);
  // Display.print("ESP");
  // delay(2000);

  // Display.setTextAlignment(PA_CENTER);
  // Display.setInvert(true);
  // Display.print("ESP");
  // delay(2000);

  Display.setTextAlignment(PA_CENTER);
  Display.setInvert(true);
  Display.print("");
  // delay(2000);

  // Display.setInvert(false);
  // delay(2000);
}