#include "BeveledCylinder.h"

#include "Instance.h"
#include "OpenCylinder.h"
#include "Torus.h"

BeveledCylinder::BeveledCylinder(	const double	bottom_,
									const double 	top_, 
									const double 	radius, 
									const double	bevel_radius
									)
			: Compound(),
			bottom(bottom_),
			top(top_),
			r(radius),
			br(bevel_radius){
		
		// construct the bottom, top, and curved surface
	
	objects.push_back(new Disk(Point3D(0, bottom, 0), Normal(0, -1, 0), r - br));  	// bottom
	objects.push_back(new Disk(Point3D(0, top, 0), Normal(0, 1, 0), r - br));   	// top
	objects.push_back(new OpenCylinder(bottom + br, top - br, r));   		  	// curved surface
	
	// have to use instances for the tori because they have to be translated
	
	Instance* bottom_torus_ptr = new Instance(new Torus(r - br, br));
	bottom_torus_ptr->translate(0, bottom + br, 0);
	bottom_torus_ptr->transform_texture(false);        
	objects.push_back(bottom_torus_ptr);
	
	Instance* top_torus_ptr = new Instance(new Torus(r - br, br));
	top_torus_ptr->translate(0, top  - br, 0);
	top_torus_ptr->transform_texture(false);	
	objects.push_back(top_torus_ptr);

	bbox.x0 = -radius;
	bbox.y0 = bottom;
	bbox.z0 = -radius;
	bbox.x1 = radius;
	bbox.y1 = top;
	bbox.z1 = radius;
}

// ----------------------------------------------------------------  default constructor

BeveledCylinder::BeveledCylinder (void)
	: 	Compound()
{}


// ---------------------------------------------------------------- clone

BeveledCylinder* 
BeveledCylinder::clone(void) const {
	return (new BeveledCylinder(*this));
}


// ---------------------------------------------------------------- copy constructor

BeveledCylinder::BeveledCylinder (const BeveledCylinder& c)
	:	Compound(c),
		bottom(0),
		top(0),
		r(0),
		br(0) {
	
	copy_objects(c.objects);					
}



// ---------------------------------------------------------------- assignment operator

BeveledCylinder& 
BeveledCylinder::operator= (const BeveledCylinder& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);						
	
	copy_objects(rhs.objects);

	this->bottom = rhs.bottom;
	this->top = rhs.top;
	this->r = rhs.r;
	this->br = rhs.br;

	return (*this);
}


// ---------------------------------------------------------------- destructor

BeveledCylinder::~BeveledCylinder(void) {	
	delete_objects();				
}


//------------------------------------------------------------------ set_material
// sets the same material on all objects

void 
BeveledCylinder::set_material(Material* material_ptr) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		objects[j]->set_material(material_ptr);
}


//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty 

void
BeveledCylinder::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase(objects.begin(), objects.end());
}


//------------------------------------------------------------------ copy_objects

void
BeveledCylinder::copy_objects(const vector<GeometricObject*>& rhs_ojects) {
	delete_objects();    	
	int num_objects = rhs_ojects.size();
	
	for (int j = 0; j < num_objects; j++)
		objects.push_back(rhs_ojects[j]->clone());
}


//------------------------------------------------------------------ hit

bool 															 
BeveledCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

// ------------------------------------------------- shadow hit

bool 																						 
BeveledCylinder::shadow_hit(const Ray& ray, float& tmin) const
{
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
}

void 
BeveledCylinder::set_bottom_material(Material* material_ptr)
{
	objects[0]->set_material(material_ptr);
}	//19.29

void 
BeveledCylinder::set_top_material(Material* material_ptr)
{
	objects[1]->set_material(material_ptr);
}	//19.29

void 
BeveledCylinder::set_wall_material(Material* material_ptr)
{
	objects[2]->set_material(material_ptr);
}//19.29
