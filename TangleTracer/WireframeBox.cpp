// 	Copyright (C) Mp77 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "WireframeBox.h"

#include "Instance.h"
#include "OpenCylinder.h"

WireframeBox::WireframeBox(const Point3D	bottom_,
							const Point3D 	top_,
							const float	bevel_radius
									)
			: Compound(),
			p0(bottom_),
			p1(top_),
			br(bevel_radius){
		
	double width = p1.z - p0.z;
	double length = p1.x - p0.x;
	double height = p1.y - p0.y;

	OpenCylinder *ocd = new OpenCylinder(p0.y,p1.y,br);
	
	parts.reserve(12);
	parts.assign(12,0);

	parts[0] = new Instance(ocd);
	parts[1] =  new Instance(ocd->clone());
	parts[2] = new Instance(ocd->clone());
	parts[3] = new Instance(ocd->clone());
	parts[4] = new Instance(ocd->clone());
	parts[5] = new Instance(ocd->clone());
	parts[6] = new Instance(ocd->clone());
	parts[7] = new Instance(ocd->clone());
	parts[8] = new Instance(ocd->clone());
	parts[9] = new Instance(ocd->clone());
	parts[10] = new Instance(ocd->clone());
	parts[11] = new Instance(ocd->clone());

	
	parts[0]->translate(-width/2+br/2,0,-length/2);
	parts[1]->translate(-width/2+br/2,0,length/2);
	parts[2]->translate(width/2-br/2,0,length/2);
	parts[3]->translate(width/2-br/2,0,-length/2);
	
	parts[4]->translate(0,-(p0.y + p1.y)/2,0);
	parts[4]->rotate_z(90);
	parts[4]->translate(0,height/2-br/2,width/2);
	parts[5]->translate(0,-(p0.y + p1.y)/2,0);
	parts[5]->rotate_z(90);
	parts[5]->translate(0,-height/2+br/2,width/2);
	parts[6]->translate(0,-(p0.y + p1.y)/2,0);
	parts[6]->rotate_z(90);
	parts[6]->translate(0,-height/2+br/2,-width/2);
	parts[7]->translate(0,-(p0.y + p1.y)/2,0);
	parts[7]->rotate_z(90);
	parts[7]->translate(0,height/2-br/2,-width/2);

	parts[8]->translate(0,-(p0.y + p1.y)/2,0);
	parts[8]->rotate_x(90);
	parts[8]->translate(-length/2+br/2,height/2-br/2,0);
	parts[9]->translate(0,-(p0.y + p1.y)/2,0);
	parts[9]->rotate_x(90);
	parts[9]->translate(-length/2+br/2,-height/2+br/2,0);
	parts[10]->translate(0,-(p0.y + p1.y)/2,0);
	parts[10]->rotate_x(90);
	parts[10]->translate(length/2-br/2,-height/2+br/2,0);
	parts[11]->translate(0,-(p0.y + p1.y)/2,0);
	parts[11]->rotate_x(90);
	parts[11]->translate(length/2-br/2,height/2-br/2,0);

	bbox.x0 = p0.x - bevel_radius;
	bbox.y0 = p0.y - bevel_radius;
	bbox.z0 = p0.z - bevel_radius;
	bbox.x1 = p1.x + bevel_radius;
	bbox.y1 = p1.y + bevel_radius;
	bbox.z1 = p1.z + bevel_radius;
}

// ----------------------------------------------------------------  default constructor

WireframeBox::WireframeBox (void)
	: 	Compound()
{}


// ---------------------------------------------------------------- clone

WireframeBox* 
WireframeBox::clone(void) const {
	return (new WireframeBox(*this));
}


// ---------------------------------------------------------------- copy constructor

WireframeBox::WireframeBox (const WireframeBox& c)
	:	Compound(c),
		p0(c.p0),
		p1(c.p1),
		br(c.br) {
	
		copy_objects(c.parts);					
}



// ---------------------------------------------------------------- assignment operator

WireframeBox& 
WireframeBox::operator= (const WireframeBox& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);						
	
	copy_objects(rhs.parts);

	this->p0 = rhs.p0;
	this->p1 = rhs.p1;
	this->br = rhs.br;

	return (*this);
}


// ---------------------------------------------------------------- destructor

WireframeBox::~WireframeBox(void) {	
	delete_objects();				
}


//------------------------------------------------------------------ set_material
// sets the same material on all objects

void 
WireframeBox::set_material(Material* material_ptr) {
	int num_objects = parts.size();

	for (int j = 0; j < num_objects; j++)
		parts[j]->set_material(material_ptr);
}


//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty 

void
WireframeBox::delete_objects(void) {
	int num_objects = parts.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete parts[j];
		parts[j] = NULL;
	}	
	
	parts.erase(parts.begin(), parts.end());
}


//------------------------------------------------------------------ copy_objects

void
WireframeBox::copy_objects(const vector<Instance*>& rhs_ojects) {
	delete_objects();    	
	int num_objects = rhs_ojects.size();
	
	for (int j = 0; j < num_objects; j++)
		parts.push_back(rhs_ojects[j]->clone());


}


//------------------------------------------------------------------ hit
//This function has been modified since Listing 8.22

bool 															 
WireframeBox::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
	{
		double		t; 
		Normal		normal;
		Point3D		local_hit_point;
		bool		hit 		= false;
					tmin 		= kHugeValue;
		int 		num_objects	= parts.size();
	
		for (int j = 0; j < num_objects; j++)
			if (parts[j]->hit(ray, t, sr) && (t < tmin)) {
				hit				= true;
				tmin 			= t;
				material_ptr	= parts[j]->get_material();	// lhs is GeometricObject::material_ptr
				normal			= sr.normal;
				local_hit_point	= sr.local_hit_point;  
			}
	
		if (hit) {
			sr.t				= tmin;
			sr.normal 			= normal;   
			sr.local_hit_point 	= local_hit_point;  
		}	
		return (hit);
	}
	else
		return (false);
}

// ------------------------------------------------- shadow hit
//This function has been modified since Listing 8.22

bool 																						 
WireframeBox::shadow_hit(const Ray& ray, float& tmin) const
{
	if (bbox.hit(ray))
	{
		float		t = 100000;		// may be important too 
		Normal		normal;
		Point3D		local_hit_point;
		bool		hit 		= false;
		int 		num_objects	= parts.size();
	
		for (int j = 0; j < num_objects; j++)
			if (parts[j]->shadow_hit(ray, t) && (t < tmin)) {
				hit				= true;
				tmin 			= t;
			}
		return (hit);
	}
	else
		return (false);
}
