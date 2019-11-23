Ros with Arduino

ros를 이용해 Arduino를 제어하기위한 틀이다.


먼저 ros에 rosserial을 설치해야한다.

설치방법은 http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup 참고.

실행순서는 roscore > rosrun rosserial_python serial_node.py /dev/ttyACM0 > rostopic pub 토픽이름/자료형 이다.

이때 /dev/ttyACM0의 ttyACM0부분은 arduino에 연결한 port를 확인하여 그 이름을 넣어주어야 한다.



코드설명


#include <ros.h> //ROS Arduino프로그램을 사용하기 위한 header file



#include <std_msgs/String.h> //String형식의 message를 위한 header file



#include <std_msgs/Int16.h> //Int16형식의 message를 위한 header file



#include <std_msgs/UInt16.h> //UInt16형식의 message를 위한 header file

void leftpwm_commandCb(const std_msgs::Int16& cmd); //subscrber를 위한 callback함수 정의

void rightpwm_commandCb(const std_msgs::Int16& cmd); //subscrber를 위한 callback함수 정의

void result_yoloCb(const std_msgs::String& cmd); //subscrber를 위한 callback함수 정의

void InitPWM();

ros::NodeHandle nh; //publisher와 subscriber, serial port communications를 위한 nodehandle 객체화

ros::Subscriber<std_msgs::String> subresult_yolo("result_yolo", &result_yoloCb); //subscriber와 구독할 topic을 객체화

ros::Subscriber<std_msgs::Int16> subLeftPwm_cmd("cmd_lpwm", leftpwm_commandCb); //subscriber와 구독할 topic을 객체화

ros::Subscriber<std_msgs::Int16> subRightPwm_cmd("cmd_rpwm", rightpwm_commandCb); //subscriber와 구독할 topic을 객체화

//subsciber를 위한 callback함수

void leftpwm_commandCb(const std_msgs::Int16& cmd) 

{
  
}

void rightpwm_commandCb(const std_msgs::Int16& cmd) 

{

}

void result_yoloCb(const std_msgs::String& cmd) 

{

}

//nodehandle과 subscriber초기화

void setup() { 
 nh.initNode();
 nh.subscriber(subresult_yolo);
 nh.subscribe(subLeftPwm_cmd);
 nh.subscribe(subRightPwm_cmd);
}

void loop() { //동작에 사용되는 코드들이 위치할 곳, ros::spinOnce는 Ros communication callback들이 다뤄지는 곳이다.
 
 nh.spinOnce();
 delay(1);
}


추가구현

yolo에서 보내는 int16muㅣtiarray형의 topic을 subscribe하기위한 코드를 추가적으로 구현 할 예정이다.
