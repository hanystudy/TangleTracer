// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the declaration of the class Orthographic
// This class seems only to appear in building 4.04, but its implementation is too easy

#pragma once

#include "Point2D.h"
#include "World.h"    // we can #include "World.h" here

//--------------------------------------------------------------------- class Orthographic

class Orthographic: public Camera {
	public:
	
		Orthographic();   							

		Orthographic(const Orthographic& ph);	
		
		virtual Camera*						
		clone(void) const;			

		Orthographic& 							
		operator= (const Orthographic& rhs);	
		
		virtual
		~Orthographic();   						
			
		void
		set_view_distance(const float vpd);
		
		void
		set_zoom(const float zoom_factor);
		
		Vector3D								
		get_direction(const Point2D& p) const;
		
		virtual void 												
		render_scene(World& w);
		
		void
		render_stereo(World& w, float x, int pixel_offset);
	private:
			
		float	d;		// view plane distance
		float	zoom;	// zoom factor
		
};




//-------------------------------------------------------------------------- set_vpd

inline void
Orthographic::set_view_distance(float _d) {
	d = _d;
}	
	


//-------------------------------------------------------------------------- set_zoom

inline void
Orthographic::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}	
