// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the Camera class

#include "Camera.h"


// ----------------------------------------------------------------- default constructor

Camera::Camera(void)		
	:	eye(0, 0, 500),
		lookat(0),
		ra(0),
		up(0, 1, 0),
		u(1, 0, 0),
		v(0, 1, 0),
		w(0, 0, 1),
		exposure_time(1.0)
{}


// ----------------------------------------------------------------- copy constructor

Camera::Camera(const Camera& c)   		
	: 	eye(c.eye),
		lookat(c.lookat),
		ra(c.ra),
		up(c.up),
		u(c.u),
		v(c.v),
		w(c.w),
		exposure_time(c.exposure_time)
{}



// ----------------------------------------------------------------- assignment operator

Camera& 
Camera::operator= (const Camera& rhs) {
	if (this == &rhs)
		return (*this);
	
	eye				= rhs.eye;
	lookat			= rhs.lookat;
	ra				= rhs.ra;
	up				= rhs.up;
	u				= rhs.u;
	v				= rhs.v;
	w				= rhs.w;
	exposure_time 	= rhs.exposure_time;

	return (*this);
}


// ----------------------------------------------------------------- destructor

Camera::~Camera(void) {}



//-------------------------------------------------------------- compute_uvw

// This computes an orthornormal basis given the view point, lookat point, and up vector

void
Camera::compute_uvw(void) {
	w = eye - lookat;
	w.normalize();
	u = up ^ w; 
	u.normalize();
	v = w ^ u;

	// take care of the singularity by hardwiring in specific camera orientations
	
	if (eye.x == lookat.x && eye.z == lookat.z && eye.y > lookat.y) { // camera looking vertically down
		u = Vector3D(0, 0, 1);
		v = Vector3D(1, 0, 0);
		w = Vector3D(0, 1, 0);	
	}
	
	if (eye.x == lookat.x && eye.z == lookat.z && eye.y < lookat.y) { // camera looking vertically up
		u = Vector3D(1, 0, 0);
		v = Vector3D(0, 0, 1);
		w = Vector3D(0, -1, 0);
	}
}

// ----------------------------------------------------------------- set_roll_angle

void
Camera::set_roll_angle(const float r) {

	float ra = r * PI_ON_180;
	//T(1)*R(-1)R(a)R(1)T(-1)
	Matrix F,T,R,Ra;
	T.set_identity();
	R.set_identity();
	Ra.set_identity();
	
	Vector3D q = up;
	q.normalize();
	Vector3D w = eye-lookat;
	w.normalize();
	Vector3D p = w^q;
	p.normalize();

	T.m[0][3] = lookat.x;
	T.m[1][3] = lookat.y;
	T.m[2][3] = lookat.z;
	
	R.m[0][0] = q.x;
	R.m[1][0] = q.y;
	R.m[2][0] = q.z;
	R.m[0][1] = p.x;
	R.m[1][1] = p.y;
	R.m[2][1] = p.z;
	R.m[0][2] = w.x;
	R.m[1][2] = w.y;
	R.m[2][2] = w.z;

	Ra.m[0][0] = cos(ra);
	Ra.m[0][1] = sin(ra);
	Ra.m[1][0] = -sin(ra);
	Ra.m[1][1] = cos(ra);

	F = (T*R)*Ra;

	T.m[0][3] = -lookat.x;
	T.m[1][3] = -lookat.y;
	T.m[2][3] = -lookat.z;
	
	R.m[0][0] = q.x;
	R.m[0][1] = q.y;
	R.m[0][2] = q.z;
	R.m[1][0] = p.x;
	R.m[1][1] = p.y;
	R.m[1][2] = p.z;
	R.m[2][0] = w.x;
	R.m[2][1] = w.y;
	R.m[2][2] = w.z;

	F = (F*R)*T;

	up = (F * (eye + up) - eye);
	up.normalize();
}
