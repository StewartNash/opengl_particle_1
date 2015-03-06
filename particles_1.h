/*
File:			particles_1.h
Author:			Stewart Nash
Date:			March 4, 2015
Description:	Declaration of particle class for use in diffusion application.
Version:		0.0
Last update:	None
*/
#include <iostream>
#define DIMENSION 3

class Particle
{
	double position[DIMENSION];
	double velocity[DIMENSION];
	double acceleration[DIMENSION];
	double elasticity; //Should this value always be positive?
	double radius;
	double mass;
	double time;
	int flags;
public:
	Particle();

//	double * getposition();
	double getposition(unsigned short coordinate);
//	double * getvelocity();
	double getvelocity(unsigned short coordinate);
//	double * getacceleration();
	double getacceleration(unsigned short coordinate);
	double getelasticity();
	double getradius();
	double getmass();
	double gettime();
	int getflags(); 

	void setposition(double input_pos_x, double input_pos_y, double input_pos_z);
	double setposition(unsigned short coordinate, double input_position);
	void setvelocity(double input_veloc_x, double input_veloc_y, double input_veloc_z);
	double setvelocity(unsigned short coordinate, double input_velocity);
	void setacceleration(double input_accel_x, double input_accel_y, double input_accel_z);
	double setacceleration(unsigned short coordinate, double input_acceleration);
	double setelasticity(double input_elasticity);
	double setradius(double input_radius);
	double setmass(double input_mass);
	double settime(double input_time);
	int setflags(int input_flags);

	double addtime(double intput_time);
};