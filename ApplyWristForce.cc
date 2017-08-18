#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>
#include <yarp/os/all.h>
#include <iostream>

namespace gazebo
{

class ApplyWristForce : public ModelPlugin
{
public:
    yarp::os::Network yarp;

    ApplyWristForce()
    {
    }

    ~ApplyWristForce()
    {
        port.close();
    }

    void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
        model = _parent;
        port.open("/Gazebo/ApplyWristForce:i");
        updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&ApplyWristForce::OnUpdate, this, _1));

        l_forearm = model->GetLink("iCub::l_forearm");
        r_forearm = model->GetLink("iCub::r_forearm");

        force = math::Vector3::Zero;

        l_offset = math::Vector3(0.0, 0.1, 0.0);
        r_offset = math::Vector3(0.0, -0.1, 0.0);
    }

    void OnUpdate(const common::UpdateInfo & )
    {
        yarp::os::Bottle *b;
        b = port.read(false);
        if (b!=NULL)
        {
            // std::cout << "b: " << b->toString() << std::endl;

            if(b->size()==3) {
                force.x = b->get(0).asDouble();
                force.y = b->get(1).asDouble();
                force.z = b->get(2).asDouble();
                std::cout << "Applying constant force of magnitude: " << force.GetLength() << " to left and right forearms." << std::endl;
            } else if(b->size()==1) {
                force = math::Vector3::One*b->get(0).asDouble();
                std::cout << "Applying constant force of magnitude: " << force.GetLength() << " to left and right forearms." << std::endl;
            } else {
                std::cout << "[ERROR] apply_wrist_force plugin expects exacly 1 or 3 force arguments." << std::endl;
            }
        }

        l_forearmTransform = math::Pose(l_offset, math::Quaternion()) + l_forearm->GetWorldPose();
        l_forceTransformed = l_forearmTransform.rot.GetInverse() * force;

        r_forearmTransform = math::Pose(r_offset, math::Quaternion()) + r_forearm->GetWorldPose();
        r_forceTransformed = r_forearmTransform.rot.GetInverse() * force;

        l_forearm->AddLinkForce(l_forceTransformed, l_offset);
        r_forearm->AddLinkForce(r_forceTransformed, r_offset);
    }

private:
    math::Vector3 force;
    math::Vector3 l_offset;
    math::Vector3 r_offset;

    math::Pose l_forearmTransform;
    math::Vector3 l_forceTransformed;

    math::Pose r_forearmTransform;
    math::Vector3 r_forceTransformed;

    physics::ModelPtr model;
    physics::LinkPtr l_forearm;
    physics::LinkPtr r_forearm;
    event::ConnectionPtr updateConnection;
    yarp::os::BufferedPort<yarp::os::Bottle> port;


};

// Register this plugin with the simulator
GZ_REGISTER_MODEL_PLUGIN(ApplyWristForce)
}

