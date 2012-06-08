// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Constants.h"
#include "Disk.h"
#include "ConvexPartSphere.h"
#include "ConcavePartSphere.h"
//#include "ConvexPartTorus.h"
//#include "ConcavePartTorus.h"
#include "Instance.h"
#include "FlatRimmedBowl.h"
#include "Annulus.h"


// ------------------------------------------------------------------------------ default constructor

FlatRimmedBowl::FlatRimmedBowl(void)
	: 	Compound(),
		inner_radius(0.9),
		outer_radius(1.0)
{	
	build_components();														
}


// ------------------------------------------------------------------------------ constructor

FlatRimmedBowl::FlatRimmedBowl(	const double i, const double o)
	: 	Compound(),
		inner_radius(i),
		outer_radius(o)	
{	
	build_components();														
}


																																																												

// ------------------------------------------------------------------------------ copy constructor

FlatRimmedBowl::FlatRimmedBowl(const FlatRimmedBowl& fb)  			
	: 	Compound(fb),
		inner_radius(fb.inner_radius),
		outer_radius(fb.outer_radius)	
{}


// ------------------------------------------------------------------------------ clone

FlatRimmedBowl* 
FlatRimmedBowl::clone(void) const {
	return(new FlatRimmedBowl(*this));
}


// ------------------------------------------------------------------------------ assignment operator

FlatRimmedBowl& 
FlatRimmedBowl::operator= (const FlatRimmedBowl& rhs) {
	if (this == &rhs)
		return (*this);

	Compound::operator=(rhs); 
	
	inner_radius = rhs.inner_radius;
	outer_radius = rhs.outer_radius;

	return (*this) ;
}


// ------------------------------------------------------------------------------ destructor
 
FlatRimmedBowl::~FlatRimmedBowl(void) {}


// ------------------------------------------------------------------------------ build_components

void 
FlatRimmedBowl::build_components(void) {
	
	objects.push_back(new ConvexPartSphere(	Point3D(0.0), 
											outer_radius, 
											0, 360,  				// azimuth angle range - full circle
											90,  					// minimum polar angle measured from top
											180));                 	// maximum polar angle measured from top


	objects.push_back(new ConcavePartSphere(Point3D(0.0), 			 
											inner_radius, 
											0, 360, 				// azimuth angle - full circle
											90,    // mimimum polar angle measured from top
											180));   			// maximum polar angle measured from top

	objects.push_back(new Annulus(Point3D(0.0),Normal(0,1,0),inner_radius,outer_radius-inner_radius));   			// maximum polar angle measured from top
}

void
FlatRimmedBowl::set_material(Material* m_ptr) {
	for (int j = 0; j < 3; j++)
		objects[j]->set_material(m_ptr);
}
