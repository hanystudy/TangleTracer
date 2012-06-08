// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the definition of the class LightProbeMap
// This class inherits from Mapping, and defines a default spherical mapping
// Here, an image with an aspect ratio of 2:1 is mapped onto a sphere so
// that it just covers the whole sphere

#pragma once

#include "Constants.h"
#include "Mapping.h"

typedef enum {
	light_probe, 
	panoramic
} MapType;

class LightProbeMap: public Mapping {		
	public:
	
		LightProbeMap(void);									
		
		LightProbeMap(const LightProbeMap& sm);					

		LightProbeMap& 											
		operator= (const LightProbeMap& rhs);		

		virtual LightProbeMap*									
		clone(void) const;				

		~LightProbeMap(void);									
		
		virtual void
		get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
								const 	int 		xres, 
								const 	int 		yres, 
										int& 		row, 
										int& 		column) const;


		void set_map_type(MapType);

	private:
	
		MapType map_type;

};

inline void
LightProbeMap::set_map_type(MapType m)
{
	this->map_type = m;
}