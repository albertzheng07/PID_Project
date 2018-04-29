#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	Kp_ = Kp;
	Ki_ = Ki;
	Kd_ = Kd;
	prev_error = 0.0;	
}

void PID::UpdateError(double cte) {
	p_error = Kp_*cte;
	i_error += Ki_*cte; 
	i_error = clip(i_error,-0.5*Kp_,0.5*Kp_); // clip integrator to avoid windup issues
	double diff_error = prev_error-cte;
	d_error = Kd_*diff_error;
	prev_error = cte;

}

double PID::TotalError() {
	return p_error+i_error+d_error;
}

