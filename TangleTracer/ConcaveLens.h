// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the declaration of the class ConcaveLens
// It consists of two concave part spheres and a convex part cylinder

// The parameters are:
//						radius 			
//						thickness
//						min_distance:   the minimum distance between the curved surfaces
//										at the center

// it's horizontal with the (x, z) plane through the center

#pragma once

#include "Compound.h"

//------------------------------------------------------------------------- class ConcaveLens

class ConcaveLens: public Compound {
	public:
		
		ConcaveLens(const double radius, const double _thickness, const double _min_distance);

		ConcaveLens(const ConcaveLens& cl); 					
		
		virtual ConcaveLens* 								
		clone(void) const;

		virtual ConcaveLens& 						
		operator= (const ConcaveLens& rhs);		
		
		virtual 								
		~ConcaveLens(void); 
		
		virtual BBox 
		get_bounding_box(void);
		
		virtual bool 																						 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
		
	private:
	
		float 		lens_radius; 
		float 		thickness; 
		float 		min_distance;
		BBox		bbox;
};
