#pragma once
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Sampler.h"
#include "GeometricObject.h"

class TRectangle: public GeometricObject {	
	public:
		
		TRectangle(void);   									
				
		TRectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);
		
		TRectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n);
		
		virtual GeometricObject* 										
		clone(void) const;
	
		TRectangle(const TRectangle& r); 						

		virtual													
		~TRectangle(void);   									

		GeometricObject& 												
		operator= (const TRectangle& rhs);
		
		BBox
		get_bounding_box(void);				
	
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const;	
				
		
		// the following functions are used when the TRectangle is a light source
		
		virtual void 								
		set_sampler(Sampler* sampler); 
				
		virtual Point3D 											
		sample(void);
		
		virtual Normal 																
		get_normal(const Point3D& p);		
		
		virtual float												
		pdf(ShadeRec& sr);

		bool shadow_hit(const Ray& ray, float& tmin) const;
		
		virtual void									
		set_shadows(bool);
	private:
	
		Point3D 		p0;   			// corner vertex 
		Vector3D		a;				// side
		Vector3D		b;				// side
		double			a_len_squared;	// square of the length of side a
		double			b_len_squared;	// square of the length of side b
		Normal			normal;	
		
		float			area;			// for rectangular lights
		float			inv_area;		// for rectangular lights
		Sampler*		sampler_ptr;	// for rectangular lights 	
		
		static const double kEpsilon;   	

		bool shadows;					// for cornell box only
};
