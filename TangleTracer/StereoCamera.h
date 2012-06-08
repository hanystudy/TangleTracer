// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

//You need to notice that here left and right cameras don't only refers to Pinhole or Thinlen, so we have to make them as subclass

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

		StereoCamera(Camera*, Camera*);

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
		
		virtual void
		render_stereo(World& w, float x, int pixel_offset);

	private:
		
		ViewingType	viewing_type;		// parallel or transverse viewing
		int			pixel_gap;			// gap in pixels between the left and right images
		float		beta;				// stereo separation angle	
		Camera*		left_camera_ptr;	// left eye camera, note: here we use Pinhole directly to avoid too many stereo function
		Camera*		right_camera_ptr;	// right eye camera
};

