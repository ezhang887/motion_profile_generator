#include "../include/motion_segment.h"
#include "../include/utils.h"

MotionSegment::MotionSegment(MotionState* initial, MotionState* final){
    this->initial = initial;
    this->final = final;
}

MotionSegment::MotionSegment(MotionSegment* other){
    this->initial = new MotionState(other->initial);
    this->final = new MotionState(other->final);
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
            cout << initial->get_accel() << " " << final->get_accel() << endl;
            cout << "DEBUG" << endl;
            return false;
    }
    MotionState* extrapolated = initial->extrapolate(final->get_time());
    if (*extrapolated != *final){
            return false;
    }
    delete extrapolated;
    return true;			
}

bool MotionSegment::contains_time(double time){
    return time >= get_initial()->get_time() && time <= get_final()->get_time();
}

ostream& operator<<(ostream& stream, const MotionSegment& obj){
    return stream << *(obj.initial) << "\t" << *(obj.final) << endl;
}
