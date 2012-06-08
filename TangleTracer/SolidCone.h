// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// The SolidCone class is from excercise 24.36

#pragma once

#include "GeometricObject.h"
#include "OpenCone.h"
#include "Compound.h"
#include "Disk.h"
#include <math.h>

class SolidCone: public Compound {
	
	public:
		
		SolidCone(void);   									

		SolidCone(const double radius, const double height);

		SolidCone(const SolidCone& c); 					
		
		virtual SolidCone* 									
		clone (void) const;

		SolidCone& 											
		operator= (const SolidCone& rhs);		
		
		virtual 												
		~SolidCone(void);
						
		virtual bool
		hit(const Ray& ray, double& t, ShadeRec& sr) const;

		virtual bool
		shadow_hit(const Ray& ray, float& tmin) const;
		
		virtual void 
		set_material(Material* material_ptr);
		
		virtual BBox 
		get_bounding_box(void);

	protected:

		void 													
		delete_objects(void);								

		void												
		copy_objects(const vector<GeometricObject*>& rhs_objects);
		
		BBox		bbox;	// the bounding box
};
