// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Matte.h"

#include "Light.h"

// ---------------------------------------------------------------- default constructor

Matte::Matte (void)
	:	Material(),
		ambient_brdf(new Lambertian),
		diffuse_brdf(new Lambertian),
		shadows(true)
{
	//ambient_brdf->set_sampler(new MultiJittered(16));
	//diffuse_brdf->set_sampler(new MultiJittered(16));
}



// ---------------------------------------------------------------- copy constructor

Matte::Matte(const Matte& m)
	: 	Material(m),
		shadows(m.shadows)
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
Matte::clone(void) const {
	return (new Matte(*this));
}	


// ---------------------------------------------------------------- assignment operator

Matte& 
Matte::operator= (const Matte& rhs) {
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

	shadows = rhs.shadows;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Matte::~Matte(void) {

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
Matte::shade(ShadeRec& sr) {
	/*
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);    
		float ndotwi = sr.normal * wi;
	
		if (ndotwi > 0.0) 
			L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
	}
	
	return (L);*/

	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();

	for (int j = 0; j < num_lights; j++) {
		Vector3D 	wi 		= sr.w.lights[j]->get_direction(sr);    
		float 		ndotwi 	= sr.normal * wi;

		if (ndotwi > 0.0) {
			if(shadows)
			{
				bool in_shadow = false;

				if (sr.w.lights[j]->casts_shadows()) {
					Ray shadowRay(sr.hit_point, wi);
					in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
				}

				if ( shadows && !in_shadow) 
					L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
			}
			else
			{
				L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
			}
		}
	}
	return (L);
}

void									
Matte::set_ce(const float r, const float g, const float b)
{
	//ce = RGBColor(r, g, b);
	return;
}

RGBColor
Matte::get_Le(ShadeRec& sr) const
{
	return RGBColor(1.0);
}
	
RGBColor
Matte::area_light_shade(ShadeRec& sr)
{
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		Vector3D 	wi 		= sr.w.lights[j]->get_direction(sr);    
		float 		ndotwi 	= sr.normal * wi;
	
		if (ndotwi > 0.0) {
			if(shadows)
			{
				bool in_shadow = false;
	
				if (sr.w.lights[j]->casts_shadows()) {
					Ray shadow_ray(sr.hit_point, wi);
					in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr); 
				}
	
				if ( shadows && !in_shadow) 
					L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * sr.w.lights[j]->G(sr) * ndotwi / sr.w.lights[j]->pdf(sr);
			}
			else
			{
				L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * sr.w.lights[j]->G(sr) * ndotwi / sr.w.lights[j]->pdf(sr);
			}
		}
	}
	//L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);
	return (L);
}

// --------------------------- path shade

RGBColor							
Matte::path_shade(ShadeRec& sr) {
	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;
	float 		pdf;
	RGBColor 	f = diffuse_brdf->sample_f(sr, wo, wi, pdf);   
	float 		ndotwi = sr.normal * wi;
	Ray 		reflected_ray(sr.hit_point, wi);
	
	return (f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi / pdf);
}

RGBColor							
Matte::global_shade(ShadeRec& sr) {
	RGBColor L;
	
	if (sr.depth == 0)
		L = area_light_shade(sr); 
	
	Vector3D 	wi;
	Vector3D 	wo 		= -sr.ray.d;
	float 		pdf;
	RGBColor 	f 		= diffuse_brdf->sample_f(sr, wo, wi, pdf);   
	float 		ndotwi 	= sr.normal * wi;
	Ray 		reflected_ray(sr.hit_point, wi);
	
	L += f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi / pdf;
	
	return (L);
}

void
Matte::set_sampler(Sampler* sPtr)
{
	//ambient_brdf->set_sampler(sPtr);
	diffuse_brdf->set_sampler(sPtr);
}
