
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN    12          // trigger Pin
#define ECHO_PIN    11          // Echo Pin
#define MAX_DISTANCE 200 //公分計算


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);    // 設定 NewPing 物件，並給與最遠測試距離
Servo myservo;
char ch ;
int pos = 0;
int cm = 0;
int delay_time = 500;
void setup() {
  Serial.begin(115200);         // 開啟串列埠顯示 ping 的距離值
  myservo.attach(9);
}


void loop() {                       
  // 等待 50 毫秒，需大於前程式說明的 29 秒



  if (Serial.available()){
    ch = Serial.read();
  }
  unsigned int uS = sonar.ping();   // 送出 ping，並取得微秒 microseconds(uS) 時間
  cm = sonar.convert_cm(uS);
  Serial.print("Ping: ");
  Serial.print(cm);    // 換算時間為公分，如顯示 0，表示超出距離範圍
  Serial.println("cm");

  if ( ch  == '1' || ( cm >= 3 && cm <= 20) ){
    myservo.write(180);    // 告訴 servo 走到 'pos' 的位置
    delay_time = 3000;
  }
  else if (ch == '0'|| ( cm < 3 || cm > 20)){
    myservo.write(30);   // 告訴 servo 走到 'pos' 的位置
    delay_time = 50;
  }
  Serial.print(pos);
  delay(delay_time); 
}
