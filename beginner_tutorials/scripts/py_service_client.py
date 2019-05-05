#!/usr/bin/env python
import rospy
from rospy_tutorials.srv import AddTwoInts, AddTwoIntsResponse, AddTwoIntsRequest  # Messages used in the node must be imported.

rospy.init_node('service_client_node_py',anonymous=True) #initialzing the node with name "service_client_node_py". The second arugument "anonymous" is optional. If anonymous is set to true, then you can run this node in more than one terminal simultanously.

rate = rospy.Rate(1) # 1 hz

x=0
y=1
element=1

rospy.wait_for_service('add_py') # wait_for_service(service_name) will wait until the serivce node is ready and running.

'''
A service client is created in the below line. 
First argument is the name of the service to be regitered
Second argument is the message type of the service
'''
add=rospy.ServiceProxy('add_py', AddTwoInts) 

rospy.loginfo("Fibanocci series element 0: 0")

while not rospy.is_shutdown() and element < 81: 
	'''
	In the below line, client is requesting for service. 
	The argument order is the same as the order of the fields in the Message, and you must provide a value for all of the fields. In this case rospy_tutorials.srv.AddTwoIntsRequest has two integer fields, hence add(x,y).
	"resp" will be assigned with the response message.
	'''
	resp = add(x,y) 
	
	rospy.loginfo("Fibanocci series element %d: %d", element, resp.sum)
	
	x=y
	y=resp.sum
	element+=1
	rate.sleep() # This makes the loop to iterate at 1 Hz i.e., once in 1 sec.
