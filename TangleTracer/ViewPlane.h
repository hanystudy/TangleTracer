// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

//-------------------------------------------------------------------------------------- class ViewPlane

#include "MultiJittered.h"
#include "Regular.h"


class ViewPlane {
public:
	int 			hres;   					// horizontal image resolution 
	int 			vres;   					// vertical image resolution
	float			s;							// pixel size

	float			gamma;						// gamma correction factor
	float			inv_gamma;					// the inverse of the gamma correction factor
	bool			show_out_of_gamut;			// display red if RGBColor out of gamut
	
	Sampler *sampler_ptr;
	int num_samples;

	int max_depth;
public:

	ViewPlane();   								// default Constructor

	ViewPlane(const ViewPlane& vp);				// copy constructor

	ViewPlane& operator= (const ViewPlane& rhs);		// assignment operator

	~ViewPlane();   							// destructor

	void 													
		set_hres(const int h_res);

	void 													
		set_vres(const int v_res);

	void
		set_pixel_size(const float size);

	void
		set_gamma(const float g);

	void
		set_gamut_display(const bool show);	

	void 
		set_sampler(Sampler* sp);

	void 
		set_samples(const int count );

	void
		set_max_depth(const int d);
};

// ------------------------------------------------------------------------------ set_hres

inline void 													
	ViewPlane::set_hres(const int h_res) {
		hres = h_res;
}


// ------------------------------------------------------------------------------ set_vres

inline void 													
	ViewPlane::set_vres(const int v_res) {
		vres = v_res;
}


// ------------------------------------------------------------------------------ set_pixel_size

inline void 													
	ViewPlane::set_pixel_size(const float size) {
		s = size;
}


// ------------------------------------------------------------------------------ set_gamma

inline void
	ViewPlane::set_gamma(const float g) {
		gamma = g;
		inv_gamma = 1.0 / gamma;
}


// ------------------------------------------------------------------------------ set_gamut_display

inline void
	ViewPlane::set_gamut_display(const bool show) {
		show_out_of_gamut = show;
}

inline void
	ViewPlane::set_max_depth(const int d) {
		max_depth = d;
}