// 	Copyright (C) Mp77 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "BeveledBoxShell.h"

#include "Instance.h"
#include "OpenCylinder.h"
#include "Box.h"
#include "Rectangle.h"
#include "BeveledCylinder.h"
#include "Sphere.h"
#include "Reflective.h"

BeveledBoxShell::BeveledBoxShell(const Point3D	bottom_,
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

	//BeveledCylinder *ocd = new BeveledCylinder(p0.y,p1.y,br,br);
	OpenCylinder *ocd = new OpenCylinder(p0.y+br,p1.y-br,br);
	
	// Here we must know that there is another box except previous twelve axis
	parts.reserve(26);
	parts.assign(26,0);

	parts[0] = new Instance(ocd);
	parts[1] =  new Instance(ocd->clone());
	parts[2] = new Instance(ocd->clone());
	parts[3] = new Instance(ocd->clone());
	
	OpenCylinder *ocd1 = new OpenCylinder(p0.x+br,p1.x-br,br);
	//BeveledCylinder *ocd1 = new BeveledCylinder(p0.x,p1.x,br,br);

	parts[4] = new Instance(ocd1->clone());
	parts[5] = new Instance(ocd1->clone());
	parts[6] = new Instance(ocd1->clone());
	parts[7] = new Instance(ocd1->clone());
	
	//BeveledCylinder *ocd2 = new BeveledCylinder(p0.z,p1.z,br,br);
	OpenCylinder *ocd2 = new OpenCylinder(p0.z+br,p1.z-br,br);
	parts[8] = new Instance(ocd2->clone());
	parts[9] = new Instance(ocd2->clone());
	parts[10] = new Instance(ocd2->clone());
	parts[11] = new Instance(ocd2->clone());
	
	//Here add a box
	parts[12] = new Instance(new TRectangle( Point3D( -length/2+br,-height/2+br, width/2 ), Vector3D( length - 2 * br, 0, 0 ), Vector3D(  0, height - 2 * br, 0 ), Normal(0, 0, 1) ));
	parts[13] = new Instance(new TRectangle( Point3D( length/2,-height/2+br, width/2-br), Vector3D( 0, 0, - width + 2 * br ), Vector3D(  0, height - 2 * br, 0 ), Normal(1, 0, 0) ));
	parts[14] = new Instance(new TRectangle( Point3D( length/2-br,-height/2+br, -width/2), Vector3D( - length + 2 * br, 0, 0 ), Vector3D( 0, height - 2 * br, 0 ), Normal(0, 0, -1) ));
	parts[15] = new Instance(new TRectangle( Point3D( -length/2, -height/2+br, -width/2+br), Vector3D( 0, 0, width - 2 * br ), Vector3D(  0, height - 2 * br, 0 ), Normal(-1, 0, 0) ));
	parts[16] = new Instance(new TRectangle( Point3D( -length/2+br,height/2, width/2-br), Vector3D( length - 2 * br, 0, 0 ), Vector3D(  0, 0, -width + 2 * br ), Normal(0, 1, 0) ));
	parts[17] = new Instance(new TRectangle( Point3D( -length/2+br,-height/2, -width/2+br), Vector3D( length - 2 * br, 0, 0 ), Vector3D(  0, 0, width - 2 * br ), Normal(0, -1, 0) ));
		
	parts[18] = new Instance(new Sphere( Point3D( -length/2+br,height/2-br, width/2-br ), br ));
	parts[19] = new Instance(new Sphere( Point3D( length/2-br,height/2-br, width/2-br ), br ));
	parts[20] = new Instance(new Sphere( Point3D( length/2-br,height/2-br, -width/2+br ), br ));
	parts[21] = new Instance(new Sphere( Point3D( -length/2+br,height/2-br, -width/2+br ), br ));
	parts[22] = new Instance(new Sphere( Point3D( -length/2+br,-height/2+br, width/2-br ), br ));
	parts[23] = new Instance(new Sphere( Point3D( length/2-br,-height/2+br, width/2-br ), br ));
	parts[24] = new Instance(new Sphere( Point3D( length/2-br,-height/2+br, -width/2+br ), br ));
	parts[25] = new Instance(new Sphere( Point3D( -length/2+br,-height/2+br, -width/2+br ), br ));

	parts[0]->translate(-length/2+br,0,-width/2+br);
	parts[1]->translate(-length/2+br,0,width/2-br);
	parts[2]->translate(length/2-br,0,width/2-br);
	parts[3]->translate(length/2-br,0,-width/2+br);
	
	parts[4]->translate(0,-(p0.x + p1.x)/2,0);
	parts[4]->rotate_z(90);
	parts[4]->translate(0,height/2-br,width/2-br);
	parts[5]->translate(0,-(p0.x + p1.x)/2,0);
	parts[5]->rotate_z(90);
	parts[5]->translate(0,-height/2+br,width/2-br);
	parts[6]->translate(0,-(p0.x + p1.x)/2,0);
	parts[6]->rotate_z(90);
	parts[6]->translate(0,-height/2+br,-width/2+br);
	parts[7]->translate(0,-(p0.x + p1.x)/2,0);
	parts[7]->rotate_z(90);
	parts[7]->translate(0,height/2-br,-width/2+br);

	parts[8]->translate(0,-(p0.z + p1.z)/2,0);
	parts[8]->rotate_x(90);
	parts[8]->translate(-length/2+br,height/2-br,0);
	parts[9]->translate(0,-(p0.z + p1.z)/2,0);
	parts[9]->rotate_x(90);
	parts[9]->translate(-length/2+br,-height/2+br,0);
	parts[10]->translate(0,-(p0.z + p1.z)/2,0);
	parts[10]->rotate_x(90);
	parts[10]->translate(length/2-br,-height/2+br,0);
	parts[11]->translate(0,-(p0.z + p1.z)/2,0);
	parts[11]->rotate_x(90);
	parts[11]->translate(length/2-br,height/2-br,0);

	bbox.x0 = p0.x - bevel_radius;
	bbox.y0 = p0.y - bevel_radius;
	bbox.z0 = p0.z - bevel_radius;
	bbox.x1 = p1.x + bevel_radius;
	bbox.y1 = p1.y + bevel_radius;
	bbox.z1 = p1.z + bevel_radius;

	// The code below only works for 24.29d, which can replace the outer material set by others with random reflective materials
	set_rand_seed(1000);
	float c = 0.25;
		
	for (int j = 0; j < parts.size(); j++) {
		Reflective* reflective_ptr = new Reflective;			
		reflective_ptr->set_ka(0.0); 
		reflective_ptr->set_kd(0.0);
		reflective_ptr->set_ks(0.0);
		reflective_ptr->set_cd(0.0);
		reflective_ptr->set_kr(0.9);
		reflective_ptr->set_cr(1.0, 0.75 + c * (-1.0 + 2.0 * rand_float()) , 0.25 + c * (-1.0 + 2.0 * rand_float()));		
		parts[j]->set_material(reflective_ptr);
	}
}

