/*
 * rosserial SRF08 Ultrasonic Ranger Example
 * rosserial example using SRF08 Ultrasonic sensor with Arduino
 * Rae Jeong :: raychanjeong@gmail.com  :: following http://wiki.ros.org/rosserial_arduino/Tutorials/SRF08%20Ultrasonic%20Range%20Finder
 */

#include <Sonar_srf08.h> // SRF08 specific library

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Wire.h>
#include <ros.h>
#include <std_msgs/Float32.h>

// Set up the ros node and publisher
std_msgs::Float32 sonar_msg;
ros::Publisher pub_sonar("sonar", &sonar_msg);
ros::NodeHandle nh;

Sonar_srf08 MySonar; // Create MySonar object

#define CommandRegister 0x00
int New_Address = 248; // 0xF8
#define ResultRegister 0x02

float sensorReading = 0;

char unit = 'i'; // 'i' for inches, 'c' for centimeters

void setup()
{
  MySonar.connect();
  MySonar.changeAddress(CommandRegister, New_Address);
  New_Address += 4;
  nh.initNode();
  nh.advertise(pub_sonar);
}

long publisher_timer;

void loop()
{
  if (millis() > publisher_timer) {
    
    // Request reading from sensor
    MySonar.setUnit(CommandRegister, New_Address, unit);
    
    // Pause
    delay(70);
    
    // Set registar for reading
    MySonar.setRegister(New_Address, ResultRegister);
    
    // Read data from result register
    sensorReading = MySonar.readData(New_Address, 2);
    
    sonar_msg.data = sensorReading;
    pub_sonar.publish(&sonar_msg);
    
    publisher_timer = millis() + 4000; // Publish once a second
    
  }
  
  nh.spinOnce();
}

