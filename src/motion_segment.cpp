#include "../include/motion_segment.h"

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
	return true;			
}
