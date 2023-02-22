#include <ros/ros.h>
#include <std_msgs/String.h>

namespace hello_world {

class HelloWorld 
{
public:

    HelloWorld(ros::NodeHandle& nh) 
    {
        output_pub_ = nh.advertise<std_msgs::String>("output", 1);

        std::string input_topic_name;
        if (!nh.getParam("input_topic", input_topic_name))
        {
          ROS_FATAL("Can't find intput_topic parameter... shutting down :(");
          ros::shutdown();
        } 
        else
        {
          ROS_INFO_STREAM("Using topic parameter " << input_topic_name);
          ROS_WARN_STREAM("Using topic parameter " << input_topic_name);
          ROS_ERROR_STREAM("Using topic parameter " << input_topic_name);
        }
        input_sub_ = nh.subscribe(input_topic_name, 10, &HelloWorld::msgCallback, this);
    }

private:

    void msgCallback(const std_msgs::String& msg)
    {
        std::string response = "I heard: [" + msg.data + "]"; 
        ROS_INFO_STREAM(response);
        
        std_msgs::String msg_out;
        msg_out.data = response;
        output_pub_.publish(msg_out);
    }

    ros::Publisher output_pub_;
    ros::Subscriber input_sub_;
};

} // namespace hello_world

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "hello_world");

  ros::NodeHandle nodeHandle("~");
  hello_world::HelloWorld helloWorld(nodeHandle);

  ros::spin();
  return 0;
}

