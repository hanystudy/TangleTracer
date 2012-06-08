// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "SV_Matte.h"

#include "Light.h"

// ---------------------------------------------------------------- default constructor

SV_Matte::SV_Matte (void)
	:	Material(),
		ambient_brdf(new SV_Lambertian),
		diffuse_brdf(new SV_Lambertian)
{
	//ambient_brdf->set_sampler(new MultiJittered(16));
	//diffuse_brdf->set_sampler(new MultiJittered(16));
}



// ---------------------------------------------------------------- copy constructor

SV_Matte::SV_Matte(const SV_Matte& m)
	: 	Material(m)
{
	if(m.ambient_brdf)
		ambient_brdf = m.ambient_brdf->clone(); 
	else  ambient_brdf = NULL;
	
	if(m.diffuse_brdf)
		diffuse_brdf = m.diffuse_brdf->clone(); 
	else  diffuse_brdf = NULL;
}


// ---------------------------------------------------------------- clone

Material*										
SV_Matte::clone(void) const {
	return (new SV_Matte(*this));
}	


// ---------------------------------------------------------------- assignment operator

SV_Matte& 
SV_Matte::operator= (const SV_Matte& rhs) {
	if (this == &rhs)
		return (*this);
		
	Material::operator=(rhs);
	
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();
		
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();

	return (*this);
}


// ---------------------------------------------------------------- destructor

SV_Matte::~SV_Matte(void) {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}


// ---------------------------------------------------------------- shade

RGBColor
SV_Matte::shade(ShadeRec& sr) {
	
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
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
}

void									
SV_Matte::set_ce(const float r, const float g, const float b)
{
	//ce = RGBColor(r, g, b);
	return;
}

RGBColor
SV_Matte::get_Le(ShadeRec& sr) const
{
	return RGBColor(1.0);
}
	
RGBColor
SV_Matte::area_light_shade(ShadeRec& sr)
{
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
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
				L += diffuse_brdf->f(sr, wo, wi) * light_ptr->L(sr) * light_ptr->G(sr) * ndotwi / sr.w.lights[j]->pdf(sr);
		}
	}
		
	return (L);
}

// --------------------------- path shade

RGBColor							
SV_Matte::path_shade(ShadeRec& sr) {
	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;
	RGBColor 	f = diffuse_brdf->sample_f(sr, wo, wi);   
	float 		ndotwi = sr.normal * wi;
	Ray 		reflected_ray(sr.hit_point, wi);
	
	return (f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi);
}

RGBColor							
SV_Matte::global_shade(ShadeRec& sr) {
	RGBColor L;
	
	if (sr.depth == 0)
		L = area_light_shade(sr); 
	
	Vector3D 	wi;
	Vector3D 	wo 		= -sr.ray.d;
	RGBColor 	f 		= diffuse_brdf->sample_f(sr, wo, wi);   
	float 		ndotwi 	= sr.normal * wi;
	Ray 		reflected_ray(sr.hit_point, wi);
	
	L += f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi;
	
	return (L);
}

void
SV_Matte::set_sampler(Sampler* sPtr)
{
	//ambient_brdf->set_sampler(sPtr);
	diffuse_brdf->set_sampler(sPtr);
}
