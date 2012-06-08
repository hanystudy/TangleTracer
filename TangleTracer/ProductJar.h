// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// ProductJar here must normalize the height of hitpoint if the ray intersect with body, since it uses Cylinderical Mapping technique

#pragma once

#include "Compound.h"

#include "Disk.h"

class ProductJar: public Compound {
	public:
		
		ProductJar(void);   									
		
		ProductJar(const double bottom, const double top, const double radius);
		ProductJar(const double bottom, const double body_top, const double cap_top, const double body_radius, const double bottom_bevel_radius, const double top_bevel_radius, const double cap_bevel_radius);
		/*
		bottom
		body_top
		cap_top
		body_radius
		bottom_bevel_radius
		top_bevel_radius
		cap_bevel_radius
		product_jar_ptr->set_material(matte_ptr);
		product_jar_ptr->set_body_material(body_matte_ptr);		// renders vertical body surface red
		*/
		
		ProductJar(const ProductJar& cc);

		~ProductJar (void);   									

		ProductJar& 												
		operator= (const ProductJar& c);	

		virtual ProductJar* 										
		clone(void) const;

		virtual bool 															 
		hit(const Ray& ray, double& tmin, ShadeRec& s) const;
		
		virtual bool 																						 
		shadow_hit(const Ray& ray, float& tmin) const;

		virtual void 
		set_material(Material* material_ptr);

		virtual BBox 
		get_bounding_box(void);

		virtual void
		set_body_material(Material* material_ptr);	//29.26
		
	private:
	
		void 													
		delete_objects(void);								

		void												
		copy_objects(const vector<GeometricObject*>& rhs_objects);
		
		BBox		bbox;	// the bounding box

		double body_top;
		double body_bottom;
};