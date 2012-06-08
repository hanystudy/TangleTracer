// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include <vector> 
#include "GeometricObject.h"

using namespace std;

//-------------------------------------------------------------------------------- class Compound

class Compound: public GeometricObject {	
	public:
		
		Compound(void);   										

		virtual Compound* 										
		clone(void) const;
	
		Compound(const Compound& c); 							

		~Compound (void);   									

		Compound& 												
		operator= (const Compound& c);	
		
		virtual void 
		set_material(Material* material_ptr);
		
		virtual void 											
		add_object(GeometricObject* object_ptr);  
		
		int
		get_num_objects(void);						

		virtual bool 															 
		hit(const Ray& ray, double& tmin, ShadeRec& s) const;

		virtual bool 																						 
		shadow_hit(const Ray& ray, float& tmin) const;
			
	protected:		
		
		vector<GeometricObject*> objects;
		
	private:
	
		void 													
		delete_objects(void);								

		void												
		copy_objects(const vector<GeometricObject*>& rhs_objects);
	
};


// ------------------------------------------------------------------------------- get_num_objects

inline int
Compound::get_num_objects(void) {
	return (objects.size());
}
