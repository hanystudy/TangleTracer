// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the definition of the class ConcaveSphere

#include "ConcaveSphere.h"
#include "math.h"

const double ConcaveSphere::kEpsilon = 0.001;
					
// ---------------------------------------------------------------- default constructor

ConcaveSphere::ConcaveSphere(void)	
	: 	GeometricObject(),
		center(0.0),
		radius(1.0),
		shadows(false)
{}


// ---------------------------------------------------------------- constructor

ConcaveSphere::ConcaveSphere(Point3D c, double r)
	: 	GeometricObject(),
		center(c),
		radius(r)
{}


// ---------------------------------------------------------------- clone

GeometricObject* 
ConcaveSphere::clone(void) const {
	return (new ConcaveSphere(*this));
}


// ---------------------------------------------------------------- copy constructor

ConcaveSphere::ConcaveSphere (const ConcaveSphere& ConcaveSphere)
	: 	GeometricObject(ConcaveSphere),
		center(ConcaveSphere.center),
		radius(ConcaveSphere.radius)
{}



// ---------------------------------------------------------------- assignment operator

ConcaveSphere& 
ConcaveSphere::operator= (const ConcaveSphere& rhs)		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;

	return (*this);
}


// ---------------------------------------------------------------- destructor

ConcaveSphere::~ConcaveSphere(void) {}


//---------------------------------------------------------------- hit

bool
ConcaveSphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	Vector3D	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal 	 = -(temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	
		t = (-b + e) / denom;    // larger root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = -(temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	}
	
	return (false);
}

bool 												
ConcaveSphere::shadow_hit(const Ray& ray, float& tmin) const {

	if(shadows)
	{
		double 		t;
		Vector3D  	temp 	= ray.o - center;
		double 		a 		= ray.d * ray.d;
		double 		b 		= 2.0 * temp * ray.d;
		double 		c 		= temp * temp - radius * radius;
		double 		disc 	= b * b - 4.0 * a * c;
	
		if (disc < 0.0)
			return(false);
		else {	
			double e = sqrt(disc);
			double denom = 2.0 * a;
			t = (-b - e) / denom;    // smaller root
		
			if (t > kEpsilon) {	
				if ( t < tmin ) 
				{				
					tmin = t;				
					return (true);
				}
			} 
		
			t = (-b + e) / denom;    // larger root
		
			if (t > kEpsilon) {	
				if ( t < tmin ) 
				{
					tmin = t;
					return (true);
				}
			} 
		}
	}
	return (false);

}
