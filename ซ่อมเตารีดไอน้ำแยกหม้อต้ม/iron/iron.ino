// #include <Wire.h>
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
  wdt_enable(WDTO_8S);
  clearEEPROM();
  Serial.begin(9600);
  mlx.begin();  

  pinMode(relayBoiler, OUTPUT);
  // pinMode(relayIron, OUTPUT);
  pinMode(relaywaterPump, OUTPUT);
  digitalWrite(relayBoiler, HIGH);
  // digitalWrite(relayIron, HIGH);
  digitalWrite(relaywaterPump, HIGH);
}
void ArduinoReset() {
  wdt_enable(WDTO_15MS);
  while (1) {}
}
void clearEEPROM() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}
void runProgram(){
  // if (count >= 300) {
  //   ArduinoReset();
  // }
  printTime();
  // digitalWrite(relayIron, LOW);
  if (doWaterPump() == true) {
    doBoiler();
  } else {
    digitalWrite(relayBoiler, HIGH);
  }
  showTemp();
  count ++;
  countWaterPump ++;
}
void doBoiler() {
  float boilerTemperature = mlx.readObjectTempC();
  bool isBoiler = boilerTemperature > maxTemperature ? HIGH : LOW;
  digitalWrite(relayBoiler, isBoiler);
  if (isBoiler) {
    Serial.print("Boiler close\t");
  } else {
    Serial.print("Boiler open\t");
  }
}
void printTime() {
  String test = "Time: " + String(count) + " s\twater: " + String(countPump) + "\t";
  Serial.print(test);
}
void showTemp() {
  String textTemperature =  "Ambient = " 
                            + String(mlx.readAmbientTempC()) + "*C\t" 
                            + String(mlx.readAmbientTempF()) + "*F\tObject = "
                            + String(mlx.readObjectTempC()) + "*C\t" 
                            + String(mlx.readObjectTempF()) + "*F";
  String textTempC =  "Temp: " + String(mlx.readObjectTempC()) + "*C\t";
  Serial.println(textTempC);
}
bool doWaterPump() {
  bool isBoilerWater = true;
  if (countWaterPump <= delayWaterPump) {
    digitalWrite(relaywaterPump, HIGH);
    isBoilerWater = true;
  } else if (countWaterPump > delayWaterPump && countWaterPump <= waterPumpTimer) {
    digitalWrite(relaywaterPump, LOW);
    isBoilerWater = false;
    Serial.print("pump open\t");
  } else if (countWaterPump > waterPumpTimer) {
    countWaterPump = 0;
    countPump ++;
    isBoilerWater = false;
    Serial.print("pump close\t");
  } else {
    isBoilerWater = true;
  }
  return isBoilerWater;
}
void loop() {
  // digitalWrite(relayIron, LOW);
  if (countDownWhenStart >= timeWhenStart) {
    runProgram();
  } else {
    countDown();
  }
  delay(1000);
  wdt_reset();
}
void countDown() {
  countDownWhenStart ++;
  String countDown = "countDownWhenStart : " + String(countDownWhenStart) + " s";
  Serial.println(countDown);
}