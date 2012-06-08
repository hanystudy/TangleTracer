// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "SV_Emissive.h"

// ---------------------------------------------------------------- default constructor

SV_Emissive::SV_Emissive(void) :ls(1.0),t(NULL){}


// ---------------------------------------------------------------- copy constructor

SV_Emissive::SV_Emissive(const SV_Emissive& m): t(m.t) {}



// ---------------------------------------------------------------- assignment operator

SV_Emissive& 
SV_Emissive::operator= (const SV_Emissive& rhs) {
	if (this == &rhs)
		return (*this);

	t = rhs.t;

	return (*this);
}

SV_Emissive*								
SV_Emissive::clone(void) const
{
	return (new SV_Emissive(*this));
}


// ---------------------------------------------------------------- destructor

SV_Emissive::~SV_Emissive(void)
{}


// ---------------------------------------------------------------- shade

RGBColor
SV_Emissive::shade(ShadeRec& sr) {
	
	/*
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= //ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights 	= sr.w.lights.size();		
		
	for (int j = 0; j < num_lights; j++) {
		Light* light_ptr = sr.w.lights[j];
		Vector3D wi = light_ptr->get_direction(sr);	//compute_direction ?
		wi.normalize();
		float ndotwi = sr.normal * wi;
		float ndotwo = sr.normal * wo;
		
		if (ndotwi > 0.0 && ndotwo > 0.0) {
			bool in_shadow = false;
		
			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadow_ray(sr.hit_point, wi);		//hitPoint ?
				in_shadow = light_ptr->in_shadow(shadow_ray, sr);	//.object ?
			}
		
			if (!in_shadow)
				L += diffuse_brdf->f(sr, wo, wi) * light_ptr->L(sr) * light_ptr->G(sr) * ndotwi;
		}
	}
		
	return (L);
	
	*/
	return ls * t->get_color(sr);
	/*
	if (-sr.normal * sr.ray.d > 0.0)		//here may be ConcaveSphere not support
		return (ls * ce);
	else
		return (black);*/
}

void
SV_Emissive::scale_radiance(const float _ls)
{
	this->ls = _ls;
}
	
void									
SV_Emissive::set_ce(const float r, const float g, const float b)
{
	ce = RGBColor(r, g, b);
}

void									
SV_Emissive::set_ce(RGBColor c)
{
	ce = c;
}

void
SV_Emissive::set_ce(Texture *t)
{
	this->t = t;
}
		
RGBColor
SV_Emissive::get_Le(ShadeRec& sr) const
{
	/*
	return ls * ce;		//here is added, this is very important to multiply ce with ls!!!!!!
	*/
	return ls * t->get_color(sr);
}

RGBColor
SV_Emissive::area_light_shade(ShadeRec& sr)
{
	return ls * t->get_color(sr);
	/*
	if (-sr.normal * sr.ray.d > 0.0)		//here may be ConcaveSphere not support
		return (ls * ce);
	else
		return (black);*/
}

RGBColor
SV_Emissive::global_shade(ShadeRec& sr) {	
	if (sr.depth == 1)
		return (black);
	
	return ls * t->get_color(sr);
	/*
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return (black);*/
}

RGBColor
SV_Emissive::path_shade(ShadeRec& sr) {		//this new path shade returns final result
	/*
	if (sr.depth == 1)
		return (black);
		*/
	return ls * t->get_color(sr);
	/*
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return (black);*/

}