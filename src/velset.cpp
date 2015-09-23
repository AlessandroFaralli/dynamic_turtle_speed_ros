#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <dynamic_turtle_speed_ros/velocityConfig.h>

void callback(dynamic_turtle_speed_ros::velocityConfig &config, uint32_t level) {
  ROS_INFO("Reconfigure Request: %d %d", 
            config.velocity_x, 
            config.velocity_rotation_z);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "dynamic_turtle_speed_ros");

  dynamic_reconfigure::Server<dynamic_turtle_speed_ros::velocityConfig> velset;
  dynamic_reconfigure::Server<dynamic_turtle_speed_ros::velocityConfig>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  velset.setCallback(f);

  ROS_INFO("Spinning node");
  ros::spin();
  return 0;
}

