// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "AnotherRosette.h"
#include "BeveledWedge.h"

const int AnotherRosette::num_wedges[6] = {10, 12, 15, 18, 24, 36};  // these numbers exactly divide into 360

// ------------------------------------------------------------------------------ default constructor

AnotherRosette::AnotherRosette(void)
			:	Grid(),
				num_rings(1), 
				hole_radius(1.0),
				ring_width(1.0),
				rb(0.25),
				y0(-1.0),
				y1(1.0)
{
	construct_rosette();
}


// ------------------------------------------------------------------------------ constructor

AnotherRosette::AnotherRosette(	const int 	_num_rings, 
					const double	_hole_radius,
					const double _ring_width,
					const double _rb,
					const double _y0,
					const double _y1)

	:	Grid(),
		num_rings(_num_rings), 
		hole_radius(_hole_radius),
		ring_width(_ring_width),
		rb(_rb),
		y0(_y0),
		y1(_y1)
{
	construct_rosette();
}	

	
// ------------------------------------------------------------------------------ copy constructor

AnotherRosette::AnotherRosette(const AnotherRosette& r)  			
			: 	Grid(r),
				num_rings(r.num_rings), 
				hole_radius(r.hole_radius),
				ring_width(r.ring_width),
				rb(r.rb),
				y0(r.y0),
				y1(r.y1)
{}

// ------------------------------------------------------------------------------ clone

AnotherRosette* 
AnotherRosette::clone(void) const {
	return(new AnotherRosette(*this));
}


// ------------------------------------------------------------------------------ assignment operator

AnotherRosette& 
AnotherRosette::operator= (const AnotherRosette& rhs) {
	if (this == &rhs)
		return (*this);

	Grid::operator= (rhs); 
	
	num_rings	= rhs.num_rings; 
	hole_radius	= rhs.hole_radius;
	ring_width  = rhs.ring_width;
	rb			= rhs.rb;
	y0			= rhs.y0;
	y1			= rhs.y1;

	return (*this) ;
}


// ------------------------------------------------------------------------------ destructor
 
AnotherRosette::~AnotherRosette(void) {}

/*
// ------------------------------------------------------------------------------ construct_rosette
// this function constructs the wedges in a rosette pattern and stores them in a grid
// this is the regular version, for Figure 21.11
 
void
AnotherRosette::construct_rosette(void) {	
	
	for (int k = 0; k < num_rings; k++) {
		for (int j = 0; j < num_wedges[k]; j++) {
			double angle_width = 360 / num_wedges[k];  // the azimuth angle extent of each wedge
			double r0 = hole_radius + k * ring_width;
			double r1 = hole_radius + (k + 1) * ring_width;
			double phi0 = j * angle_width;
			double phi1 = (j + 1) * angle_width;
			
			BeveledWedge* wedge_ptr = new BeveledWedge(y0, y1, r0, r1, rb, phi0 , phi1);
			add_object(wedge_ptr);										
		}
	}
}
*/
// ------------------------------------------------------------------------------ construct_rosette
// use this version to render Figure 21.17
 
void
AnotherRosette::construct_rosette(void) {	
	
	for (int k = 0; k < num_rings; k++) {
		for (int j = 0; j < num_wedges[k]; j++) {
			double angle_width = 360 / num_wedges[k];  // the azimuth angle extent of each wedge
			double r0 = hole_radius + k * ring_width;
			double r1 = hole_radius + (k + 1) * ring_width;
			double angle_offset = 63 * k;			
			double phi0 = j * angle_width + angle_offset;
			double phi1 = (j + 1) * angle_width + angle_offset;
			
			BeveledWedge* wedge_ptr = new BeveledWedge(y0, y1, r0, r1, rb, phi0 , phi1);
			add_object(wedge_ptr);										
		}
	}
}

/*
#include "AnotherRosette.h"

#include "OpenCylinder.h"
#include "Instance.h"
#include "BeveledWedge.h"

AnotherRosette::AnotherRosette(int num_rings, const float hole_r, const float ring_w, const float rb, const float y0, const float y1)
			: Grid() {

	int max = 9;
	double min_azimuth, max_azimuth;
	double step;
	double min_r = hole_r,max_r;
	double flaw = 0;
	for(int i = 0; i < num_rings; ++i)
	{
		max += i + 1;
		step = 360.0 / max;
		min_r = hole_r+i*ring_w;
		max_r = min_r + ring_w;
		flaw = rb / (hole_r+(i+1)*ring_w) * 180 * invPI;
		for(int j =0 ; j< max ; ++j)
		{
			min_azimuth = j*step;
			max_azimuth = (j+1)*step;
			BeveledWedge *bw = new BeveledWedge( y0, y1, min_r,max_r,rb,min_azimuth+flaw,max_azimuth-flaw);
			this->add_object(bw);
		}	
	}
}

// ----------------------------------------------------------------  default constructor

AnotherRosette::AnotherRosette (void)
	: 	Grid()
{
}

// ---------------------------------------------------------------- clone

AnotherRosette* 
AnotherRosette::clone(void) const {
	return (new AnotherRosette(*this));
}


// ---------------------------------------------------------------- copy constructor

AnotherRosette::AnotherRosette (const AnotherRosette& c)
	: Grid(c) {
	
	copy_objects(c.objects);					
}



// ---------------------------------------------------------------- assignment operator

AnotherRosette& 
AnotherRosette::operator= (const AnotherRosette& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);						
	
	copy_objects(rhs.objects);				

	return (*this);
}


// ---------------------------------------------------------------- destructor

AnotherRosette::~AnotherRosette(void) {	
	delete_objects();				
}

//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty 

void
AnotherRosette::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase(objects.begin(), objects.end());
}


//------------------------------------------------------------------ copy_objects

void
AnotherRosette::copy_objects(const vector<GeometricObject*>& rhs_ojects) {
	delete_objects();    	
	int num_objects = rhs_ojects.size();
	
	for (int j = 0; j < num_objects; j++)
		objects.push_back(rhs_ojects[j]->clone());
}

void
AnotherRosette::store_material(Material* material_ptr,int no)
{
	objects[no]->set_material(material_ptr);
}
*/