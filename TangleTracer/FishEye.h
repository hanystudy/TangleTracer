#pragma once

#include "Camera.h"
#include "Sampler.h"

class FishEye: public Camera {			
public:

	FishEye();

	FishEye(const FishEye& ph);	

	virtual Camera*						
		clone(void) const;			

	FishEye& 							
		operator= (const FishEye& rhs);	

	virtual
		~FishEye();   						

	void
		set_fov(const float d);
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
};

inline void
FishEye::set_fov(const float d)
{
	this->psi_max = d;
}