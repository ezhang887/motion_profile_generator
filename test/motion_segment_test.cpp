#include <gtest/gtest.h>

#include "../include/motion_segment.h"
#include "../include/motion_state.h"

TEST(MotionSegment, valid){
    MotionSegment* m = new MotionSegment(new MotionState(0,0,0,0), new MotionState(0,0,0,1));
    ASSERT_TRUE(m->is_valid());
    delete m;
}

TEST(MotionSegment, non_constant_acceleration){
    MotionSegment* m = new MotionSegment(new MotionState(0,0,0,0), new MotionState(0,0,1,1));
    ASSERT_FALSE(m->is_valid());
    delete m;
}

TEST(MotionSegment, continuous){
    MotionSegment* m = new MotionSegment(new MotionState(0,10,10,0), new MotionState(15,20,10,1));
    ASSERT_TRUE(m->is_valid());
    delete m;
}

TEST(MotionSegment, contains_time){
    MotionSegment* m = new MotionSegment(new MotionState(0,10,10,0), new MotionState(15,20,10,1));
    ASSERT_TRUE(m->contains_time(0.0));
    ASSERT_TRUE(m->contains_time(1.0));
    ASSERT_TRUE(m->contains_time(0.5));
    ASSERT_FALSE(m->contains_time(1.111111));
    ASSERT_FALSE(m->contains_time(-0.01));
    delete m;
}
