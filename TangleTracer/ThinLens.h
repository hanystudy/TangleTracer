#pragma once

#include "Camera.h"
#include "Sampler.h"

class ThinLens: public Camera {

public:

	ThinLens();

	ThinLens(const ThinLens& ph);	

	virtual Camera*						
		clone(void) const;			

	ThinLens& 							
		operator= (const ThinLens& rhs);	

	virtual
		~ThinLens();   						

	void
		set_view_distance(const float vpd);

	void
		set_zoom(const float zoom_factor);

	void
		set_lens_radius(const float);

	void
		set_focal_distance(const float _d);

	Vector3D								
		get_direction(const Point2D& p) const;

	// constructors, access functions, etc

	void
		set_sampler(Sampler* sp);	

	Vector3D
		ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const;

	virtual void 												
		render_scene(World& w);		//Here may need a const to asure the implementation of the same function in Camera class				

private:

	float		lens_radius;	// lens radius
	float		d;				// view plane distance
	float		f;				// focal distance
	float		zoom;			// zoom factor
	Sampler*	sampler_ptr;	// sampler object
};

//-------------------------------------------------------------------------- set_focal_distance

inline void
	ThinLens::set_focal_distance(const float _d) {
		f = _d;
}	

//-------------------------------------------------------------------------- set_lens_radius

inline void
	ThinLens::set_lens_radius(const float _d) {
		lens_radius = _d;
}	

//-------------------------------------------------------------------------- set_vpd

inline void
	ThinLens::set_view_distance(float _d) {
		d = _d;
}	

//-------------------------------------------------------------------------- set_zoom

inline void
	ThinLens::set_zoom(float zoom_factor) {
		zoom = zoom_factor;
}	
