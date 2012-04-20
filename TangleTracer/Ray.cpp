#include "Ray.h"

// ---------------------------------------------------------------- default constructor

Ray::Ray (void)
	: 	o(0.0), 
		d(0.0, 0.0, 1.0),
		depth(0)
{}

// ---------------------------------------------------------------- constructor

Ray::Ray (const Point3D& origin, const Vector3D& dir)
	: 	o(origin), 
		d(dir),
		depth(0)
{}

// ---------------------------------------------------------------- copy constructor

Ray::Ray (const Ray& ray)
	: 	o(ray.o), 
		d(ray.d),
		depth(ray.depth)
{}

// ---------------------------------------------------------------- assignment operator

Ray& 
Ray::operator= (const Ray& rhs) {
	
	if (this == &rhs)
		return (*this);
		
	o = rhs.o; 
	d = rhs.d; 
	depth = rhs.depth;

	return (*this);	
}

// ---------------------------------------------------------------- destructor

Ray::~Ray (void) {}



