// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "RGBColor.h"
#include "Material.h"


class Emissive: public Material {	
	private:
	
		float		ls;		// radiance scaling factor						 
		RGBColor 	ce;		// color
	
	public:
	
		Emissive(void);						
		
		Emissive(const Emissive& material); 
		
		virtual Emissive*								
		clone(void) const;	
		
		virtual Emissive& 
		operator= (const Emissive& rhs);

		virtual 								
		~Emissive(void);
				
		virtual RGBColor
		shade(ShadeRec& sr);
	
		void
		scale_radiance(const float _ls);
	
		void									
		set_ce(const float r, const float g, const float b);

		void									
		set_ce(RGBColor);
		
		virtual RGBColor
		get_Le(ShadeRec& sr) const;	
	
		virtual RGBColor
		area_light_shade(ShadeRec& sr);	

		virtual RGBColor
		global_shade(ShadeRec& sr);

		RGBColor
		path_shade(ShadeRec& sr);
};
