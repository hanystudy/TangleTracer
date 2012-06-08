// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Maths.h"	// for SolveQuartic
#include "ConvexPartTorus.h"

// ---------------------------------------------------------------- default constructor

ConvexPartTorus::ConvexPartTorus (void)
	: 	GeometricObject(),
		a(2.0),
		b(0.5),
		min_azimuth(0),
		max_azimuth(TWO_PI),
		min_polar(0),
		max_polar(TWO_PI),
		bbox(-a - b, a + b, -b, b, -a - b, a + b) 			
{}

// ---------------------------------------------------------------- constructor

ConvexPartTorus::ConvexPartTorus (const double _a, const double _b, const double _min_azimuth, const double _max_azimuth, const double _min_polar, const double _max_polar)
	: 	GeometricObject(),
		a(_a),
		b(_b),
		bbox(-a - b, a + b, -b, b, -a - b, a + b),
		min_azimuth(_min_azimuth*PI_ON_180),
		max_azimuth(_max_azimuth*PI_ON_180),
		min_polar(_min_polar*PI_ON_180),
		max_polar(_max_polar*PI_ON_180)
{}																			
																				
// ---------------------------------------------------------------- clone

ConvexPartTorus* 
ConvexPartTorus::clone(void) const {
	return (new ConvexPartTorus(*this));
}																				
																				

// ---------------------------------------------------------------- copy constructor																																											

ConvexPartTorus::ConvexPartTorus (const ConvexPartTorus& torus) 
	: 	GeometricObject(torus),
		a(torus.a),
		b(torus.b),
		bbox(torus.bbox),
		min_azimuth(torus.min_azimuth),
		max_azimuth(torus.max_azimuth),
		min_polar(torus.min_polar),
		max_polar(torus.max_polar)	 				
{}


// ---------------------------------------------------------------- assignment operator	

ConvexPartTorus& 
ConvexPartTorus::operator = (ConvexPartTorus& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);
				
	a		= rhs.a;
	b 		= rhs.b;
	bbox	= rhs.bbox;

	min_azimuth = rhs.min_azimuth;
	max_azimuth = rhs.max_azimuth;
	min_polar = rhs.min_polar;
	max_polar = rhs.max_polar;	
	
	return (*this);
}


//------------------------------------------------------------------- destructor 	

ConvexPartTorus::~ConvexPartTorus(void) {}


//------------------------------------------------------------------ FindNormal
// Find the normal vector at the specified position
// This works because the torus is defined by a single implicit equation 

Normal
ConvexPartTorus::compute_normal(const Point3D& p) const {
	Normal normal;
	double param_squared = a * a + b * b;

	double x = p.x;
	double y = p.y;
	double z = p.z;
	double sum_squared = x * x + y * y + z * z;
	
	normal.x = 4.0 * x * (sum_squared - param_squared);
	normal.y = 4.0 * y * (sum_squared - param_squared + 2.0 * a * a);
	normal.z = 4.0 * z * (sum_squared - param_squared);
	normal.normalize();
	
	return (normal);	
}


//---------------------------------------------------------------- hit 
	
