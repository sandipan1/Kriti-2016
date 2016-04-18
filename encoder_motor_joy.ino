#include <Wire.h>
#include <ros.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle nh;

void SpeedRun(byte Address,int Speed)
{
  Wire.beginTransmission(Address);
  Wire.write(1);
  Wire.write(Speed      &0xff);
  Wire.write((Speed >>8) &0xff);
  Wire.endTransmission();//stops transmitting
}

void SetMaxSpeed(byte Address,int Speed)
{
  Wire.beginTransmission(Address);
  Wire.write(0);
  Wire.write(Speed);
  Wire.write(0);
  Wire.endTransmission();
}

void SetDamping(byte Address,byte Damping)
{
  Wire.beginTransmission(Address);
  Wire.write(2);
  Wire.write(Damping);
  Wire.write(0);
  Wire.endTransmission();
  delay(500);//for storing settings
  
}
void MoveAbs(byte Address, long Position)
{
   Wire.beginTransmission(Address);
   Wire.write(4);
   Wire.write(Position         & 0xff); 
   Wire.write((Position >>  8) & 0xff);
   Wire.write((Position >> 32) & 0xff);
   Wire.write((Position >> 24) & 0xff);
   Wire.endTransmission();
}
void MoveRel(byte Address,int Position)
{
  Wire.beginTransmission(Address);
  Wire.write(8);
  Wire.write(Position         &0xff);
  Wire.write((Position >>  8) &0xff);
  Wire.write((Position >> 32) &0xff);
  Wire.write((Position >> 24) &0xff);
  Wire.endTransmission();
}    



void Callback(const sensor_msgs::Joy& joy)
{byte left_motor=0x0F;  
 byte right_motor=0x1e;
  
  int a,b,left,right,up,down;
  a = joy.axes[1];
  b= joy.axes[0];
  if (a>0)
  up=1;
  if (a<0)
  down=-1;
  if (b>0)
  left=1;
  if(b<0)
  right=-1;
  SetDamping(left_motor,255);
  SetDamping(right_motor,255);
  if (up==1)
  { 
    SpeedRun(left_motor,255);
    SpeedRun(right_motor,255);  
  } 
  if (down==-1)
  {
  SpeedRun(left_motor,-255);
  SpeedRun(right_motor,-255);
  }     
if (left==1)
{
SpeedRun(left_motor,-255);
    SpeedRun(right_motor,255);
  }
  if (right==-1)
{SpeedRun(left_motor,255);
    SpeedRun(right_motor,-255);}





       } 
}
    
  
  
  
  
  
  
  
  




ros::Subscriber<sensor_msgs::Joy> sub("p", Callback);
void setup(){
  
  nh.initNode();
  nh.subscribe(sub);
}

void loop(){
  nh.spinOnce();
  delay(1);
}


