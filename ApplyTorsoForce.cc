#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>
#include <yarp/os/all.h>
#include <iostream>

namespace gazebo
{

class ApplyTorsoForce : public ModelPlugin
{
public:
    yarp::os::Network yarp;

    ApplyTorsoForce()
    {
    }

    ~ApplyTorsoForce()
    {
        port.close();
    }

    void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
        model = _parent;
        port.open("/Gazebo/ApplyTorsoForce:i");
        updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&ApplyTorsoForce::OnUpdate, this, _1));

        torso  = model->GetLink("iCub::root_link");

        force  = math::Vector3::Zero;
        offset = math::Vector3(0.0, -0.1, 0.0);
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
                std::cout << "Applying constant force of magnitude: " << force.GetLength() << " to robot torso." << std::endl;
            } else if(b->size()==1) {
                force = math::Vector3::One*b->get(0).asDouble();
                std::cout << "Applying constant force of magnitude: " << force.GetLength() << " to robot torso." << std::endl;
            } else {
                std::cout << "[ERROR] apply_torso_force plugin expects exacly 1 or 3 force arguments." << std::endl;
            }
        }

        torsoTransform   = math::Pose(offset, math::Quaternion()) + torso->GetWorldPose();
        forceTransformed = torsoTransform.rot.GetInverse() * force;

        torso->AddLinkForce(forceTransformed, offset);
    }

private:
    math::Vector3 force;
    math::Vector3 offset;

    math::Pose torsoTransform;
    math::Vector3 forceTransformed;

    physics::ModelPtr model;
    physics::LinkPtr torso;
    event::ConnectionPtr updateConnection;
    yarp::os::BufferedPort<yarp::os::Bottle> port;


};

// Register this plugin with the simulator
GZ_REGISTER_MODEL_PLUGIN(ApplyTorsoForce)
}

