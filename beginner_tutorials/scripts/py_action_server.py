#!/usr/bin/env python
import rospy
import actionlib # import actionlib library
from actionlib.msg import TestAction, TestGoal, TestResult, TestFeedback # Messages used in the node must be imported.

'''
This is the execute callback function that will run everytime a new goal is received. The argument "g" has the goal information of the action.
'''
def execute_cb(g):

	fb = TestFeedback() # declaring a feedback varible of the action message. 
	res= TestResult()   # declaring a result varible of the action message.
	
	success = True
	r = rospy.Rate(1) # 1 hz
	fb.feedback=1
	multiplier=2

	while (multiplier <= g.goal):		
		if server.is_preempt_requested(): # check that preempt has not been requested by the client
			rospy.loginfo('The goal has been cancelled/preempted')
			server.set_preempted() # set_preempted function will signals that the action has been preempted by user request. 
			success = False
			break
			
		fb.feedback=fb.feedback*multiplier
		multiplier+=1
		server.publish_feedback(fb) # Here the feedback variable is published on the feedback channel provided by the action server.
		r.sleep() # This will make the loop to iterate at rate 1 hz i.e, 1 iteration/sec
		
	if success:
		res.result = fb.feedback # assgining the final value to the result variable of the action
		rospy.loginfo('Succeeded calculating the Factorial of %d in time. %d!= %d', g.goal, g.goal, res.result)
		server.set_succeeded(res) # Once the action has finished computing, the action server notifies the action client that the goal is complete by calling set_succeeded. 

rospy.init_node('action_server_node_py') # initialzing the node with name "action_server_node_py"

'''
In the next line, a ActionServer is created.
First argument is the name of the action.
Second argument is the action message type.
Thrid argument is an execute callback function that will be called whenever a new goal is received. 
Fourth argument is auto_start. You should always set auto_start to False explicitly TO AVOID RACE CONDITIONS and start() should be called after construction of the server.
'''
server = actionlib.SimpleActionServer("factorial_py", TestAction, execute_cb, False)
server.start()
rospy.loginfo('Python Action server started to find the factorial of a number')

'''
rospy.spin() simply keeps your node from exiting until the node has been shutdown. Unlike roscpp::spin(), rospy.spin() does not affect the subscriber callback functions, as those have their own threads.
'''
rospy.spin()
