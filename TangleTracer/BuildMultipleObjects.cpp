#include "MultipleObjects.h"
#include "SingleSphere.h"
#include "Plane.h"
#include "World.h"

#define MM2

#ifdef MM5

void World::build(void) {

	vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	background_color = white;
	tracer_ptr = new SingleSphere(this); 

	sphere.set_center(0.0);
	sphere.set_radius(85);
	sphere.set_color(1.0,0,0);


	tracer_ptr = new SingleSphere(this); 
	sphere.set_center(50.50);
	sphere.set_radius(150);
	sphere.set_color(0,1.0,0);
}

#elif defined MM2

void 												
	World::build(void) {
		//vp.set_hres(5);
		//vp.set_vres(5);
		//vp.set_pixel_size(1.0);
		Pinhole* camera_ptr = new Pinhole;
		camera_ptr->set_eye(0, 0, 250);
		camera_ptr->set_lookat(0);    
		camera_ptr->set_view_distance(200);  	// for Figure 8.16(a)	
		//	camera_ptr->set_view_distance(450);  	// for Figure 8.16(b)		
		//	camera_ptr->set_view_distance(1000);  	// for Figure 8.16(c)
		camera_ptr->compute_uvw();		  
		set_camera(camera_ptr);

		tracer_ptr = new MultipleObjects(this); 

		background_color = RGBColor(black);

		// use access functions to set centre and radius

		Sphere* sphere_ptr = new Sphere;
		sphere_ptr->set_center(0, -25, -100);
		sphere_ptr->set_radius(80);
		sphere_ptr->set_color(1, 0, 0);  // red
		add_object(sphere_ptr);

		// use constructor to set centre and radius 

		sphere_ptr = new Sphere(Point3D(0, 30, -100), 100);
		sphere_ptr->set_color(1, 1, 0);	// yellow
		add_object(sphere_ptr);

		Plane* plane_ptr = new Plane(Point3D(0,0,-100), Normal(0, 1, 1));
		plane_ptr->set_color(0.0, 0.3, 0.0);	// dark green
		add_object(plane_ptr);
}
#endif