#include "../include/motion_segment.h"
#include "../include/utils.h"

MotionSegment::MotionSegment(MotionState* initial, MotionState* final){
	this->initial = initial;
	this->final = final;
}

MotionSegment::~MotionSegment(){
	delete initial;
	delete final;
}

MotionState* MotionSegment::get_initial(){
	return this->initial;
}

MotionState* MotionSegment::get_final(){
	return this->final;
}

bool MotionSegment::is_valid(){
	//make sure a segment has constant acceleration
	if (!equals(initial->get_accel(), final->get_accel())){
		return false;
	}
	MotionState* extrapolated = initial->extrapolate(final->get_time());
	if (*extrapolated != *final){
		return false;
	}
	delete extrapolated;
	return true;			
}

ostream& operator<<(ostream& stream, const MotionSegment& obj){
	return stream << *(obj.initial) << "\t" << *(obj.final) << endl;
}
