void CHECK_START(){
  digitalWrite(MUX_S0, LOW);
  digitalWrite(MUX_S1, HIGH);
  digitalWrite(MUX_S2, HIGH);
  digitalWrite(IR_EMIT_PIN, HIGH);  // turn on all IR emittor pins
  delayMicroseconds(200);
  ir_6 = analogRead(MUX_OUTPUT);
  ir_6_obstacle = !(ir_6 / 700);
  if(ir_6_obstacle_pre == true && ir_6_obstacle == false) flag_start ^= 1;
  ir_6_obstacle_pre = ir_6_obstacle;
  if(!(flag_start)){
    digitalWrite(BACK_LEFT_LED, HIGH);
    digitalWrite(BACK_RIGHT_LED, HIGH);
  }
  else{
    digitalWrite(BACK_LEFT_LED, LOW);
    digitalWrite(BACK_RIGHT_LED, LOW);    
  }
}
