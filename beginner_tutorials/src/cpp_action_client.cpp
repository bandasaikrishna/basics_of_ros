#include "ros/ros.h"
#include <actionlib/client/simple_action_client.h>
#include <actionlib/TestAction.h>

int fac;

/*
This method is called when the goal completes
*/
void doneCb(const actionlib::SimpleClientGoalState& s,const actionlib::TestResultConstPtr& result)
{
	if (s == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO("Action completed in Time. Answer= %d", result->result);
	else
		ROS_INFO("Action is preempted");	
}

/*
 This method is called when the goal becomes active
*/
void activeCb()
{
	ROS_INFO("Goal just went active");
}

/*
This method is called whenever there is data present on feedback channel
*/
void feedback_callback(const actionlib::TestFeedbackConstPtr& feedback)
{
	ROS_INFO("Done till %d! =  %d",fac,feedback->feedback);
	fac++;
}

void factorial(int num)
{
	int count=0;
	fac=2;
	ros::Rate loop_rate(1); // 1 hz
	
	actionlib::TestGoal g; // Create a goal variable to send to the action server.
	g.goal=num;
	
/*
In the next line, a ActionClient is created.
First argument is the name of the action.
Second argument is spin_thread. If true, spins up a thread to service this action's subscriptions. If false, then the user has to call ros::spin() themselves. Defaults to True
*/
	actionlib::SimpleActionClient<actionlib::TestAction> client("factorial_cpp", true);
	
	client.waitForServer(); // This line waits until we are connected to the action server.
	
/*
In the next line goal is sent to the action server.
The first argument is the goal variable of the action.s
The second argument is the name of the callback method that is called when the goal completes
The third argument is the name of the callback method that is called when the goal becomes active
The fourth argument is the name of the callback method that is called whenever there is data on feedback channel
*/
	client.sendGoal(g, &doneCb, &activeCb, &feedback_callback);
	
	actionlib::SimpleClientGoalState state=client.getState(); // Get the state of the goal. Possible states are PENDING, ACTIVE, RECALLED, REJECTED, PREEMPTED, ABORTED, SUCCEEDED, LOST.

	while(!(state == actionlib::SimpleClientGoalState::PREEMPTED || state == actionlib::SimpleClientGoalState::SUCCEEDED)) // Run the loop until the goal is success or preempted.
	{
		if (count > 10) // This condition is to make the loop run for approx 10 secs. After 10 secs, the goal is preempted and loop is exited.
		{
			ROS_INFO("time exceed the limit hence preempting"); 
			client.cancelGoal(); // This line will preempt the goal
			break;
		}

		state = client.getState(); // Get the state of the goal.
		count++;
		loop_rate.sleep(); // This will make the loop to iterate at rate 1 hz i.e, 1 iteration/sec
	}
	
	loop_rate.sleep();
	state = client.getState();	
	ROS_INFO("Goal state: %s",state.toString().c_str());
	
			
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "action_clien_node_cpp"); // Node declared with name "service_server_node_cpp"
	ros::NodeHandle nh; // NodeHandle will actually initialze the node
	factorial(8);
	factorial(14);
	
	return 0;

}
