#pragma once

// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// FlatUVMeshTriangle is a MeshTriangle that uses smooth shading with an interpolated normal at each hit point

#include "FlatMeshTriangle.h"

class FlatUVMeshTriangle: public FlatMeshTriangle {		
	public:
		
		FlatUVMeshTriangle(void);   									
		
		FlatUVMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);		

		virtual FlatUVMeshTriangle* 										
		clone(void) const;
	
		FlatUVMeshTriangle(const FlatUVMeshTriangle& fmt); 					

		virtual
		~FlatUVMeshTriangle(void);   									

		FlatUVMeshTriangle& 												
		operator= (const FlatUVMeshTriangle& rhs);
				
		virtual	bool 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const; 																	

};
