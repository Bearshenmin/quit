/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 31 May 2022 00:44:51 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd_i2c(0x27);

#include <LRTC.h>

int get_field_from_time_string(const String& time_str, int field_index) {
  // field_index [0,1,2,3,4,5] = [Year,Month,Day,Hour,Minute,Sec]
  int fields[6] = {0};
  sscanf(time_str.c_str(), "%d-%d-%dT%d:%d:%d+08",
          &fields[0], &fields[1], &fields[2],
          &fields[3], &fields[4], &fields[5]);
  if(field_index < 0 || field_index > 5) {
    return 0;
  } else {
    return fields[field_index];
  }
}

String get_time_from_RTC() {
  // get time from the RTC module
  LRTC.get();

  // format to time string
  static char buffer[] = "YYYY-MM-DDTHH:MM:SS+08";
  sprintf(buffer, "%04ld-%02ld-%02ldT%02ld:%02ld:%02ld+08",
    LRTC.year(),
    LRTC.month(),
    LRTC.day(),
    LRTC.hour(),
    LRTC.minute(),
    LRTC.second());

  return String(buffer);
}

void setup()
{
  lcd_i2c.begin(16, 2);
  LRTC.begin();
  lcd_i2c.backlight();
  lcd_i2c.clear();
  LRTC.set(2022, 5, 31, 8, 50, 0);
}


void loop()
{
  lcd_i2c.setCursor(0,0);
  lcd_i2c.print(get_field_from_time_string(get_time_from_RTC(), 0));
  delay(1000);
}