bool 																 
ConvexPartTorus::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (!bbox.hit(ray))
		return (false);
		
	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;	
	
	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation
	
	// define the coefficients of the quartic equation
	
	double sum_d_sqrd 	= d1 * d1 + d2 * d2 + d3 * d3;
	double e			= x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f			= x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd	= 4.0 * a * a;
	
	coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1); 	// constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  					// coefficient of t^4
	
	// find roots of the quartic equation
	
	int num_real_roots = SolveQuartic(coeffs, roots);
	
	bool	intersected = false;
	double 	t 		 	= kHugeValue;
	
	if (num_real_roots == 0)  // ray misses the torus
		return(false);
	
	// find the smallest root greater than kEpsilon, if any
	// the roots array must be sorted in part torus
			
	for (int j = 0; j < num_real_roots; j++)
	{
		t = roots[j];
		if (roots[j] > kEpsilon) {
			intersected = true;
		}
		for( int k = j; k < num_real_roots; ++k)
		{
			if( roots[k] < t)
			{
				roots[j] = roots[k];
				roots[k] = t;
				t = roots[k];
			}
		}
		/*if (roots[j] < t)
				t = roots[j];*/
	}
		
	//if (roots[j] > kEpsilon) {		
	if(!intersected)
		return (false);

	for(int j = 0; j < num_real_roots; ++j)
	{
		if (roots[j] > kEpsilon )
		{
			t = roots[j];
			Point3D hit = ray.o + t * ray.d;
			double phi = atan2(hit.x, hit.z);
					if (phi < 0.0)
						phi += TWO_PI;

			if(phi >= min_azimuth && phi <= max_azimuth)
			{
				Point3D point(a * cos(-phi+PI/2),0,a * sin(-phi+PI/2));

				Vector3D dir = hit - point;
				dir.normalize();

				if( hit.y <= b * cos(min_polar) && hit.y >= b * cos(max_polar) )
				{
					tmin 			 	= t;
					sr.local_hit_point 	= ray.o + t * ray.d;
					/*if(hit.distance(Point3D(0,0,0)) > a)
					{
						sr.normal 		 	= compute_normal(sr.local_hit_point);
					}
					else
					{
						sr.normal 		 	= -compute_normal(sr.local_hit_point);
					}*/
					sr.normal 		 	= compute_normal(sr.local_hit_point);
				}
				return (true);
			}
		}
	}
	/*
	Point3D hit = ray.o + t * ray.d;
	double phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
				phi += TWO_PI;

	if(phi >= min_azimuth && phi <= max_azimuth)
	{
		Point3D point(a * cos(-phi+PI/2),0,a * sin(-phi+PI/2));

		Vector3D dir = hit - point;
		dir.normalize();

		hit.y = 0;

		double angle = acos(dir * Vector3D(0,1,0));

		if(hit.distance(Point3D(0,0,0)) > a && angle < min_polar )
		{
			if( angle >= min_polar && angle <= max_polar )
			{
				
			}
		}
		else
		{
			
		}

		tmin 			 	= t;
		sr.local_hit_point 	= ray.o + t * ray.d;
		sr.normal 		 	= compute_normal(sr.local_hit_point);
		
		return (true);
	}*/

	return false;
}

// ---------------------------------------------------------- shadow hit

bool 																						 
ConvexPartTorus::shadow_hit(const Ray& ray, float& tmin) const
{
	/*
	if (!bbox.hit(ray))
		return (false);
		
	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;	
	
	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation
	
	// define the coefficients of the quartic equation
	
	double sum_d_sqrd 	= d1 * d1 + d2 * d2 + d3 * d3;
	double e			= x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f			= x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd	= 4.0 * a * a;
	
	coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1); 	// constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  					// coefficient of t^4
	
	// find roots of the quartic equation
	
	int num_real_roots = SolveQuartic(coeffs, roots);
	
	bool	intersected = false;
	double 	t 		 	= kHugeValue;
	
	if (num_real_roots == 0)  // ray misses the torus
		return(false);
	
	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted
			
	for (int j = 0; j < num_real_roots; j++)  
		if (roots[j] > kEpsilon) {
			intersected = true;
			if (roots[j] < t)
				t = roots[j];
		}
		
	if(!intersected)
		return (false);
		
	tmin 			 	= t;
	return (true);
	*/

	if (!bbox.hit(ray))
		return (false);
		
	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;	
	
	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation
	
	// define the coefficients of the quartic equation
	
	double sum_d_sqrd 	= d1 * d1 + d2 * d2 + d3 * d3;
	double e			= x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f			= x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd	= 4.0 * a * a;
	
	coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1); 	// constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  					// coefficient of t^4
	
	// find roots of the quartic equation
	
	int num_real_roots = SolveQuartic(coeffs, roots);
	
	bool	intersected = false;
	double 	t 		 	= kHugeValue;
	
	if (num_real_roots == 0)  // ray misses the torus
		return(false);
	
	// find the smallest root greater than kEpsilon, if any
	// the roots array must be sorted in part torus
			
	for (int j = 0; j < num_real_roots; j++)
	{
		t = roots[j];
		if (roots[j] > kEpsilon) {
			intersected = true;
		}
		for( int k = j; k < num_real_roots; ++k)
		{
			if( roots[k] < t)
			{
				roots[j] = roots[k];
				roots[k] = t;
				t = roots[k];
			}
		}
		/*if (roots[j] < t)
				t = roots[j];*/
	}
		
	//if (roots[j] > kEpsilon) {		
	if(!intersected)
		return (false);

	for(int j = 0; j < num_real_roots; ++j)
	{
		if (roots[j] > kEpsilon )
		{
			t = roots[j];
			Point3D hit = ray.o + t * ray.d;
			double phi = atan2(hit.x, hit.z);
					if (phi < 0.0)
						phi += TWO_PI;

			if(phi >= min_azimuth && phi <= max_azimuth)
			{
				Point3D point(a * cos(-phi+PI/2),0,a * sin(-phi+PI/2));

				Vector3D dir = hit - point;
				dir.normalize();

				if( hit.y <= b * cos(min_polar) && hit.y >= b * cos(max_polar) )
				{
					tmin 			 	= t;
					return (true);
				}
			}
		}
	}
	return false;
}