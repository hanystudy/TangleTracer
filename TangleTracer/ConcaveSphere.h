// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the declaration of the class ConcaveSphere
// Notice that this class is not appeared in book or website, I cannot ensure its correctionm, but result image is OK.  

#pragma once

#include "GeometricObject.h"

//-------------------------------------------------------------------------------- class ConcaveSphere

class ConcaveSphere: public GeometricObject {	
								  	
	public:
		
		ConcaveSphere(void);   									// Default constructor
				
		ConcaveSphere(Point3D center, double r);					// Constructor 
					
		ConcaveSphere(const ConcaveSphere& ConcaveSphere); 						// Copy constructor
		
		virtual GeometricObject* 									// Virtual copy constructor
		clone(void) const;

		virtual												// Destructor
		~ConcaveSphere(void);   									

		ConcaveSphere& 											// assignment operator
		operator= (const ConcaveSphere& ConcaveSphere);				
																					
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
	private:
	
		Point3D 	center;   			// center coordinates as a point  
		double 		radius;				// the radius 
		
		static const double kEpsilon;   // for shadows and secondary rays

		bool shadows;
};



inline void
ConcaveSphere::set_center(const Point3D& c) {
	center = c;
}
		
inline void
ConcaveSphere::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}
		
inline void
ConcaveSphere::set_radius(const double r) {
	radius = r;
}

inline void
ConcaveSphere::set_shadows(bool b)
{
	this->shadows = b;
}