#include <gtest/gtest.h>
#include "../include/motion_state.h"

using namespace std;

TEST(MotionState, constructor){
	MotionState state(10.0, 10.0, 0.0, 2.0);
	EXPECT_EQ(10.0, state.get_pos());
	EXPECT_EQ(10.0, state.get_vel());
	EXPECT_EQ(100.0, state.get_vel2());
	EXPECT_EQ(0.0, state.get_accel());
	EXPECT_EQ(2.0, state.get_time());
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
