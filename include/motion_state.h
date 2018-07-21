#ifndef MOTION_STATE_H
#define MOTION_STATE_H

#include <iostream>
#include <vector>

using namespace std;

class MotionState{
	public:
		MotionState(double p, double v, double a, double t);
		double get_pos();
		double get_vel();
		double get_vel2();
		double get_accel();
		double get_time();

		friend ostream& operator<<(ostream& stream, const MotionState& obj);

	private:
		double pos = 0;
		double vel = 0;
		double accel = 0;
		double time = 0;

};

#endif
