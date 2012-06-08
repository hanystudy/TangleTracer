// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// Notice that I have implemented my own BeveledWedge class back of this file, but the original code is still given, you can see the difference between these two samples

#pragma once

#include "Compound.h"

//-------------------------------------------------------------------------------- class BeveledWedge

class BeveledWedge: public Compound {
	public:
	
		BeveledWedge(	const double y0,		// minimum y value
						const double y1,		// minimum y value
						const double r0,		// inner radius
						const double r1,		// outer radius
						const double rb,		// bevel radius
						const double phi0,		// minimum azimuth angle in degrees
						const double phi1);		// maximum azimuth angle
		
							
		BeveledWedge(const BeveledWedge& bw); 				
		
		virtual BeveledWedge* 								
		clone(void) const;

		virtual BeveledWedge& 								
		operator= (const BeveledWedge& rhs);		
		
		virtual 											
		~BeveledWedge(void); 
		
		virtual BBox 
		get_bounding_box(void);
		
		virtual bool 																						 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
				
	private:
	
		double 	y0;		// minimum y value
		double 	y1;		// minimum y value
		double 	r0; 	// inner radius
		double 	r1;		// outer radius
		double 	rb;		// bevel radius
		double 	phi0;	// maximum azimuth angle
		double 	phi1;	// minimum azimuth angle

		BBox	bbox;	// bounding box
};

/*
class BeveledWedge: public Compound {
	public:
		
		BeveledWedge(void);   									
		
		//BeveledWedge(const double bottom, const double top, const double i_radius, const double o_radius, const double b_radius);
		BeveledWedge(const double bottom, const double top, const double i_radius, const double o_radius, const double b_radius, const double min_azimuth, const double max_azimuth);

		BeveledWedge(const BeveledWedge& cc);

		~BeveledWedge (void);   									

		BeveledWedge& 												
		operator= (const BeveledWedge& c);	

		virtual BeveledWedge* 										
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
*/