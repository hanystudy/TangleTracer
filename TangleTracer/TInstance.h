// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Texture.h"
#include "Constants.h"

class TInstance: public Texture {	
	public:
		
		TInstance(void);										
		
		TInstance(const TInstance& sc);
		
		TInstance(Texture *t);

		TInstance& 												
		operator= (const TInstance& rhs);		

		virtual TInstance*							
		clone(void) const;				

		~TInstance(void);
		// constructors etc
	
		void 							
		set_texture(Texture* t_ptr);	
	
		virtual RGBColor
		get_color(const ShadeRec& sr) const;
	
		// affine tranformation functions:
	
		void												
		scale(const double sx, const double sy, const double sz);	

		void
		scale(const double x);
	
		// other affine transformations ...
	
		// affine tranformation functions
		
		void												
		translate(const Vector3D& trans);
		
		void
		translate(const double dx, const double dy, const double dz);	
		
		virtual void										
		rotate_x(const double r);
		
		virtual void										
		rotate_y(const double r);
		
		virtual void										
		rotate_z(const double r);
		
		void												
		shear(const Matrix& m);
	private:
	
		Texture* 	texture_ptr;	// texture being transformed
		Matrix		inv_matrix;		// inverse transformation matrix
};

inline void
TInstance::set_texture(Texture* t_ptr)
{
	texture_ptr = t_ptr;
}
