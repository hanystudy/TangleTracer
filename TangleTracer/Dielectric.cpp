// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Dielectric.h"

// ---------------------------------------------------------------- default constructor

Dielectric::Dielectric (void)
	:	Phong(),
		fresnel_brdf(new FresnelReflector),
		fresnel_btdf(new FresnelTransmitter),
		shadows(true)
{}



// ---------------------------------------------------------------- copy constructor

Dielectric::Dielectric(const Dielectric& m)
	: 	Phong(m),
		shadows(m.shadows)
{
	if(m.ambient_brdf)
		ambient_brdf = m.ambient_brdf->clone(); 
	else  ambient_brdf = NULL;
	
	if(m.diffuse_brdf)
		diffuse_brdf = m.diffuse_brdf->clone(); 
	else  diffuse_brdf = NULL;

	if(m.specular_brdf)
		specular_brdf = m.specular_brdf->clone(); 
	else  specular_brdf = NULL;

	if(m.fresnel_brdf)
		fresnel_brdf = m.fresnel_brdf->clone(); 
	else  fresnel_brdf = NULL;

	if(m.fresnel_btdf)
		fresnel_btdf = m.fresnel_btdf->clone(); 
	else  fresnel_btdf = NULL;
}


// ---------------------------------------------------------------- clone

Material*										
Dielectric::clone(void) const {
	return (new Dielectric(*this));
}	


// ---------------------------------------------------------------- assignment operator

Dielectric& 
Dielectric::operator= (const Dielectric& rhs) {
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

	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}

	if (rhs.specular_brdf)
		specular_brdf = rhs.specular_brdf->clone();

	if (rhs.fresnel_btdf)
		this->fresnel_btdf = rhs.fresnel_btdf->clone();

	if (rhs.fresnel_brdf)
		this->fresnel_brdf = rhs.fresnel_brdf->clone();

	shadows = rhs.shadows;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Dielectric::~Dielectric(void) {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}

	if (fresnel_brdf) {
		delete fresnel_brdf;
		fresnel_brdf = NULL;
	}

	if (fresnel_btdf) {
		delete fresnel_btdf;
		fresnel_btdf = NULL;
	}
}

// --------------------------------------------------

RGBColor
Dielectric::shade(ShadeRec& sr) {
	RGBColor L(Phong::shade(sr));
		
	Vector3D 	wi;
	Vector3D 	wo(-sr.ray.d);
	RGBColor 	fr = fresnel_brdf->sample_f(sr, wo, wi);  	// computes wi
	Ray 		reflected_ray(sr.hit_point, wi); 
	double 		t;
	RGBColor 	Lr, Lt;
	float 		ndotwi =  sr.normal * wi;
		
	if(fresnel_btdf->tir(sr)) {								// total internal reflection
		if (ndotwi < 0.0) {  	
			// reflected ray is inside
			
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			L += cf_in.powc(t) * Lr;   						// inside filter color
		}
		else {				
			// reflected ray is outside
			
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);   // kr = 1  
			L += cf_out.powc(t) * Lr;   					// outside filter color
		}
	}
	else { 													// no total internal reflection
		Vector3D wt;
		RGBColor ft = fresnel_btdf->sample_f(sr, wo, wt);  	// computes wt
		Ray transmitted_ray(sr.hit_point, wt);
		float ndotwt = sr.normal * wt;
							
		if (ndotwi < 0.0) {
			// reflected ray is inside
						
			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
			L += cf_in.powc(t) * Lr;     					// inside filter color
				
			// transmitted ray is outside
							
			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
			L += cf_out.powc(t) * Lt;   					// outside filter color
		}
		else {				
			// reflected ray is outside

			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi); 
			L += cf_out.powc(t) * Lr;						// outside filter color
				
			// transmitted ray is inside
			
			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
			L += cf_in.powc(t) * Lt; 						// inside filter color
		}		
	}	
	
	return (L);
}  

RGBColor
Dielectric::area_light_shade(ShadeRec& sr)			//this is for chapter 18 page one image ad-hoc
{
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();

	for (int j = 0; j < num_lights; j++) {
		Vector3D 	wi 		= sr.w.lights[j]->get_direction(sr);    
		float 		ndotwi 	= sr.normal * wi;

		if (ndotwi > 0.0) {
			bool in_shadow = false;

			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadowRay(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
			}

			if (!in_shadow) 
				L += (	diffuse_brdf->f(sr, wo, wi) 
						  + specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * ndotwi * sr.w.lights[j]->G(sr) / sr.w.lights[j]->pdf(sr);
		}
	}
	return (L);
}
