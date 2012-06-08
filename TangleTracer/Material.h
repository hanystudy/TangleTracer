// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "World.h"			// required for the shade function in all derived classes
#include "RGBColor.h"
#include "ShadeRec.h"

class Material {	
	public:
	
		Material(void);						
		
		Material(const Material& material); 
		
		virtual Material*								
		clone(void) const = 0;	
				
		virtual 								
		~Material(void);
				
		virtual RGBColor
		shade(ShadeRec& sr);	

		virtual void									
		set_ce(const float r, const float g, const float b) = 0;
		
		virtual RGBColor
		get_Le(ShadeRec& sr) const = 0;	
	
		virtual RGBColor
		area_light_shade(ShadeRec& sr) = 0;	
		
		virtual RGBColor
		path_shade(ShadeRec& sr);

		virtual RGBColor
		global_shade(ShadeRec& sr);

	protected:
	
		Material& 								
		operator= (const Material& rhs);						
};
