// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Vector3D.h"
#include "RGBColor.h"
#include "Ray.h"

class ShadeRec;


//-------------------------------------------------------------------- class Light

class Light {	
public:
	
	Light(void);
								
	Light(const Light& ls);			

	Light& 								
	operator= (const Light& rhs); 

	virtual Light* 						
	clone(void) const = 0;
		
	virtual 							
	~Light(void);
						
	virtual Vector3D								
	get_direction(ShadeRec& sr) = 0;				
																
	virtual RGBColor														
	L(ShadeRec& sr);

	bool
	casts_shadows();

	void
	set_shadows(bool);

	virtual bool									
	in_shadow(const Ray& ray, const ShadeRec& sr) const = 0;	//virtual must be added

	virtual float
	G(const ShadeRec& sr) const;
		
	virtual float									
	pdf(ShadeRec& sr) const;

protected:
	bool shadows;
};
