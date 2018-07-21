#include <gtest/gtest.h>
#include "../include/motion_state.h"

using namespace std;

TEST(MotionState, constructor){
	MotionState state(10.0, 10.0, 0.0, 2.0);
	ASSERT_EQ(10.0, state.get_pos());
	ASSERT_EQ(10.0, state.get_vel());
	ASSERT_EQ(100.0, state.get_vel2());
	ASSERT_EQ(0.0, state.get_accel());
	ASSERT_EQ(2.0, state.get_time());
}
