// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// A mesh object stores the data for mesh triangles:
//
//			vertices
//			normals
//			uv texture coordinates
//			lists of triangles that share each vertex
//
// Mesh triangles are stored in a grid, which has a pointer to the mesh
// Each mesh triangle also has a pointer to the mesh
// The Mesh class does not inherit from GeometricObject

#pragma once

#include <vector>

#include "Point3D.h"
#include "Normal.h"

using namespace std;
	
class Mesh {										  	
	public:

		vector<Point3D> 		vertices;				// mesh vertices 
		vector<Normal> 			normals;				// average normal at each vertex;
		vector<float>			u;						// u texture coordinate at each vertex
		vector<float>			v;						// v texture coordinate at each vertex
		vector<vector<int> > 	vertex_faces;			// the triangles shared by each vertex
		int 					num_vertices; 			// number of vertices
		int 					num_triangles; 			// number of triangles
		
		Mesh(void);   								
			
		Mesh(const Mesh& m); 						

		~Mesh(void);   							

		Mesh& 										
		operator= (const Mesh& rhs);
};
