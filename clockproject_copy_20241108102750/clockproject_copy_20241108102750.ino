/*
* Name: clock and temp project
* Author: Victor Huke
* Date: 2024-10-10
* Description: This project uses a ds3231 to measure time and displays the time to an 1306 oled display,
* Further, it measures temprature with a analog temprature module and displays a mapped value to a 9g-servo-motor
*/

// Include Libraries
#include <RTClib.h>
#include <Wire.h>
#include <U8glib.h>


// Init constants

// Init global variables

// construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup() {
  // init communication
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  
  // Init Hardware
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  //Settings
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  u8g.setFont(u8g_font_unifont);
}

void loop() {

  oledWrite("Time: " + getTime(),"Temp: " + String(getTemp()));
  setColor(int(trunc(getTemp())), 0, 0);
  delay(1000);

}


/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime() {
  DateTime now = rtc.now();
  return String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}

/*
* This function reads an analog pin connected to an analog temprature sensor and calculates the corresponding temp
*Parameters: Void
*Returns: temprature as float
*/
float getTemp() {
  return rtc.getTemperature();
}

/*
* This function takes a string and draws it to an oled display
*Parameters: - text: String to write to display
*Returns: void
*/
void oledWrite(String text1,String text2) {
  u8g.firstPage();
  do {
    u8g.drawStr(0, 22, text1.c_str());
    u8g.drawStr(0, 44, text2.c_str());
  } while (u8g.nextPage());
}

void setColor(int red, int green, int blue) {
  red = red - 18;
  red = red*red;
  analogWrite(2, red);
  analogWrite(3, green);
  analogWrite(4, blue);
  Serial.println(red);
}
