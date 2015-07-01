/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 * Rae Jeong :: raychanjeong@gmail.com :: following http://wiki.ros.org/rosserial_arduino/Tutorials/Blink
 */ 
 
 #include <ros.h>
 #include <std_msgs/Empty.h>
 
 ros::NodeHandle nh;
 
 void messageCb( const std_msgs::Empty& toggle_msg){
   digitalWrite(13, HIGH-digitalRead(13)); // Blink the LED
 }
 
 ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb);
 
 void setup()
 {
   pinMode(13, OUTPUT);
   nh.initNode();
   nh.subscribe(sub);
 }
 
 void loop()
 {
   nh.spinOnce();
   delay(1);
 }
 
