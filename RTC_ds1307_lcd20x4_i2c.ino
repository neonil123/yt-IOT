#include "Wire.h"
#include "LCD.h"
#include "LiquidCrystal_I2C.h"
#include "RTClib.h"

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd (0x3F,2,1,0,4,5,6,7); //I2C Configuration

char week [7] [4] ={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  void setup()

  {
    Serial.begin(9600);
    // LCD Configuration
    lcd.begin(20,4);
    lcd.setBacklightPin(3,POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.clear();
    //RTC Configuration
    if(!rtc.begin()){
      Serial.println("ERROR");
      return;
    }

    if(!rtc.isrunning()){
      rtc.adjust(DateTime(__DATE__,__TIME__)); // set time in the rtc first time
      Serial.println("TIME-SET");
    }
    
  }



 void loop(){

  DateTime now = rtc.now();
  lcd.setCursor(0,1);
  lcd.print(now.hour(),DEC);
  lcd.print(':');
  lcd.print(now.minute(),DEC);
  lcd.print(':');
  lcd.print(now.second(),DEC);

  lcd.setCursor(0,0);
  lcd.print(week[now.dayOfTheWeek()]);
  lcd.print(" ");
  lcd.print(now.year(),DEC);
  lcd.print('/');
  lcd.print(now.month(),DEC);
  lcd.print('/');
  lcd.print(now.day(),DEC);

  Serial.println(now.second());
  
  int i = now.second();

  delay(1000);
  if(i==59){
    lcd.clear(); //Clear the display every second
    Serial.println("CLEAR");
  }
 }

 

















  
