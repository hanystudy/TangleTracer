#include "World.h"

#include "World.h"
#include "Constants.h"

// geometric objects

#include "Plane.h"
#include "Sphere.h"

// tracers

#include "SingleSphere.h"
#include "MultipleObjects.h"

// utilities

#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"

// build functions

#include "BuildSingleSphere.cpp"
//#include "BuildMultipleObjects.cpp"
//#include "BuildBBCoverPic.cpp"

#include "RenderThread.h"


// -------------------------------------------------------------------- default constructor

World::World(void)
	:  	background_color(black),
		tracer_ptr(NULL),
		eye(200)
{}



//------------------------------------------------------------------ destructor

World::~World(void) {	
	
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}	
	
	delete_objects();	
}


//------------------------------------------------------------------ render_scene

// This uses orthographic viewing along the zw axis

// edition: chapter 1-3 

void 												
World::render_scene(void) const {

	RGBColor	pixel_color;	 	
	Ray			ray;					
	int 		hres 	= vp.hres;
	int 		vres 	= vp.vres;
	float		s		= vp.s;
	float		zw		= 100.0;			// hardwired in

	ray.d = Vector3D(0, 0, -1);
	
	for (int r = 0; r < vres; r++)			// up
		for (int c = 0; c <= hres; c++) {	// across 					
			ray.o = Point3D(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw);
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);
		}	
}  


// edition: chapter 4.1

void 												
World::render_scene_antialise_regular(void) const {

	RGBColor	pixel_color;	 	
	Ray			ray;					
	int 		hres 	= vp.hres;
	int 		vres 	= vp.vres;
	float		s		= vp.s;
	float		zw		= 100.0;			// hardwired in

	int n = 5;	//sqrt number of samples

	ray.d = Vector3D(0, 0, -1);
	
	for (int r = 0; r < vres; r++)			// up
		for (int c = 0; c <= hres; c++) {	// across 		
			pixel_color = black;

			for(int p=0; p < n; ++p)
			{
				for(int q = 0;q< n;++q)
				{
					ray.o = Point3D(s * (c - hres / 2.0 + (q+0.5)/n), s * (r - vres / 2.0 + (p+0.5)/n), zw);
					pixel_color += tracer_ptr->trace_ray(ray);
				}
			}
			pixel_color /= n*n;
			display_pixel(r, c, pixel_color);
		}	
}  

// edition: chapter 4.2

void 												
World::render_scene_antialise_random(void) const
{
	RGBColor	pixel_color;	 	
	Ray			ray;					
	int 		hres 	= vp.hres;
	int 		vres 	= vp.vres;
	float		s		= vp.s;
	float		zw		= 100.0;			// hardwired in

	int n = 25;	//number of samples

	ray.d = Vector3D(0, 0, -1);
	
	for (int r = 0; r < vres; r++)			// up
		for (int c = 0; c <= hres; c++) {	// across 		
			pixel_color = black;

			for(int p=0; p < n; ++p)
			{
				ray.o = Point3D(s * (c - hres / 2.0 + 1.0*qrand()/RAND_MAX), s * (r - vres / 2.0 + 1.0*qrand()/RAND_MAX), zw);
				pixel_color += tracer_ptr->trace_ray(ray);
			}
			pixel_color /= n;
			display_pixel(r, c, pixel_color);
		}	
}

// edition: chapter 5.6

void
World::render_scene_antialise_regular_sampler(void) const
{
	RGBColor	pixel_color;	 	
	Ray			ray;					
	float		zw		= 100.0;		
	Point2D		sp;		// sample point in [0, 1] x [0, 1] 
	Point2D 	pp;		// sample point on a pixel

	//open_window(vp.hres, vp.vres);  
	ray.d = Vector3D(0, 0, -1);

	for (int r = 0; r < vp.vres; r++)				// up
		for (int c = 0; c <= vp.hres; c++) {		// across 

			pixel_color = black;

			for (int j = 0; j < vp.num_samples; j++) {	
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
				pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
				ray.o = Point3D(pp.x, pp.y, zw);				
				pixel_color += tracer_ptr->trace_ray(ray);        
			}

			pixel_color /= vp.num_samples; 	// average the colors
			display_pixel(r, c, pixel_color);
		}
}

// edition: chapter 8.1

void 
	World::render_scene_perspective(void) const
{
	RGBColor	pixel_color;	 	
	Ray			ray;

	ray.o = Point3D(0, 0, eye);

	for (int r = 0; r < vp.vres; r++)				// up
		for (int c = 0; c <= vp.hres; c++) {		// across 

			pixel_color = black;
			ray.d = Vector3D(
				vp.s * (c - 0.5 * (vp.hres-1)),
				vp.s * (r - 0.5 * (vp.vres-1)),
				-250								//refers to d, which means distance between eye and viewplane, you can see how to zoom in respective viewing?
				);
			ray.d.normalize();

			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);
		}
}

// ------------------------------------------------------------------ clamp

RGBColor
World::max_to_one(const RGBColor& c) const  {
	float max_value = max(c.r, max(c.g, c.b));
	
	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}


// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one

RGBColor
World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
		
	return (c);
}


// ---------------------------------------------------------------------------display_pixel

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function


void
World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);
	
	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);
	
   //have to start from max y coordinate to convert to screen coordinates
   int x = column;
   int y = vp.vres - row - 1;

   paintArea->setPixel(x, y, (int)(mapped_color.r * 255),
                             (int)(mapped_color.g * 255),
                             (int)(mapped_color.b * 255));
}



// ----------------------------------------------------------------------------- hit_bare_bones_objects

ShadeRec									
World::hit_bare_bones_objects(const Ray& ray) {
	ShadeRec	sr(*this); 
	double		t; 			
	float		tmin 			= kHugeValue;
	int 		num_objects 	= objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t; 
			sr.color			= objects[j]->get_color(); 
		}
		
	return (sr);   
}


//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}

//------------------------------------------------------------------ only works after chapter 8

void
World::set_camera(Camera* c_ptr)
{
	this->camera_ptr = c_ptr;
}