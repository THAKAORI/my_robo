cmake_minimum_required(VERSION 2.8.3)
project(my_robo_description)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  mavros_msgs
)

catkin_package(
  LIBRARIES my_robo_description
  CATKIN_DEPENDS roscpp rospy std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(joy_controller src/joy_controller.cpp)
target_link_libraries(joy_controller ${catkin_LIBRARIES})

