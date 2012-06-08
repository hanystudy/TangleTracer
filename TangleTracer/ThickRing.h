// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Compound.h"

#include "Disk.h"

class ThickRing: public Compound {
	public:
		
		ThickRing(void);   									
		
		ThickRing(const double bottom, const double top, const double i_radius, const double o_radius);
		
		ThickRing(const ThickRing& cc);

		~ThickRing (void);   									

		ThickRing& 												
		operator= (const ThickRing& c);	

		virtual ThickRing* 										
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
		set_inner_wall_material(Material* material_ptr);	//19.29

		virtual void 
		set_outer_wall_material(Material* material_ptr);	//19.29

		virtual BBox 
		get_bounding_box(void);
		
	private:
	
		void 													
		delete_objects(void);								

		void												
		copy_objects(const vector<GeometricObject*>& rhs_objects);
		
		BBox		bbox;	// the bounding box
};