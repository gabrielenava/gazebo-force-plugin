#!/bin/bash

# Synchronization with Gazebo for applying input always at the same time. This script is called from Matlab while initializing Simulink model, and it is assumed that after 20s an impulsive force is applied to the robot. It is also assumed the usage of a fixed step integrator, with t_step = 0.01s.

n=1

# continue until $n equals 20*100 = 2000
while [ $n -le 2000 ]
do
	sleep 0.01
	n=$(( n+1 )) # increment $n
done

echo "Applying impulse force on robot torso..."

echo "0.0 150.0 0.0"  | yarp write ... /Gazebo/ApplyTorsoForce:i

sleep 0.01

echo "0.0 0.0 0.0"  | yarp write ... /Gazebo/ApplyTorsoForce:i

echo "Done!"



