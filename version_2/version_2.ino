#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include "DHT.h"
#include "PMS.h"

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display
PMS pms(Serial);
PMS::DATA data;
DHT dht;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0x27);
  lcd.begin(16, 2); // initialize the lcd
  dht.setup(2); // data pin 2

}

void loop()
{
  if (pms.read(data))
  {
    float humidity = dht.getHumidity(); // ดึงค่าความชื้น
    float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ
    
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    Serial.print(dht.getStatusString());
    Serial.print("\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Serial.print("\t\t");
    Serial.println(dht.toFahrenheit(temperature), 1);

    Serial.println(); 
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    
    lcd.setCursor(0, 0);
//    String text = "PM1:" +  data.PM_AE_UG_1_0 + " 2.5:" + data.PM_AE_UG_2_5
    lcd.print(String("PM1: ") + String(data.PM_AE_UG_1_0) +  String(" 2.5: ") + String(data.PM_AE_UG_2_5));
    
    lcd.setCursor(0, 1);
    lcd.print(String("PM10: ") + String(data.PM_AE_UG_10_0));
    
    delay(2000);
    
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("humidity: " + String(humidity));
    
    lcd.setCursor(0, 1);
    lcd.print("Temp: " + String(temperature) + " C");
    
    delay(2000);
  }
 
}
