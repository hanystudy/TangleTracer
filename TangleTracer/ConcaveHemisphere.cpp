// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the definition of the class ConcaveHemisphere

#include "ConcaveHemisphere.h"
#include "math.h"

const double ConcaveHemisphere::kEpsilon = 0.001;
					
// ---------------------------------------------------------------- default constructor

ConcaveHemisphere::ConcaveHemisphere(void)	
	: 	GeometricObject(),
		center(0.0),
		radius(1.0),
		shadows(false)
{}


// ---------------------------------------------------------------- constructor

ConcaveHemisphere::ConcaveHemisphere(Point3D c, double r)
	: 	GeometricObject(),
		center(c),
		radius(r)
{}


// ---------------------------------------------------------------- clone

GeometricObject* 
ConcaveHemisphere::clone(void) const {
	return (new ConcaveHemisphere(*this));
}


// ---------------------------------------------------------------- copy constructor

ConcaveHemisphere::ConcaveHemisphere (const ConcaveHemisphere& ConcaveHemisphere)
	: 	GeometricObject(ConcaveHemisphere),
		center(ConcaveHemisphere.center),
		radius(ConcaveHemisphere.radius)
{}



// ---------------------------------------------------------------- assignment operator

ConcaveHemisphere& 
ConcaveHemisphere::operator= (const ConcaveHemisphere& rhs)		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;

	return (*this);
}


// ---------------------------------------------------------------- destructor

ConcaveHemisphere::~ConcaveHemisphere(void) {}


//---------------------------------------------------------------- hit

bool
ConcaveHemisphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
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

			Vector3D hit = ray.o + t * ray.d - center;
			
			if (hit.y > center.y )
			{				
				tmin = t;
				sr.normal = - (temp + t * ray.d) / radius;   // points outwards
				sr.local_hit_point = ray.o + tmin * ray.d;				
				return (true);
			}
			/*
			tmin = t;
			sr.normal 	 = -(temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);*/
		} 
	
		t = (-b + e) / denom;    // larger root
	
		if (t > kEpsilon) {
			
			Vector3D hit = ray.o + t * ray.d - center;
			
			if (hit.y > center.y )
			{				
				tmin = t;
				sr.normal = - (temp + t * ray.d) / radius;   // points outwards
				sr.local_hit_point = ray.o + tmin * ray.d;				
				return (true);
			}
			/*
			tmin = t;
			sr.normal   = -(temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
			*/
		} 
	}
	
	return (false);
}

bool 												
ConcaveHemisphere::shadow_hit(const Ray& ray, float& tmin) const {

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
				Vector3D hit = ray.o + t * ray.d - center;			
				if ( t < tmin && hit.y > 0 ) 
				{				
					tmin = t;				
					return (true);
				}
			} 
		
			t = (-b + e) / denom;    // larger root
		
			if (t > kEpsilon) {
				Vector3D hit = ray.o + t * ray.d - center;			
				if ( t < tmin && hit.y > 0) 
				{
					tmin = t;
					return (true);
				}
			} 
		}
	}
	return (false);
}

float
ConcaveHemisphere::pdf(ShadeRec& sr)
{
	return 0;
}