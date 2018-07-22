#include <gtest/gtest.h>

#include "../include/motion_profile.h"
#include "../include/motion_segment.h"

TEST(MotionProfile, triangular_profile){
	vector<MotionSegment*> v;	
	//accelerate from 0 unit/sec up to 1 unit/sec at 1 unit/sec^2 for 1 sec
	v.push_back(new MotionSegment(new MotionState(0,0,1,0), new MotionState(1.5,1,1,1)));
	//decelerate back down to 0 unit/sec from 1 unit/sec at 1 unit/sec^2 for 1 sec
	v.push_back(new MotionSegment(new MotionState(1.5,1,-1,1), new MotionState(2,0,-1,2)));

	MotionProfile* m = new MotionProfile(v);
	ASSERT_TRUE(m->is_valid());
	cout << *m << endl;
	delete m;
}
