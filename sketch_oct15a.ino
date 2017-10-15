#include <Servo.h>

Servo spcon_chasen;
Servo spcon_chasen_lift;
Servo spcon_turntable;
Servo servo_hisyaku;
Servo servo_arm1;
Servo servo_arm2;
Servo servo_arm3;
Servo servo_arm4;


void setup() {
  // put your setup code here, to run once:

  //Input Port
  pinMode(2, INPUT_PULLUP);   //D2
  pinMode(3, INPUT_PULLUP);  //D3
  pinMode(4, INPUT_PULLUP);   //D4
  pinMode(5, INPUT_PULLUP);   //D5
  pinMode(14, INPUT_PULLUP);  //A0
  pinMode(15, INPUT_PULLUP);  //A1
  
  //OutPort
  spcon_chasen.attach(6);     //D6
  spcon_chasen_lift.attach(7);//D7
  spcon_turntable.attach(8);  //D8
  servo_hisyaku.attach(9);    //D9
  servo_arm1.attach(10);      //D10
  servo_arm2.attach(11);      //D11
  servo_arm3.attach(12);      //D12
  servo_arm4.attach(13);      //D13

  Serial.begin(9600); // open a serial connection to your computer

}

void loop() {
  // put your main code here, to run repeatedly:
  int val_in_0 = 0;
  int val_in_1 = 0;
  int val_in_2 = 0;
  int val_in_3 = 0;
  int val_in_4 = 0;
  int val_in_5 = 0;

  val_in_0 = digitalRead(2);
  val_in_1 = digitalRead(3);
  val_in_2 = digitalRead(4);
  val_in_3 = digitalRead(5);
  val_in_4 = digitalRead(14);
  val_in_5 = digitalRead(15);
    
  Serial.print("In:");       // 文字列を送信
  Serial.print("_in_0:");       // 文字列を送信
  Serial.print(val_in_0);       // 文字列を送信
  Serial.print("_in_1:");       // 文字列を送信
  Serial.print(val_in_1);       // 文字列を送信
  Serial.print("_in_2:");       // 文字列を送信
  Serial.print(val_in_2);       // 文字列を送信
  Serial.print("_in_3:");       // 文字列を送信
  Serial.print(val_in_3);       // 文字列を送信
  Serial.print("_in_4:");       // 文字列を送信
  Serial.print(val_in_4);       // 文字列を送信
  Serial.print("_in_5:");       // 文字列を送信
  Serial.print(val_in_5);       // 文字列を送信
  Serial.print("\n");       // 文字列を送信
}
