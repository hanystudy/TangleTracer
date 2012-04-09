#pragma once

typedef enum {
	parallel, 
	transverse
} ViewingType;

#include "constants.h"
#include "Pinhole.h"
#include "math.h"

class StereoCamera: public Camera {						
	public:
	
		StereoCamera();

		StereoCamera(const StereoCamera& ph);	

		virtual Camera*						
			clone(void) const;			

		StereoCamera& 							
			operator= (const StereoCamera& rhs);	

		virtual
			~StereoCamera();

		void
		set_left_camera(Camera*);

		void
		set_right_camera(Camera*);
		
		void
		use_parallel_viewing();
	
		void
		use_transverse_viewing();
		
		void
		set_pixel_gap(int);       
		
		void
		set_stereo_angle(double);  

		void
		setup_cameras(); 

		// constructors, etc

		virtual void 												
		render_scene(World& w);
		
	private:
		
		ViewingType	viewing_type;		// parallel or transverse viewing
		int			pixel_gap;			// gap in pixels between the left and right images
		float		beta;				// stereo separation angle	
		Pinhole*		left_camera_ptr;	// left eye camera, note: here we use Pinhole directly to avoid too many stereo function
		Pinhole*		right_camera_ptr;	// right eye camera
};

