#include <Wire.h> 

#define MUX_S0 15
#define MUX_S1 16
#define MUX_S2 17
#define MUX_OUTPUT 21

#define MOTOR_LEFT_A 5 
#define MOTOR_LEFT_B 6 
#define MOTOR_RIGHT_A 10
#define MOTOR_RIGHT_B 9 

#define IR_EMIT_PIN 3
#define IR_REMREC_PIN 4

#define RIGHT_FRONT_IR  1
#define LEFT_FRONT_IR   6 

#define RIGHT_BOTTOM_IR 2 //Hardware interrupt Setup
#define LEFT_BOTTOM_IR  4

#define RIGHT_REAR_IR   3
#define LEFT_REAR_IR    5 

#define FRONT_LEFT_LED 12
#define FRONT_RIGHT_LED 11
#define BACK_LEFT_LED  7
#define BACK_RIGHT_LED  8

#define BUZZER_PIN 14

/*===========================================Line==================================*/


// Control
int s1,s2;
int normal = 0;

/*===========================================Line==================================*/
void setup() {
  
  // put your setup code here, to run once:
  pinMode(MOTOR_LEFT_A, OUTPUT);
  pinMode(MOTOR_LEFT_B, OUTPUT);
  pinMode(MOTOR_RIGHT_A, OUTPUT);
  pinMode(MOTOR_RIGHT_B, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  pinMode(FRONT_LEFT_LED, OUTPUT);
  pinMode(FRONT_RIGHT_LED, OUTPUT);
  
  pinMode(MUX_S0,OUTPUT);
  pinMode(MUX_S1,OUTPUT);
  pinMode(MUX_S2,OUTPUT);
  pinMode(MUX_OUTPUT,OUTPUT);
  digitalWrite(IR_EMIT_PIN,HIGH);
  Serial.begin(115200);
  
  
  // OLED setup
  /*display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); //create  cleared display image
  display.display(); //display the cleared image
  //Hardware interrupt setup
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);  // Prevents Pi from launching its boot script
  digitalWrite(Z_LED, LOW); // led will be off to indicate
    
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);// Start at top-left corner

 
  Serial.print(F("Zumi version "));
  Serial.println(VERSION_NUMBER);
  //  Serial.println(F(__FILE__));
  Serial.println (F( __DATE__ " " __TIME__ " Ard ver." xstr(ARDUINO) "."));
  irTest();//checks the state of the IR sensors

  delay(50);
  
  while(1){  
    // LED setup
    pinMode(FRONT_RIGHT_LED, OUTPUT);
    pinMode(FRONT_LEFT_LED, OUTPUT);
    pinMode(BACK_RIGHT_LED, OUTPUT);
    pinMode(BACK_LEFT_LED, OUTPUT);
    pinMode(Z_LED, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    */
    /*
    analogWrite(MOTOR_LEFT_A, 100);
    analogWrite(MOTOR_LEFT_B, 0);
    analogWrite(MOTOR_RIGHT_A, 100);
    analogWrite(MOTOR_RIGHT_B, 0);
  
    Serial.begin(9600);
    digitalWrite(FRONT_RIGHT_LED, HIGH);
    digitalWrite(FRONT_LEFT_LED, HIGH);
    delay(1000);
    digitalWrite(FRONT_RIGHT_LED, LOW);
    digitalWrite(FRONT_LEFT_LED, LOW);
    delay(1000);
    analogWrite(MOTOR_LEFT_A, 0);
    analogWrite(MOTOR_LEFT_B, 0);
    analogWrite(MOTOR_RIGHT_A, 0);
    analogWrite(MOTOR_RIGHT_B, 0);
    break;
    int i;
    wakeUpSound();
    delay(2000);
    Sound_FireBall();
    delay(2000);
    chargingSound();
    delay(2000);
    
    Serial.begin(9600);

  }
  while(1){
    //업데이트 반복 . 50milli초마다 체크
    if((millis() +1) % 50 == 0){
      recieveData();// What recieveData??
      //일단 에니메이션이 한 번 발생하면 카운트 다운을 시작한다.
      if(arduinoI2CMaster == false && warningcounter <200){
        warningCounter ++;
      }
      if(warningCounter >= 200){
      
        //반복 시키려는 메인코드를 이쪽에 삽입 시켜라.
        checkIfPibooted(); // What is checkIfPibooted ? : 50초 이상 아무 문제 없다면
        //주미를 일으킨다. 그리고 메인코드를 읽을것이다.
      }
      // PI가 부팅 되는 동안 코드는 게쏙해서 반복 될 것이다.
      //
      if( arduinoI2CMaster == true){
        switch(chargingState){ // 어떻게 CASE 1,2,3 인지 아냐?
          case GOOD_BATTERY_DETECTED : { //CASE 3
            //주비가 정상적으로 부팅될경우
            if(chargeOnlyMode == true
               && batteryVoltage > MIN_BATTERY_VOLTAGE)
            {
              zumi_bootCountdown();// What is zubi_bootCountdown
              // 100보다 작으면 count를 계속 1증가시킨다
              // 40보다
            }
            if(chargeOnlyMode == false && batteryVoltage > MIN_BATTERY_VOLTAGE)
            {
              zumi_wakeUpAnimation();
            }
            break;
          }
          case LOW_BATTERY_DETECTED : // CASE 2
          {
            delay(20);
            // 
          }
          case USB_POWER_DETECTED: //1 
          {
            if (chargeOnlyMode == true)
            {
              bootupCounter = 0;
              zumi_ChargingAnimation();
            }
            else
            {
              zumi_WakeUpAnimation();
            }
            break;
          }//end switch(ChargingState) //What chargingState?
        }//end of if(arduinoI2CMaster) // What arduinoI2CMaster : 단지 변수
        // recieveData(); 함수가 가장 먼저 실행이 된다 arduinoI2CMater는 그때 초기설정 됨
        if(batteryVoltage <= USB_VOLTAGE_DETECTED)
        {
          if(chargingState != USB_POWER_DETECTED)
          {
            LEDbyte=0b00000000;
            chargingSound(); // what charginSound?
          }
        }
        else if(batteryVoltage > USB_VOLTAGE_DETECTED && batteryVoltage < = MIN_BATTERY_VOLTAGE)
        {
          LEDbyte = 0b11110000;
          chargingState = LOW_BATTERY_DETECTED;

          if((millis()/1000)%10 == 0)
          {
            Sound_Beep1();
          }
        }
        else if(batteryVoltage > MIN_BATTERY_VOLTAGE)
        {
          if(chargingState != GOOD_BATTERY_DETECTED)
          {
            batteryPowerBeep(); // BatteryPowerBeep : 
            LEDbyte = 0b00000000; //LEDbyte가 뭐일까 그냥 변수 선언한거 아닌가?
          }
          chargingState = GOOD_BATTERY_DETECTED;
        }// 이부분이 뭔데 UPDATE LED, BATTERY LEVEL하냐
        
      }
      LEDcount++;
      batteryCount++;//if문 계속 돌때마다 Update해주는거구나
    }//결국 아무것도 들어있지 않은  우리 주미찡은 켜지고 애니메이션만 보여주고 아무 동장안하는구나.
  if(noteType >= 0) playNote(noteType, noteDuration);
  //playNote는 뭐하는놈임?
  }*/

}

void loop() {
  // put your main code here, to run repeatedly:
  AutoTracking();
  
/*
  delay(1000);
  digitalWrite(FRONT_RIGHT_LED, LOW);
  digitalWrite(FRONT_LEFT_LED, LOW);
*/
          
  
}
void AutoTracking(){
  // RIGHT IR
  digitalWrite(MUX_S0, LOW);
  digitalWrite(MUX_S1, HIGH);
  digitalWrite(MUX_S2, LOW);
  delayMicroseconds(200);
  s1 = analogRead(MUX_OUTPUT);
  // LEFT IR
  digitalWrite(MUX_S0, LOW);
  digitalWrite(MUX_S1, LOW);
  digitalWrite(MUX_S2, HIGH);
  delayMicroseconds(200);
  s2 = analogRead(MUX_OUTPUT);

  s1 = map(s1, 45, 850, 0, 100);
  s2 = map(s2, 45, 880, 0, 100);
  
  normal = s1*(-1) + s2;

  setMotorsToSpeed(50-normal,50+normal);  
}
void checkIfPiBooted(){ //실행시킬 수 있는 상황인지 확인
  if ((millis() / 1000>50) //what millis??
      && displayWarring ==false
      && PiBooted == false
      && chargeOnlyMode == false){
        digitalWrite(Z_LED, LOW); //Z_LED 끄기
        digitalWrite(2, HIGH); //무엇을 키느냐?
        display.drowBitmap(0,0,cant_wake_up,1 28,64,1); // X_X 화면띄우기
      }
}

void setMotorsToSpeed(int speedM1, int speedM2)
{
  byte motorState = 0;
  
  if (speedM1 < 0) {
    speedM1 = abs(speedM1);
  }
  if (speedM2 < 0) {
    speedM2 = abs(speedM2);
  }
  Serial.println(spdA);
  analogWrite(MOTOR_LEFT_A, speedM1);
  analogWrite(MOTOR_LEFT_B, 0);
  analogWrite(MOTOR_RIGHT_A, speedM2);
  analogWrite(MOTOR_RIGHT_B, 0);
}

void SoundProcess(int _melody[], int _tempo[], int _size)
{
  for (int thisNote = 0; thisNote < _size; thisNote++)
  {
    int noteDuration = 1000 / _tempo[thisNote];
    tone(BUZZER_PIN, _melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
}
void wakeUpSound()
{
  //  int melody[] = {1319, 1568, 2637, 2093, 2349, 3136};
  //  int tempo[] = {25, 25, 25, 25, 25, 25};
  int melody[] = {1319, 1568, 2637, 2093, 2349, 3136};
  int tempo[] = {25, 25, 25, 25, 25, 25};
  SoundProcess(melody, tempo, 6);

}
void chargingSound()
{
  int melody[] = {1500, 1500, 1500, 3000, 2000, 2500, 2500};
  int tempo[] = {25, 25, 25, 25, 25, 25, 25};
  SoundProcess(melody, tempo, 7);
}

void Sound_Beep1()
{
  int melody[] = {2637, 1568, 1216};
  int tempo[] = {16, 16, 12};
  SoundProcess(melody, tempo, 3);
}
//----------------------------------------------------------------------------------//
void Sound_Beep2()
{
  int melody[] = {167, 593};
  int tempo[] = {64, 8};

  SoundProcess(melody, tempo, 2);
}
void Sound_Beep3()
{
  int melody[] = {167, 314};
  int tempo[] = {64, 8};

  SoundProcess(melody, tempo, 2);
}
void batteryPowerBeep()
{
  int melody[] = {2437, 1968, 1216, 900};
  int tempo[] = {25, 25, 25, 25};
  SoundProcess(melody, tempo, 3);
}

//----------------------------------------------------------------------------------//

void Sound_Coin()
{
  int melody[] = {988, 1319};
  int tempo[] = {16, 2};
  SoundProcess(melody, tempo, 2);
}
//----------------------------------------------------------------------------------//

void Sound_FireBall()
{
  int melody[] = {392, 784, 1568};
  int tempo[] = {36, 36, 36};
  SoundProcess(melody, tempo, 3);
}
