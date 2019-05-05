#include "ros/ros.h"
#include "std_msgs/Int32.h" // Messages used in the node must be included.

int main(int argc, char **argv)
{
	ros::init(argc, argv, "publisher_cpp"); // Node declared with name "publisher_cpp"
	ros::NodeHandle nh; // NodeHandle will actually initialze the node

/*
A Publisher is created in the below line
First argument is the name of the topic.
Second argument is queue_size which is used to buffer up a maximum of 10 messages before beginning to throw away old ones if we are publishing too quickly
This publisher is using Int32 message to publish data on "topic_cpp" 
*/	
	ros::Publisher pub = nh.advertise<std_msgs::Int32>("topic_cpp", 10);
	
	ROS_INFO("publisher_cpp node started and publishing data on topic_cpp");
	
	ros::Rate loop_rate(10); //10 Hz
	
	std_msgs::Int32 count; // declaring a variable of type Int32
	count.data=0; // Initializing count
	
    while (ros::ok()) // run the node until Ctrl-C is pressed
    {		
		pub.publish(count); // publishing data on topic "topic_py"
		count.data++;	
		loop_rate.sleep(); // This makes the loop to iterate at 10Hz i.e., 10 times a sec.
	}
	return 0;
}

