#include <Servo.h>
Servo myservo;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
#include <LiquidCrystal.h>
#define LCD_RS 12 // Chân RS của LCD kết nối với chân 12 của Arduino
#define LCD_EN 11 // Chân EN của LCD kết nối với chân 11 của Arduino
#define LCD_D4 8  // Chân D4 của LCD kết nối với chân 8 của Arduino
#define LCD_D5 7  // Chân D5 của LCD kết nối với chân 7 của Arduino
#define LCD_D6 6  // Chân D6 của LCD kết nối với chân 6 của Arduino
#define LCD_D7 5  // Chân D7 của LCD kết nối với chân 5 của Arduino
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

int goc =0; //góc ban đầu
#define nut1 2
#define nut2 3
bool thuan = true;
bool nguoc = false;
bool tt = false;
String chieuquay = " ";
long time =0;
void setup() {
  myservo.attach(4);  // attaches the servo on pin 9 to the servo object
  myservo.write(goc);
  myservo2.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.write(goc);
  lcd.begin(16, 2); // Khởi động màn hình LCD 16x2
  pinMode(nut1, INPUT_PULLUP);
  pinMode(nut2, INPUT_PULLUP);
  Serial.begin(9600);
  hienthi();
  time = millis();
}
void hienthi(){
  lcd.setCursor(0, 0);
    lcd.print("GOC HT:         ");
    lcd.setCursor(10, 0);
    lcd.print(goc);
    lcd.setCursor(0, 1);
    lcd.print("TRANG THAI:     ");
    lcd.setCursor(10, 1);
    lcd.print(chieuquay);
}
void loop() {
  if(digitalRead(nut1) == 0 && tt == false){
   tt = true;
   time = millis();
   Serial.println("DA NHAN NUT 1");
  }
  if(thuan == true && tt == true){
    Serial.println("CHAY THUAN");
    chieuquay = " THUAN";
    goc = goc + 1;
    myservo.write(goc);
    hienthi();
    if(millis() - time >= 5000){
    myservo2.write(goc);
    }
    delay(30);
    if(goc >= 180){
      thuan = false;
      nguoc = true; 
    }
  }

  if(nguoc == true && tt == true){
    Serial.println("CHAY NGUOC");
    goc = goc - 1;
    chieuquay = " NGUOC";
    myservo.write(goc);
    hienthi();
    delay(30);
    if(goc <= 0){
      thuan = true;
      nguoc = false; 
    }
  }

  if(digitalRead(nut2) == 0){
    Serial.println("DUNG");
    chieuquay = " DUNG";
    tt = false;
  }  
}
