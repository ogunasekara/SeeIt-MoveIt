#include <ros.h>
#include <std_msgs/UInt16.h>
#include "nRF24L01.h" //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"  

#define VEL_THRESHOLD 1470
#define ANG_VEL_THRESHOLD 1460
#define MOVE_THRESHOLD 10

int vel = 0;
int ang_vel = 0;

int SentMessage = 0; // Used to store value before being sent through the NRF24L01
RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

std_msgs::UInt16 confirm_msg;

ros::NodeHandle nh;
ros::Publisher confirm_pub("confirm", &confirm_msg);

/* ROS CALLBACK FUNCTIONS */

void ang_vel_callback(const std_msgs::UInt16& msg){
  ang_vel = msg.data - ANG_VEL_THRESHOLD;
}

void vel_callback(const std_msgs::UInt16& msg){
  vel = msg.data - VEL_THRESHOLD;
}

/* HELPER FUNCTIONS */

bool is_moving(int vel){
  return !(abs(vel) < MOVE_THRESHOLD);
}

void move_robot(){
  if (!is_moving(vel) && !is_moving(ang_vel)){
    SentMessage = 000;
  } 
  else if (!is_moving(vel) && (ang_vel > 0)){
    SentMessage = 010;
  }
  else if (!is_moving(vel) && (ang_vel < 0)){
    SentMessage = 020;
  }
  else if (!is_moving(ang_vel) && (vel > 0)){
    SentMessage = 100;
  }
  else if (!is_moving(ang_vel) && (vel < 0)){
    SentMessage = 200;
  }
  else if ((vel < 0) && (ang_vel < 0)){
    SentMessage = 220;
  }
  else if ((vel < 0) && (ang_vel > 0)){
    SentMessage = 210;
  }
  else if ((vel > 0) && (ang_vel < 0)){
    SentMessage = 120;
  }
  else if ((vel > 0) && (ang_vel > 0)){
    SentMessage = 110;
  }

  if(!radio.write(&SentMessage, sizeof(int))){
    return;
  }

//  confirm_msg.data = SentMessage;
//  confirm_pub.publish(&confirm_msg);
}

ros::Subscriber <std_msgs::UInt16> vel_sub("vel", &vel_callback);
ros::Subscriber <std_msgs::UInt16> ang_vel_sub("ang_vel", &ang_vel_callback);

void setup(void){  
  nh.initNode();
  nh.subscribe(vel_sub);
  nh.subscribe(ang_vel_sub);

  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
}

void loop(void){
//  Serial.println("LOOPING...");
  move_robot();
  nh.spinOnce();
  delay(100);
}
