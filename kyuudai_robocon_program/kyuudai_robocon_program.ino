int M0A=2,M0B=3;//右輪上
int M1A=4,M1B=5;//左輪下
int M2A=6,M2B=9;//左輪上
int M3A=45,M3B=46;//右輪下
int M4A=11,M4B=12;//アームの滑車
int ARM = 48; //エアー
int TOUCH = 22;//タッチセンサーの認識
int ReStart = 52;//電源回路についてる５V出力のスイッチの制御
unsigned long time_m = 0;
unsigned long time_n = 0;
unsigned long time_nagasa = 0;
int flag1 = 0;//タッチセンサ までの　条件分岐の　flag1
int flag2 = 0;//リスタートまでの条件分岐で使うflag2
int flag3 = 0;//台までの条件分岐で使うflag3
int flag4 = 0;


//最初からアームを上げておく
void setup() 
{
    // put your setup code here, to run once:
    pinMode(M0A, OUTPUT);
    pinMode(M0B, OUTPUT);
    pinMode(M1A, OUTPUT);
    pinMode(M1B, OUTPUT);
    pinMode(M2A, OUTPUT);
    pinMode(M2B, OUTPUT);
    pinMode(M3A, OUTPUT);
    pinMode(M3B, OUTPUT);
    pinMode(M4A, OUTPUT);
    pinMode(M4B, OUTPUT);
    pinMode(ARM, OUTPUT);
    pinMode(TOUCH,INPUT);
    pinMode(ReStart,INPUT);
    Serial.begin(115200);
    //Serial.begin(57600);
    
    int num;
    num = digitalRead(ReStart) ; //電源回路のスイッチの状態を読む
    int status = 0 ;
    
    if(digitalRead(TOUCH)  == HIGH)
    {
        status = status + 1;
    }
}

void loop() 
{
   int num;
   num = digitalRead(ReStart) ; //電源回路のスイッチの状態を読む
   int status = 0 ;
   
   if(digitalRead(TOUCH)  == HIGH)
   {
      status = status + 1;
      Serial.print(F("\r\n5VOFF ＆＆　タッチO"));
   }
  
   /* while (num == HIGH) {}
    time_m = micros();//スイッチが押され始めた時刻
    delayMicroseconds(20); //チャタリング対策
    Serial.println(time_m);
    while (num == LOW) {}
    time_n = micros(); //リスタートスイッチが話された時刻
    delayMicroseconds(20);
    time_nagasa = time_n - time_m; //スイッチが押下されて離された時間を算出*/

  
   if(num == HIGH)
   {
      if(status == 0)
      {
         Serial.print(F("\r\n5Von ＆＆　タッチOFF"));
         if(flag1==0)
         {
            Right();
            delay(1100);
            flag1++;
         }
         else
         {
            Stop(); 
         }
      }
      else
      {
         Serial.print(F("\r\n5Von ＆＆　タッチOn"));
         if ( flag2 == 0)
         {
            delay(900);
            Left();
            delay(1000);
            Up();
            delay(1800);
            Right();
            delay(1000);
            Up();
            delay(2000);
            Left();
            delay(800);
            Up();
            delay(2500);//リスタート位置到着
            flag2++;
         }
         else
         {
            Stop();
         }
      }
  }

  if(num == LOW)
  {
     if(status == 0)
     {
         Serial.print(F("\r\n5VOFF ＆＆　タッチO"));
         Stop();
     }
     else
     {
         Serial.print(F("\r\n5VOFF ＆＆　タッチ1"));
         //リスタート位置から
         if (flag3 == 0)
         {
          Serial.print(F("\r\n5VOFF ＆＆　タッチO flag3 == 0"));
            Right();
            delay(3000);
            Stop();
            delay(4000);
            flag3++;
         }
          
         if(flag3 == 1)
         {
             Serial.print(F("\r\n5VOFF ＆＆　タッチO flag3 == 0"));
              if(flag4 == 0){
                 ARMDOWN();
                  delay(3500);//アームを下げる
                  ARMSTOP();
                  delay(100);
                  ARMCATCH();
                  
              flag4++;
            } 
           if(flag4 ==1){
              Serial.print(F("\r\n5VOFF ＆＆　タッチO flag4 == 1"));
              ARMUP();
              delay(3600);//ゴールカップを掴む
            flag4++;
           } 
           if(flag4 ==2){
              Serial.print(F("\r\n5VOFF ＆＆　タッチO flag4 == 2"));       
            ARMSTOP();
           }
              flag3++;
         }
         
         if(flag3 == 2)
         {
            Left();
            delay(600);
            TurnRight();//右旋回(フィールドに依存）
            delay(1400);
            Right();//台に到着
            delay(2000);
            ARMLEAVE();
            delay(500);
            Right();
            delay(10);
            Stop();
            delay(10000); 
         }
     } 
  }
}

void Stop() {
 moterrun(M0A,M0B,0);//右輪上
 moterrun(M1A,M1B,0);//左輪上
 moterrun(M2A,M2B,0);//右輪下
 moterrun(M3A,M3B,0);//左輪下
 
}
void Up() {
 moterrun(M0A,M0B,-255);//右輪上
 moterrun(M1A,M1B,-255);//左輪下
 moterrun(M2A,M2B,-255);//左輪上
 moterrun(M3A,M3B,-255);//右輪下
 
}


void Left() {
 moterrun(M0A,M0B,-255);//右輪上
 moterrun(M1A,M1B,-255);//左輪上
 moterrun(M2A,M2B,255);//右輪下
 moterrun(M3A,M3B,255);//左輪下
  
}


void Down() {
  moterrun(M0A,M0B,255);//右輪上
 moterrun(M1A,M1B,255);//左輪上
 moterrun(M2A,M2B,255);//右輪下
 moterrun(M3A,M3B,255);//左輪下
}



void Right() {
 moterrun(M0A,M0B,255);//右輪上
 moterrun(M1A,M1B,255);//左輪上
 moterrun(M2A,M2B,-255);//右輪下
 moterrun(M3A,M3B,-255);//左輪下
}

void TurnRight(){
 moterrun(M0A,M0B,255);//右輪上
 moterrun(M1A,M1B,-255);//左輪上
 moterrun(M2A,M2B,255);//右輪下
 moterrun(M3A,M3B,-255);//左輪下
}

void TurnLeft(){
 moterrun(M0A,M0B,-255);//右輪上
 moterrun(M1A,M1B,255);//左輪上
 moterrun(M2A,M2B,255);//右輪下
 moterrun(M3A,M3B,-255);//左輪下
}





void ARMUP()
{
   moterrun(M4A,M4B,100);//アームをあげる
}

void ARMDOWN()
{
   moterrun(M4A,M4B,-100);//アームを下げる
}

void ARMSTOP()
{
  moterrun(M4A,M4B,0);//アームを下げる
}
void ARMCATCH()
{
   digitalWrite(ARM, HIGH);           //カップを掴む
}

void ARMLEAVE()
{
   digitalWrite(ARM, LOW); //カップを離す
} 


void moterrun(int pin1,int pin2,int power)
{
  if(power>=0)
  //正回転
  {
     analogWrite(pin1,power);
     analogWrite(pin2,0); 
  }
  else
  //逆回転
  {
     analogWrite(pin1,0);
     analogWrite(pin2,-power);
  }
  
  return;
}

void omni(int m0,int m1)
//（右輪、左輪）
{
   moterrun(M0A,M0B,m0);
   moterrun(M1A,M1B,m1);
   
   return;
}
