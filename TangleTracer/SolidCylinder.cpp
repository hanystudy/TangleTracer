// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "SolidCylinder.h"

#include "OpenCylinder.h"

SolidCylinder::SolidCylinder(	const double bottom, 
								const double top, 
								const double radius)
			: Compound() {
		
	objects.push_back(new Disk(	Point3D(0, bottom, 0), 			// bottom
								Normal(0, -1, 0), 
								radius));  
		
	objects.push_back(new Disk(	Point3D(0, top, 0), 			// top
								Normal(0, 1, 0), 
								radius));   	
		
	objects.push_back(new OpenCylinder(bottom, top, radius));	// wall

	bbox.x0 = -radius;
	bbox.y0 = bottom;
	bbox.z0 = -radius;
	bbox.x1 = radius;
	bbox.y1 = top;
	bbox.z1 = radius;
}

// ----------------------------------------------------------------  default constructor

SolidCylinder::SolidCylinder (void)
	: 	Compound()
{
	//This is new function for chapter 30 for any diffault para solid cylinders. Ex 30.12
	objects.push_back(new Disk(	Point3D(0, -1, 0), 			// bottom
								Normal(0, -1, 0), 
								1));  
		
	objects.push_back(new Disk(	Point3D(0, 1, 0), 			// top
								Normal(0, 1, 0), 
								1));   	
		
	objects.push_back(new OpenCylinder(-1, 1, 1));	// wall

	bbox.x0 = -1;
	bbox.y0 = -1;
	bbox.z0 = -1;
	bbox.x1 = 1;
	bbox.y1 = 1;
	bbox.z1 = 1;
}


// ---------------------------------------------------------------- clone

SolidCylinder* 
SolidCylinder::clone(void) const {
	return (new SolidCylinder(*this));
}


// ---------------------------------------------------------------- copy constructor

SolidCylinder::SolidCylinder (const SolidCylinder& c)
	: Compound(c) {
	
	copy_objects(c.objects);					
}



// ---------------------------------------------------------------- assignment operator

SolidCylinder& 
SolidCylinder::operator= (const SolidCylinder& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);						
	
	copy_objects(rhs.objects);				

	return (*this);
}


// ---------------------------------------------------------------- destructor

SolidCylinder::~SolidCylinder(void) {	
	delete_objects();				
}


//------------------------------------------------------------------ set_material
// sets the same material on all objects

void 
SolidCylinder::set_material(Material* material_ptr) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		objects[j]->set_material(material_ptr);
}


//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty 

void
SolidCylinder::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase(objects.begin(), objects.end());
}


//------------------------------------------------------------------ copy_objects

void
SolidCylinder::copy_objects(const vector<GeometricObject*>& rhs_ojects) {
	delete_objects();    	
	int num_objects = rhs_ojects.size();
	
	for (int j = 0; j < num_objects; j++)
		objects.push_back(rhs_ojects[j]->clone());
}


//------------------------------------------------------------------ hit

bool 															 
SolidCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

// ------------------------------------------------- shadow hit

bool 																						 
SolidCylinder::shadow_hit(const Ray& ray, float& tmin) const
{
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
}

void 
SolidCylinder::set_bottom_material(Material* material_ptr)
{
	objects[0]->set_material(material_ptr);
}	//19.29

void 
SolidCylinder::set_top_material(Material* material_ptr)
{
	objects[1]->set_material(material_ptr);
}	//19.29

void 
SolidCylinder::set_wall_material(Material* material_ptr)
{
	objects[2]->set_material(material_ptr);
}//19.29

BBox 
SolidCylinder::get_bounding_box(void)
{
	return bbox;
}