#pragma once

#include "Camera.h"
#include "Sampler.h"

class Spherical: public Camera {			
public:

	Spherical();

	Spherical(const Spherical& ph);	

	virtual Camera*						
		clone(void) const;			

	Spherical& 							
		operator= (const Spherical& rhs);	

	virtual
		~Spherical();   						

	void
		set_horizontal_fov(const float d);
	void
		set_vertical_fov(const float d);
	// constructors, etc

	Vector3D									
		ray_direction(	const Point2D& pp, 
		const int 	hres, 
		const int 	vres, 
		const float s, 
		float& 		r_squared) const;

	virtual void 												
		render_scene(World& w);

private:

	float	psi_max;	// in degrees
	float	lambda_max;
};

inline void
Spherical::set_horizontal_fov(const float d)
{
	this->lambda_max = d;
}

inline void
Spherical::set_vertical_fov(const float d)
{
	this->psi_max = d;
}