cmake_minimum_required(VERSION 2.8 FATAL_ERROR)


# THE APPLY FORCE PLUGIN IS DEPRECATED: IT HAS BEEN ALREADY ADDED INTO GAZEBO-YARP-PLUGIN!
#
# THIS REPO JUST ACTS AS A CONTAINER

#find_package(gazebo REQUIRED)
#find_package(YARP REQUIRED)

#include_directories(${GAZEBO_INCLUDE_DIRS}
#                    ${YARP_INCLUDE_DIRS}
#                    )

#link_directories(${GAZEBO_LIBRARY_DIRS}
#                ${YARP_LIBRARY_DIRS}
#                )

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

#add_library(apply_torso_force SHARED ApplyTorsoForce.cc)
#add_library(apply_hands_force SHARED ApplyHandsForce.cc)

#target_link_libraries(apply_torso_force ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${YARP_LIBRARIES})
#target_link_libraries(apply_hands_force ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${YARP_LIBRARIES})

#install(TARGETS apply_torso_force DESTINATION lib)
#install(TARGETS apply_hands_force DESTINATION lib)

project(gazebo-force-plugin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(gazebo-force-plugins "${CMAKE_INSTALL_PREFIX}/share/gazebo-force-plugin")

install(CODE "MESSAGE(\"This repository simply acts as a container\")")
