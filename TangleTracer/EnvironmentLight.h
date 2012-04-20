#pragma once

#include "Light.h"
#include "Sampler.h"
#include "Material.h"

class EnvironmentLight: public Light {	

public:
	// constructors etc...
			
	EnvironmentLight(void);
								
	EnvironmentLight(const EnvironmentLight& ls);			

	EnvironmentLight& 								
	operator= (const EnvironmentLight& rhs); 

	virtual Light* 						
	clone(void) const;
		
	virtual 							
	~EnvironmentLight(void);		

	void 
	set_sampler(Sampler* sampler); 
	
	virtual Vector3D												
	get_direction(ShadeRec& s);
	
	virtual RGBColor						
	L(ShadeRec& sr);
	
	virtual bool									
	in_shadow(const Ray& ray, const ShadeRec& sr) const;
		
	virtual float									
	pdf(ShadeRec& sr) const;		//here delete const 
	
	void
	set_material(Material*);
private:
	
	Sampler*	sampler_ptr;
	Material* 	material_ptr;
	Vector3D	u, v, w;		
	Vector3D	wi;
};

inline void
EnvironmentLight::set_material(Material* m)
{
	this->material_ptr = m;
}

