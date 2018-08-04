#include <gtest/gtest.h>

#include "../include/motion_profile_generator.h"
#include "../include/utils.h"

TEST(m_p_generator, generate){
    MotionConstraints constraints;
    constraints.max_vel = 10;
    constraints.accel = 10;
    ProfileTarget target;
    target.pos = 30;
    target.vel = 0;
    const double initial_pos = 0;
    const double initial_vel = 3;
    const double initial_time = 10;
    MotionProfile* p = generate_profile(new MotionState(initial_pos, initial_vel,0,initial_time), target, constraints);
    ASSERT_TRUE(p->is_valid());
    ASSERT_NEAR(target.pos, p->final_pos(), k_epsilon);
    ASSERT_NEAR(initial_pos, p->initial_pos(), k_epsilon);
    ASSERT_NEAR(target.vel, p->final_state()->get_vel(), k_epsilon);
    ASSERT_NEAR(initial_vel, p->initial_state()->get_vel(), k_epsilon);
    ASSERT_NEAR(initial_time, p->initial_time(), k_epsilon);
    delete p;
}

TEST(m_p_generator, generate_reverse){
    MotionConstraints constraints;
    constraints.max_vel = 10;
    constraints.accel = 10;
    ProfileTarget target;
    target.pos = -30;
    target.vel = 0;
    const double initial_pos = 0;
    const double initial_vel = 0;
    const double initial_time = 0;
    MotionProfile* p = generate_profile(new MotionState(initial_pos, initial_vel, 0, initial_time), target, constraints);
    ASSERT_TRUE(p->is_valid());
    ASSERT_NEAR(target.pos, p->final_pos(), k_epsilon);
    ASSERT_NEAR(initial_pos, p->initial_pos(), k_epsilon);
    ASSERT_NEAR(target.vel, p->final_state()->get_vel(), k_epsilon);
    ASSERT_NEAR(initial_vel, p->initial_state()->get_vel(), k_epsilon);
    ASSERT_NEAR(initial_time, p->initial_time(), k_epsilon);
    delete p;
}
