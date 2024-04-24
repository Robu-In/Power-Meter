#include "SparkFun_ACS37800_Arduino_Library.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

ACS37800 mySensor;

void setup() {
  Serial.begin(115200);
  Serial.println(F("ACS37800 Example"));

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  Wire.begin();

  if (mySensor.begin() == false) {
    Serial.print(F("ACS37800 not detected. Check connections and I2C address. Freezing..."));
    while (1); // Do nothing more
  }

  mySensor.setBypassNenable(false, true);
  mySensor.setDividerRes(3500000);
}

void loop() {
  float volts = 0.0;
  float amps = 0.0;

  mySensor.readRMS(&volts, &amps);
  Serial.print(F("Volts: "));
  Serial.print(volts, 2);
  Serial.print(F(" Amps: "));
  Serial.println(amps, 2);

  display.clearDisplay();
  display.setCursor(0,0);
  display.print(F("Volts:"));
  display.println(volts, 1);
  display.display();

  delay(250);
}