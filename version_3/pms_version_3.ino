#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "PMS.h"

LiquidCrystal_I2C lcd1(0x26, 16, 2);
LiquidCrystal_I2C lcd2(0x27, 16, 2);

PMS pms(Serial);
PMS::DATA data;
DHT dht;

float humidity;
float temperature;

void setup() {
  Serial.begin(9600);
  
  lcd1.begin();
  lcd1.backlight();
  lcd2.begin();
  lcd2.backlight();

  dht.setup(2); // data pin 2
}

void loop() { 
  if (pms.read(data)) {
    humidity = dht.getHumidity(); // ดึงค่าความชื้น
    temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ
    log();
    LCD1(); // สั่งให้ไปทำงานในฟังก์ชั่น LCD1
    LCD2(); // สั่งให้ไปทำงานในฟังก์ชั่น LCD2
  } 
}

void LCD1() {
  if (!isnan(humidity) || !isnan(temperature)){
  lcd1.begin();
  lcd1.clear();
  
  lcd1.setCursor(0, 0);
  lcd1.print("humidity: " + String(humidity) + "%");
  
  lcd1.setCursor(0, 1);
  lcd1.print("Temp: " + String(temperature) + " C");
  } 
}

void LCD2() {
  lcd2.begin();
  Serial.println(); 
  lcd2.clear();
  
  lcd2.setCursor(0, 0);
  lcd2.print(String("PM1: ") + String(data.PM_AE_UG_1_0) +  String(" 2.5: ") + String(data.PM_AE_UG_2_5));
  
  lcd2.setCursor(0, 1);
  lcd2.print(String("PM10: ") + String(data.PM_AE_UG_10_0));
}

void log() {
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.println(dht.toFahrenheit(temperature), 1);

  Serial.print("PM 1.0 (ug/m3): ");
  Serial.println(data.PM_AE_UG_1_0);

  Serial.print("PM 2.5 (ug/m3): ");
  Serial.println(data.PM_AE_UG_2_5);

  Serial.print("PM 10.0 (ug/m3): ");
  Serial.println(data.PM_AE_UG_10_0);
}

