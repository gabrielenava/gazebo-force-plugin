#!/bin/bash

# Synchronization with Gazebo for applying input always at the same time
yarpdatadumper 
yarp connect /Simulink/time /dump

echo "Applying impulse force on robot torso..."

echo "0.0 100.0 0.0"  | yarp write ... /Gazebo/ApplyTorsoForce:i

sleep 0.01

echo "0.0 0.0 0.0"  | yarp write ... /Gazebo/ApplyTorsoForce:i

echo "Done!"

rm -r /dump
echo "Removed dumped time"


