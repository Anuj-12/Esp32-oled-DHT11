#include <Arduino.h>
#include <SPI.h> // not required for I2C programs but necessary for compiling code
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0X3C

#define DHT_PIN 18
#define DHT_TYPE DHT11

// Creating the display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHT_PIN, DHT_TYPE);

void setup(){
  Serial.begin(9600);

  dht.begin();

  // Initializing the display object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    Serial.println(F("Display failed to initialize"));
    for(;;)
      ; 
  }
}

void loop(){
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  Serial.print("Humidity : "); Serial.print(humid, 1); Serial.println(" %");
  Serial.print("Temperature : "); Serial.print(temp, 1); Serial.println(" C");

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(35,15);
  display.print(temp, 1); display.println(" C");
  display.setCursor(35,36);
  display.print(humid, 1); display.println(" %");
  display.display();
  delay(5000);
}