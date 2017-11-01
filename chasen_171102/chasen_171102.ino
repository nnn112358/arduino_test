#include <Servo.h>

Servo spcon_chasen;
Servo spcon_chasen_lift;
Servo spcon_turntable;
Servo servo_hisyaku;
Servo servo_arm1;
Servo servo_arm2;
Servo servo_arm3;
Servo servo_arm4;

int spcon_stop_duty;
int spcon_cw_duty;
int spcon_ccw_duty;

int servo_stop_duty ;
int servo_cw_duty ;
int servo_ccw_duty ;

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
  Serial.setTimeout(10000UL); // タイムアウト設定（10秒）

  spcon_stop_duty = 90;
  spcon_cw_duty = 180;
  spcon_ccw_duty = 0;

  servo_stop_duty = 90;
  servo_cw_duty = 170;
  servo_ccw_duty = 10;

  spcon_chasen.write(spcon_stop_duty);
  spcon_chasen_lift.write(spcon_stop_duty);
  spcon_turntable.write(spcon_stop_duty);
  servo_hisyaku.write(servo_stop_duty);
  servo_arm1.write(servo_stop_duty);
  servo_arm2.write(servo_stop_duty);
  servo_arm3.write(servo_stop_duty);
  servo_arm4.write(servo_stop_duty);
}

void loop() {
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

  Serial.print("In:");       // 文字列を送信
  Serial.print("_in_0:");
  Serial.print(val_in_0);
  Serial.print("_in_1:");
  Serial.print(val_in_1);
  Serial.print("_in_2:");
  Serial.print(val_in_2);
  Serial.print("_in_3:");
  Serial.print(val_in_3);
  Serial.print("_in_4:");
  Serial.print(val_in_4);
  Serial.print("_in_5:");
  Serial.print(val_in_5);
  Serial.print("_ana_5:");
  Serial.print(ana_in_1);
  Serial.print("\n");

  // シリアルポートより1文字読み込む
  pc_input_char = Serial.read();
  int spcon_cw_duty_ch1 = 120;
  int spcon_cw_duty_ch2 = 120;
  int spcon_ccw_duty_ch2 = 60;
  int spcon_turntable_ccw = 0;
  int servo_arm1_ccw = 60;


  if (pc_input_char != -1 ) {
    // 読み込んだデータが -1 以外の場合以下の処理を行う
    switch (pc_input_char) {

    //1,2     茶筅
    //3,4,5   リフト
    //6,7,8   ターンテーブル
    //9,0     柄杓
    //q,w     ARM1
    //e,r     ARM2
    //t,y     ARM3
    //a,s,d   ARM4
    


      case '1':     //茶筅を動かす
        for (int i = spcon_stop_duty; i < spcon_cw_duty_ch1; i++) {
          spcon_chasen.write(i);
          delay(50);
        }
        break;
      case '2':   //茶筅が止まる
        for (int i = spcon_cw_duty_ch1; i > spcon_stop_duty; i--) {
          spcon_chasen.write(i);
          delay(50);
        }
        break;


      case '3':   //リフトダウン
        for (int i = spcon_stop_duty; i < spcon_cw_duty_ch2; i++) {
          spcon_chasen_lift.write(i);
          delay(50);

        }
        break;
      case '4':   //リフト停止
        spcon_chasen_lift.write(spcon_stop_duty);
        break;
      case '5':   //リフトアップ
        for (int i = spcon_stop_duty; i > spcon_ccw_duty_ch2; i--) {
          spcon_chasen_lift.write(i);
          delay(50);
        }
        break;


      case '6': //ターンテーブル正回転
        for (int i = spcon_stop_duty; i < spcon_cw_duty; i++) {
          spcon_turntable.write(i);
          delay(50);
        }
        break;
      case '7': //ターンテーブル停止
        spcon_turntable.write(spcon_stop_duty);
        break;
      case '8': //ターンテーブル逆回転
        for (int i = spcon_cw_duty; i > spcon_stop_duty; i--) {
          spcon_turntable.write(spcon_turntable_ccw);
          delay(50);
        }
        break;


      case '9':   //柄杓可動
        for (int i = servo_stop_duty; i < servo_cw_duty; i++) {
          servo_hisyaku.write(i);
          delay(50);
        }
        break;
      case '0': //柄杓停止
        for (int i = servo_cw_duty; i > servo_stop_duty; i--) {
          servo_hisyaku.write(spcon_stop_duty);
          delay(50);
        }
        break;


      case 'q'://arm1 ccw
        for (int i = servo_stop_duty; i > servo_arm1_ccw; i--) {
          servo_arm1.write(i);
          delay(20);
        }
        break;
      case 'w'://arm1 stop
        for (int i = servo_arm1_ccw; i < servo_stop_duty; i++) {
          servo_arm1.write(i);
          delay(20);
        }

        break;
      case 'e': //arm2 stop
        for (int i = servo_stop_duty; i > servo_ccw_duty; i--) {
          servo_arm2.write(i);
          delay(10);
        }
        break;
      case 'r': //arm2 stop
        for (int i = servo_ccw_duty; i < servo_stop_duty; i++) {
          servo_arm2.write(i);
          delay(10);
        }
        break;
      case 't'://arm3 CW
        for (int i = servo_stop_duty; i < servo_cw_duty; i++) {
          servo_arm3.write(i);
          delay(20);
        }
        break;
      case 'y':   //arm3 stop
        for (int i = servo_cw_duty; i > servo_stop_duty; i--) {
          servo_arm3.write(i);
          delay(20);
        }

        break;
      case 'a': //arm4 CW
        for (int i = servo_stop_duty; i < servo_cw_duty; i++) {
          servo_arm4.write(i);
          delay(20);
        }
        break;
      case 's'://arm4 初期位置
        for (int i = servo_cw_duty; i > servo_stop_duty; i--) {
          servo_arm4.write(servo_stop_duty);
          delay(20);
        }
        break;

      case 'd'://arm4 CCW
        for (int i = servo_stop_duty; i > servo_ccw_duty; i--) {
          servo_arm4.write(i);
          delay(20);
        }
        break;

    }
  } else {
    // 読み込むデータが無い場合は何もしない

  }


}
