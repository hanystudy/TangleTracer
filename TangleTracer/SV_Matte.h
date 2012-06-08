// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Material.h"
#include "Texture.h"
#include "SV_Lambertian.h"

class SV_Matte: public Material {		
	public:
	
		SV_Matte(void);											

		SV_Matte(const SV_Matte& m);
		
		virtual Material*										
		clone(void) const;									

		SV_Matte& 
		operator= (const SV_Matte& rhs);							

		~SV_Matte(void);											
		
		void 													
		set_ka(const float k);
		
		void 													
		set_kd(const float k);

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
		// consructors, etc ...
	
		void
		set_cd(Texture* t_ptr);
	
		virtual RGBColor										
		shade(ShadeRec& s);	
	
	private:
	
		SV_Lambertian*	ambient_brdf;
		SV_Lambertian*	diffuse_brdf;
};



// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void								
SV_Matte::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
SV_Matte::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}

inline void
SV_Matte::set_cd(Texture* t_ptr) {
	ambient_brdf->set_cd(t_ptr);
	diffuse_brdf->set_cd(t_ptr);
}
