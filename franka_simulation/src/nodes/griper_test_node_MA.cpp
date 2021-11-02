// =============================================================================
// Name        : griper_test_node_MA.cpp
// Author      : Margarida Amaro
// Description : close and open griper. This code will probably fail in real life because the griper opens to fast.
// =============================================================================
#include <franka_simulation/spacenav.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char **argv){

    ros::init(argc, argv, "griper_test_node_MA");
    ros::NodeHandle nh;
    franka_simulation::Spacenav panda(nh);                                //Class Spacenav with lots of functions

    // ---------------------------------------------------------------------------
    // Get initial transformation matrix
    // ---------------------------------------------------------------------------
    Eigen::Matrix4d O_T_EE;                                               // Transformation matrix referred to robot 4d
    O_T_EE = panda.O_T_EE;
    Eigen::VectorXd pose(7,1);
    pose = panda.robotPose(O_T_EE);                                      // Function to get the current robot pose de 7d
   

    // ---------------------------------------------------------------------------
    // MAIN LOOP
    // ---------------------------------------------------------------------------
    ros::Rate loop_rate(1000);                                          // Make the program sleep the correct amount of time until the next loop interation. 
    int count = 0;

    Eigen::Vector2d fingers_position;
    fingers_position << 1.0, 1.0;

    while (ros::ok()){

        panda.moveFingersCallback(fingers_position);                    // Function to open/close panda fingers and publishes the new info at the end


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            break;

        ros::spinOnce();                                                // Will call all the callbacks waiting to be called at this point in time
        loop_rate.sleep();
        count++;                                                        // Counts how many loops made
    }

    std::cout << "count: " << count << std::endl;

    return 0;
}