#include <math.h>
#include <Wire.h>
#include <FaBoLCDmini_AQM0802A.h>
FaBoLCDmini_AQM0802A lcd;
 

//　ラジエータfファン制御pin
int FAN_SOCKET = 3;//digital

// 温度センサpin　サーミスタ
int THERMISTOR_SOCKET = 4;//analog
int tu_s=40;
int tl_s=35;
int tu_limit=90;
int tl_limit=70;

//button1
int button1= 8;
int button2= 9;
int i;


float analogReadVoltage(int analogPin) {
  return analogRead(analogPin) * 5 / 1024.0;
}


void setup() {
  Serial.begin(9600);
  pinMode( 3, OUTPUT);//radiator fan pin
  pinMode( 4, INPUT); //thermistor Pin
	pinMode( 8, INPUT);//button1 pin
  pinMode( 9, INPUT); //button2 Pin
   // set up the LCD:
  lcd.begin();
  // Print a message to the LCD.
  lcd.print("hello!");
 delay(2000);
}


void loop() {
//  i++;
//  while(i<10){
//    digitalWrite(FAN_SOCKET,LOW);
//    return 0;
//    }
  
  if(digitalRead(8)==LOW){
   tu_s=tu_s+1;
   if(tu_s>tu_limit){
     tu_s=30;
     delay(20);
     while(digitalRead(8)==LOW){}
   }
  }
   if(digitalRead(9)==LOW){
   tl_s=tl_s+1;
   if(tl_s>tl_limit){
     tl_s=20;
     delay(20);
     while(digitalRead(9)==LOW){}
   }
  }


  
  float x = analogReadVoltage(4);
  float temp = -2.3644*x*x*x+19.468*x*x-71.244*x+139.12;

  Serial.print("Voltage:");
  Serial.print(x);
  Serial.print(";");
  Serial.print("digitalRead(3);");
  Serial.print(digitalRead(3));
//  Serial.print(";");
//  Serial.print("checkSensor:");
//  Serial.print(checkSensor());
  
  Serial.print(";");
  Serial.print("temperature:");
  Serial.println(temp);

  if(temp > tu_s){
    i=1;
    if(i==1){
      digitalWrite(FAN_SOCKET,HIGH);  //
      }
  }
  if(temp < tl_s){
    i=0;
    if(i==0){
      digitalWrite(FAN_SOCKET,LOW);  //
      }
  }
  lcd.clear();
  lcd.print("Tc"); lcd.print(":"); 
  lcd.print(temp);lcd.print(" ");
  lcd.print(tu_s);lcd.print(",");lcd.print(tl_s);
  delay(500);
  }
//
//  int checkSensor() {
//  float y = analogReadVoltage(THERMISTOR_SOCKET);
//  float temp1 = -2.3644*y*y*y+19.468*y*y-71.244*y+139.12;
//  int flag;
//    //センサの値が閾値を超えていたら1を、閾値以下であれば0を返す関数
//  if (temp1 > tu_s) { return 1;} else if(temp1 < tl_s){return 0;}
//
//}
