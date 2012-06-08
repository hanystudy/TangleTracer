// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

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
	
	void
		set_field_of_view(const float d);
	// constructors, etc

	Vector3D									
		ray_direction(	const Point2D& pp, 
		const int 	hres, 
		const int 	vres, 
		const float s, 
		float& 		r_squared) const;

	virtual void 												
		render_scene(World& w);

	virtual void
		render_stereo(World& w, float x, int pixel_offset);

	void
		set_rectangular(bool);

private:

	float	psi_max;	// in degrees

	bool rectangular;
};


inline void
//Here we need half the view field to be psi_max, you can refer to figure 11.3
FishEye::set_fov(const float d)
{
	this->psi_max = d / 2;
}

inline void
FishEye::set_field_of_view(const float d)
{
	this->psi_max = d / 2;
}

inline void
FishEye::set_rectangular(bool b)
{

}