#include "ros/ros.h"
#include "rospy_tutorials/AddTwoInts.h" // Messages used in the node must be included.
int main(int argc, char **argv)
{
	ros::init(argc, argv, "service_client_node_cpp"); // Node declared with name "service_server_node_cpp"
	ros::NodeHandle nh;// NodeHandle will actually initialze the node

/*
A service client is created in the below line. 
Argument is the name of the service to be regitered.
This service-client is using "AddTwoInts" message type to communicate. 
*/
	ros::ServiceClient client = nh.serviceClient<rospy_tutorials::AddTwoInts>("add_cpp");
	
	rospy_tutorials::AddTwoInts var; // declaring a service message variable of type AddTwoInts
	
	ros::Rate loop_rate(1); // 1 hz
	
	var.request.a = 0;
	var.request.b = 1;
	int element =1;
	
	ROS_INFO("Fibanocci series element %d = %d", element, var.response.sum);
	while (ros::ok() && element < 81)
    {
/*
In the below line, client is requesting for service. 
The argument is the service message. So it contains both request and response variables.
In this case var.request.a and var.request.b are the request variables and var.response.sum is the response variable
*/ 
		client.call(var);
		
		ROS_INFO("Fibanocci series element %d = %d", element, var.response.sum);
		
		var.request.a = var.request.b;
		var.request.b = var.response.sum;
		element++;
		
		loop_rate.sleep(); // This makes the loop to iterate at 1 Hz i.e., once in 1 sec.	
	}
	return 0;
}