// ----------------------------------------------------------------  default constructor

BeveledBoxShell::BeveledBoxShell (void)
	: 	Compound()
{}


// ---------------------------------------------------------------- clone

BeveledBoxShell* 
BeveledBoxShell::clone(void) const {
	return (new BeveledBoxShell(*this));
}


// ---------------------------------------------------------------- copy constructor

BeveledBoxShell::BeveledBoxShell (const BeveledBoxShell& c)
	:	Compound(c),
		p0(c.p0),
		p1(c.p1),
		br(c.br) {
	
		copy_objects(c.parts);					
}



// ---------------------------------------------------------------- assignment operator

BeveledBoxShell& 
BeveledBoxShell::operator= (const BeveledBoxShell& rhs) {
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

BeveledBoxShell::~BeveledBoxShell(void) {	
	delete_objects();				
}


//------------------------------------------------------------------ set_material
// sets the same material on all objects

void 
BeveledBoxShell::set_material(Material* material_ptr) {
	int num_objects = parts.size();

	for (int j = 0; j < num_objects; j++)
		parts[j]->set_material(material_ptr);
}


//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty 

void
BeveledBoxShell::delete_objects(void) {
	int num_objects = parts.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete parts[j];
		parts[j] = NULL;
	}	
	
	parts.erase(parts.begin(), parts.end());
}


//------------------------------------------------------------------ copy_objects

void
BeveledBoxShell::copy_objects(const vector<Instance*>& rhs_ojects) {
	delete_objects();    	
	int num_objects = rhs_ojects.size();
	
	for (int j = 0; j < num_objects; j++)
		parts.push_back(rhs_ojects[j]->clone());


}


//------------------------------------------------------------------ hit
//This function has been modified since Listing 8.22

bool 															 
BeveledBoxShell::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
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
BeveledBoxShell::shadow_hit(const Ray& ray, float& tmin) const
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
