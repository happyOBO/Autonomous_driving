// wire library
#include <Wire.h> 

// Set I2C address
#define ADDRESS 0x04

// IR sensor pin map
#define MUX_S0 15  // Select IR
#define MUX_S1 16
#define MUX_S2 17
#define MUX_OUTPUT 21 // Read IR value
#define IR_EMIT_PIN 3 // IR emitter pin

// Motor pin map
#define MOTOR_LEFT_A 5 
#define MOTOR_LEFT_B 6 
#define MOTOR_RIGHT_A 10
#define MOTOR_RIGHT_B 9 

// LED pin map
#define FRONT_LEFT_LED 12
#define FRONT_RIGHT_LED 11
#define BACK_LEFT_LED  7
#define BACK_RIGHT_LED  8

// Buzzer pin map
#define BUZZER_PIN 14

// Driving
#define SPEED 60
#define K 3.5

// IR sensor values
float left =0;
float right = 0;
int ir_2, ir_4, ir_6;

//flag
bool count_switch =false; // Delay
bool motor_switch = true;
bool led_switch = true;
bool keep_going = false;
bool ir_6_obstacle = false;
bool ir_6_obstacle_pre = false;
bool flag_start = false;
bool flag_go_straight = false;
bool flag_cross = false;

int flag_counter = 0;
int cycle_counter = 0;

void setup() {
  // Motor pin
  pinMode(MOTOR_LEFT_A, OUTPUT);
  pinMode(MOTOR_LEFT_B, OUTPUT);
  pinMode(MOTOR_RIGHT_A, OUTPUT);
  pinMode(MOTOR_RIGHT_B, OUTPUT);

  // Buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);

  // LED pin
  pinMode(FRONT_LEFT_LED, OUTPUT);
  pinMode(FRONT_RIGHT_LED, OUTPUT);

  // IR sensors pin
  pinMode(MUX_S0,OUTPUT);
  pinMode(MUX_S1,OUTPUT);
  pinMode(MUX_S2,OUTPUT);
  pinMode(IR_EMIT_PIN, OUTPUT);
  
  //Init Motor STOP
  digitalWrite(MOTOR_LEFT_A, LOW);
  digitalWrite(MOTOR_RIGHT_A, LOW);
  digitalWrite(MOTOR_LEFT_B, LOW);
  digitalWrite(MOTOR_RIGHT_B, LOW);

  // I2C setting
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveData);

  Serial.begin(9600);

  // Waiting for making sure setup sequence to be done.
  delay(1000);
}
