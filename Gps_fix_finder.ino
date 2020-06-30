#include<SoftwareSerial.h>
#include<TinyGPS.h>
#include<Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);
TinyGPS gps;
SoftwareSerial ss(3, 4);


void setup() {
  
  Serial.begin(9600);
  ss.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("GPS Fix Finder");
  lcd.setCursor(0,1);
  lcd.print("v1.0");
  delay(5000);
  lcd.clear();
}

void loop() {
  
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }
if(newData)
{
  float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Satellite Fix");
    delay(2000);
    lcd.clear();
  
    
    lcd.print("SAT=");
    lcd.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    delay(2000);

    lcd.setCursor(0,0);
    lcd.print("Coordinates");
    delay(2000);
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("LAT=");
    lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    
    lcd.setCursor(0,1);
    lcd.print("LON=");
    lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(2000);
    lcd.clear();
    }
else{
    lcd.setCursor(0,0);
    lcd.print("Finding");
    lcd.setCursor(0,1);
    lcd.print("Satellites");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Please Wait");
    delay(2000);
    lcd.clear();
}
}
