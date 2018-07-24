#include <gtest/gtest.h>

#include "../include/motion_profile_generator.h"

TEST(m_p_generator, generate){
	MotionConstraints constraints;
	constraints.max_vel = 10;
	constraints.accel = 10;
	ProfileTarget target;
	target.pos = 30;
	target.vel = 0;
	const double initial_pos = 0, initial_vel = 4, initial_time = 0;
	MotionProfile* p = generate_profile(new MotionState(initial_pos, initial_vel,0,initial_time), target, constraints);
	ASSERT_TRUE(p->is_valid());
	ASSERT_EQ(target.pos, p->final_pos());
	ASSERT_EQ(initial_pos, p->initial_pos());
	ASSERT_EQ(target.vel, p->final_state()->get_vel());
	ASSERT_EQ(initial_vel, p->initial_state()->get_vel());
	ASSERT_EQ(initial_time, p->initial_time());
	cout << *p << endl;
	p->to_file("profile.txt");
	p->to_gnuplot_file("gnu_profile.txt");
	delete p;
}
