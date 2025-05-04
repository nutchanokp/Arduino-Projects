ซ่อมเตารีดไอน้ำแยกหม้อต้ม
Philips GC7230


Libeary 
Adafruit_MLX90614
https://github.com/adafruit/Adafruit-MLX90614-Library

การทำงาน เมื่อต้มความร้อนถึง 110 องศาจะตัด

ปุ๊มน้ำทำงาน 1 วินาที ทุก ๆ 15 วิ

ใช้ RC Snubber

/// กัน arduino ค้าง
#include <avr/wdt.h>  // ไลบรารีสำหรับ Watchdog Timer

void setup() {
  wdt_enable(WDTO_2S);  // ตั้งเวลา Watchdog ให้รีเซ็ต ถ้าเกิน 2 วินาที
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);

  // รีเฟรช watchdog ทุก loop — ถ้าหยุดทำงาน watchdog จะรีเซ็ตให้เอง
  wdt_reset();
}