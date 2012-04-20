#include "EnvironmentLight.h"

#include "Constants.h"
#include "ShadeRec.h"
#include "World.h"


// ---------------------------------------------------------------------- default constructor

EnvironmentLight::EnvironmentLight(void):sampler_ptr(NULL),material_ptr(NULL)
{
	this->shadows = false;
}

// ---------------------------------------------------------------------- copy constructor

EnvironmentLight::EnvironmentLight(const EnvironmentLight& ls) {}


// ---------------------------------------------------------------------- assignment operator

EnvironmentLight& 
EnvironmentLight::operator= (const EnvironmentLight& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------------- destructor

EnvironmentLight::~EnvironmentLight(void) {} 



// ---------------------------------------------------------------------- L
// returns the radiance

RGBColor								
EnvironmentLight::L(ShadeRec& sr) {
	return (material_ptr->get_Le(sr));
}

// The following function is not in the book.
// It uses Equation 18.6

float									
EnvironmentLight::pdf(ShadeRec& sr) const {
	return (sr.normal * wi * invPI);
}


Vector3D								
EnvironmentLight::get_direction(ShadeRec& sr) {
	w = sr.normal;
	v = Vector3D(0.0034, 1, 0.0071) ^ w;
	v.normalize();
	u = v ^ w;
	Point3D sp = sampler_ptr->sample_hemisphere();	
	wi = sp.x * u + sp.y * v + sp.z * w;

	return (wi);
}

bool									
EnvironmentLight::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	float t = 10000;
	int num_objects = sr.w.objects.size();
	double d = kEpsilon;
														
	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t > d)
			return (true);

	return (false);
}

// ---------------------------------------------------------------------- clone

Light* 
EnvironmentLight::clone(void) const {
	return (new EnvironmentLight(*this));
}

void
EnvironmentLight::set_sampler(Sampler* sampler)
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	
	sampler_ptr = sampler;
	sampler_ptr->map_samples_to_hemisphere(1);
}

