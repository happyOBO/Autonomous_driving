/*=====================================Loop=================================*/
void loop() {
  //if(flag_start == true && cycle_counter % 2500 == 0){
  //  led_switch ^= 1;
  //  flag_counter++;
  //  if(flag_counter >= 4){
  //    flag_start = false;
  //    flag_counter = 0;
  //  }
  //}

  // Checking start sign always
  CHECK_START();

  // Go straight test
  // if(flag_start == true && flag_cross == true) Go_Straight_R();

  // Linetracing
  AutoTracking();
  
  // count every end off loop
  // if(flag_start) cycle_counter++;
  // if(cycle_counter > 99999) cycle_counter = 0;  // Prevent overflow
}
/*==========================================================================*/
