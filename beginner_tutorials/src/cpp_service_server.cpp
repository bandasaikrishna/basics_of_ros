#include "ros/ros.h"
#include "rospy_tutorials/AddTwoInts.h" // Messages used in the node must be included.

/*
"my_server" is the callback method of the service. Make sure the return type of the service callback method is bool. 
Arguments of the service callback method are the request and the response messages of the service. 
"req" contains the request message sent from client and response is computed and sent to the client using "res".
*/
bool my_server(rospy_tutorials::AddTwoInts::Request &req, rospy_tutorials::AddTwoInts::Response &res)
{
	ROS_INFO("Request receiced to add: x=%ld and y=%ld ", (long int)req.a, (long int)req.b);
	res.sum = req.a + req.b;
	return true;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "service_server_node_cpp"); // Node declared with name "service_server_node_cpp"
	ros::NodeHandle nh; // NodeHandle will actually initialze the node

/*
A service server is created in the below line.
First argument is the name of the Service. Service with name "add_cpp" is registered. 
Second argument is the name of the callback method. This callback method is called whenever the client request for service.
*/
	ros::ServiceServer service = nh.advertiseService("add_cpp", my_server);
	ROS_INFO("Cpp Service server ready to add two numbers");
	
/*
spin() is used to call the callback methods in the code. Without out spin(), callback methods are never executed. 
spin() enters a loop, and  will exit once Ctrl-C is pressed.
*/
	ros::spin();

	return 0;
}
