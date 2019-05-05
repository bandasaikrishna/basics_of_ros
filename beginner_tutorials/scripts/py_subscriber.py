#!/usr/bin/env python
import rospy

from std_msgs.msg import Int32 # Messages used in the node must be imported.
'''
"my_callback" is the callback method of the subscriber. Argument "msg" contains the published data.
'''
def my_callback(msg):
	rospy.loginfo("received data from topic_py: %d", msg.data)


rospy.init_node('subscriber_py') #initialzing the node with name "subscriber_py"

'''
A subscriber is registered in the below line.
First argument is the name of the topic. 
Second argument is the message type of the subscribed topic. 
Thrird argument is the name of the callback method. Whenever data is published on topic "topic_py", my_callback is called. 
queue_size is the optional argument which is used to buffer up a maximum of 10 messages before beginning to throw away old ones if we are publishing too quickly.
'''
rospy.Subscriber("topic_py", Int32, my_callback, queue_size=10) 

rospy.loginfo("subscriber_py node started and subscribed to topic_py") #debug statement

'''
rospy.spin() simply keeps your node from exiting until the node has been shutdown. Unlike roscpp::spin(), rospy.spin() does not affect the subscriber callback functions, as those have their own threads.
'''
rospy.spin() 
