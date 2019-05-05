#!/usr/bin/env python
import rospy
from rospy_tutorials.srv import AddTwoInts, AddTwoIntsResponse, AddTwoIntsRequest  # Messages used in the node must be imported.

'''
"my_server" is the callback method of the service. Argument "req" contains request message sent by the client.
'''
def my_server(req):
	res = AddTwoIntsResponse() # declaring a response varible of the service. 
	rospy.loginfo("Request received to add: %d & %d", req.a, req.b)
	res.sum=req.a+req.b
	return res

rospy.init_node('service_server_node_py') #initialzing the node with name "service_server_node_py"

'''
A service server is created in the below line.
First argument is the name of the Service. Service with name "add_py" is registered. 
Second argument is the message type. The message type of this service is "AddTwoInts". 
Third argument is the name of the callback method. This callback method is called whenever the client request for service.
'''
rospy.Service('add_py', AddTwoInts, my_server)

rospy.loginfo("Python Service server ready to add two numbers")

'''
rospy.spin() simply keeps your node from exiting until the node has been shutdown. Unlike roscpp::spin(), rospy.spin() does not affect the subscriber callback functions, as those have their own threads.
'''
rospy.spin()
