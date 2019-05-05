#!/usr/bin/env python
import rospy
import actionlib # import actionlib library
from actionlib_msgs.msg import GoalStatus
from actionlib.msg import TestAction, TestGoal, TestResult, TestFeedback # Messages used in the node must be imported.

fac=0

'''
This method is called whenever there is data present on feedback channel
'''
def feedback_callback(feedback):
	global fac
	rospy.loginfo("Done till %d! = %d",fac,feedback.feedback)
	fac+=1

def factorial(num):
	global fac
	rate = rospy.Rate(1) # 1 hz
	count=0
	fac=2
	
	g= TestGoal() # Create a goal variable to send to the action server.
	g.goal=num

	client.wait_for_server() # This line waits until we are connected to the action server.

	'''
	In the next line goal is sent to the action server.
	The first argument is the goal variable of the action.
	The second argument is the name of the callback method that is called whenever there is data on feedback channel
	'''
	client.send_goal(g, feedback_cb=feedback_callback) # Send the goal to the action server.
	
	goal_state = client.get_state() # Get the state of the goal. Possible states are PENDING, ACTIVE, RECALLED, REJECTED, PREEMPTED, ABORTED, SUCCEEDED, LOST.
	
	
	while not (goal_state == GoalStatus.PREEMPTED or goal_state == GoalStatus.SUCCEEDED): # Run the loop until the goal is success or preempted.
		if count > 10: # This condition is to make the loop run for approx 10 secs. After 10 secs, the goal is preempted and loop is exited.
			rospy.loginfo("Time exceed the limit hence preempting the action")
			client.cancel_goal() # This line will preempt the goal
			break

		goal_state = client.get_state()
		count+=1
		rate.sleep() # This will make the loop to iterate at rate 1 hz i.e, 1 iteration/sec
		
	
	rate.sleep()
	goal_state = client.get_state()
	
	if (goal_state == GoalStatus.SUCCEEDED):
		rospy.loginfo("Action completed in Time. %d!= %d",g.goal, client.get_result().result)


if __name__=="__main__":
	rospy.init_node('action_client_node_py') # initialzing the node with name "action_client_node_py"
	
	'''
	In the next line, a ActionClient is created.
	First argument is the name of the action.
	Second argument is the action message type.
	'''
	client = actionlib.SimpleActionClient("factorial_py", TestAction)
	
	factorial(8) 
	factorial(14)
	
