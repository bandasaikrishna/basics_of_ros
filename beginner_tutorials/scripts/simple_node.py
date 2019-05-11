#!/usr/bin/env python
'''
The above line is must for any python script you write. Infact this line itself is making your script, a python file in linux.
'''
import rospy

count=0
rospy.init_node('simple_node_py') #initialzing the node with name "simple_node_py"
rate = rospy.Rate(10) # 10hz

while not rospy.is_shutdown(): # run the node until Ctrl-C is pressed

	#Write your code here

	rospy.loginfo("simple_node in python is running. count= %d",count) #debug statement
	
	count+=1
	
	rate.sleep()# This makes the loop to iterate at 10Hz rate i.e., 10 times a sec.
