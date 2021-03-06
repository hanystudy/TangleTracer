// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// Notice that I have implemented my own Roseete class back of this file, but the original code is still given, you can see the difference between these two samples

#pragma once

#include "Grid.h"

//-------------------------------------------------------------------------------- class AnotherRosette

class AnotherRosette: public Grid {
	public:
		
		AnotherRosette(void);   							
				
		AnotherRosette(	const int 		_num_rings, 
					const double	_hole_radius,
					const double 	_ring_width,
					const double 	_rb,
					const double 	_y0,
					const double 	_y1);	
						
		AnotherRosette(const AnotherRosette& bb); 				
		
		virtual AnotherRosette* 								
		clone(void) const;

		AnotherRosette& 								
		operator= (const AnotherRosette& rhs);		
		
		virtual 											
		~AnotherRosette(void);
		
		void
		construct_rosette(void); 
		
	private:
	
		double		num_rings;		// maximum of 6
		double		hole_radius;
		double		ring_width;
		double		rb;				// bevel radius
		double		y0, y1;			// y axis extents
		
		static const int num_wedges[6];  // number of wedges in each ring
};
/*
#include "Grid.h"

class AnotherRosette: public Grid {
	public:
		
		AnotherRosette(void);   					
		
		//AnotherRosette(const double bottom, const double top, const double radius);
		//AnotherRosette(const double bottom, const double body_top, const double cap_top, const double body_radius, const double bottom_bevel_radius, const double top_bevel_radius, const double cap_bevel_radius);
		
		AnotherRosette(int num_rings, const float hole_r, const float ring_w, const float rb, const float y0, const float y1);

		AnotherRosette(const AnotherRosette& cc);

		~AnotherRosette (void);   									

		AnotherRosette& 												
		operator= (const AnotherRosette& c);	

		virtual AnotherRosette* 										
		clone(void) const;

		virtual void
		store_material(Material* material_ptr,int no);	//21.11a
		
	private:
	
		void 													
		delete_objects(void);								

		void												
		copy_objects(const vector<GeometricObject*>& rhs_objects);
};
*/