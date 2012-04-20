#include "MultipleObjects.h"
#include "SingleSphere.h"
#include "Plane.h"
#include "World.h"
#include "RayCast.h"
#include "Matte.h"
#include "Directional.h"
#include "PointLight.h"
#include "StereoCamera.h"
#include "Phong.h"
#include "AmbientOccluder.h"
#include "AreaLight.h"
#include "AreaLighting.h"
#include "EnvironmentLight.h"
#include "Emissive.h"
#include "ConcaveSphere.h"
#include "Hammersley.h"

#include "Instance.h"
#include "Triangle.h"
#include "SolidCylinder.h"

#include "Torus.h"
#include "Box.h"

#include "BeveledCylinder.h"

#include "Grid.h"

#include "Reflective.h"
#include "Whitted.h"
#include "Rectangle.h"

#include "GlossyReflector.h"

#include "PathTrace.h"
#include "GlobalTrace.h"

#define RGBColour RGBColor

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
	int num_samples = 100;
		
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_pixel_size(0.5);
	vp.set_max_depth(0);
	
	background_color = black;
	
	tracer_ptr = new GlobalTrace(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.0);
	set_ambient_light(ambient_ptr);
	
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(27.6, 27.4, -80.0);
	pinhole_ptr->set_lookat(27.6, 27.4, 0.0);
	pinhole_ptr->set_view_distance(400);      
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	Point3D p0;
	Vector3D a, b;
	Normal normal;
	
	// box dimensions
	
	double width 	= 55.28;   	// x direction
	double height 	= 54.88;  	// y direction
	double depth 	= 55.92;	// z direction
	
		
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_ce(1.0, 0.73, 0.4);   
	emissive_ptr->scale_radiance(100.0);
	
	p0 = Point3D(21.3, height - 0.001, 22.7);
	a = Vector3D(0.0, 0.0, 10.5);
	b = Vector3D(13.0, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);
	
	TRectangle* light_ptr = new TRectangle(p0, a, b, normal);
	light_ptr->set_material(emissive_ptr);
	light_ptr->set_sampler(new MultiJittered(num_samples));
	light_ptr->set_shadows(false);
	add_object(light_ptr);
	
	AreaLight* ceiling_light_ptr = new AreaLight;   
	ceiling_light_ptr->set_object(light_ptr);		
	ceiling_light_ptr->set_shadows(true);
	add_light(ceiling_light_ptr);
	
		
	// left wall
	
	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.0);
	matte_ptr1->set_kd(0.6); 
	matte_ptr1->set_cd(0.57, 0.025, 0.025);	 // red
	matte_ptr1->set_sampler(new MultiJittered(num_samples));
	
	p0 = Point3D(width, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(-1.0, 0.0, 0.0);
	TRectangle* left_wall_ptr = new TRectangle(p0, a, b, normal);
	left_wall_ptr->set_material(matte_ptr1);
	add_object(left_wall_ptr);
	
	
	// right wall
	
	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.0);
	matte_ptr2->set_kd(0.6); 
	matte_ptr2->set_cd(0.37, 0.59, 0.2);	 // green  
	matte_ptr2->set_sampler(new MultiJittered(num_samples));
	
	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(1.0, 0.0, 0.0);
	TRectangle* right_wall_ptr = new TRectangle(p0, a, b, normal);
	right_wall_ptr->set_material(matte_ptr2);
	add_object(right_wall_ptr);
	
	
	// back wall
	
	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.0);
	matte_ptr3->set_kd(0.6); 
	matte_ptr3->set_cd(white);
	matte_ptr3->set_sampler(new MultiJittered(num_samples));
	
	p0 = Point3D(0.0, 0.0, depth);
	a = Vector3D(width, 0.0, 0.0);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(0.0, 0.0, -1.0);
	TRectangle* back_wall_ptr = new TRectangle(p0, a, b, normal);
	back_wall_ptr->set_material(matte_ptr3);
	add_object(back_wall_ptr);
	
	
	// floor
	
	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, 1.0, 0.0);
	TRectangle* floor_ptr = new TRectangle(p0, a, b, normal);
	floor_ptr->set_material(matte_ptr3);
	add_object(floor_ptr);
	
	
	// ceiling
	
	p0 = Point3D(0.0, height, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);
	TRectangle* ceiling_ptr = new TRectangle(p0, a, b, normal);
	ceiling_ptr->set_material(matte_ptr3);
	add_object(ceiling_ptr);

	
	// the two boxes defined as 5 rectangles each
	
	// short box
	
	// top
	
	p0 = Point3D(13.0, 16.5, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(16.0, 0.0, 4.9);
	normal = Normal(0.0, 1.0, 0.0);
	TRectangle* short_top_ptr = new TRectangle(p0, a, b, normal);
	short_top_ptr->set_material(matte_ptr3);
	add_object(short_top_ptr);
	
	
	// side 1
	
	p0 = Point3D(13.0, 0.0, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(0.0, 16.5, 0.0);
	TRectangle* short_side_ptr1 = new TRectangle(p0, a, b);
	short_side_ptr1->set_material(matte_ptr3);
	add_object(short_side_ptr1);
	
	
	// side 2
	
	p0 = Point3D(8.2, 0.0, 22.5);
	a = Vector3D(15.8, 0.0, 4.7);
	TRectangle* short_side_ptr2 = new TRectangle(p0, a, b);
	short_side_ptr2->set_material(matte_ptr3);
	add_object(short_side_ptr2);
	
	
	// side 3
	
	p0 = Point3D(24.2, 0.0, 27.4);
	a = Vector3D(4.8, 0.0, -16.0);
	TRectangle* short_side_ptr3 = new TRectangle(p0, a, b);
	short_side_ptr3->set_material(matte_ptr3);
	add_object(short_side_ptr3);
	
	
	// side 4
	
	p0 = Point3D(29.0, 0.0, 11.4);
	a = Vector3D(-16.0, 0.0, -4.9);
	TRectangle* short_side_ptr4 = new TRectangle(p0, a, b);
	short_side_ptr4->set_material(matte_ptr3);
	add_object(short_side_ptr4);
	
	
	
	// tall box
	
	// top
	
	p0 = Point3D(42.3, 33.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(4.9, 0.0, 15.9);
	normal = Normal(0.0, 1.0, 0.0);
	TRectangle* tall_top_ptr = new TRectangle(p0, a, b, normal);
	tall_top_ptr->set_material(matte_ptr3);
	add_object(tall_top_ptr);
	
	
	// side 1
	
	p0 = Point3D(42.3, 0.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(0.0, 33.0, 0.0);
	TRectangle* tall_side_ptr1 = new TRectangle(p0, a, b);
	tall_side_ptr1->set_material(matte_ptr3);
	add_object(tall_side_ptr1);
	
	
	// side 2
	
	p0 = Point3D(26.5, 0.0, 29.6);
	a = Vector3D(4.9, 0.0, 15.9);
	TRectangle* tall_side_ptr2 = new TRectangle(p0, a, b);
	tall_side_ptr2->set_material(matte_ptr3);
	add_object(tall_side_ptr2);
	
	
	// side 3
	
	p0 = Point3D(31.4, 0.0, 45.5);
	a = Vector3D(15.8, 0.0, -4.9);
	TRectangle* tall_side_ptr3 = new TRectangle(p0, a, b);
	tall_side_ptr3->set_material(matte_ptr3);
	add_object(tall_side_ptr3);
	
	
	// side 4
	
	p0 = Point3D(47.2, 0.0, 40.6);
	a = Vector3D(-4.9, 0.0, -15.9);
	TRectangle* tall_side_ptr4 = new TRectangle(p0, a, b);
	tall_side_ptr4->set_material(matte_ptr3);
	add_object(tall_side_ptr4);
}
#endif