#include <Servo.h>

Servo spcon_chasen;
Servo spcon_chasen_lift;
Servo spcon_turntable;
Servo servo_hisyaku;
Servo servo_arm1;
Servo servo_arm2;
Servo servo_arm3;
Servo servo_arm4;

//スピコン変数
int spcon_stop_duty;
int spcon_cw_duty_table;
int spcon_ccw_duty_table;

//サーボ変数
int servo_stop_duty;
int hisyaku_stop_duty;
int hisyaku_open_duty;
//int servo_cw_duty;
int servo_ccw_duty;//茶さじ先端の回転角度
int servo_stop_duty2;//茶さじ先端の初期角度 arm2
int servo_stop_duty4;//茶さじ左の初期角度 arm4

//モード変数
int table_mode = 0;//-1:逆転禁止、0:両方可能、1：正転禁止
int table_cnt = 0;
int lift_mode = 0;//-1:逆転禁止、0:両方可能、1：正転禁止
int lift_cnt = 0;

//セットアップ関数
void setup() {
  // put your setup code here, to run once:

  //Input Port
  pinMode(2, INPUT_PULLUP);   //D2
  pinMode(3, INPUT_PULLUP);  //D3
  pinMode(4, INPUT_PULLUP);   //D4
  pinMode(5, INPUT_PULLUP);   //D5
  //pinMode(14, INPUT_PULLUP);  //A0
  //pinMode(15, INPUT_PULLUP);  //A1

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

  //duty比 /*****変更する変数******/
  spcon_stop_duty = 90;
  spcon_cw_duty_table = 120;//テーブル回転   //ゼネバストップの関係でいじらないように
  spcon_ccw_duty_table = 60;//テーブル逆回転　//ゼネバストップの関係でいじらないように
  servo_stop_duty = 90;
  servo_stop_duty2 = 95;
  servo_stop_duty4 = 160;
  hisyaku_stop_duty = 71;//柄杓初期角度
  hisyaku_open_duty = 180;//柄杓回転角度
  //servo_cw_duty = 170;
  servo_ccw_duty = 30;//茶さじ　先端

  spcon_chasen.write(spcon_stop_duty);
  spcon_chasen_lift.write(spcon_stop_duty);
  spcon_turntable.write(spcon_stop_duty);
  servo_hisyaku.write(hisyaku_stop_duty);
  servo_arm1.write(servo_stop_duty);
  //servo_arm2.write(servo_stop_duty);
  servo_arm2.write(servo_stop_duty2);
  servo_arm3.write(servo_stop_duty);
  //servo_arm4.write(servo_stop_duty);
  servo_arm4.write(servo_stop_duty4);
  
}

