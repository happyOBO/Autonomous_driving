void Go_Straight_L(){
  if(!(flag_go_straight)){
    led_switch = true;
    flag_go_straight = true;
  }
  if(flag_start) cycle_counter++;
  
  if(flag_start == true && cycle_counter % 2500 == 0){
    led_switch ^= 1;
    flag_counter++;
    if(flag_counter >= 3){
      flag_cross = false;
      flag_counter = 0;
      flag_go_straight = false;
    }
  }
  //Serial.println(flag_go_straight);
}
void Go_Straight_R(){
  if(!(flag_go_straight)){
    led_switch = false;
    flag_go_straight = true;
  }
  if(flag_start) cycle_counter++;
  
  if(flag_start == true && cycle_counter % 2500 == 0){
    led_switch ^= 1;
    flag_counter++;
    if(flag_counter >= 3){
      flag_cross = false;
      flag_counter = 0;
      flag_go_straight = false;
    }
  }
  //Serial.println(flag_go_straight);
}
