// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Material.h"
#include "Lambertian.h"

//----------------------------------------------------------------------------- class Matte

class Matte: public Material {	
	public:
			
		Matte(void);											

		Matte(const Matte& m);
		
		virtual Material*										
		clone(void) const;									

		Matte& 
		operator= (const Matte& rhs);							

		~Matte(void);											
		
		void 													
		set_ka(const float k);
		
		void 													
		set_kd(const float k);
		
		void													
		set_cd(const RGBColor c);
		
		void													
		set_cd(const float r, const float g, const float b);
		
		void																						
		set_cd(const float c);
				
		virtual RGBColor										
		shade(ShadeRec& sr);

		virtual void									
		set_ce(const float r, const float g, const float b);
		
		virtual RGBColor
		get_Le(ShadeRec& sr) const;
	
		virtual RGBColor
		area_light_shade(ShadeRec& sr);	

		virtual RGBColor							
		path_shade(ShadeRec& sr);		//new for c26
		
		virtual RGBColor	
		global_shade(ShadeRec& sr);		//new for c26

		virtual void
		set_sampler(Sampler* sPtr);

		void
		set_shadows(bool);

	private:
		
		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;

		bool shadows;
		//float		ls;		// radiance scaling factor						 
		//RGBColor 	ce;		// color
};


// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void								
Matte::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
Matte::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void												
Matte::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


// ---------------------------------------------------------------- set_cd

inline void													
Matte::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void													
Matte::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void
Matte::set_shadows(bool b)
{
	this->shadows = b;
}