#ifndef MOTION_PROFILE_GENERATOR
#define MOTION_PROFILE_GENERATOR

#include "../include/motion_profile.h"

struct MotionConstraints{
    double max_vel;	
    double accel;
};

struct ProfileTarget{
    double pos;
    double vel;
};

MotionProfile* generate_profile(MotionState* initial_state, ProfileTarget target, MotionConstraints constraints);

ProfileTarget get_inverted_target(ProfileTarget target);
#endif
