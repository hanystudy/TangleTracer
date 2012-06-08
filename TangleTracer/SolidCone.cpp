// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "SolidCone.h"

// This uses the value of kEpsilon defined in Constants.h

// ---------------------------------------------------------------- default constructor

SolidCone::SolidCone(void)
	: 	Compound()
{
	objects.push_back(new OpenCone(	1, 2 ));  
		
	objects.push_back(new Disk(	Point3D(0, 0, 0), 			// top
								Normal(0, -1, 0), 
								1));

	bbox.x0 = -1;
	bbox.y0 = 0;
	bbox.z0 = -1;
	bbox.x1 = 1;
	bbox.y1 = 2;
	bbox.z1 = 1;
}

// ---------------------------------------------------------------- constructor

SolidCone::SolidCone(const double r, const double h)
	:  	Compound()
{
	objects.push_back(new OpenCone(	r, h ));  
		
	objects.push_back(new Disk(	Point3D(0, 0, 0), 			// top
								Normal(0, -1, 0), 
								r));

	bbox.x0 = -r;
	bbox.y0 = 0;
	bbox.z0 = -r;
	bbox.x1 = r;
	bbox.y1 = h;
	bbox.z1 = r;
}


// ---------------------------------------------------------------- copy constructor

SolidCone::SolidCone(const SolidCone& c)
	: 	Compound(c)	
{
	copy_objects(c.objects);
}
																				
																				
// ---------------------------------------------------------------- clone

SolidCone* 
SolidCone::clone(void) const {
	return (new SolidCone (*this));
}

//------------------------------------------------------------------ set_material
// sets the same material on all objects

void 
SolidCone::set_material(Material* material_ptr) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		objects[j]->set_material(material_ptr);
}


//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty 

void
SolidCone::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase(objects.begin(), objects.end());
}


//------------------------------------------------------------------ copy_objects

void
SolidCone::copy_objects(const vector<GeometricObject*>& rhs_ojects) {
	delete_objects();    	
	int num_objects = rhs_ojects.size();
	
	for (int j = 0; j < num_objects; j++)
		objects.push_back(rhs_ojects[j]->clone());
}


//------------------------------------------------------------------ hit

bool 															 
SolidCone::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

// ------------------------------------------------- shadow hit

bool 																						 
SolidCone::shadow_hit(const Ray& ray, float& tmin) const
{
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
}

BBox 
SolidCone::get_bounding_box(void)
{
	return bbox;
}																																	

// ---------------------------------------------------------------- assignment operator

SolidCone& 
SolidCone::operator= (const SolidCone& rhs) 		
{
	if (this == &rhs)
		return (*this);

	
	GeometricObject::operator= (rhs);						
	
	copy_objects(rhs.objects);	

	return (*this) ;
}


// ---------------------------------------------------------------- destructor

SolidCone::~SolidCone(void) {

	delete_objects();	
}

