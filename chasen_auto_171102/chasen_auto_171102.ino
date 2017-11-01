
#include <Servo.h>

#include <ros.h>
#include <std_msgs/Empty.h>
Servo spcon_chasen;
Servo spcon_chasen_lift;
Servo spcon_turntable;
Servo servo_hisyaku;
Servo servo_arm1;
Servo servo_arm2;
Servo servo_arm3;
Servo servo_arm4;
ros::NodeHandle nh;
int start_flg = 0;

int spcon_stop_duty;
int spcon_cw_duty;
int spcon_ccw_duty;

int servo_stop_duty ;
int servo_cw_duty ;
int servo_ccw_duty;

void messageCb( const std_msgs::Empty& toggle_msg) {
  start_flg = 1;

}
ros::Subscriber<std_msgs::Empty> sub("start", &messageCb );

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
  //servo_arm4.attach(13);      //D13

  Serial.begin(9600); // open a serial connection to your computer
  Serial.setTimeout(10000UL); // タイムアウト設定（10秒）

  spcon_stop_duty = 90;
  spcon_cw_duty = 180;
  spcon_ccw_duty = 0;

  servo_stop_duty = 90;
  servo_cw_duty = 180;
  servo_ccw_duty = 0;


  spcon_chasen.write(spcon_stop_duty);
  spcon_chasen_lift.write(spcon_stop_duty);
  spcon_turntable.write(spcon_stop_duty);
  servo_hisyaku.write(servo_stop_duty);
  servo_arm1.write(servo_stop_duty);
  servo_arm2.write(servo_stop_duty);
  servo_arm3.write(servo_stop_duty);
  //servo_arm4.write(servo_stop_duty);

  start_flg = 0;


  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);   // blink the led

  //  nh.initNode();
  // nh.subscribe(sub);
}

void loop() {
  // nh.spinOnce();
  // delay(1);


  // put your main code here, to run repeatedly:
  int val_in_0 = 0;       //D2
  int val_in_1 = 0;       //D3
  int val_in_2 = 0;       //D4
  int val_in_3 = 0;       //D5
  int val_in_4 = 0;       //A0
  int val_in_5 = 0;       //A1
  int ana_in_1 = 0;       //A5

  int pc_input_char;

  val_in_0 = digitalRead(2);
  val_in_1 = digitalRead(3);
  val_in_2 = digitalRead(4);
  val_in_3 = digitalRead(5);
  val_in_4 = digitalRead(14);
  val_in_5 = digitalRead(15);
  ana_in_1 = analogRead(5);    // アナログピンを読み取る

  pc_input_char = Serial.read();

  if (pc_input_char != -1 ) {
    // 読み込んだデータが -1 以外の場合以下の処理を行う
    switch (pc_input_char) {
      case 's':     //茶筅を動かす
        start_flg = 1;
        Serial.print("servo_arm1\n");

        break;
    }
  }


  if (start_flg) {

    //茶筅アーム
    Serial.print("servo_arm1\n");

    Serial.print("servo_arm2\n");

    Serial.print("servo_arm3\n");

    Serial.print("servo_arm4\n");
    //柄杓
    Serial.print("servo_hisyaku\n");

    //茶筅リフト
    Serial.print("spcon_chasen_lift\n");

    //茶筅
    Serial.print("spcon_chasen\n");

    //ターンテーブル
    Serial.print("spcon_turntable\n");

    digitalWrite(13, HIGH);   // blink the led
    delay(100);
    digitalWrite(13, LOW);   // blink the led
    delay(100);
    digitalWrite(13, HIGH);   // blink the led
    delay(100);
    digitalWrite(13, LOW);   // blink the led
    delay(100);


    start_flg = 0;

  }

}
