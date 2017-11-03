
roslaunch rosbridge.launch &
sleep 1s
rosrun rosserial_python serial_node.py /dev/ttyACM0 &
