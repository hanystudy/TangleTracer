#pragma once

// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// SmoothUVMeshTriangle is a MeshTriangle that uses smooth shading with an interpolated normal at each hit point

#include "SmoothMeshTriangle.h"

class SmoothUVMeshTriangle: public SmoothMeshTriangle {		
	public:
		
		SmoothUVMeshTriangle(void);   									
		
		SmoothUVMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);		

		virtual SmoothUVMeshTriangle* 										
		clone(void) const;
	
		SmoothUVMeshTriangle(const SmoothUVMeshTriangle& fmt); 					

		virtual
		~SmoothUVMeshTriangle(void);   									

		SmoothUVMeshTriangle& 												
		operator= (const SmoothUVMeshTriangle& rhs);
				
		virtual	bool 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const; 																	

};
