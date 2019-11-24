YOLO & ROS: Detect Person & Traffic sign
==================

1.YOLO with webcam
------------------

### REASON TO USE

Detect Person & Traffic sign color

### Installation

You can use python2 and also python3

    git clone https://github.com/happyOBO/ZumiGamma
    cd YOLO
    wget http://pjreddie.com/media/files/yolov3.weights
    python3 cam_demo.py

### The Code Explained : cam_demo.py

    cfgfile = "cfg/yolov3.cfg" # call yolov3.cfg. You can use other cfg file.
    weightsfile = "yolov3.weights" # call yolov3.weights. Yo can use other weight file too.
    def write(x, img):
        ...
        if label == 'traffic light': # If the frame detect 'traffic light'
            ...
            blue_range = cv2.inRange(hsv, lower_blue, upper_blue)
            green_range = cv2.inRange(hsv, lower_green, upper_green)
            red_range = cv2.inRange(hsv, lower_red, upper_red)
            blue_result = cv2.bitwise_and(dst, dst, mask=blue_range)
            red_result = cv2.bitwise_and(dst, dst, mask=red_range)
            green_result = cv2.bitwise_and(dst, dst, mask=green_range)
            r = np.mean(red_result)
            g = np.mean(green_result)
            b = np.mean(blue_result)
            if max(r,g,b) == r : # red_light
                print("red!")
            elif max(r,g,b) == g : # green_light
                print("green!")
            elif max(r,g,b) == b : # blue_light
                print("blue!")
            else :
                print("I Don't know color!")
    return img

### 실행화면

![running_view](./demo.png){: width="80%" height="80%"}

2.YOLO With ROS
----------------

### Overview

Detecting person, Car & traffic sign on Video that Raspberry pi's pi cam sends. Also It publishes processed data(locations,labels and traffic sign colors).

### Install

I recommend to running on python2.7

    # You should make your ros package at catkin_ws first.
    cd ~/catkin_ws/src/{YOUR_PACKAGE_NAME}/
    mkdir scripts
    cd ~/
    git clone https://github.com/happyOBO/ZumiGamma
    # Move YOLO contents to YOUR_PACKAGE
    mv -rf ~/YOLO/* ~/catkin_ws/src/{YOUR_PACKAGE_NAME}/scripts
    # You Can Remove other files If You don't need them.
    rm -rf ~/YOLO
    cd ~/catkin_ws/src/{YOUR_PACKAGE_NAME}
    wget http://pjreddie.com/media/files/yolov3.weights
    chmod +x send_tpc_data.py
    source ~/catkin_ws/dev/setup.bash

    cd ~/catkin_ws
    catkin_make

    rosrun {YOUR_PACKAGE_NAME} send_tpc_data.py
