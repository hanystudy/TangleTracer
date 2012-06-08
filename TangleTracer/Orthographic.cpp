// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the definition of the Orthographic class

#include "Constants.h" 
#include "Point3D.h"
#include "Vector3D.h"
#include "Orthographic.h"
#include <math.h>

// ----------------------------------------------------------------------------- default constructor

Orthographic::Orthographic(void)		
	:	Camera(),
		d(0),
		zoom(1.0)
{}


// ----------------------------------------------------------------------------- copy constructor

Orthographic::Orthographic(const Orthographic& c)   		
	: 	Camera(c),
		d(c.d),
		zoom(c.zoom)
{}


// ----------------------------------------------------------------------------- clone

Camera* 
Orthographic::clone(void) const {
	return (new Orthographic(*this));
}



// ----------------------------------------------------------------------------- assignment operator

Orthographic& 
Orthographic::operator= (const Orthographic& rhs) { 	
	if (this == &rhs)
		return (*this);
		
	Camera::operator= (rhs);

	d 		= rhs.d;
	zoom	= rhs.zoom;

	return (*this);
}


// ----------------------------------------------------------------------------- destructor

Orthographic::~Orthographic(void) {}	


// ----------------------------------------------------------------------------- get_direction

Vector3D
Orthographic::get_direction(const Point2D& p) const {
	Vector3D dir = p.x * u + p.y * v - d * w;	//Here we must know that view plane is not normal plane, so normalize() method would make serious mistake during rendering
	//dir.normalize();
	return(dir);
}



// ----------------------------------------------------------------------------- render_scene

void 												
Orthographic::render_scene(World& w) {
	RGBColor	L;
	ViewPlane	vp(w.vp);	 								
	Ray			ray;
	int 		depth = 0;  
	Point2D 	pp;		// sample point on a pixel
	int n = (int)sqrt((float)vp.num_samples);
		
	vp.s /= zoom;
	ray.o = eye;
		
	for (int r = 0; r < vp.vres; r++)			// up
		for (int c = 0; c < vp.hres; c++) {		// across 					
			L = black; 
			
			for (int p = 0; p < n; p++)			// up pixel
				for (int q = 0; q < n; q++) {	// across pixel
					pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n);
					pp.y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);
					ray.d = lookat - eye;
					ray.d.normalize();
					
					Vector3D temp = get_direction(pp);
					ray.o = eye + temp;
					//ray.o = Point3D(pp.x - ray.d.x, pp.y - ray.d.y, (eye - lookat).z);	//Just from positive direction along z axis

					//ray.o = eye + pp.x * u + pp.y *v;		//Same to get_direction method, this modification is made from 17.13a
					L += w.tracer_ptr->trace_ray(ray, depth);
				}
											
			L /= vp.num_samples;
			L *= exposure_time;
			w.display_pixel(r, c, L);
		} 
}

void						
Orthographic::render_stereo(World& w, float x, int pixel_offset) {
	RGBColor	L;	 	
	Ray			ray;
	ViewPlane	vp 			= w.vp;					
	int 		depth 		= 0;  
	Point2D 	sp; 				// sample point in [0, 1] X [0, 1]
	Point2D 	pp;					// sample point on the pixel
	
	vp.s /= zoom;	
	ray.o = eye;
	
	for (int r = 0; r < vp.vres; r++)			// up
		for (int c = 0; c < vp.hres; c++) {		// across 					
			L = black; 	

			for (int j = 0; j < vp.num_samples; j++) {	
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s * (c - 0.5 * vp.hres + sp.x) + x; 	// asymmetric view frustum
				pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
				ray.d = get_direction(pp);				
				L += w.tracer_ptr->trace_ray(ray, depth);
			}
										
			L /= vp.num_samples;
			L *= exposure_time;	
			w.display_pixel(r, c + pixel_offset, L);
		} 
}
