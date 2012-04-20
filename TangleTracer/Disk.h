#pragma once

#include "GeometricObject.h"
#include "Normal.h"

#include "Sampler.h"

//-------------------------------------------------------------------- class Disk

class Disk: public GeometricObject {
	
	public:
	
		Disk(void);   												// default constructor
		
		Disk(const Point3D& point, const Normal& normal, double radius);			// constructor	
	
		Disk(const Disk& Disk); 									// copy constructor
		
		virtual GeometricObject* 												// virtual copy constructor
		clone(void) const;

		Disk& 														// assignment operator
		operator= (const Disk& rhs);	
		
		virtual														// destructor
		~Disk(void);   											
					
		virtual bool 																								 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		bool shadow_hit(const Ray& ray, float& tmin) const;
		

		//functions below only work in chapter 18.05
		virtual void								
		set_sampler(Sampler*s);
		
		virtual void									
		set_shadows(bool);

		virtual void									
		compute_uvw(void);

		virtual Point3D 		
		sample(void);
		
		virtual float
		pdf(ShadeRec& sr);
		
		virtual Normal
		get_normal(void) const; 

		virtual Normal
		get_normal(const Point3D&);

	private:
	
		Point3D 	center;   				// point through which Disk passes 
		Normal 		normal;					// normal to the Disk
		double r_squared;
		double r;
				
		static const double kEpsilon;   // for shadows and secondary rays

		Sampler *sampler_ptr;
		bool shadows;
		
		float			area;			// for disk lights
		float			inv_area;		// for disk lights
		Vector3D u,v,w;
};
