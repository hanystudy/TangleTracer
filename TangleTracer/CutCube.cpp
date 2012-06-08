// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "CutCube.h"
#include "Constants.h"

const double CutCube::kEpsilon = 0.001;


// --------------------------------------------------------------------- default constructor

CutCube::CutCube (void)
	: p0(-1), p1(1), sphere(new ConcavePartSphere(p1,1,180,270,90,180)),sp(new Sphere(p1,1))
{
	
}	

// --------------------------------------------------------------------- constructor

CutCube::CutCube (const Point3D a, const Point3D b, const double radius)
{
	p0 = a;
	p1 = b;
	sphere = new ConcavePartSphere(p1,radius,180,270,90,180);
	sp = new Sphere(p1,radius);
}

// --------------------------------------------------------------------- copy constructor

CutCube::CutCube (const CutCube& CutCube)
	: p0(CutCube.p0), p1(CutCube.p1), sphere(CutCube.sphere), sp(CutCube.sp)
{}						
				

// --------------------------------------------------------------------- assignment operator

CutCube&
CutCube::operator= (const CutCube& rhs) {
	if (this == &rhs)
		return (*this);

	p0	= rhs.p0;
	p1	= rhs.p1;
	sphere	= rhs.sphere;
	sp = rhs.sp;
	return (*this);
}			


// --------------------------------------------------------------------- destructor

CutCube::~CutCube (void) {}	

// ---------------------------------------------------------------- clone

CutCube* 
CutCube::clone(void) const {
	return (new CutCube(*this));
}

// --------------------------------------------------------------------- hit

bool 									
CutCube::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
	double ox = ray.o.x; double oy = ray.o.y; double oz = ray.o.z;
	double dx = ray.d.x; double dy = ray.d.y; double dz = ray.d.z;
	
	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max; 

	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (p0.x - ox) * a;
		tx_max = (p1.x - ox) * a;
	}
	else {
		tx_min = (p1.x - ox) * a;
		tx_max = (p0.x - ox) * a;
	}
	
	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (p0.y - oy) * b;
		ty_max = (p1.y - oy) * b;
	}
	else {
		ty_min = (p1.y - oy) * b;
		ty_max = (p0.y - oy) * b;
	}
	
	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (p0.z - oz) * c;
		tz_max = (p1.z - oz) * c;
	}
	else {
		tz_min = (p1.z - oz) * c;
		tz_max = (p0.z - oz) * c;
	}
	
	double t0, t1;
	
	// this is the same as Listing 19.1 down to the statement float t0, t1;

	int face_in, face_out;

	// find largest entering t value

	if (tx_min > ty_min) {
		t0 = tx_min;
		face_in = (a >= 0.0) ? 0 : 3;
	}
	else {
		t0 = ty_min;
		face_in = (b >= 0.0) ? 1 : 4;
	}

	if (tz_min > t0) {
		t0 = tz_min;
		face_in = (c >= 0.0) ? 2 : 5;
	}

	// find smallest exiting t value

	if (tx_max < ty_max) {
		t1 = tx_max;
		face_out = (a >= 0.0) ? 3 : 0;
	}
	else {
		t1 = ty_max;
		face_out = (b >= 0.0) ? 4 : 1;
	}

	if (tz_max < t1) {
		t1 = tz_max;
		face_out = (c >= 0.0) ? 5 : 2;
	}
	double tm = 0;
	ShadeRec srr = sr;
	bool hitsp = false;
	if (t0 < t1 && t1 > kEpsilon) 
	{  
		// condition for a hit
		if (t0 > kEpsilon) 
		{
			tmin = t0;  			// ray hits outside surface
			if( (hitsp = sphere->hit(ray, tm, srr)) && tm < tmin)
			{
				tmin = tm;
				sr.local_hit_point = srr.local_hit_point;
				sr.normal = srr.normal;
			}
			else
			{
				if( !sp->hit(ray, tm, srr) || !hitsp )
				{
					sr.normal = get_normal(face_in);
				}
				else
					return false;
			}
		}
		else 
		{
			tmin = t1;				// ray hits inside surface
			sr.normal = get_normal(face_out);
		}

		sr.local_hit_point = ray.o + tmin * ray.d;
		return (true);
	}
	else
		return (false);
}

// ---------------------------------------------------------- shadow hit

bool CutCube::shadow_hit(const Ray& ray, float& tmin) const
{
	double ox = ray.o.x; double oy = ray.o.y; double oz = ray.o.z;
	double dx = ray.d.x; double dy = ray.d.y; double dz = ray.d.z;
	
	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max; 

	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (p0.x - ox) * a;
		tx_max = (p1.x - ox) * a;
	}
	else {
		tx_min = (p1.x - ox) * a;
		tx_max = (p0.x - ox) * a;
	}
	
	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (p0.y - oy) * b;
		ty_max = (p1.y - oy) * b;
	}
	else {
		ty_min = (p1.y - oy) * b;
		ty_max = (p0.y - oy) * b;
	}
	
	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (p0.z - oz) * c;
		tz_max = (p1.z - oz) * c;
	}
	else {
		tz_min = (p1.z - oz) * c;
		tz_max = (p0.z - oz) * c;
	}
	
	double t0, t1;
	
	// this is the same as Listing 19.1 down to the statement float t0, t1;

	int face_in, face_out;

	// find largest entering t value

	if (tx_min > ty_min) {
		t0 = tx_min;
		face_in = (a >= 0.0) ? 0 : 3;
	}
	else {
		t0 = ty_min;
		face_in = (b >= 0.0) ? 1 : 4;
	}

	if (tz_min > t0) {
		t0 = tz_min;
		face_in = (c >= 0.0) ? 2 : 5;
	}

	// find smallest exiting t value

	if (tx_max < ty_max) {
		t1 = tx_max;
		face_out = (a >= 0.0) ? 3 : 0;
	}
	else {
		t1 = ty_max;
		face_out = (b >= 0.0) ? 4 : 1;
	}

	if (tz_max < t1) {
		t1 = tz_max;
		face_out = (c >= 0.0) ? 5 : 2;
	}
	float tm = 0;
	bool hitsp = false;
	if (t0 < t1 && t1 > kEpsilon) 
	{  
		// condition for a hit
		if (t0 > kEpsilon) 
		{
			tmin = t0;  			// ray hits outside surface
			if( ( hitsp = sphere->shadow_hit(ray, tm) ) && tm < tmin)
			{
				tmin = tm;
			}
			else
			{
				if( sp->shadow_hit(ray, tm)  || !hitsp )
				{
					return false;
				}
			}
		}
		else 
		{
			tmin = t1;				// ray hits inside surface
		}
		return (true);
	}
	else
		return (false);
}

// ---------------------------------------------------------- get_normal

Normal	
CutCube::get_normal(const int face_hit) const {
	switch (face_hit) {
		case 0:	return (Normal(-1, 0, 0));	// -x face
		case 1:	return (Normal(0, -1, 0));	// -y face
		case 2:	return (Normal(0, 0, -1));	// -z face
		case 3:	return (Normal(1, 0, 0));	// +x face
		case 4:	return (Normal(0, 1, 0));	// +y face
		case 5:	return (Normal(0, 0, 1));	// +z face
	}
}

BBox
CutCube::get_bounding_box(void)	//BCutCube needed here because CutCube has been used in Grid 
{
	return BBox(p0.x, p1.x, p0.y, p1.y, p0.z, p1.z);
}
