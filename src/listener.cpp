#include <ros/ros.h>
#include <std_msgs/String.h>

void chatterCallback(const std_msgs::String& msg)
{
  ROS_INFO_STREAM("I heard: [" << msg.data << "]");
  ROS_WARN_STREAM("I heard: [" << msg.data << "] !");
  ROS_ERROR_STREAM("I heard: [" << msg.data << "] !!");
}

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "listener");

  // Try different nodehandle types
  ros::NodeHandle nh;                //< public
  // ros::NodeHandle nh("~");           //< private (topics fall under node name)
  // ros::NodeHandle nh("/global_bad"); //< global (bad)

  ros::Subscriber subscriber =
       nh.subscribe("chatter",10,chatterCallback);
  ros::spin();
  return 0;
}
