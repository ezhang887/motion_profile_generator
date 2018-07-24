#include <cmath>

#include "motion_profile.h"

MotionProfile::MotionProfile(vector<MotionSegment*> segments){
	this->segments = segments;
}

MotionProfile::MotionProfile(){}

MotionProfile::~MotionProfile(){
	for(auto it = segments.begin(); it != segments.end(); it++){
		delete *it;
	}
}

int MotionProfile::size(){
	return segments.size();	
}

double MotionProfile::initial_time(){
	return initial_state()->get_time();
}

double MotionProfile::final_time(){
	return final_state()->get_time();	
}

double MotionProfile::elapsed_time(){
	return final_time()-initial_time();
}

double MotionProfile::initial_pos(){
	return initial_state()->get_pos();
}

double MotionProfile::final_pos(){
	return final_state()->get_pos();
}

double MotionProfile::total_dist(){
	return fabs(fabs(final_pos())-fabs(initial_pos()));
}

void MotionProfile::add_segment(MotionSegment* segment){
	segments.push_back(segment);
}

bool MotionProfile::is_empty(){
	return this->size() == 0;
}

bool MotionProfile::is_valid(){
	if (!segments.at(0)->is_valid()){
		return false;
	}
	for(auto it = segments.begin(), it2 = segments.begin()+1; it2 != segments.end(); it++, it2++){
		if (!(*it2)->is_valid()){
			return false;
		}
		//make sure the connections between segments are continuous
		if (!(*it)->get_final()->coincident((*it2)->get_initial())){
			return false;
		}
	}
	return true;
}

vector<MotionSegment*> MotionProfile::get_segments(){
	return segments;
}

MotionState* MotionProfile::initial_state(){
	return segments.at(0)->get_initial();
}

MotionState* MotionProfile::final_state(){
	return segments.at(size()-1)->get_final();
}

MotionState* MotionProfile::get_state(double time){
	for(auto it = segments.begin(); it != segments.end(); it++){
		if ((*it)->contains_time(time)) return (*it)->get_initial()->extrapolate(time);
	}
	return nullptr;
}

void MotionProfile::to_file(string name){
	ofstream file(name);
	for(auto it = segments.begin(); it != segments.end(); it++){
		file << **it << endl;
	}
	file.close();
}

void MotionProfile::to_gnuplot_file(string name){
	ofstream file(name);	
	file << "X\tY1\tY2\tY3\n";
	double curr_time = initial_time();
	int k = 100000;
	int iter = elapsed_time()*k;
	for(int i=0; i<iter; i++){
		MotionState* s = get_state(curr_time);
		if (s == nullptr){
			continue;
		}
		file << s->get_time() << "\t" << s->get_pos() << "\t" << s->get_vel() << "\t" << s->get_accel() << endl;
		curr_time += elapsed_time()/k;
		delete s;
	}
	file.close();
}

ostream& operator<<(ostream& stream, const MotionProfile& obj){
	for(auto it = obj.segments.begin(); it != obj.segments.end(); it++){
		stream << **it << endl;
	}
	return stream;
}
