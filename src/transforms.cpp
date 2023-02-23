#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "tf2_listener");
  ros::NodeHandle nodeHandle;
  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);

  ros::Rate rate(10.0);
  
  while (nodeHandle.ok()) 
  {
    geometry_msgs::TransformStamped transformStamped;
    try 
    {
      transformStamped = tfBuffer.lookupTransform("base",
	               "odom", ros::Time(0));
      ROS_INFO_THROTTLE(0.5, "Received a transform!");
    } 
    catch (tf2::TransformException &exception) 
    {
      ROS_WARN("%s", exception.what());
      ros::Duration(1.0).sleep();
      continue;
    }
    rate.sleep();
  }

  return 0;
};
