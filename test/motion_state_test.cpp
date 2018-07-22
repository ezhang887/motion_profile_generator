#include <gtest/gtest.h>
#include "../include/motion_state.h"

using namespace std;

TEST(MotionState, constructor){
	MotionState* state = new MotionState(10.0, 10.0, 0.0, 2.0);
	ASSERT_EQ(10.0, state->get_pos());
	ASSERT_EQ(10.0, state->get_vel());
	ASSERT_EQ(100.0, state->get_vel2());
	ASSERT_EQ(0.0, state->get_accel());
	ASSERT_EQ(2.0, state->get_time());
	delete state;
}

TEST(MotionState, operator_equals){

}

TEST(MotionState, extrapolate_no_acceleration){
	MotionState* start = new MotionState(12.0, 10.0, 0.0, 0.0);
	MotionState* extrapolated = start->extrapolate(1);
	ASSERT_EQ(22.0, extrapolated->get_pos());
	ASSERT_EQ(10.0, extrapolated->get_vel());
	ASSERT_EQ(0.0, extrapolated->get_accel());
	ASSERT_EQ(1.0, extrapolated->get_time());
	delete start;
	delete extrapolated;
}

TEST(MotionState, extrapolate_with_acceleration){
	//start at time t=1, with position 12, velocity 10, and acceleration 5
	MotionState* start = new MotionState(12.0, 10.0, 5.0, 1.0);
	//find our state at time t=2
	MotionState* extrapolated = start->extrapolate(2);
	ASSERT_EQ(24.5, extrapolated->get_pos());
	ASSERT_EQ(15.0, extrapolated->get_vel());
	ASSERT_EQ(5.0, extrapolated->get_accel());
	ASSERT_EQ(2.0, extrapolated->get_time());
	delete start;
	delete extrapolated;
}

TEST(MotionState, extrapolate_backwards){
	//start at time t=1, with position 12, velocity 10, and acceleration 5
	MotionState* start = new MotionState(12.0, 10.0, 5.0, 1.0);
	//find our state at time t=0 (i.e. one second ago)
	MotionState* extrapolated = start->extrapolate(0);
	ASSERT_EQ(4.5, extrapolated->get_pos());
	ASSERT_EQ(5.0, extrapolated->get_vel());
	ASSERT_EQ(5.0, extrapolated->get_accel());
	ASSERT_EQ(0.0, extrapolated->get_time());
	delete start;
	delete extrapolated;
}

TEST(MotionState, equals){
	MotionState* a = new MotionState(1.0, -5.0, 4.0, 2.5);
	MotionState* b = new MotionState(1.0, -5.0, 4.0, 2.5);
	MotionState* c = new MotionState(1.0, -4.0, 4.0, 2.5);
	ASSERT_TRUE(*a == *b);
	ASSERT_FALSE(*a != *b);
	ASSERT_FALSE(*a == *c);
	ASSERT_FALSE(*c == *b);
	ASSERT_TRUE(*a != *c);
	ASSERT_TRUE(*c != *b);
	delete a;
	delete b;
	delete c;
}

TEST(MotionState, coincident){
	MotionState* a = new MotionState(0.0, 0.0, 0.0, 1.0);
	MotionState* b = new MotionState(0.0, 0.0, 5.0, 1.0);
	ASSERT_TRUE(a->coincident(b));
	delete b;
	b = new MotionState(1.0, 0.0, 5.0, 1.0);
	ASSERT_FALSE(a->coincident(b));
	delete a;
	delete b;
}
