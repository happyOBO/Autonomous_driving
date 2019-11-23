


#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/UInt16.h>

//void ros_init();
void leftpwm_commandCb(const std_msgs::Int16& cmd);
void rightpwm_commandCb(const std_msgs::Int16& cmd);
void result_yoloCb(const std_msgs::String& cmd);
void InitPWM();

ros::NodeHandle nh;
ros::Subscriber<std_msgs::String> subresult_yolo("result_yolo", &result_yoloCb);
ros::Subscriber<std_msgs::Int16> subLeftPwm_cmd("cmd_lpwm", leftpwm_commandCb);
ros::Subscriber<std_msgs::Int16> subRightPwm_cmd("cmd_rpwm", rightpwm_commandCb);


void leftpwm_commandCb(const std_msgs::Int16& cmd)
{
  
}

void rightpwm_commandCb(const std_msgs::Int16& cmd)
{

}
void result_yoloCb(const std_msgs::String& cmd)
{

}

void setup() {
  
 nh.initNode();
 nh.subscriber(subresult_yolo);
 nh.subscribe(subLeftPwm_cmd);
 nh.subscribe(subRightPwm_cmd);
}

void loop() {
  
 nh.spinOnce();
 delay(1);
}
