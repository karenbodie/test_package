#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <std_msgs/String.h>

namespace callback_threads
{

  class CallBackThreads
  {
  public:
    CallBackThreads(ros::NodeHandle &nh)
    {
      const std::string topic_name = "hot_topic";

      input_sub_1_ = nh.subscribe(topic_name, 10, &CallBackThreads::msgCallback1, this);
      input_sub_2_ = nh.subscribe(topic_name, 10, &CallBackThreads::msgCallback2, this);
      input_sub_3_ = nh.subscribe(topic_name, 10, &CallBackThreads::msgCallback3, this);
    }

  private:
    void msgCallback1(const std_msgs::String& msg)
    {
      doCountdown(5);
    }

    void msgCallback2(const std_msgs::String& msg)
    {
      doCountdown(3);
    }

    void msgCallback3(const std_msgs::String& msg)
    {
      doCountdown(1);
    }

    void doCountdown(const int delay_time)
    {
      ros::Duration one_second(1.0);
      ROS_WARN_STREAM("Counting down from " << delay_time << "!");
      for (std::size_t i = delay_time; i > 0; i--)
      {
        ROS_INFO_STREAM(i << " ...");
        one_second.sleep();
      }
    }

    ros::Subscriber input_sub_1_;
    ros::Subscriber input_sub_2_;
    ros::Subscriber input_sub_3_; 
  };

} // namespace hello_world

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "callback_threads");

  ros::NodeHandle nh("~");

  // Read parameter to use async spinner (default false if param not found)
  const bool use_async = nh.param("use_async", false);
  const std::string alert_msg = use_async ? "Using async threads! :)" : "Using synchronous threads... :(";
  ROS_ERROR_STREAM(alert_msg);

  // Set up an asynchronous spinner
  ros::CallbackQueue async_queue;
  ros::AsyncSpinner async_spinner(3, &async_queue); // Give it 3 threads. Try with 2!

  if (use_async){
    nh.setCallbackQueue(&async_queue);
    async_spinner.start();
  }

  // Start object
  callback_threads::CallBackThreads cbt(nh);

  ros::spin();

  return 0;
}
