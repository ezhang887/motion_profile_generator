#include <iostream>

#include "include/motion_profile_generator.h"
#include "include/motion_profile.h"

using namespace std;

int main(){
    MotionState* initial_state = new MotionState(0.0,0.0,0.0,0.0);

    ProfileTarget target;
    //10 ft
    target.pos = 10.0;
    target.vel = 0.0;

    MotionConstraints constraints;
    //12 ft/sec
    constraints.max_vel = 12.0;
    //10 ft/sec/sec
    constraints.accel = 8.0;

    MotionProfile* profile =  generate_profile(initial_state, target, constraints);
    //profile->to_gnuplot_file("gnu_profile.txt");
    delete profile;
    return 0;
}
