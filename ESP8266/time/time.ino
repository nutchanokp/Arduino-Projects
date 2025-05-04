#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
const char *ssid     = "Xiaomi_6AD6";
const char *password = "10683524";

int potpin = A0;
int val;
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
SoftwareSerial NodeMCU(D2, D3); // RX | TX

const long offsetTime = 25200;       // หน่วยเป็นวินาที จะได้ 7*60*60 = 25200

#define MAX_DEVICES 4
#define CLK_PIN   D5 // or SCK
#define DATA_PIN  D7 // or MOSI
#define CS_PIN    D4 // or SS // you can set it to any pin


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", offsetTime);

MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int hourNow, minuteNow, secondNow;

void setup(){
// เริ่มใช้งาน Serial
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(9600); // Hardware Serial ที่แสดงออกหน้าจอ Serial Monitor
  NodeMCU.begin(9600); // Software Serial ที่ NodeMCU ใช้สื่อสากับ Arduino Uno
// เขื่อมต่อกับ WiFi 
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    Serial.println(WiFi.status());
    
  }
  timeClient.begin();
  Display.begin();
  Display.setIntensity(0);
  Display.displayClear();
}


void loop() {
  
  timeClient.update(); 
  secondNow = timeClient.getSeconds();
  minuteNow = timeClient.getMinutes();
  hourNow = timeClient.getHours();

  val = analogRead(potpin);         // อ่านค่า Analog ขาA0 เก็บไว้ในตัวแปร Val
  val = map(val, 0, 1023, 0, 15);  // แปลงค่า ระหว่าง 0-1023 เป็น 0-180
  Serial.print("val = ");           // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(val);              // พิมพ์ค่าของตัวแปร val

  Display.setIntensity(val);
  NodeMCU.println(timeClient.getFormattedTime()); // ส่งเลข 1 ไปให้ Arduino Uno และจบค่าที่ส่งด้วย \n

  Display.setTextAlignment(PA_CENTER);
  // String time = String(hourNow) + " : " + String(minuteNow) + " : " + String(secondNow);
  Display.print(timeClient.getFormattedTime());
  Serial.println(timeClient.getFormattedTime());
// แสดงผลทาง Serial monitor รูปแบบ hh:mm:ss หากตัวไหนมีหลักเดียวให้เติม 0 ด้านหน้า ให้ครบ 2 หลักเสมอ
  if(hourNow < 10)(Serial.print("0"));
  Serial.print(hourNow);
  // NodeMCU.println(1);
  Serial.print(":");
  if(minuteNow < 10)(Serial.print("0"));
  Serial.print(minuteNow);
  // NodeMCU.println(1);
  Serial.print(":");
  if(secondNow < 10)(Serial.print("0"));
  Serial.print(secondNow);
  // NodeMCU.println(0);
  Serial.println();
// หน่วงเวลา 1 วินาที
  delay(1000);
}