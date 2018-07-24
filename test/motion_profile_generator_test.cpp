#include <gtest/gtest.h>

#include "../include/motion_profile_generator.h"

TEST(m_p_generator, generate){
	MotionConstraints constraints;
	constraints.max_vel = 10;
	constraints.accel = 10;
	ProfileTarget target;
	target.pos = 120;
	target.vel = 0;
	MotionProfile* p = generate_profile(new MotionState(0,0,0,0), target, constraints);
	ASSERT_TRUE(p->is_valid());
	cout << *p << endl;
	p->to_file("profile1.txt");
	delete p;
}
