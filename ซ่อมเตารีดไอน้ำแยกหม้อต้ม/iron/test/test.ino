#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <EEPROM.h>
#include <avr/wdt.h>  

int relaywaterPump = 3;
// int relayIron = 4;
int relayBoiler = 5;

float maxTemperature = 110.0f;
int delayWaterPump = 15;
int waterPumpTimer = delayWaterPump + 1;

int count = 0;
int countWaterPump = 0;
int countPump = 0;
int timeWhenStart = 0;
int countDownWhenStart = 0;

void setup() {
  Serial.begin(115200);
  mlx.begin();  

  pinMode(relayBoiler, OUTPUT);
  // pinMode(relayIron, OUTPUT);
  pinMode(relaywaterPump, OUTPUT);
  digitalWrite(relayBoiler, HIGH);
  // digitalWrite(relayIron, HIGH);
  digitalWrite(relaywaterPump, HIGH);
}\
void loop() {
  digitalWrite(relaywaterPump, HIGH);
  delay(1000);
  digitalWrite(relaywaterPump, LOW);
  delay(1000);
  count++;
  Serial.println(count);
}\