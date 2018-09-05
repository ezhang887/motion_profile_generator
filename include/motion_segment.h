#ifndef MOTION_SEGMENT_H
#define MOTION_SEGMENT_H

#include "motion_state.h"

class MotionSegment{

    public:
        MotionSegment(MotionState* initial, MotionState* final);
        MotionSegment(MotionSegment* copy);
        ~MotionSegment();
        MotionState* get_initial();
        MotionState* get_final();
        bool is_valid();
        bool contains_time(double time);
        bool contains_pos(double pos);
        
        friend ostream& operator<<(ostream& stream, const MotionSegment& obj);

    private:
        MotionState* initial;
        MotionState* final;

};

#endif
