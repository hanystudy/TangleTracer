// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "OpenCone.h"

// This uses the value of kEpsilon defined in Constants.h

// ---------------------------------------------------------------- default constructor

OpenCone::OpenCone(void)
	: 	GeometricObject(),
		h(2.0),
		r(1.0)
{}

// ---------------------------------------------------------------- constructor

OpenCone::OpenCone(const double radius, const double height)
	:  	GeometricObject(),
		h(height),
		r(radius)
{}


// ---------------------------------------------------------------- copy constructor

OpenCone::OpenCone(const OpenCone& c)
	: 	GeometricObject(c),
		h(c.h),
		r(c.r)			
{}
																				
																				
// ---------------------------------------------------------------- clone

OpenCone* 
OpenCone::clone(void) const {
	return (new OpenCone (*this));
}

// ---------------------------------------------------------------- shadow hit

bool
OpenCone::shadow_hit(const Ray& ray, float& tmin) const
{
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;
	
	double h2r2 = h*h/(r*r);
	double a = h2r2 * dx * dx + h2r2 * dz * dz - dy * dy;
	double b = 2.0 * ( h2r2 * ox * dx - oy * dy + 2 * h * dy + h2r2 * oz * dz);
	double c = h2r2 * ox * ox - oy * oy + 2 * h * oy - h * h + h2r2 * oz * oz;
	double disc = b * b - 4.0 * a * c ;

			
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			if( t < tmin && yhit < h && yhit > 0 )
			{
				tmin = t;
				return (true);
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			if( t < tmin && yhit < h && yhit > 0 )
			{
				tmin = t;		// this is very important
				return (true);
			}
		} 
	}	
	return (false);	
}
																																											

// ---------------------------------------------------------------- assignment operator

OpenCone& 
OpenCone::operator= (const OpenCone& rhs) 		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);
	
	h 			= rhs.h;
	r 			= rhs.r;

	return (*this) ;
}


// ---------------------------------------------------------------- destructor

OpenCone::~OpenCone(void) {}


// ----------------------------------------------------------------------------- hit
// The code reverses the normal when the ray hits the inside surface, allows both
// sides to be shaded, but completely messes up transparency.

bool 															 
OpenCone::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
															
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;
	
	double h2r2 = h*h/(r*r);
	double a = h2r2 * dx * dx + h2r2 * dz * dz - dy * dy;
	double b = 2.0 * ( h2r2 * ox * dx - oy * dy + h * dy + h2r2 * oz * dz);
	double c = h2r2 * ox * ox - oy * oy + 2 * h * oy - h * h + h2r2 * oz * oz;
	double disc = b * b - 4.0 * a * c ;

	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			
			Point3D hitpoint = ray.o + t * ray.d;
			
			if( hitpoint.y > 0 && hitpoint.y < h )
			{
				tmin = t;
				sr.normal = Normal( 2 * h * hitpoint.x / r, - 2 * ( hitpoint.y - h), 2 * h * hitpoint.z / r);
				
				sr.normal.normalize();
				// test for hitting from inside
				if (-ray.d * sr.normal < 0.0)
					sr.normal = -sr.normal;
					
				sr.local_hit_point = ray.o + tmin * ray.d;
							
				return (true);
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {

			Point3D hitpoint = ray.o + t * ray.d;

			if( hitpoint.y > 0 && hitpoint.y < h )
			{
				tmin = t;
				sr.normal = Normal( 2 * h * hitpoint.x / r, - 2 * ( hitpoint.y - h), 2 * h * hitpoint.z / r);
				
				sr.normal.normalize();
				// test for hitting inside surface
				if (-ray.d * sr.normal < 0.0)
					sr.normal = -sr.normal;
					
				sr.local_hit_point = ray.o + tmin * ray.d;
	
				return (true);
			}
		} 
	}
	
	return (false);			
}



