#include <cmath>

#include "../include/utils.h"
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

MotionState* MotionState::extrapolate(double time){
	double dt = time - this->time;
	double new_pos = this->pos + this->vel*dt + 0.5*this->accel*dt*dt;
	double new_vel = this->vel + this->accel*dt;
	return new MotionState(new_pos, new_vel, accel, time);
}

bool MotionState::coincident(MotionState* other){
	return this->time == other->time && this->pos == other->pos && this->vel == other->vel;
}

ostream& operator<<(std::ostream& stream, const MotionState& obj){
	return stream << "T:" << obj.time << " P: " << obj.pos << " V:" << obj.vel << " A:" << obj.accel;
}

bool operator==(const MotionState& first, const MotionState& second){
	return equals(first.pos, second.pos) && equals(first.vel, second.vel) && equals(first.accel, second.accel) && equals(first.time, second.time);
}

bool operator!=(const MotionState& first, const MotionState& second){
	return !(first==second);
}
