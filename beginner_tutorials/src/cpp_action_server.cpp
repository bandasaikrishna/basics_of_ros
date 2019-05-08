#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h> // This is the action library used for implementing simple actions.
#include <actionlib/TestAction.h> // Messages used in the node must be included.

/*
This is the execute callback function that will run everytime a new goal is received. The argument "g" has the goal information of the action.
*/
void execute(const actionlib::TestGoalConstPtr& g, actionlib::SimpleActionServer<actionlib::TestAction>* server)  
{

	actionlib::TestFeedback fb; // declaring a feedback varible of the action message. 
	actionlib::TestResult res; // declaring a result varible of the action message. 	
	
	bool success = true;
	ros::Rate loop_rate(1); // 1 hz
	fb.feedback=1;
	int multiplier=2;

	while (multiplier <= g->goal)
	{
		if (server->isPreemptRequested()) // check that preempt has not been requested by the client
		{
			ROS_INFO("The goal has been cancelled/preempted");
			server->setPreempted(); // set_preempted function will signals that the action has been preempted by user request. 
			success = false;
			break;
		}
			
		fb.feedback=fb.feedback*multiplier;
		multiplier++;
		server->publishFeedback(fb); // Here the feedback variable is published on the feedback channel provided by the action server.
		loop_rate.sleep(); // This will make the loop to iterate at rate 1 hz i.e, 1 iteration/sec
	}
		
	if (success)
	{
		res.result = fb.feedback; // assgining the final value to the result variable of the action
		ROS_INFO("Succeeded calculating the Fibonacci of order %d",res.result);
		server->setSucceeded(res); // Once the action has finished computing, the action server notifies the action client that the goal is complete by calling set_succeeded. 
	}
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "action_server_node_cpp"); // Node declared with name "service_server_node_cpp"
	ros::NodeHandle nh; // NodeHandle will actually initialze the node
	
/*
In the next line, a ActionServer is created.
First argument is the node handle.
Second argument is the name of the action.
Thrid argument is an execute callback function that will be called whenever a new goal is received. 
Fourth argument is auto_start. You should always set auto_start to False explicitly TO AVOID RACE CONDITIONS and start() should be called after construction of the server.
*/
	actionlib::SimpleActionServer<actionlib::TestAction> server(nh, "factorial_cpp", boost::bind(&execute, _1, &server), false);
	server.start();
	ROS_INFO("CPP Action server started to find the factorial of a number");

/*
ros::spin() is used to call the callback methods in the code. Without out spin(), callback methods are never executed. 
ros::spin() enters a loop, and  will exit once Ctrl-C is pressed.
*/
	ros::spin();
	return 0;
}
