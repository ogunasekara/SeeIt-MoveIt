#include <ros.h>
#include <std_msgs/UInt16.h>

#define VEL_PIN 11
#define ANG_VEL_PIN 12

ros::NodeHandle nh;

std_msgs::UInt16 vel_msg;
std_msgs::UInt16 ang_vel_msg;

ros::Publisher vel_pub("/vel", &vel_msg);
ros::Publisher ang_vel_pub("/ang_vel", &ang_vel_msg);

int val12 = 0;
int new_val12;
float k12 = .3;
int err12;

int val11 = 0;
int new_val11;
float k11 = .3;
int err11;
  
void setup() {
  Serial.begin(9600);
  pinMode(VEL_PIN, INPUT);
  pinMode(ANG_VEL_PIN, INPUT);

  nh.initNode();
  nh.advertise(vel_pub);
  nh.advertise(ang_vel_pub);
}

void loop() {
  new_val12 = pulseIn(ANG_VEL_PIN, HIGH);
  err12 = new_val12 - val12;
  val12 = val12 + k12*err12;
  
  new_val11 = pulseIn(VEL_PIN, HIGH);
  err11 = new_val11 - val11;
  val11 = val11 + k12*err11;
  
  Serial.print(val12);
  Serial.print('\t');
  Serial.print(val11);
  Serial.println('\t');

  vel_msg.data = val11;
  ang_vel_msg.data = val12;
  
  vel_pub.publish(&vel_msg);
  ang_vel_pub.publish(&ang_vel_msg);
  
  nh.spinOnce();  
  delay(1);
}
