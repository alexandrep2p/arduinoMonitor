#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() { 
 Serial.begin(9600);
 lcd.init();
 lcd.setBacklight(HIGH);
}
  
String readStringSerial(){
  String content = "";
  char character;
  
  while(Serial.available() > 0) {
    character = Serial.read();
    content.concat(character);
    delay(20);
  } 
  return content;
}

String splitData(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void loop() {
  if (Serial.available() > 0){
    String receivedData = readStringSerial();
    String line01 = splitData(receivedData,';',1);
    String line02 = splitData(receivedData,';',0);
    lcd.setCursor(0,1);
    lcd.print(line01);
    lcd.setCursor(0,0);
    lcd.print(line02);
  }
}
