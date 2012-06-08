// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "GeometricObject.h"
#include "Normal.h"

#include "ConcavePartSphere.h"
#include "Point3D.h"
#include "Sphere.h"

//-------------------------------------------------------------------- class CutCube

class CutCube: public GeometricObject {
	
	public:
	
		CutCube(void);   												// default constructor									
						
		CutCube(const Point3D p0, const Point3D p1, const double radius);				
	
		CutCube(const CutCube& CutCube); 									// copy constructor
		
		virtual CutCube* 												// virtual copy constructor
		clone(void) const;

		CutCube& 														// assignment operator
		operator= (const CutCube& rhs);	
		
		virtual														// destructor
		~CutCube(void);   											
					
		virtual bool 																								 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		bool shadow_hit(const Ray& ray, float& tmin) const;
		
		Normal	
		CutCube::get_normal(const int face_hit) const;

		virtual BBox
		get_bounding_box(void);	//BBox needed here because CutCube has been used in Grid 

	private:

		Point3D p0;
		Point3D p1;
				
		static const double kEpsilon;   // for shadows and secondary rays

		ConcavePartSphere *sphere;
		Sphere *sp;
};
