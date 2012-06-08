// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Maths.h"	// for SolveQuartic
#include "PartAnnulus.h"

// ---------------------------------------------------------------- default constructor

PartAnnulus::PartAnnulus (void)
	: 	GeometricObject(),
		center(0,0,0),
		normal(0,1,0),
		inner_radius(1),
		wall_thickness(1),
		bbox( -1, 1, - kEpsilon, kEpsilon, -1, 1),
		min_azimuth(0),
		max_azimuth(2*PI),
		i_squared(0),
		w_squared(4)
{}

// ---------------------------------------------------------------- constructor

PartAnnulus::PartAnnulus(Point3D c, Normal n, double i, double w, double mi, double ma)
	: 	GeometricObject(),
		center(c),
		normal(n),
		inner_radius(i),
		wall_thickness(w),
		min_azimuth(mi * PI_ON_180),
		max_azimuth(ma * PI_ON_180),
		bbox( center.x - i - w, center.x + i + w, center.y - kEpsilon, center.y + kEpsilon, center.z - i - w, center.z + i + w),
		i_squared(i*i),
		w_squared((i+w)*(i+w))
{}																			
																				
// ---------------------------------------------------------------- clone

PartAnnulus* 
PartAnnulus::clone(void) const {
	return (new PartAnnulus(*this));
}

// ---------------------------------------------------------------- copy constructor																																											

PartAnnulus::PartAnnulus (const PartAnnulus& torus) 
	: 	GeometricObject(torus),
	center(torus.center),
	normal(torus.normal),
	inner_radius(torus.inner_radius),
	wall_thickness(torus.wall_thickness),
	bbox( torus.bbox),
	i_squared(torus.i_squared),
	w_squared(torus.w_squared),
	min_azimuth(torus.min_azimuth),
	max_azimuth(torus.max_azimuth)
{}


// ---------------------------------------------------------------- assignment operator	

PartAnnulus& 
PartAnnulus::operator = (PartAnnulus& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);
				
	center = rhs.center;
	normal = rhs.normal;
	inner_radius = rhs.inner_radius;
	wall_thickness = rhs.wall_thickness;
	bbox = rhs.bbox;			

	i_squared = rhs.i_squared;
	w_squared = rhs.w_squared;
	
	min_azimuth = rhs.min_azimuth;
	max_azimuth = rhs.max_azimuth;

	return (*this);
}


//------------------------------------------------------------------- destructor 	

PartAnnulus::~PartAnnulus(void) {}


//------------------------------------------------------------------ FindNormal
// Find the normal vector at the specified position
// This works because the torus is defined by a single implicit equation 

Normal
PartAnnulus::compute_normal(const Point3D& p) const {
	return (normal);	
}


//---------------------------------------------------------------- hit 
	
bool 																 
PartAnnulus::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (!bbox.hit(ray))
		return (false);
		
	double t = (center - ray.o) * normal / (ray.d * normal);
		
	if (t <= kEpsilon)
		return (false);
		
	Point3D p = ray.o + t * ray.d;
		
	double v = center.d_squared(p);

	if ( v < w_squared && v > i_squared ) {

		double phi = atan2(p.x, p.z);
		if (phi < 0.0)
			phi += TWO_PI;

		if( phi <= max_azimuth && phi >= min_azimuth )
		{
			tmin 				= t;
			sr.normal 			= normal;
			sr.local_hit_point	= p;
			return (true);	
		}
		else
			return false;
	}
	else
		return (false);
}

// ---------------------------------------------------------- shadow hit

bool 																						 
PartAnnulus::shadow_hit(const Ray& ray, float& tmin) const
{
	if (!bbox.hit(ray))
		return (false);
				
	double t = (center - ray.o) * normal / (ray.d * normal);
		
	if (t <= kEpsilon)
		return (false);
		
	Point3D p = ray.o + t * ray.d;
		
	double v = center.d_squared(p);

	if ( v < w_squared && v > i_squared ) {

		double phi = atan2(p.x, p.z);
		if (phi < 0.0)
			phi += TWO_PI;

		if( phi <= max_azimuth && phi >= min_azimuth )
		{
			tmin 				= t;
			return true;
		}
		else
			return false;
	}
	else
		return (false);
}