// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Disk.h"

const double Disk::kEpsilon = 0.001;

// ----------------------------------------------------------------------  default constructor

Disk::Disk(void)	
	: 	GeometricObject(),
		center(0.0),
		normal(0, 1, 0),
		r(1),
		r_squared(1),
		sampler_ptr(NULL),
		shadows(false),
		area(1),
		inv_area(1)
{}


// ----------------------------------------------------------------------  constructor

Disk::Disk(const Point3D& point, const Normal& normal, const double ra)
	:	GeometricObject(),
		center(point),
		normal(normal),
		r(ra),
		r_squared(ra*ra),
		sampler_ptr(NULL),
		shadows(false),
		area(0.5*PI*r_squared),
		inv_area(1.0 / area)
{
	this->normal.normalize();
}


// ---------------------------------------------------------------- copy constructor

Disk::Disk(const Disk& Disk) 
	:	GeometricObject(Disk),
		center(Disk.center),
		normal(Disk.normal),
		r(Disk.r),
		r_squared(Disk.r_squared),
		sampler_ptr(Disk.sampler_ptr),
		shadows(Disk.shadows),
		area(Disk.area),
		inv_area(Disk.inv_area)
{}


// ---------------------------------------------------------------- clone

GeometricObject* 
Disk::clone(void) const {
	return (new Disk(*this));
}


// ---------------------------------------------------------------- assignment operator

Disk& 
Disk::operator= (const Disk& rhs)	{
	
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center = rhs.center;
	normal  = rhs.normal;
	r = rhs.r;
	r_squared = rhs.r_squared;
	sampler_ptr = rhs.sampler_ptr,
	shadows = rhs.shadows;

	area = rhs.area,
	inv_area = rhs.inv_area;
	return (*this);
}


// ---------------------------------------------------------------- destructor

Disk::~Disk(void)				
{}


// ----------------------------------------------------------------- hit

bool 															 
Disk::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
		
	double t = (center - ray.o) * normal / (ray.d * normal);
		
	if (t <= kEpsilon)
		return (false);
		
	Point3D p = ray.o + t * ray.d;
		
	if (center.d_squared(p) < r_squared) {
		tmin 				= t;
		sr.normal 			= normal;
		sr.local_hit_point	= p; 
		return (true);	
	}
	else
		return (false);
}


bool 												
Disk::shadow_hit(const Ray& ray, float& tmin) const {	
	double t = (center - ray.o) * normal / (ray.d * normal);
		
	if (t <= kEpsilon)
		return (false);
		
	Point3D p = ray.o + t * ray.d;
		
	if (center.d_squared(p) < r_squared) {
		tmin = t;
		return (true);	
	}
	else
		return (false);
}

void								
Disk::set_sampler(Sampler* sp)
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	sampler_ptr = sp;
	sampler_ptr->map_samples_to_unit_disk();
}
		
void									
Disk::set_shadows(bool b)
{
	shadows = b;
}

void									
Disk::compute_uvw(void)
{
	w = normal;
	u = Vector3D(1000,1000,0);
	
	u.z = center * normal - u.x * normal.x - u.y * normal.y;//( -(u.x - center.x)*normal.x - (u.y - center.y)*normal.y ) / normal.z + center.z;		//generate a artificial basis
 	u = u - center;
	u.normalize();

	v = w ^ u;

	v.normalize();
	/*
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
	*/
}

Point3D 		
Disk::sample(void)
{
	Point2D sample_point = sampler_ptr->sample_unit_disk();
	return (this->center + sample_point.x * this->u + sample_point.y * this->v);
}
		
float
Disk::pdf(ShadeRec& sr)
{
	return this->inv_area;
}
		
Normal
Disk::get_normal(void) const
{
	return normal;
}

Normal
Disk::get_normal(const Point3D&)
{
	return normal;
}