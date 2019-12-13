void AutoTracking(){
  if(led_switch){
    digitalWrite(FRONT_LEFT_LED,LOW);
    digitalWrite(FRONT_RIGHT_LED,HIGH);
    digitalWrite(MUX_S0, LOW);    // Choose PT2 IR sensor which is left side
    digitalWrite(MUX_S1, HIGH);
    digitalWrite(MUX_S2, LOW);
    digitalWrite(IR_EMIT_PIN, HIGH);  // turn on all IR emittor pins
    delayMicroseconds(200);
    ir_2 = analogRead(MUX_OUTPUT);  // read a IR value (in this case PT2)
    float normal = (512 - ir_2) / K;  // 512 is threshold(because input value is 0~1023)
                                        // and to be sure, 512 is not a exact threshold value
                                        // i will explain why later.
    left = SPEED - normal;  // left motor pwm
    right = SPEED + normal; // right motor pwm
  } else{ // When led_switch is FALSE and same things but PT4.
    digitalWrite(FRONT_LEFT_LED,HIGH);
    digitalWrite(FRONT_RIGHT_LED,LOW);
    digitalWrite(MUX_S0, LOW);
    digitalWrite(MUX_S1, LOW);
    digitalWrite(MUX_S2, HIGH);
    digitalWrite(IR_EMIT_PIN, HIGH);
    delayMicroseconds(200);
    ir_4 = analogRead(MUX_OUTPUT);
    float normal = (512 - ir_4) / K; 
    left = SPEED + normal;
    right = SPEED - normal;
  }
  setMotorsToSpeed(left,right);
}

void setMotorsToSpeed(int speedM1, int speedM2)
{
  if(flag_start){
    if(motor_switch){ 
      if(speedM1 < 0){
        speedM1 = -speedM1;
        if(speedM1 > 255) speedM1 = 255;
        analogWrite(MOTOR_LEFT_A, 0);
        analogWrite(MOTOR_LEFT_B, speedM1);
      }
      else{
        if(left > 255) speedM1 = 255;
        analogWrite(MOTOR_LEFT_A, speedM1);
        analogWrite(MOTOR_LEFT_B, 0);
      }
      if(right < 0){
        speedM2 = -speedM2;
        if(speedM2 > 255) speedM2 = 255;
        analogWrite(MOTOR_RIGHT_A, 0);
        analogWrite(MOTOR_RIGHT_B, speedM2);
      }
      else{
        if(speedM2 > 255) speedM2 = 255;
        analogWrite(MOTOR_RIGHT_A, speedM2);
        analogWrite(MOTOR_RIGHT_B, 0);
      }    
    }
    else{  // when motor_switch is FALSE, motors stop.
      digitalWrite(MOTOR_LEFT_A, LOW);
      digitalWrite(MOTOR_LEFT_B, LOW);
      digitalWrite(MOTOR_RIGHT_A, LOW);
      digitalWrite(MOTOR_RIGHT_B, LOW);
    }    
  }
  else{  // when motor_switch is FALSE, motors stop.
    digitalWrite(MOTOR_LEFT_A, LOW);
    digitalWrite(MOTOR_LEFT_B, LOW);
    digitalWrite(MOTOR_RIGHT_A, LOW);
    digitalWrite(MOTOR_RIGHT_B, LOW);
  }
}
void receiveData(){
  if(Wire.available()){
    byte receiveByte = Wire.read();
    byte commandType = receiveByte >>1; //총 3bit frame data = XXY, XX
    byte command = receiveByte & 0x01; //Get Y
    /*
    byte commandType = receiveByte >>6; //총 8bit frame data = XXYYYZZZ, XX
    byte command = receiveByte & 0x38; //Get 3rd-5th significant bits =YYY
    byte extraBit = receiveByte & 0x07; // get 3 least significant bits = ZZZ
    */
    switch(receiveByte){
      case 0 :  //drive
        motor_switch = true;
        break;
      case 1 : //stop
        motor_switch = false;
        break;
    }
//    switch(commandType){
//      byte turncom = commandType & 0x01;
//      case 0 : //keep going
//        motor_switch = true;
//        count_switch = true;
//        led_switch = true;
//        break;
//        
//      case 1 : //stop
//        motor_switch = false;
//        count_switch = false;
//        break;
//        
//      case 2 : //right
//        motor_switch = true;  
//        count_switch = false;
//        led_switch = true;    
//        break;
//        
//      case 3 : // left
//        motor_switch = true;
//        count_switch = false;
//        led_switch = false;
//        break;
//
//      case 4 : // go straight
//        motor_switch = true;
//        flag_cross = true;
//    }
  }
}
