#!/usr/bin/env python
import rospy
from std_msgs.msg import Int32 # Messages used in the node must be imported.

rospy.init_node('publisher_py') # initialzing the node with name "publisher_py"

'''
A Publisher is created in the below line
First argument is the name of the topic.
Second argument is the type of the message that is published on the topic.
queue_size is the optional argument which is used to buffer up a maximum of 10 messages before beginning to throw away old ones if we are publishing too quickly. 
'''
pub = rospy.Publisher('topic_py', Int32, queue_size=10)

rospy.loginfo("publisher_py node started and publishing data on topic_py")

rate = rospy.Rate(10) # 10hz

count=Int32() # declaring a message variable of type Int32

count.data=0 # Initializing count

while not rospy.is_shutdown(): # run the node until Ctrl-C is pressed

	pub.publish(count) # publishing data on topic "topic_py"
  
	count.data+=1
	
	rate.sleep() # This makes the loop to iterate at 10Hz i.e., 10 times a sec.
