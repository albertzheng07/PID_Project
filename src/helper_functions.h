/* 
* helpers_functions.h
*/

#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

#include <math.h>
#include <iostream>

using namespace std;

/*
 * Clips the input value to the min and max values
 * @param x - input value
 * @param min - minimum value
 * @param max - maximum value 
 * @output bounded value between min and max
 */
inline double clip(double x, double min_, double max_)
{
	return max(min(x,max_),min_);
}

inline double unWrapAngle(double angle) 
{
  if (angle > M_PI)
  {
    angle = fmod(angle+M_PI,2.0*M_PI)-M_PI;
  }
  else if (angle < -M_PI)
  {
    angle = fmod(angle-M_PI,2.0*M_PI)+M_PI;
  }
  return angle; 
}

#endif /* HELPER_FUNCTIONS_H_ */
