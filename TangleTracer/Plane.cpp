// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Plane.h"

const double Plane::kEpsilon = 0.001;

// ----------------------------------------------------------------------  default constructor

Plane::Plane(void)	
	: 	GeometricObject(),
		a(0.0),
		n(0, 1, 0),
		shadows(true)
{}


// ----------------------------------------------------------------------  constructor

Plane::Plane(const Point3D& point, const Normal& normal)
	:	GeometricObject(),
		a(point),
		n(normal),
		shadows(true)
{
		n.normalize();
}


// ---------------------------------------------------------------- copy constructor

Plane::Plane(const Plane& plane) 
	:	GeometricObject(plane),
		a(plane.a),
		n(plane.n),
		shadows(plane.shadows)
{}


// ---------------------------------------------------------------- clone

GeometricObject* 
Plane::clone(void) const {
	return (new Plane(*this));
}


// ---------------------------------------------------------------- assignment operator

Plane& 
Plane::operator= (const Plane& rhs)	{
	
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	a = rhs.a;
	n = rhs.n;
	shadows = rhs.shadows;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Plane::~Plane(void)				
{}


// ----------------------------------------------------------------- hit

bool 															 
Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
	float t = (a - ray.o) * n / (ray.d * n); 
														
	if (t > kEpsilon) {
		tmin = t;
		sr.normal = n;
		sr.local_hit_point = ray.o + t * ray.d;
		
		return (true);	
	}

	return(false);
}


bool 												
Plane::shadow_hit(const Ray& ray, float& tmin) const {	
	
	if(!shadows)
	{
		return false;
	}
	
	float t = (a - ray.o) * n / (ray.d * n);
														
	if (t > kEpsilon) {
		tmin = t;
		return (true);
	}
	else
		return (false);
}
