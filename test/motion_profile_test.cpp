#include <gtest/gtest.h>

#include "../include/motion_profile.h"
#include "../include/motion_segment.h"

TEST(MotionProfile, triangular_profile){
    vector<MotionSegment*> v;	
    MotionState* initial = new MotionState(12.0, 0.0, 1.0, 0.0);
    MotionState* final = new MotionState(13.0, 0.0, -1.0, 2.0);
    MotionState* test_state = new MotionState(12.125, 0.5, 1.0, 0.5);
    //accelerate from 0 units/sec up to 1 units/sec at 1 units/sec^2 for 1 sec
    v.push_back(new MotionSegment(new MotionState(12.0,0.0,1.0,0.0), new MotionState(12.5,1.0,1.0,1.0)));
    //decelerate back down to 0 units/sec from 1 units/sec at 1 units/sec^2 for 1 sec
    v.push_back(new MotionSegment(new MotionState(12.5,1.0,-1.0,1.0), new MotionState(13.0,0.0,-1.0,2.0)));

    MotionProfile* m = new MotionProfile(v);
    ASSERT_TRUE(m->is_valid());
    ASSERT_EQ(2, m->size());
    ASSERT_EQ(0.0, m->initial_time());
    ASSERT_EQ(2.0, m->final_time());
    ASSERT_EQ(2.0, m->elapsed_time());
    ASSERT_EQ(12.0, m->initial_pos());
    ASSERT_EQ(13.0, m->final_pos());
    ASSERT_EQ(1.0, m->total_dist());


    ASSERT_TRUE(*initial == *(m->initial_state()));
    ASSERT_TRUE(*final == *(m->final_state()));

    MotionState* extrapolated = m->get_state(0.5);
    ASSERT_TRUE(*test_state == *extrapolated);
    delete extrapolated;
    extrapolated = m->get_state(0.0);
    ASSERT_TRUE(*initial == *extrapolated);
    delete extrapolated;
    extrapolated = m->get_state(2.0);
    ASSERT_TRUE(*final == *extrapolated);
    delete extrapolated;
    ASSERT_TRUE(m->get_state(3.0) == nullptr);

    ASSERT_FALSE(m->is_empty());

    delete initial;
    delete final;
    delete test_state;
    delete m;
}

TEST(MotionProfile, trapezoidal_profile){
    vector<MotionSegment*> v;	
    MotionState* initial = new MotionState(0.0, 0.0, 1.0, 10.0);
    MotionState* final = new MotionState(200.0, 0.0, -1.0, 40.0);
    MotionState* test_state = new MotionState(100.0, 10.0, 0.0, 25.0);
    //accelerate from 0 units/sec up to 10 units/sec at 1 units/sec^2 for 10 sec
    v.push_back(new MotionSegment(new MotionState(0.0, 0.0, 1.0, 10.0), new MotionState(50.0, 10.0, 1.0, 20.0)));
    //cruise at 10 units/sec with 0 acceleration for 10 sec
    v.push_back(new MotionSegment(new MotionState(50.0, 10.0, 0.0, 20.0), new MotionState(150.0, 10.0, 0.0, 30.0)));
    //decelerate from 10 units/sec down to 0 units/sec at -1 units/sec^2 for 10 sec
    v.push_back(new MotionSegment(new MotionState(150.0, 10.0, -1.0, 30.0), new MotionState(200.0, 0.0, -1.0, 40.0)));
    
    MotionProfile* m = new MotionProfile();
    for(unsigned int i=0; i<v.size(); i++){
            m->add_segment(v.at(i));
    }
    ASSERT_TRUE(m->is_valid());
    ASSERT_EQ(3, m->size());
    ASSERT_EQ(10.0, m->initial_time());
    ASSERT_EQ(40.0, m->final_time());
    ASSERT_EQ(30.0, m->elapsed_time());
    ASSERT_EQ(0.0, m->initial_pos());
    ASSERT_EQ(200.0, m->final_pos());
    ASSERT_EQ(200.0, m->total_dist());

    ASSERT_TRUE(*initial == *(m->initial_state()));
    ASSERT_TRUE(*final == *(m->final_state()));

    MotionState* extrapolated = m->get_state(25.0);
    ASSERT_TRUE(*test_state == *extrapolated);
    delete extrapolated;
    ASSERT_TRUE(m->get_state(0.0) == nullptr);
    ASSERT_TRUE(m->get_state(50.0) == nullptr);

    ASSERT_FALSE(m->is_empty());

    delete initial;
    delete final;
    delete test_state;
    delete m;
}
