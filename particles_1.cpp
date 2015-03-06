/*
File:			particles_1.cpp
Author:			Stewart Nash
Date:			March 4, 2015
Description:	Implementation or definition of particle class for use in diffusion application.
Version:		0.0
Last update:	None
*/
#include "particles_1.h"

Particle::Particle()
{
	int i;
	for (i = 0; i < 3; i++)
	{
		position[i] = 0;
		velocity[i] = 0;
		acceleration[i] = 0;
	}	
	radius = 0;
	elasticity = 0;
	mass = 0;
	time = 0;
	flags = 0;
}

//double * Particle::getposition(){}

double Particle::getposition(unsigned short coordinate)
{
	if (coordinate < 3)
		return position[coordinate];
	else
		std::cout << "ERROR (particles_1.cpp): getposition(coordinate) - Coordinate out of range. Results may be inaccurate.";
	return 0;
}

//double * Particle::getvelocity(){}

double Particle::getvelocity(unsigned short coordinate)
{
	if (coordinate < 3)
		return velocity[coordinate];
	else
		std::cout << "ERROR (particles_1.cpp): getvelocity(coordinate) - Coordinate out of range. Results may be inaccurate.";
	return 0;
}
//double * Particle::getacceleration(){}

double Particle::getacceleration(unsigned short coordinate)
{
	if (coordinate < 3)
		return acceleration[coordinate];
	else
		std::cout << "ERROR (particles_1.cpp): getacceleration(coordinate) - Coordinate out of range. Results may be inaccurate.";
	return 0;
}

double Particle::getelasticity()
{
	return elasticity;
}

double Particle::getradius()
{
	return radius;
}

double Particle::getmass()
{
	return mass;
}

double Particle::gettime()
{
	return time;
}

int Particle::getflags()
{
	return flags;
}

void Particle::setposition(double input_pos_x, double input_pos_y, double input_pos_z)
{
	position[0] = input_pos_x;
	position[1] = input_pos_y;
	position[2] = input_pos_z;
	return;
}

double Particle::setposition(unsigned short coordinate, double input_position)
{
	if (coordinate < 3)
	{
		position[coordinate] = input_position;
		return position[coordinate];
	}
	else
		std::cout << "ERROR (particles_1.cpp): setposition(coordinate) - Coordinate out of range. Value not set. Results may be inaccurate.";
	return 0;
}

void Particle::setvelocity(double input_veloc_x, double input_veloc_y, double input_veloc_z)
{
	velocity[0] = input_veloc_x;
	velocity[1] = input_veloc_y;
	velocity[2] = input_veloc_z;
	return;
}

double Particle::setvelocity(unsigned short coordinate, double input_velocity)
{
	if (coordinate < 3)
	{
		velocity[coordinate] = input_velocity;
		return velocity[coordinate];
	}
	else
		std::cout << "ERROR (particles_1.cpp): setvelocity(coordinate) - Coordinate out of range. Value not set. Results may be inaccurate.";
	return 0;
}

void Particle::setacceleration(double input_accel_x, double input_accel_y, double input_accel_z)
{
	acceleration[0] = input_accel_x;
	acceleration[1] = input_accel_y;
	acceleration[2] = input_accel_z;
	return;
}

double Particle::setacceleration(unsigned short coordinate, double input_acceleration)
{
	if (coordinate < 3)
	{
		acceleration[coordinate] = input_acceleration;
		return acceleration[coordinate];
	}
	else
		std::cout << "ERROR (particles_1.cpp): setacceleration(coordinate) - Coordinate out of range. Value not set. Results may be inaccurate.";
	return 0;
}

double Particle::setelasticity(double input_elasticity)
{
	//Should this value always be positive?
	elasticity = input_elasticity;
	return elasticity;
}

double Particle::setradius(double input_radius)
{
	radius = input_radius;
	return radius;
}

double Particle::setmass(double input_mass)
{
	mass = input_mass;
	return mass;
}

double Particle::settime(double input_time)
{
	time = input_time;
	return time;
}

int Particle::setflags(int input_flags)
{
	flags = input_flags;
	return flags;
}

double Particle::addtime(double input_time)
{
	int i;

	time = time + input_time;
	for (i = 0; i < 3; i++)
	{
		velocity[i] = velocity[i] + acceleration[i] * input_time;
		position[i] = position[i] + velocity[i] * input_time + acceleration[i] * input_time * input_time / 2;
	}

	return time;
}