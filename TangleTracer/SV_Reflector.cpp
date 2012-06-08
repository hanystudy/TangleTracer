// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "SV_Reflector.h"

// ---------------------------------------------------------------- default constructor

SV_Reflector::SV_Reflector (void)
	:	Phong(),
		reflective_brdf(new SV_PerfectSpecular),
		texture_ptr(NULL)
{}


// ---------------------------------------------------------------- copy constructor

SV_Reflector::SV_Reflector(const SV_Reflector& rm)
	: 	Phong(rm),
		texture_ptr(rm.texture_ptr) 
{
	
	if(rm.reflective_brdf)
		reflective_brdf = rm.reflective_brdf->clone(); 
	else  
		reflective_brdf = NULL;
}


// ---------------------------------------------------------------- assignment operator

SV_Reflector& 
SV_Reflector::operator= (const SV_Reflector& rhs) {
	if (this == &rhs)
		return (*this);
		
	Phong::operator=(rhs);
	
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}

	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();

	texture_ptr = rhs.texture_ptr;

	return (*this);
}


// ---------------------------------------------------------------- clone

SV_Reflector*										
SV_Reflector::clone(void) const {
	return (new SV_Reflector(*this));
}	


// ---------------------------------------------------------------- destructor

SV_Reflector::~SV_Reflector(void) {
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
}


// ------------------------------------------------------------------------------------ shade 

RGBColor
SV_Reflector::shade(ShadeRec& sr) {	
	RGBColor L(Phong::shade(sr));  // direct illumination
	
	Vector3D wo = -sr.ray.d;
	Vector3D wi;	
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi); 
	Ray reflected_ray(sr.hit_point, wi); 
	reflected_ray.depth = sr.depth + 1;
	
	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);
					
	return (L);
}

RGBColor
SV_Reflector::area_light_shade(ShadeRec& sr) {

	RGBColor L(Phong::shade(sr));  // direct illumination
	
	Vector3D wo = -sr.ray.d;
	Vector3D wi;	
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi); 
	Ray reflected_ray(sr.hit_point, wi); 
	reflected_ray.depth = sr.depth + 1;
	
	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);
	//L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * sr.w.lights[j]->G(sr) * ndotwi / sr.w.lights[j]->pdf(sr);

	return (L);
}
//This function doesn't appear in book, but needed by 24.43

RGBColor
SV_Reflector::global_shade(ShadeRec& sr) {
	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;	
	float 		pdf;
	RGBColor 	fr = reflective_brdf->sample_f(sr, wo, wi, pdf);  
	Ray 		reflected_ray(sr.hit_point, wi);
		
	if (sr.depth == 0)			
		return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 2) * (sr.normal * wi) / pdf);
	else
		return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
}

RGBColor
SV_Reflector::path_shade(ShadeRec& sr) {		
	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;	
	float 		pdf;
	RGBColor 	fr = reflective_brdf->sample_f(sr, wo, wi, pdf); 
	Ray 		reflected_ray(sr.hit_point, wi);
					
	return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
}
