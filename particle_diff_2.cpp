/*
File:			particle_diff_2.cpp
Author:			Stewart Nash
Date:			March 4, 2015
Description:	Program using OpenGL to visualize rudimentary particle diffusion.
Version:		0.0
Last update:	None
*/
#include <GL/glut.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "particles_1.h"

void init();
void display();
void reshape(GLint width, GLint height);
void timer(int value);
void special(int key, int, int);
void drawparticles(unsigned long count, Particle * myParticle);
void updateposition(unsigned long count, Particle * myParticle, double input_time);
void drawborder(double * center, double width, double length, double height);
void drawborder(double center_x, double center_y, double center_z, double width, double length, double height);

// A camera class from http://cs.lmu.edu/~ray/notes/openglexamples/. It moves horizontally in a circle centered at the origin of radius 16.  It moves vertically straight up and down.
class Camera
{
	double theta;      // determines the x and y positions
	double z;          // the current z position
	double dTheta;     // increment in theta for swinging the camera around
	double dz;         // increment in z for moving the camera up/down
public:
	Camera(): theta(0), z(16), dTheta(0.04), dz(0.2) {}
	double getX() {return 16 * cos(theta);}
	double getZ() {return z;}
	double getY() {return 16 * sin(theta);}
	void moveRight() {theta += dTheta;}
	void moveLeft() {theta -= dTheta;}
	void moveUp() {z += dz;}
	void moveDown() {if (z > dz) z -= dz;}
};

// Colors
GLfloat WHITE[] = {1, 1, 1};
GLfloat RED[] = {1, 0, 0};
GLfloat GREEN[] = {0, 1, 0};
GLfloat MAGENTA[] = {1, 0, 1};

GLfloat temp_color[] = {1, 0, 1};
Particle * globalParticle;
Camera myCamera;

const static int PARTICLE_COUNT = 15;
const static int MAX_DISTANCE = 8;
const static int MAX_SPEED = 3;
const static int MAX_ACCEL = 2;
const static double SPEED_SCALE = 0.0625;
const static double ACCEL_SCALE = 0.0625;
const static double POS_SCALE = 0.5;

static int windowwidth = 1280;
static int windowheight = 720;
static int framespersecond = 60;

// Initialization, including GLUT initialization and entry into main loop.
int main(int argc, char** argv)
{
	int i;
	double speed_x, speed_y, speed_z;
	double accel_x, accel_y, accel_z;
	double pos_x, pos_y, pos_z;
	Particle myParticle[PARTICLE_COUNT];

	srand(time(NULL));
	
	globalParticle = myParticle;
	for (i = 0; i < PARTICLE_COUNT; i++)
	{
		speed_x = SPEED_SCALE * (MAX_SPEED - (rand() % (2 * MAX_SPEED + 1)));
		speed_y = SPEED_SCALE * (MAX_SPEED - (rand() % (2 * MAX_SPEED + 1)));
		speed_z = SPEED_SCALE * (MAX_SPEED - (rand() % (2 * MAX_SPEED + 1)));
		accel_x = ACCEL_SCALE * (MAX_ACCEL - (rand() % (2 * MAX_ACCEL + 1)));
		accel_y = ACCEL_SCALE * (MAX_ACCEL - (rand() % (2 * MAX_ACCEL + 1)));
		accel_z = ACCEL_SCALE * (MAX_ACCEL - (rand() % (2 * MAX_ACCEL + 1)));
		pos_x = POS_SCALE * (MAX_DISTANCE - (rand() % (2 * MAX_DISTANCE + 1)));
		pos_y = POS_SCALE * (MAX_DISTANCE - (rand() % (2 * MAX_DISTANCE + 1)));
		pos_z = POS_SCALE * (MAX_DISTANCE - (rand() % (2 * MAX_DISTANCE + 1)));
		globalParticle[i].setposition(pos_x, pos_y, pos_z);
		globalParticle[i].setvelocity(speed_x, speed_y, speed_z);
		globalParticle[i].setacceleration(accel_x, accel_y, accel_z);
		globalParticle[i].setradius(0.25);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(windowwidth, windowheight);
	glutCreateWindow("Particle Diffusion 2");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutTimerFunc(100, timer, 0);
	init();
	glutMainLoop();
}

// Application-specific initialization: Set up global lighting parameters and create display lists.
void init()
{
	GLfloat temp_color_white[] = {1, 1, 1};

	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, temp_color_white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, temp_color_white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, temp_color_white);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

// Draw the border and particles.
void display()
{
	double dimensions;
	double center;

	dimensions = static_cast <double> (MAX_DISTANCE);
	center = 0.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(myCamera.getX(), myCamera.getY(), myCamera.getZ(), center, center, center, 0.0, 0.0, 1.0);
	drawborder(0.0, 0.0, 0.0, dimensions, dimensions, dimensions);
	for (int i = 0; i < PARTICLE_COUNT; i++)
		drawparticles(PARTICLE_COUNT, globalParticle);
	glFlush();
	glutSwapBuffers();
}

// On reshape, constructs a camera that perfectly fits the window.
void reshape(GLint width, GLint height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, GLfloat(width) / GLfloat(height), 1.0, 150.0);
	glMatrixMode(GL_MODELVIEW);
}

// Draw succeeding frame when timer goes off.
void timer(int value)
{
	double temp_time;

	temp_time = static_cast <double> (framespersecond);
	temp_time = 1 / temp_time;
	updateposition(PARTICLE_COUNT, globalParticle, temp_time);

	glutPostRedisplay();
	glutTimerFunc(1000 / framespersecond, timer, value);
}

// Moves the camera according to the key pressed, then ask to refresh the
// display.
void special(int key, int, int)
{
  switch (key)
  {
    case GLUT_KEY_LEFT: myCamera.moveLeft(); break;
    case GLUT_KEY_RIGHT: myCamera.moveRight(); break;
    case GLUT_KEY_UP: myCamera.moveUp(); break;
    case GLUT_KEY_DOWN: myCamera.moveDown(); break;
  }
  glutPostRedisplay();
}

//Draw particles.
void drawparticles(unsigned long count, Particle * myParticle)
{
	int i;
	GLfloat temp_color[] = {1, 0, 1};

	for (i = 0; i < count; i++)
	{
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, temp_color);	
		glTranslated(myParticle[i].getposition(0), myParticle[i].getposition(1), myParticle[i].getposition(2));
		glutSolidSphere(myParticle[i].getradius(), 30, 30);
		glPopMatrix();
	}
}

//Update particle position using member function.
void updateposition(unsigned long count, Particle * myParticle, double input_time)
{
	int i;
	for (i = 0; i < count; i++)
	{
		myParticle[i].addtime(input_time);
	}	
}

//Draw a border around the boundary.
void drawborder(double * center, double width, double length, double height)
{
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WHITE);	
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(center[0], center[1], center[2]);
	glScalef(width, length, height);
	glutWireCube(1.0);
	glPopMatrix();
}

//Draw a border around the boundary.
void drawborder(double center_x, double center_y, double center_z, double width, double length, double height)
{
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WHITE);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(center_x, center_y, center_z);
	glScalef(width, length, height);
	glutWireCube(1.0);
	glPopMatrix();
}