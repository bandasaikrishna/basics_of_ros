#include <ros/ros.h>

int main(int argc, char** argv)
{
	int count = 0;
	ros::init(argc, argv, "simple_node"); // Node declared with name "simple_node_cpp"
	ros::NodeHandle nh; // NodeHandle will actually initialze the node
	ros::Rate loop_rate(10); // 10Hz
	
	while (ros::ok()) // run the node until Ctrl-C is pressed
	{
		//Wirte your code here
		
		ROS_INFO("simple_node in cpp is running. count= %d",count);// Debug statement
	
		ros::spinOnce(); // spinOnce() is used to call the callbacks (if any) in the code. This is not required for this node But it is a best practise to have it. 
		
		count++;
		
		loop_rate.sleep(); // This makes the loop to iterate at 10Hz i.e., 10 times a sec.
	}
}
