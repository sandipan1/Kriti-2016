#include <ros.h>
#include <Wire.h>
#include <sensor_msgs/Joy.h>
ros::NodeHandle nh;

void joyCallback(const sensor_msgs::Joy& joymsg)
{ int a;
  a = joymsg->axes[1];
  digitalWrite(13,HIGH - digitalRead(13));  
}

ros::Subscriber<sensor_msgs::Joy> sub("joy",&joyCallback);

void setup()
{ pinMode(13,OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}
  
void loop()
{ 
  nh.spinOnce();
  delay(1);
}

