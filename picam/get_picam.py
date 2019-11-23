#!/usr/bin/env python
print("Start import")
import cv2
import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

print("import done")

bridge = CvBridge()

cv2.namedWindow("cv_image", cv2.WINDOW_NORMAL)

def callback(data):
    cv_image = bridge.imgmsg_to_cv2(data, "bgr8")
    cv2.imshow("cv_image", cv_image)
    cv2.waitKey(1)

def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber('chatter', Image, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()

