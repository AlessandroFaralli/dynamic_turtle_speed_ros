#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <dynamic_turtle_speed_ros/velocityConfig.h>
#include <geometry_msgs/Twist.h>
int x;
int z;

void callback(dynamic_turtle_speed_ros::velocityConfig &config, uint32_t level) {
  ROS_INFO("Reconfigure Request: %d %d", 
            config.velocity_x, 
            config.velocity_rotation_z);  
  x = config.velocity_x;
  z = config.velocity_rotation_z;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "dynamic_turtle_speed_ros");

  dynamic_reconfigure::Server<dynamic_turtle_speed_ros::velocityConfig> velset;
  dynamic_reconfigure::Server<dynamic_turtle_speed_ros::velocityConfig>::CallbackType f;
    
  f = boost::bind(&callback, _1, _2);
  velset.setCallback(f);
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1000);
  ros::Rate loop_rate(10);
  int count = 0;
  
  while (ros::ok()){
  geometry_msgs::Twist cmd_velocity;
  geometry_msgs::Vector3 linear;
  linear.x = x;
  cmd_velocity.linear = linear;
  geometry_msgs::Vector3 angular;
  angular.z = z;
  cmd_velocity.angular = angular;
  chatter_pub.publish(cmd_velocity);
  ros::spinOnce();
  loop_rate.sleep();
  ++count;
  }
  
  return 0;
}

