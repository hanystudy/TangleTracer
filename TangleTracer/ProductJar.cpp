// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "ProductJar.h"

#include "OpenCylinder.h"
#include "Instance.h"
#include "Torus.h"

ProductJar::ProductJar(	const double bottom, 
								const double top, 
								const double radius)
			: Compound() {
}

// ----------------------------------------------------------------  default constructor

ProductJar::ProductJar (void)
	: 	Compound()
{
}


// ---------------------------------------------------------------- new constructor


ProductJar::ProductJar(const double bottom, const double body_top, const double cap_top, const double body_radius, const double bottom_bevel_radius, const double top_bevel_radius, const double cap_bevel_radius)
{
	/*
		bottom
		body_top
		cap_top
		body_radius
		bottom_bevel_radius
		top_bevel_radius
		cap_bevel_radius
		product_jar_ptr->set_material(matte_ptr);
		product_jar_ptr->set_body_material(body_matte_ptr);		// renders vertical body surface red
		*/
	this->body_top = body_top - top_bevel_radius;
	this->body_bottom = bottom + bottom_bevel_radius;

	objects.push_back(new OpenCylinder(bottom+bottom_bevel_radius, body_top-top_bevel_radius, body_radius));	// wall
	
	Instance* top_torus_ptr = new Instance(new Torus(body_radius - top_bevel_radius, top_bevel_radius));
	top_torus_ptr->translate(0, body_top - top_bevel_radius, 0);
	top_torus_ptr->transform_texture(false);        
	objects.push_back(top_torus_ptr);

	Instance* bottom_torus_ptr = new Instance(new Torus(body_radius - bottom_bevel_radius, bottom_bevel_radius));
	bottom_torus_ptr->translate(0, bottom_bevel_radius, 0);
	bottom_torus_ptr->transform_texture(false);        
	objects.push_back(bottom_torus_ptr);

	objects.push_back(new OpenCylinder(bottom+body_top, cap_top-cap_bevel_radius, body_radius-top_bevel_radius));	// wall

	Instance* cap_torus_ptr = new Instance(new Torus(body_radius-top_bevel_radius-cap_bevel_radius, cap_bevel_radius));
	cap_torus_ptr->translate(0, cap_top-cap_bevel_radius, 0);
	cap_torus_ptr->transform_texture(false);        
	objects.push_back(cap_torus_ptr);

	objects.push_back(new Disk(	Point3D(0, bottom, 0), 			// bottom
								Normal(0, -1, 0), 
								body_radius - bottom_bevel_radius));  

	objects.push_back(new Disk(	Point3D(0, cap_top, 0), 			// bottom
								Normal(0, 1, 0), 
								body_radius-top_bevel_radius-cap_bevel_radius));  
	
	bbox.x0 = -body_radius;
	bbox.y0 = bottom;
	bbox.z0 = -body_radius;
	bbox.x1 = body_radius;
	bbox.y1 = cap_top;
	bbox.z1 = body_radius;
}

// ---------------------------------------------------------------- clone

ProductJar* 
ProductJar::clone(void) const {
	return (new ProductJar(*this));
}


// ---------------------------------------------------------------- copy constructor

ProductJar::ProductJar (const ProductJar& c)
	: Compound(c) {
	
	copy_objects(c.objects);					
}



// ---------------------------------------------------------------- assignment operator

ProductJar& 
ProductJar::operator= (const ProductJar& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);						
	
	copy_objects(rhs.objects);				

	return (*this);
}


// ---------------------------------------------------------------- destructor

ProductJar::~ProductJar(void) {	
	delete_objects();				
}


//------------------------------------------------------------------ set_material
// sets the same material on all objects

void 
ProductJar::set_material(Material* material_ptr) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		objects[j]->set_material(material_ptr);
}


//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty 

void
ProductJar::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase(objects.begin(), objects.end());
}


//------------------------------------------------------------------ copy_objects

void
ProductJar::copy_objects(const vector<GeometricObject*>& rhs_ojects) {
	delete_objects();    	
	int num_objects = rhs_ojects.size();
	
	for (int j = 0; j < num_objects; j++)
		objects.push_back(rhs_ojects[j]->clone());
}


//------------------------------------------------------------------ hit

bool 															 
ProductJar::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
	{
		bool b;
		b= Compound::hit(ray, tmin, sr);
		if ( b && sr.local_hit_point.y >= body_bottom && sr.local_hit_point.y <= body_top )
		{
			sr.local_hit_point.y = (sr.local_hit_point.y - body_bottom) / ( body_top - body_bottom );
		}
		return b;
	}
	else
		return (false);
}

// ------------------------------------------------- shadow hit

bool 																						 
ProductJar::shadow_hit(const Ray& ray, float& tmin) const
{
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
}

void 
ProductJar::set_body_material(Material* material_ptr)
{
	objects[0]->set_material(material_ptr);
}

BBox 
ProductJar::get_bounding_box(void)
{
	return bbox;
}