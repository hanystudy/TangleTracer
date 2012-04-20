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
{}


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