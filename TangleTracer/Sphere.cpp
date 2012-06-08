// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the definition of the class sphere

#include "Sphere.h"
#include "math.h"

const double Sphere::kEpsilon = 0.001;
					
// ---------------------------------------------------------------- default constructor

Sphere::Sphere(void)	
	: 	GeometricObject(),
		center(0.0),
		radius(1.0),
		shadows(true),
		sampler_ptr(NULL),
		num_samples(0),
		inv_area(0.25*invPI),
		boundingbox(-1,1,-1,1,-1,1)
{
}


// ---------------------------------------------------------------- constructor

Sphere::Sphere(Point3D c, double r)
	: 	GeometricObject(),
		center(c),
		radius(r),
		shadows(true),
		sampler_ptr(NULL),
		num_samples(0),
		inv_area(0.25*invPI/(r*r)),
		boundingbox(-c.x - r,c.x + r,c.y -r,c.y + r,c.z -r,c.z + r)
{}


// ---------------------------------------------------------------- clone

GeometricObject* 
Sphere::clone(void) const {
	return (new Sphere(*this));
}


// ---------------------------------------------------------------- copy constructor

Sphere::Sphere (const Sphere& sphere)
	: 	GeometricObject(sphere),
		center(sphere.center),
		radius(sphere.radius),
		shadows(sphere.shadows),
		sampler_ptr(sphere.sampler_ptr),
		num_samples(sphere.num_samples),
		inv_area(sphere.inv_area),
		boundingbox(sphere.boundingbox)
{}



// ---------------------------------------------------------------- assignment operator

Sphere& 
Sphere::operator= (const Sphere& rhs)		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;
	shadows = rhs.shadows;
	sampler_ptr = rhs.sampler_ptr;
	num_samples = rhs.num_samples;
	inv_area = rhs.inv_area;
	boundingbox = rhs.boundingbox;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Sphere::~Sphere(void) {}


//---------------------------------------------------------------- hit

bool
Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
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
			sr.normal 	 = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	
		t = (-b + e) / denom;    // larger root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	}
	
	return (false);
}

bool 												
Sphere::shadow_hit(const Ray& ray, float& tmin) const {	
	
	if(!shadows)
		return false;

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
			return (true);
		} 
	
		t = (-b + e) / denom;    // larger root
	
		if (t > kEpsilon) {
			tmin = t;
			return (true);
		}
	}
	
	return (false);
}

void 
Sphere::set_shadows(bool s)
{
	shadows = s;
}


void 
Sphere::set_sampler(Sampler* sp)
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
		
	num_samples = sp->get_num_samples();
	sampler_ptr = sp;
	sampler_ptr->map_samples_to_sphere();
}

void									
Sphere::compute_uvw(void)
{
	return;
}

Point3D 		
Sphere::sample(void)
{
	Point3D s = sampler_ptr->sample_sphere();
	return (s + center);
}
		
float
Sphere::pdf(ShadeRec& sr)
{
	return this->inv_area;
}

Normal
Sphere::get_normal(const Point3D& hit)
{
	Normal normal = hit - center;
	normal.normalize();
	return normal;
}

BBox 
Sphere::get_bounding_box(void)
{
	return boundingbox;
}