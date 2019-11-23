#!/usr/bin/env python

# Alert
print("Start 'picam2.py'")
print("import ...")

# import
import cv2
import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
print("import done")

def talker():
    # Initialize the node 'zumi_cam'
    rospy.init_node('zumi_cam', anonymous=True)

    # Set a topic 'chatter'
    pub = rospy.Publisher('chatter', Image, queue_size=10)

    # Set CvBridge
    bridge = CvBridge()

    # Set control cycle
    rate = rospy.Rate(30) # 30hz

    # Turn on the camera
    print("camera on")
    cap = cv2.VideoCapture('/dev/video0')
    print("camera has been opened successfully")

    # Set the resolution
    cap.set(3, 30)
    cap.set(4, 30)

    while not rospy.is_shutdown():
        # Get a frame from picam
        ret, frame = cap.read()

        # If it doesn't get a frame, break.
        if ret is not True:
            print("frame error")
            break

        # Change frame as a message form of 'Image'
        cv_image = bridge.cv2_to_imgmsg(frame, "bgr8")

        # Publish
        pub.publish(cv_image)

        # Keep cycle rate
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
