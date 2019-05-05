#include "ros/ros.h"
#include "std_msgs/Int32.h" // Messages used in the node must be included.

/*
"my_callback" is the callback method of the subscriber.Argument "msg" contains the published data whose type is Int32.
*/
void my_callback(const std_msgs::Int32::ConstPtr& msg)
{
	ROS_INFO("received data from topic_cpp: [%ld]", (long int)msg->data);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "subscriber_cpp"); // Node declared with name "subscriber_cpp"
	ros::NodeHandle nh; // NodeHandle will actually initialze the node
	
/*
A subscriber is registered in the below line.
First argument is the name of the topic to be subscribed. 
Second argument is the queue_size which is used to buffer up the messages. 
Thrird argument is the name of the callback method. Whenever data is published on topic "topic_cpp", my_callback is called.
*/
	ros::Subscriber sub = nh.subscribe("topic_cpp", 10, my_callback);
	
	ROS_INFO("subscriber_cpp node started and subscribed to topic_cpp");
/*
ros::spin() is used to call the callback methods in the code. Without out spin(), callback methods are never executed. 
ros::spin() enters a loop, and  will exit once Ctrl-C is pressed.
*/	
	ros::spin();

	return 0;
}
