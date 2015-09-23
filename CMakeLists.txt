cmake_minimum_required(VERSION 2.8.3)
project(dynamic_turtle_speed_ros)
find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  roscpp
  rospy
)


 generate_dynamic_reconfigure_options(
   cfg/velocity.cfg
   )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES dynamic_turtle_speed_ros
 CATKIN_DEPENDS dynamic_reconfigure roscpp rospy
#  DEPENDS system_lib
)


include_directories(
  ${catkin_INCLUDE_DIRS}
  ${dynamic_reconfigure_PACKAGE_PATH}/cmake/cfgbuild.cmake
)

add_executable(velset src/velset.cpp)
add_dependencies(velset ${PROJECT_NAME}_gencfg)
target_link_libraries(velset ${catkin_LIBRARIES})