//main loop関数
void loop() {
  
  // put your main code here, to run repeatedly:
  int val_in_0 = 0;       //D2//リフト上
  int val_in_1 = 0;       //D3//リフト下
  int val_in_2 = 0;       //D4//テーブル後
  int val_in_3 = 0;       //D5//テーブル前
  //int val_in_4 = 0;       //A0
  //int val_in_5 = 0;       //A1
  int ana_in_1 = 0;       //A5//可変抵抗
  int pc_input_char;

  //データ読み込み
  val_in_0 = digitalRead(2);//リフト上
  val_in_1 = digitalRead(3);//リフト下
  val_in_2 = digitalRead(4);//テーブル後
  val_in_3 = digitalRead(5);//テーブル前
  //val_in_4 = digitalRead(14);//何もつないでいない
  //val_in_5 = digitalRead(15);//何もつないでいない
  ana_in_1 = analogRead(5);    // アナログピンを読み取る

  //リミットスイッチによる停止指令（リフト）
    if(val_in_0==0){//リミットスイッチ上ON
        if(lift_cnt == 0)spcon_chasen_lift.write(spcon_stop_duty);
        lift_mode = 1;//正転禁止
        lift_cnt = 1;
    }else if(val_in_1==0){//リミットスイッチ下ON
        if(lift_cnt == 0)spcon_chasen_lift.write(spcon_stop_duty);
        lift_mode = -1;//逆転禁止
        lift_cnt = 1;       
    }else{
        lift_mode = 0;
        lift_cnt = 0;
    }

  //リミットスイッチによる停止指令（テーブル）
    if(val_in_3==0){//リミットスイッチ前ON
        if(table_cnt == 0)spcon_turntable.write(spcon_stop_duty);
        table_mode = 1;//正転禁止
        table_cnt = 1;
    }else if(val_in_2==0){//リミットスイッチ後ろON
        if(table_cnt == 0)spcon_turntable.write(spcon_stop_duty);
        table_mode = -1;//逆転禁止
        table_cnt = 1;
    }else{
        table_mode = 0;
        table_cnt = 0;
    }

  //モード確認 /*******変更*******/
  //Serial.print("  mode:");
  //Serial.print(table_mode);//テーブル
  //Serial.print(lift_mode);//リフト
  
  //cnt確認 /*******変更*******/
  //Serial.print("  table_cnt:");//テーブル
  //Serial.print(table_cnt);
  //Serial.print(" lift_cnt:");//リフト
  //Serial.print(lift_cnt);

  // 文字列を送信
  Serial.print(" In:");
  Serial.print("  リフト上in_0:");
  Serial.print(val_in_0); 
  Serial.print("  リフト下in_1:");
  Serial.print(val_in_1);
  Serial.print("  テーブル後in_2:");
  Serial.print(val_in_2);
  Serial.print("  テーブル前in_3:");
  Serial.print(val_in_3);
  //Serial.print("  in_4:");
  //Serial.print(val_in_4);
  //Serial.print("  in_5:");
  //Serial.print(val_in_5);
  //Serial.print("  ana_5:");//可変抵抗。不要なので、コメント化。
  //Serial.print(ana_in_1);
  Serial.print("\n");

  // シリアルポートより1文字読み込む
  pc_input_char = Serial.read();

  //duty指定0～180  /*****変更する変数******/
  int spcon_cw_duty_ch1 = 180;//150;//茶筌
  int spcon_cw_duty_ch2 = 120;//リフトダウン
  int spcon_ccw_duty_ch2 = 60;//リフトアップ
  int servo_down = 65;
  int servo_kaiten =100;
  int servo_kaiten2 = 125;
  int hurui = 3;

  if (pc_input_char != -1 ) {
    // 読み込んだデータが -1 以外の場合以下の処理を行う
    switch (pc_input_char) {

    //1,2     茶筅
    //3,4,5   リフト
    //6,7,8   ターンテーブル
    //9,0     柄杓
    //q,w     ARM1 茶さじ根本
    //e,r     ARM2
    //t,y     ARM3
    //s,d   　ARM4 茶さじ先端  "a"は不要のため、削除
    //f,g     茶さじ動作
    //i,o,m   シーケンス　i(in)：動作、m(max):動作、o(out):戻り動作
    
    
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
       if(lift_mode == -1){
          spcon_chasen_lift.write(spcon_stop_duty);
       }else{//リミットスイッチ下OFF
          for (int i = spcon_stop_duty; i < spcon_cw_duty_ch2; i++) {
            val_in_1 = digitalRead(3);//リフト下
            if(val_in_1==0){//台形制御中の停止
              spcon_chasen_lift.write(spcon_stop_duty);
            }else{
              spcon_chasen_lift.write(i);
            }
          }
          delay(50);
        }
        break;
        
      case '4':   //リフト停止
        spcon_chasen_lift.write(spcon_stop_duty);
        break;
        
      case '5':   //リフトアップ
        if(lift_mode == 1){
          spcon_chasen_lift.write(spcon_stop_duty);
       }else{//リミットスイッチ上OFF
          for (int i = spcon_stop_duty; i > spcon_ccw_duty_ch2; i--) {
              val_in_0 = digitalRead(2);//リフト上
              if(val_in_0==0){//台形制御中の停止
                spcon_chasen_lift.write(spcon_stop_duty);
              }else{
                spcon_chasen_lift.write(i);
              }
              delay(50);
           }
       }
        break;

      case '6': //ターンテーブル正回転
       if(table_mode == 1){
          spcon_turntable.write(spcon_stop_duty);
          //Serial.print("stop");
          //Serial.print("\n");
       }else{//リミットスイッチ前OFF
          for (int i = spcon_stop_duty; i < spcon_cw_duty_table; i++) {
             val_in_3 = digitalRead(5);//テーブル前
             if(val_in_3==0){//台形制御中の停止。
                spcon_turntable.write(spcon_stop_duty);
             }else{
                spcon_turntable.write(i);
             }
             delay(50);
          }
        } 
        break;

      case '7': //ターンテーブル停止
        spcon_turntable.write(spcon_stop_duty);
        break;
        
      case '8': //ターンテーブル逆回転
        if(table_mode == -1){//リミットスイッチ前ON
          spcon_turntable.write(spcon_stop_duty);
        }else{//リミットスイッチ前OFF
          for (int i = spcon_stop_duty; i > spcon_ccw_duty_table; i--) {
            val_in_2 = digitalRead(4);//テーブル後
            if(val_in_2==0){//台形制御中の停止。
                spcon_turntable.write(spcon_stop_duty);
             }else{
                spcon_turntable.write(i);
             }
            delay(50);
          }
        }
        break;
        /*
        //スイッチに無関係で動作
        for (int i = spcon_stop_duty; i > spcon_ccw_duty_table; i--) {
          spcon_turntable.write(i);
        }
        break;
        */

      case '9':   //柄杓可動
        for (int i = hisyaku_stop_duty; i < hisyaku_open_duty; i++) {
          servo_hisyaku.write(i);
          delay(20);
        }
        break;

      case '0': //柄杓停止
        for (int i = hisyaku_open_duty; i > hisyaku_stop_duty; i--) {
          servo_hisyaku.write(i);
          delay(20);
        }
        break;

      case 'q'://arm1 茶さじ根本 cw
        for (int i = servo_stop_duty; i < servo_kaiten2; i++) {
          servo_arm1.write(i);
          delay(20);
        }
        break;
      
      case 'w'://arm1 茶さじ根本 stop
        for (int i = servo_kaiten2; i > servo_stop_duty; i--) {
          servo_arm1.write(i);
          delay(20);
        }
        break;
        
      case 'r': //arm2 左サーボ 下げ（正面から見て）
        for (int i = servo_stop_duty2; i > servo_down; i--) {
          servo_arm2.write(i);
          delay(20);
        }
        break;
      
      case 'e': //arm2 左サーボ stop
        for (int i = servo_down; i < servo_stop_duty2; i++) {
          servo_arm2.write(i);
          delay(20);
        }
        break;
      
      case 't'://arm3 右サーボ　//サーボ故障中
        for (int i = servo_stop_duty; i > 70; i--) {
          servo_arm3.write(i);
          delay(20);
        }
        break;
      
      case 'y':   //arm3 右サーボ stop　//サーボ故障中
        for (int i = 70; i < servo_stop_duty; i++) {
          servo_arm3.write(i);
          delay(20);
        }
        break;
        
      /*
      case 'a': //arm4 茶さじ先端 CW　//不要
        for (int i = servo_stop_duty; i < servo_cw_duty; i++) {
          servo_arm4.write(i);
          delay(20);
        }
        break;
      */
      
      case 's'://arm4 茶さじ先端 初期位置
        for (int i = servo_ccw_duty; i < servo_stop_duty4; i++) {
          servo_arm4.write(i);
          delay(10);
        }
        break;

      case 'd'://arm4 茶さじ先端 CCW
        for (int i = servo_stop_duty4; i > servo_ccw_duty; i--) {
          servo_arm4.write(i);
          delay(10);
        }
        break;

      case 'f'://茶さじ動作シーケンス draft
        //arm4 茶さじ先端
        for (int i = servo_stop_duty; i > servo_ccw_duty; i--) {
          servo_arm4.write(i);
          delay(10);
        }
        //arm2 左サーボ　ダウン
        for (int i = servo_stop_duty2; i > servo_down; i--) {
          servo_arm2.write(i);
          delay(10);
        }
        //arm1 茶さじ根本
        for (int i = spcon_stop_duty; i < servo_kaiten; i++) {
          servo_arm1.write(i);
          delay(50);
        }
        //arm4 茶さじ先端
        for (int i = servo_ccw_duty; i < servo_stop_duty4; i++) {
          servo_arm4.write(i);
          delay(10);
        }
        //左サーボ　アップ
        for (int i = servo_down; i < servo_stop_duty2; i++) {
          servo_arm2.write(i);
          delay(20);
        }
        //arm1 茶さじ根本
        for (int i = servo_kaiten; i < servo_kaiten2; i++) {
          servo_arm1.write(i);
          delay(20);
        }
         //arm4 茶さじ先端
        for (int i = servo_stop_duty4; i > servo_ccw_duty; i--) {
          servo_arm4.write(i);
          delay(5);
        }
        for (int i = servo_ccw_duty; i < servo_stop_duty4; i++) {
          servo_arm4.write(i);
          delay(5);
        }
        break;

     case 'g'://茶さじ戻り動作
        for (int i = servo_kaiten2; i > servo_stop_duty; i--) {
          servo_arm1.write(i);
          delay(10);
        }
        break;

     case 'i'://シーケンス動作（ノーマルスピード）
        //柄杓可動
        for (int i = hisyaku_stop_duty; i < hisyaku_open_duty; i++) {
          servo_hisyaku.write(i);
          delay(20);
        }
        delay(500);
        for (int i = hisyaku_open_duty; i > hisyaku_stop_duty; i--) {
          servo_hisyaku.write(i);
          delay(20);
        }         

        //茶さじ動作　すくう
        //arm4 茶さじ先端
        for (int i = servo_stop_duty2; i > (servo_stop_duty4-90); i--) {
          servo_arm4.write(i);
          delay(10);
        }
        //arm2 左サーボ　ダウン
        for (int i = servo_stop_duty2; i > servo_down; i--) {
          servo_arm2.write(i);
          delay(10);
        }
        //arm1 茶さじ根本
        for (int i = spcon_stop_duty; i < servo_kaiten; i++) {
          servo_arm1.write(i);
          delay(50);
        }
        //arm4 茶さじ先端
        for (int i = (servo_stop_duty4-90); i < servo_stop_duty4; i++) {
          servo_arm4.write(i);
          delay(50);
        }
        //左サーボ　アップ
        for (int i = servo_down; i <  (servo_down+15); i++) {
          servo_arm2.write(i);
          delay(50);
        }
        //茶さじ ふるい 3回
         for (int i = servo_kaiten; i < (servo_kaiten + hurui); i++) {
          servo_arm1.write(i);
          delay(100);
        }
        delay(100);
         for (int i = (servo_kaiten + hurui); i < (servo_kaiten - hurui); i--) {
          servo_arm1.write(i);
          delay(500);
        }
        delay(100);
        for (int i = (servo_kaiten - hurui); i < (servo_kaiten + hurui); i++) {
          servo_arm1.write(i);
          delay(100);
        }
        delay(100);
        for (int i = (servo_kaiten + hurui); i < (servo_kaiten - hurui); i--) {
          servo_arm1.write(i);
          delay(500);
        }
        delay(100);
        for (int i = (servo_kaiten - hurui); i < (servo_kaiten + hurui); i++) {
          servo_arm1.write(i);
          delay(100);
        }
        delay(100);
        for (int i = (servo_kaiten + hurui); i < (servo_kaiten - hurui); i--) {
          servo_arm1.write(i);
          delay(500);
        }
        delay(100);
        for (int i = (servo_kaiten - hurui); i < servo_kaiten; i++) {
          servo_arm1.write(i);
          delay(100);
        }
        //左サーボ　アップ
        for (int i = (servo_down+15); i < servo_stop_duty2; i++) {
          servo_arm2.write(i);
          delay(50);
        }
        //arm1 茶さじ根本
        for (int i = servo_kaiten; i < servo_kaiten2; i++) {
          servo_arm1.write(i);
          delay(150);
        }
        //arm4 茶さじ先端
        for (int i = servo_stop_duty4; i > servo_ccw_duty; i--) {
          servo_arm4.write(i);
          delay(10);
        }
        for (int i = servo_ccw_duty; i < servo_stop_duty4; i++) {
          servo_arm4.write(i);
          delay(10);
        }
        //茶さじ動作 戻り
        for (int i = servo_kaiten2; i > servo_stop_duty; i--) {
          servo_arm1.write(i);
          delay(10);
        }
        
       //リフトダウン
       for (int i = spcon_stop_duty; i < spcon_cw_duty_ch2; i++) {
          spcon_chasen_lift.write(i);
       }
        delay(50);        
        while(1){
          val_in_1 = digitalRead(3);//リフト下
          if(val_in_1==0){
            spcon_chasen_lift.write(spcon_stop_duty);
            break;
          }
        }
        
        //茶筌　抹茶たて
        for (int i = spcon_stop_duty; i < spcon_cw_duty_ch1; i++) {
          spcon_chasen.write(i);
          delay(50);
        }
        delay(500);/*****変更*******/
        for (int i = spcon_cw_duty_ch1; i > spcon_stop_duty; i--) {
          spcon_chasen.write(i);
          delay(50);
        }
        
       //リフトアップ
       for (int i = spcon_stop_duty; i > spcon_ccw_duty_ch2; i--) {
          spcon_chasen_lift.write(i);
          delay(50);
       } 
       while(1){
          val_in_0 = digitalRead(2);//リフト上
          if(val_in_0==0){
            spcon_chasen_lift.write(spcon_stop_duty);
            break;
          }
        }
        
       //回転テーブル
       for (int i = spcon_stop_duty; i < spcon_cw_duty_table; i++) {
          spcon_turntable.write(i);
       }
       delay(50);        
       while(1){
          val_in_3 = digitalRead(5);//テーブル前
          if(val_in_3==0){
            spcon_turntable.write(spcon_stop_duty);
            break;
          }
        }
        break;

     case 'o'://シーケンス動作（終了）
        //回転テーブル
       for (int i = spcon_stop_duty; i > spcon_ccw_duty_table; i--) {
          spcon_turntable.write(i);
       }
       delay(50);        
       while(1){
           val_in_2 = digitalRead(4);//テーブル後
          if(val_in_2==0){
            spcon_turntable.write(spcon_stop_duty);
            break;
          }
        }
        break;
      
     }
  } else {
    // 読み込むデータが無い場合は何もしない
  }
}
