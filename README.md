# gazebo-force-plugin

Plugin for using external constant forces in Gazebo.

## Usage:

- append to your .sdf model the following lines:

    ```
    <plugin name="apply_external_wrench" filename="libapply_NAME LIB_force.so">
      <robotNamefromConfigFile>model://icub/conf/gazebo_icub_robotname.ini</robotNamefromConfigFile>>
    </plugin>

   ```
where `NAME_LIB` is the name of the .so file to be used -- currently available files: `torso`, `hands`.

- open the port by typing `yarp write ... /Gazebo/ApplyLINK_NAMEForce:i` (substitute `LINK_NAME` with the proper name).

- insert the force magnitude (only 1 number) or the magnitude in each direction (3 numbers). 

## Apply impulse forces:

- modify accordingly file `ApplyImpluseGazebo.sh` and then launch it using command `sh ApplyImpluseGazebo.sh`.
