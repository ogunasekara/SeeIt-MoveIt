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

int SentMessage[1] = {000}; // Used to store value before being sent through the NRF24L01
RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

/* ROS CALLBACK FUNCTIONS */

void ang_vel_callback(const std_msgs::UInt16& msg){
  vel = msg.data - ANG_VEL_THRESHOLD;
}

void vel_callback(const std_msgs::UInt16& msg){
  ang_vel = msg.data - VEL_THRESHOLD;
}

/* HELPER FUNCTIONS */

bool is_moving(int vel){
  return !(abs(vel) < MOVE_THRESHOLD);
}

void move_robot(){
  if (!is_moving(vel) && !is_moving(ang_vel)){
    SentMessage[0] = 00;
  } 
  else if (!is_moving(vel) && (ang_vel > 0)){
    SentMessage[0] = 01;
  }
  else if (!is_moving(vel) && (ang_vel < 0)){
    SentMessage[0] = 02;
  }
  else if (!is_moving(ang_vel) && (vel > 0)){
    SentMessage[0] = 10;
  }
  else if (!is_moving(ang_vel) && (vel < 0)){
    SentMessage[0] = 20;
  }
  else if ((vel < 0) && (ang_vel < 0)){
    SentMessage[0] = 22;
  }
  else if ((vel < 0) && (ang_vel > 0)){
    SentMessage[0] = 21;
  }
  else if ((vel > 0) && (ang_vel < 0)){
    SentMessage[0] = 12;
  }
  else if ((vel > 0) && (ang_vel > 0)){
    SentMessage[0] = 11;
  }

  Serial.println(SentMessage[0]);
  radio.write(SentMessage, 1);
}

ros::NodeHandle nh;
ros::Subscriber<std_msgs::UInt16> vel_sub("/vel", &vel_callback);
ros::Subscriber<std_msgs::UInt16> ang_vel_sub("/ang_vel", &ang_vel_callback);

void setup(void){
  Serial.begin(9600);

  nh.initNode();
  nh.subscribe(vel_sub);
  nh.subscribe(ang_vel_sub);

  nh.spinOnce();
  
  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
}

void loop(void){
  move_robot();
  nh.spinOnce();
  delay(1);
}
