// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Maths.h"	// for SolveQuartic
#include "Annulus.h"

// ---------------------------------------------------------------- default constructor

Annulus::Annulus (void)
	: 	GeometricObject(),
		center(0,0,0),
		normal(0,1,0),
		inner_radius(1),
		wall_thickness(1),
		bbox( -1, 1, - kEpsilon, kEpsilon, -1, 1),
		i_squared(0),
		w_squared(4)
{}

// ---------------------------------------------------------------- constructor

Annulus::Annulus (Point3D c, Normal n, double i, double w)
	: 	GeometricObject(),
		center(c),
		normal(n),
		inner_radius(i),
		wall_thickness(w),
		bbox( center.x - i - w, center.x + i + w, center.y - kEpsilon, center.y + kEpsilon, center.z - i - w, center.z + i + w),
		i_squared(i*i),
		w_squared((i+w)*(i+w))
{}																			
																				
// ---------------------------------------------------------------- clone

Annulus* 
Annulus::clone(void) const {
	return (new Annulus(*this));
}																				
																				

// ---------------------------------------------------------------- copy constructor																																											

Annulus::Annulus (const Annulus& torus) 
	: 	GeometricObject(torus),
	center(torus.center),
	normal(torus.normal),
	inner_radius(torus.inner_radius),
	wall_thickness(torus.wall_thickness),
	bbox( torus.bbox),
	i_squared(torus.i_squared),
	w_squared(torus.w_squared)
{}


// ---------------------------------------------------------------- assignment operator	

Annulus& 
Annulus::operator = (Annulus& rhs) {
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
	
	return (*this);
}


//------------------------------------------------------------------- destructor 	

Annulus::~Annulus(void) {}


//------------------------------------------------------------------ FindNormal
// Find the normal vector at the specified position
// This works because the torus is defined by a single implicit equation 

Normal
Annulus::compute_normal(const Point3D& p) const {
	return (normal);	
}


//---------------------------------------------------------------- hit 
	
bool 																 
Annulus::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (!bbox.hit(ray))
		return (false);
		
	double t = (center - ray.o) * normal / (ray.d * normal);
		
	if (t <= kEpsilon)
		return (false);
		
	Point3D p = ray.o + t * ray.d;
		
	double v = center.d_squared(p);

	if ( v < w_squared && v > i_squared ) {
		tmin 				= t;
		sr.normal 			= normal;
		sr.local_hit_point	= p;
		return (true);	
	}
	else
		return (false);
}

// ---------------------------------------------------------- shadow hit

bool 																						 
Annulus::shadow_hit(const Ray& ray, float& tmin) const
{
	if (!bbox.hit(ray))
		return (false);
				
	double t = (center - ray.o) * normal / (ray.d * normal);
		
	if (t <= kEpsilon)
		return (false);
		
	Point3D p = ray.o + t * ray.d;
		
	double v = center.d_squared(p);

	if ( v < w_squared && v > i_squared ) {
		tmin 				= t;
		return (true);	
	}
	else
		return (false);
}