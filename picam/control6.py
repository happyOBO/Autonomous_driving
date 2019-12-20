#/usr/bin/env python
import rospy
import Queue
from std_msgs.msg import String
import smbus
import min_dist
import time
print('import done')

on_off = 1
count = 0
idx = 0

def callback(data):
    global on_off, idx, count
    if(idx > len(Order)):
        on_off = 1
    elif(data.data == 'red_sign'):
        on_off = 1
        count = 0
    else:
        if(on_off == 1):
            if(idx >= len(Order)):
                on_off = 6 # The End
            elif(count >= 10):
                on_off = Order[idx]
                idx +=1
            else :
                count +=1
        else:
            pass

class I2CComm(object):
    I2C_BUS_NUM = 1

    def __init__(self):
        self.master = ambus.SMBus(self.I2C_BUS_NUM)
        self.slave_addr_list =4
    def run(self):
        global Order,on_off,Direct, Order, NEWS
        me = self.master
        rospy.init_node('zumi_control',anonymous = True)
        rospy.Subscriber('send_trf',String,callback)
        rate = rospy.Rate(3)
        print('now jmup into while loop')
        while not rospy.is_shutdown():
            try:
                me.write_byte(4, on_off)
                print('on_off',on_off)
                if(on_off == 5):
                    on_off = 0
                elif(on_off == 6):
                    Direct, Order, NEWS = min_dist.navigator('N',(2,0),(2,4))
                    idx = 0
                    on_off = 1
            except IOError:
                pass
            rate.sleep()

def main():
    i2c = I2CComm()
    i2c.run()
#####################################################################################################
##############################################navigator##############################################
#####################################################################################################

Direct, Order, NEWS = min_dist.navigator('N',(2,0),(2,4))

print(Order)
print(Direct)
print(NEWS)

if __name__ == "__main__":
    main()
