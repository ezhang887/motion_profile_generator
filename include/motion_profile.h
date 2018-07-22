#ifndef MOTION_PROFILE_H
#define MOTION_PROFILE_H

#include <ostream>
#include <vector>

#include "../include/motion_segment.h"

using namespace std;

class MotionProfile{

	public:
		MotionProfile(vector<MotionSegment*> segments);
		MotionProfile();
		~MotionProfile();
		int size();
		double initial_time();
		double final_time();
		double elapsed_time();
		double initial_pos();
		double final_pos();
		double total_dist();
		void add_segment(MotionSegment* segment);
		bool is_empty();
		bool is_valid();
		vector<MotionSegment*> get_segments();
		MotionState* initial_state();
		MotionState* final_state();
		MotionState* get_state(double time);

		friend ostream& operator<<(ostream& stream, const MotionProfile& obj);

	private:
		vector<MotionSegment*> segments;
};

#endif
