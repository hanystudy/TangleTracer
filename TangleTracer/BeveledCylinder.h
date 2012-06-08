// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Compound.h"

#include "Disk.h"

class BeveledCylinder: public Compound {
	public:
		
		BeveledCylinder(void);   									
		
		BeveledCylinder(const double	bottom_,
						const double 	top_, 
						const double 	radius, 
						const double	bevel_radius);
		
		BeveledCylinder(const BeveledCylinder& cc);

		~BeveledCylinder (void);   									

		BeveledCylinder& 												
		operator= (const BeveledCylinder& c);	

		virtual BeveledCylinder* 										
		clone(void) const;

		virtual bool 															 
		hit(const Ray& ray, double& tmin, ShadeRec& s) const;
		
		virtual bool 																						 
		shadow_hit(const Ray& ray, float& tmin) const;

		virtual void 
		set_material(Material* material_ptr);

		virtual void 
		set_bottom_material(Material* material_ptr);	//19.29

		virtual void 
		set_top_material(Material* material_ptr);	//19.29

		virtual void 
		set_wall_material(Material* material_ptr);	//19.29
		
	private:
	
		void 													
		delete_objects(void);								

		void												
		copy_objects(const vector<GeometricObject*>& rhs_objects);
		
		BBox		bbox;	// the bounding box

		double bottom;
		double top;
		double r;
		double br;
};