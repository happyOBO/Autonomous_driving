#!/usr/bin/env python
from __future__ import division
import time
import torch 
import torch.nn as nn
from torch.autograd import Variable
import numpy as np
import cv2 
from util import *
from darknet import Darknet
from preprocess import prep_image, inp_to_image
import pandas as pd
import random 
import argparse
import pickle as pkl
import rospy
from sensor_msgs.msg import Image
from sensor_msgs.msg import CompressedImage
from cv_bridge import CvBridge, CvBridgeError

print("import done")

bridge = CvBridge()

# cv2.namedWindow("cv_image", cv2.WINDOW_NORMAL)

#def callback(data):
#    np_arr = np.fromstring(data.data, np.uint8)
#    frame = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
#    cv2.imshow('frame', frame)
#    if cv2.waitKey(10) == 27:
#        cv2.destoryAllWindows()
#        print("Esc key has been pressed")
#        print("Ctrl+C to terminate")

def prep_image(img, inp_dim):
    """
    Prepare image for inputting to the neural network. 
    
    Returns a Variable 
    """

    orig_im = img
    dim = orig_im.shape[1], orig_im.shape[0]
    img = cv2.resize(orig_im, (inp_dim, inp_dim))
    img_ = img[:,:,::-1].transpose((2,0,1)).copy()
    img_ = torch.from_numpy(img_).float().div(255.0).unsqueeze(0)
    return img_, orig_im, dim

def write(x, img):
    c1 = tuple(x[1:3].int())
    c2 = tuple(x[3:5].int())
    cls = int(x[-1])
    label = "{0}".format(classes[cls])
    # color = random.choice(colors)
    cv2.rectangle(img, c1, c2,[255,255,255], 1)
    t_size = cv2.getTextSize(label, cv2.FONT_HERSHEY_PLAIN, 1 , 1)[0]

    cv2.rectangle(img, c1,( c1[0] + t_size[0] + 3, c1[1] + t_size[1] + 4),[0,0,0], -1)
    cv2.putText(img, label, (c1[0], c1[1] + t_size[1] + 4), cv2.FONT_HERSHEY_PLAIN, 1, [225,255,255], 1);
    dst = img[c1[1]:c2[1],c1[0]:c2[0]]
    pub_trf = rospy.Publisher('send_trf', String, queue_size=10)
    pub_percar = rospy.Publisher('send_percar', Int16MultiArray, queue_size=1)
    rospy.init_node('talker', anonymous=True)
    if label == 'traffic light':
        lower_blue = np.array([110, 100, 100])
        upper_blue = np.array([130, 255, 255])
        lower_green = np.array([50, 100, 100])
        upper_green = np.array([70, 255, 255])
        lower_red = np.array([-10, 100, 100])
        upper_red = np.array([10, 255, 255])
        hsv = cv2.cvtColor(dst, cv2.COLOR_BGR2HSV)
        blue_range = cv2.inRange(hsv, lower_blue, upper_blue)
        green_range = cv2.inRange(hsv, lower_green, upper_green)
        red_range = cv2.inRange(hsv, lower_red, upper_red)
        blue_result = cv2.bitwise_and(dst, dst, mask=blue_range)
        red_result = cv2.bitwise_and(dst, dst, mask=red_range)
        green_result = cv2.bitwise_and(dst, dst, mask=green_range)
        # print(np.mean(red_result) ,"  ", np.mean(blue_result), "  ",np.mean(green_result))
        r = np.mean(red_result)
        g = np.mean(green_result)
        b = np.mean(blue_result)
        if max(r,g,b) == r :
            trf_msg = "red_sign"
        elif max(r,g,b) == g :
            trf_msg = "green_sign"
        elif max(r,g,b) == b :
            trf_msg = "blue_sign"
        else :
            print("no_sign")
        print("I send msg :"+ trf_msg)
        rospy.loginfo(trf_msg)
        pub_trf.publish(trf_msg)
    elif label == 'person' or label == 'car ':
        percar_msg = Int16MultiArray()
        if label == 'person':
            percar_msg.data = [0,c1[1],c2[1],c1[0],c2[0]]
        else :
            percar_msg.data = [1,c1[1],c2[1],c1[0],c2[0]]
        rospy.loginfo(percar_msg)
        pub_percar.publish(percar_msg)
    else :
        pass
    return img

def arg_parse():
    """
    Parse arguements to the detect module
    
    """
    
    
    parser = argparse.ArgumentParser(description='YOLO v3 Cam Demo')
    parser.add_argument("--confidence", dest = "confidence", help = "Object Confidence to filter predictions", default = 0.25)
    parser.add_argument("--nms_thresh", dest = "nms_thresh", help = "NMS Threshhold", default = 0.4)
    parser.add_argument("--reso", dest = 'reso', help = 
                        "Input resolution of the network. Increase to increase accuracy. Decrease to increase speed",
                        default = "160", type = str)
    return parser.parse_args()


def callback(data):
    cfgfile = "~/catkin_ws/src/send_yolo_data/script/cfg/yolov3.cfg"
    weightsfile = "~/catkin_ws/src/send_yolo_data/script/yolov3.weights"
    num_classes = 80
    args = arg_parse()
    confidence = float(args.confidence)
    nms_thesh = float(args.nms_thresh)
    start = 0
    CUDA = torch.cuda.is_available()
    num_classes = 80
    bbox_attrs = 5 + num_classes
    model = Darknet(cfgfile)
    model.load_weights(weightsfile)
    model.net_info["height"] = args.reso
    inp_dim = int(model.net_info["height"])
    assert inp_dim % 32 == 0 
    assert inp_dim > 32
    if CUDA:
        model.cuda()      
    model.eval()

    frame = bridge.imgmsg_to_cv2(data, "bgr8")
    # cv2.imshow("cv_image", cv_image)
    #print("get")
    # cv2.waitKey(1)

    img, orig_im, dim = prep_image(frame, inp_dim)
    
    if CUDA:
        im_dim = im_dim.cuda()
        img = img.cuda()
    
    
    output = model(Variable(img), CUDA)
    output = write_results(output, confidence, num_classes, nms = True, nms_conf = nms_thesh)

    if type(output) == int:
        frames += 1
        print("FPS of the video is {:5.2f}".format( frames / (time.time() - start)))
        cv2.imshow("frame", orig_im)
        key = cv2.waitKey(1)
        if key & 0xFF == ord('q'):
            quit()
        pass
    


    output[:,1:5] = torch.clamp(output[:,1:5], 0.0, float(inp_dim))/inp_dim
    
#            im_dim = im_dim.repeat(output.size(0), 1)
    output[:,[1,3]] *= frame.shape[1]
    output[:,[2,4]] *= frame.shape[0]

    
    classes = load_classes('data/coco.names')
    # colors = pkl.load(open("pallete", "rb"))
    
    list(map(lambda x: write(x, orig_im), output))
    
    
    cv2.imshow("frame", orig_im)
    key = cv2.waitKey(1)
    if key & 0xFF == ord('q'):
        quit()
    frames += 1
    print("FPS of the video is {:5.2f}".format( frames / (time.time() - start)))



def listener():
    rospy.init_node('listener', anonymous=True)
#    rospy.Subscriber('usb_cam/image_raw/compressed', CompressedImage, callback)
    rospy.Subscriber('chatter', Image, callback)
#    rospy.Subscriber('chatter', CompressedImage, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
