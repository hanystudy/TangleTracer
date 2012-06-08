// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

// This file contains the declaration of the class Sphere

#include "GeometricObject.h"
#include "Sampler.h"

//-------------------------------------------------------------------------------- class Sphere

class Sphere: public GeometricObject {	
								  	
	public:
		
		Sphere(void);   									// Default constructor
				
		Sphere(Point3D center, double r);					// Constructor 
					
		Sphere(const Sphere& sphere); 						// Copy constructor
		
		virtual GeometricObject* 									// Virtual copy constructor
		clone(void) const;

		virtual												// Destructor
		~Sphere(void);   									

		Sphere& 											// assignment operator
		operator= (const Sphere& sphere);				
																					
		void
		set_center(const Point3D& c);
		
		void
		set_center(const double x, const double y, const double z);
		
		void
		set_radius(const double r);
						
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const;	

		bool shadow_hit(const Ray& ray, float& tmin) const;

		void set_shadows(bool);

		void 
		set_sampler(Sampler* sp);

		virtual void									
		compute_uvw(void);

		virtual Point3D 		
		sample(void);

		virtual float
		pdf(ShadeRec& sr);

		virtual Normal
		get_normal(const Point3D&);

		virtual BBox 
		get_bounding_box(void);

		virtual void
		set_bounding_box(void);
		
	private:
	
		Point3D 	center;   			// center coordinates as a point  
		double 		radius;				// the radius 
		
		static const double kEpsilon;   // for shadows and secondary rays

		bool shadows;

		Sampler *sampler_ptr;
		int num_samples;
		double inv_area;
		Vector3D u,v,w;

		BBox boundingbox;
};



inline void
Sphere::set_center(const Point3D& c) {
	center = c;
}
		
inline void
Sphere::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}
		
inline void
Sphere::set_radius(const double r) {
	radius = r;
}

inline void
Sphere::set_bounding_box(void)
{
	boundingbox.x0 = center.x - radius;
	boundingbox.x1 = center.x + radius;
	boundingbox.y0 = center.y - radius;
	boundingbox.y1 = center.y + radius;
	boundingbox.z0 = center.z - radius;
	boundingbox.z1 = center.z + radius;
}