#include <Wire.h>
#include <AHT20.h>
AHT20 aht20;
int Relay1 = D5;

void setup()
{
  Serial.begin(9600);
  Serial.println("AHT20 example");

  Wire.begin();
  if (aht20.begin() == false)
  {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    while(true);
  }
  pinMode(Relay1, OUTPUT); // กำหนดขาทำหน้าที่ให้ขา D0 เป็น OUTPUT
  digitalWrite(Relay1, HIGH);
}

void loop()
{
  float temperature = aht20.getTemperature();
  float humidity = aht20.getHumidity();

  Serial.print("T: ");
  Serial.print(temperature, 2);
  Serial.print(" C\t H: ");
  Serial.print(humidity, 2);
  Serial.println("% RH");
  if (temperature > 37.0f) {
    digitalWrite(Relay1, HIGH);
  } else {
    digitalWrite(Relay1, LOW);
  }

  delay(15000);
}
