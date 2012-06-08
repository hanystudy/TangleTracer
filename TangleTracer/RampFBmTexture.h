// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2008
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This is slightly different from Listing 31.15 in the book.
// The data member "a" has been replaced by "perturbation", which is set
// with the access function set_perturbation.
// The horizonal image resolution is stored in the data member hres.
// This can be initialized in the constuctors by calling Image::get_hres.
// It saves having to call Image::get_hres in the RampFBmTexture::get_color function.
// See Listing 31.17.

#pragma once

#include "Texture.h"
#include "Image.h"
#include "LatticeNoise.h"
#include "CubicNoise.h"
#include "LinearNoise.h"

class RampFBmTexture: public Texture {			
		
	public:
		
		// constructors etc ...	
		RampFBmTexture(void);										
		
		RampFBmTexture(const RampFBmTexture& texture); 			

		RampFBmTexture(Image*);

		RampFBmTexture( Image*, int, float );
				
		virtual RampFBmTexture*									
		clone(void) const;

		virtual 											
		~RampFBmTexture(void);

		Texture& 											
		operator= (const RampFBmTexture& rhs);		
		
		void set_noise(LatticeNoise*);  

		void set_perturbation(float);  
		
		//
		
		virtual RGBColor 														
		get_color(const ShadeRec& sr) const;

		void
		set_num_octaves(float num_octaves);
		
		void
		set_lacunarity(float lacunarity);

		void
		set_gain(float gain);
		
	private:
		
		Image*				ramp_ptr;			// this stores the ramp image	
		LatticeNoise*  		noise_ptr;			// supplies the value_fbm noise function
		float				perturbation;		// the amount of fbm ("a" in the book)
		int					hres;				// horizontal ramp image resolution
};

inline void 
RampFBmTexture::set_noise(LatticeNoise* n)
{
	if(noise_ptr != NULL)
	{
		delete noise_ptr;
		noise_ptr = NULL;
	}
	this->noise_ptr = n;
}

inline void 
RampFBmTexture::set_perturbation(float a)
{
	perturbation = a;
}

inline void
RampFBmTexture::set_num_octaves(float num_octaves)
{
	if(noise_ptr == NULL)
	{
		this->noise_ptr = new CubicNoise();
	}
	noise_ptr->set_num_octaves(num_octaves);
}
		
inline void
RampFBmTexture::set_lacunarity(float lacunarity)
{
	if(noise_ptr == NULL)
	{
		this->noise_ptr = new CubicNoise();
	}
	noise_ptr->set_lacunarity(lacunarity);
}

inline void
RampFBmTexture::set_gain(float gain)
{
	if(noise_ptr == NULL)
	{
		this->noise_ptr = new CubicNoise();
	}
	noise_ptr->set_gain(gain);
}
