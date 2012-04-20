#include "StereoCamera.h"

#include "World.h"

// ----------------------------------------------------------------------------- default constructor

StereoCamera::StereoCamera(void)		
	:	Camera()
{}


// ----------------------------------------------------------------------------- copy constructor

StereoCamera::StereoCamera(const StereoCamera& c)   		
	: 	Camera(c),
	viewing_type(c.viewing_type),
	pixel_gap(c.pixel_gap),
	beta(c.beta),
	left_camera_ptr(c.left_camera_ptr),
	right_camera_ptr(c.right_camera_ptr)
{}


// ----------------------------------------------------------------------------- clone

Camera* 
StereoCamera::clone(void) const {
	return (new StereoCamera(*this));
}



// ----------------------------------------------------------------------------- assignment operator

StereoCamera& 
StereoCamera::operator= (const StereoCamera& rhs) { 	
	if (this == &rhs)
		return (*this);
		
	Camera::operator= (rhs);

	viewing_type = rhs.viewing_type;
	pixel_gap = rhs.pixel_gap;
	beta = rhs.beta;
	left_camera_ptr = rhs.left_camera_ptr;
	right_camera_ptr = rhs.right_camera_ptr;
	return (*this);
}


// ----------------------------------------------------------------------------- destructor

StereoCamera::~StereoCamera(void) {}	

void
StereoCamera::set_left_camera(Camera* l)
{
	this->left_camera_ptr = (Pinhole*)l;
}

void
StereoCamera::set_right_camera(Camera* l)
{
	this->right_camera_ptr = (Pinhole*)l;
}
		
void
StereoCamera::use_parallel_viewing()
{
	viewing_type = ViewingType::parallel;
}
	
void
StereoCamera::use_transverse_viewing()
{
	viewing_type = ViewingType::transverse;
}

void
StereoCamera::set_pixel_gap(int g)
{
	pixel_gap = g;
}
		
void
StereoCamera::set_stereo_angle(double b)
{
	beta = b;
}

void 
StereoCamera::setup_cameras(void) {
	double r = eye.distance(lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);  //  half the camera separation distance
		
	left_camera_ptr->set_eye(eye - x * u);
	left_camera_ptr->set_lookat(lookat - x * u);
	left_camera_ptr->compute_uvw();
	
	right_camera_ptr->set_eye(eye + x * u);
	right_camera_ptr->set_lookat(lookat + x * u);
	right_camera_ptr->compute_uvw();
}

void 												
StereoCamera::render_scene(World& w) {
	ViewPlane	vp 		= w.vp;					
	int 		hres	= vp.hres;
	int 		vres 	= vp.vres;
	
	//w.open_window(2 * hres + pixel_gap, vres);
						
	double r = eye.distance(lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);  
		
	if (viewing_type == parallel) {
		left_camera_ptr->render_stereo(w, x, 0);						// left view on left
		right_camera_ptr->render_stereo(w, -x, hres + pixel_gap);   	// right view on right
	}
	
	if (viewing_type == transverse) {
		right_camera_ptr->render_stereo(w, -x, 0);   					// right view on left
		left_camera_ptr->render_stereo(w, x, hres + pixel_gap);    		// left view on right
	}
} 

