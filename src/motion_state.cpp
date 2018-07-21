#include <cmath>

#include "../include/motion_state.h"

MotionState::MotionState(double p, double v, double a, double t){
	this->pos = p;
	this->vel = v;
	this->accel = a;
	this->time = t;
}

double MotionState::get_pos(){
	return this->pos;
}

double MotionState::get_vel(){
	return this->vel;
}

double MotionState::get_vel2(){
	return pow(this->vel, 2);
}

double MotionState::get_accel(){
	return this->accel;
}

double MotionState::get_time(){
	return this->time;
}

ostream& operator<<(std::ostream& stream, const MotionState& obj){
	return stream << "T: " << obj.time << "\tP: " << obj.pos << "\tV: " << obj.vel << "\tA: " << obj.accel;
}
