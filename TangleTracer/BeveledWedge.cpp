// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "BeveledWedge.h"

#include "Constants.h"

#include "Annulus.h"
#include "ConcavePartCylinder.h"
#include "ConvexPartCylinder.h"
#include "ConvexPartTorus.h"
#include "Instance.h"
#include "OpenCylinder.h"
#include "PartAnnulus.h"
#include "Rectangle.h"
#include "Sphere.h"

// ------------------------------------------------------------------------------ constructor

BeveledWedge::BeveledWedge(	const double _y0,		// minimum y value
							const double _y1,		// minimum y value
							const double _r0,		// inner radius
							const double _r1,		// outer radius
							const double _rb,		// bevel radius
							const double _phi0,		// minimum azimuth angle in degrees
							const double _phi1)		// maximum azimuth angle in degrees

	:	y0(_y0),
		y1(_y1),
		r0(_r0),
		r1(_r1),
		rb(_rb),
		phi0(_phi0),
		phi1(_phi1)
{	
	double sin_phi0 = sin(phi0 * PI_ON_180);  // in radians
	double cos_phi0 = cos(phi0 * PI_ON_180);  // in radians
	double sin_phi1 = sin(phi1 * PI_ON_180);  // in radians
	double cos_phi1 = cos(phi1 * PI_ON_180);  // in radians
	
	double sin_alpha = rb / (r0 + rb);
	double cos_alpha = sqrt(r0 * r0 + 2.0 * r0 * rb) / (r0 + rb);
	double sin_beta = rb / (r1 - rb);
	double cos_beta = sqrt(r1 * r1 - 2.0 * r1 * rb) / (r1 - rb);
		
	double xc1 = (r0 + rb) * (sin_phi0 * cos_alpha + cos_phi0 * sin_alpha);
	double zc1 = (r0 + rb) * (cos_phi0 * cos_alpha - sin_phi0 * sin_alpha);
	
	double xc2 = (r1 - rb) * (sin_phi0 * cos_beta + cos_phi0 * sin_beta);
	double zc2 = (r1 - rb) * (cos_phi0 * cos_beta - sin_phi0 * sin_beta);
		
	double xc3 = (r0 + rb) * (sin_phi1 * cos_alpha - cos_phi1 * sin_alpha);
	double zc3 = (r0 + rb) * (cos_phi1 * cos_alpha + sin_phi1 * sin_alpha);
	
	double xc4 = (r1 - rb) * (sin_phi1 * cos_beta - cos_phi1 * sin_beta);
	double zc4 = (r1 - rb) * (cos_phi1 * cos_beta + sin_phi1 * sin_beta);
	
	
	// corner spheres -------------------------------------------------------------------------------
		
	// bottom spheres
	
	Sphere* bottom_c1 = new Sphere(Point3D(xc1, y0 + rb, zc1), rb);
	objects.push_back(bottom_c1);
	
	Sphere* bottom_c2 = new Sphere(Point3D(xc2, y0 + rb, zc2), rb);
	objects.push_back(bottom_c2);
	
	Sphere* bottom_c3 = new Sphere(Point3D(xc3, y0 + rb, zc3), rb);
	objects.push_back(bottom_c3);
	
	Sphere* bottom_c4 = new Sphere(Point3D(xc4, y0 + rb, zc4), rb);
	objects.push_back(bottom_c4);
	
	
	// top spheres 
	
	Sphere* top_c1 = new Sphere(Point3D(xc1, y1 - rb, zc1), rb);
	objects.push_back(top_c1);
	
	Sphere* top_c2 = new Sphere(Point3D(xc2, y1 - rb, zc2), rb);
	objects.push_back(top_c2);
	
	Sphere* top_c3 = new Sphere(Point3D(xc3, y1 - rb, zc3), rb);
	objects.push_back(top_c3);
	
	Sphere* top_c4 = new Sphere(Point3D(xc4, y1 - rb, zc4), rb);
	objects.push_back(top_c4);	
	
	
	// vertical cylinders ------------------------------------------------------------------------------
	
	Instance* bottom_c1_cylinder = new Instance(new OpenCylinder(y0 + rb, y1 - rb, rb));
	bottom_c1_cylinder->translate(xc1, 0.0, zc1);
	bottom_c1_cylinder->transform_texture(false);
	objects.push_back(bottom_c1_cylinder);	
	
	Instance* bottom_c2_cylinder = new Instance(new OpenCylinder(y0 + rb, y1 - rb, rb));
	bottom_c2_cylinder->translate(xc2, 0.0, zc2);
	bottom_c2_cylinder->transform_texture(false);
	objects.push_back(bottom_c2_cylinder);
	
	Instance* bottom_c3_cylinder = new Instance(new OpenCylinder(y0 + rb, y1 - rb, rb));
	bottom_c3_cylinder->translate(xc3, 0.0, zc3);
	bottom_c3_cylinder->transform_texture(false);
	objects.push_back(bottom_c3_cylinder);
	
	Instance* bottom_c4_cylinder = new Instance(new OpenCylinder(y0 + rb, y1 - rb, rb));
	bottom_c4_cylinder->translate(xc4, 0.0, zc4);
	bottom_c4_cylinder->transform_texture(false);
	objects.push_back(bottom_c4_cylinder);
	
	
	// inner curved surface ---------------------------------------------------------------------------------
	
	// the azimuth angle range has to be specified in degrees
	
	double alpha = acos(cos_alpha);  // radians
	double phi_min = phi0 + alpha * 180.0 / PI;
	double phi_max = phi1 - alpha * 180.0 / PI;
	
	ConcavePartCylinder* inner_cylinder_ptr = new ConcavePartCylinder(y0 + rb, y1 - rb, r0, phi_min, phi_max); 
	objects.push_back(inner_cylinder_ptr);
	
	
	// outer curved surface -----------------------------------------------------------------------------------
	
	// the azimuth angle range has to be specified in degrees
	
	double beta = acos(cos_beta);  // radians
	phi_min = phi0 + beta * 180.0 / PI;
	phi_max = phi1 - beta * 180.0 / PI;
	
	ConvexPartCylinder* outer_cylinder_ptr = new ConvexPartCylinder(y0 + rb, y1 - rb, r1, phi_min, phi_max); 
	objects.push_back(outer_cylinder_ptr);
	
	
	// phi0 vertical rectangle
	
	double s1 = sqrt(r0 * r0 + 2.0 * r0 * rb);
	double s2 = sqrt(r1 * r1 - 2.0 * r1 * rb);
	Point3D p1(s1 * sin_phi0, y0 + rb, s1 * cos_phi0);
	Point3D p2(s2 * sin_phi0, y0 + rb, s2 * cos_phi0);
	Vector3D a = p2 - p1;
	Vector3D b(0, y1 - y0 - 2.0 * rb, 0);
	
	TRectangle* phi0_rectangle_ptr = new TRectangle(p1, a, b); 
	objects.push_back(phi0_rectangle_ptr);
	
	
	// phi1 vertical rectangle
	
	Point3D p3(s1 * sin_phi1, y0 + rb, s1 * cos_phi1);
	Point3D p4(s2 * sin_phi1, y0 + rb, s2 * cos_phi1);
	a = p3 - p4;
	
	TRectangle* phi1_rectangle_ptr = new TRectangle(p4, a, b); 
	objects.push_back(phi1_rectangle_ptr);
	
	
	
	// the tori --------------------------------------------------------------------------------------------
	
	// inner bottom
	
	phi_min = phi0 + alpha * 180.0 / PI;
	phi_max = phi1 - alpha * 180.0 / PI;
	
	Instance* inner_bottom_torus = new Instance(new ConvexPartTorus(r0 + rb, rb, phi_min, phi_max, 0, 360));
	inner_bottom_torus->translate(0.0, y0 + rb, 0.0);
	inner_bottom_torus->transform_texture(false);
	objects.push_back(inner_bottom_torus);
	
	
	// inner top
	
	Instance* inner_top_torus = new Instance(new ConvexPartTorus(r0 + rb, rb, phi_min, phi_max, 0, 360));
	inner_top_torus->translate(0.0, y1 - rb, 0.0);
	inner_top_torus->transform_texture(false);
	objects.push_back(inner_top_torus);
	
	
	// outer bottom
	
	phi_min = phi0 + beta * 180.0 / PI;
	phi_max = phi1 - beta * 180.0 / PI;
	
	Instance* outer_bottom_torus = new Instance(new ConvexPartTorus(r1 - rb, rb, phi_min, phi_max, 0, 360));
	outer_bottom_torus->translate(0.0, y0 + rb, 0.0);
	outer_bottom_torus->transform_texture(false);
	objects.push_back(outer_bottom_torus);
	
	
	// outer top
		
	Instance* outer_top_torus = new Instance(new ConvexPartTorus(r1 - rb, rb, phi_min, phi_max, 0, 360));
	outer_top_torus->translate(0.0, y1 - rb, 0.0);
	outer_top_torus->transform_texture(false);
	objects.push_back(outer_top_torus);
	
	
	// horizontal cylinders ----------------------------------------------------------------------------------
	
	// phi0 bottom cylinder
	
	Instance* phi0_bottom_cylinder_ptr = new Instance(new OpenCylinder(0, s2 - s1, rb));
	phi0_bottom_cylinder_ptr->rotate_x(90);
	phi0_bottom_cylinder_ptr->rotate_y(phi0);
	phi0_bottom_cylinder_ptr->translate(xc1, y0 + rb, zc1);
	phi0_bottom_cylinder_ptr->transform_texture(false);
	objects.push_back(phi0_bottom_cylinder_ptr);
	
	
	// phi0 top cylinder
	
	Instance* phi0_top_cylinder_ptr = new Instance(new OpenCylinder(0, s2 - s1, rb));
	phi0_top_cylinder_ptr->rotate_x(90);
	phi0_top_cylinder_ptr->rotate_y(phi0);
	phi0_top_cylinder_ptr->translate(xc1, y1 - rb, zc1);
	phi0_top_cylinder_ptr->transform_texture(false);
	objects.push_back(phi0_top_cylinder_ptr);
	
	
	// phi1 bottom cylinder
	
	Instance* phi1_bottom_cylinder_ptr = new Instance(new OpenCylinder(0, s2 - s1, rb));
	phi1_bottom_cylinder_ptr->rotate_x(90);
	phi1_bottom_cylinder_ptr->rotate_y(phi1);
	phi1_bottom_cylinder_ptr->translate(xc3, y0 + rb, zc3);
	phi1_bottom_cylinder_ptr->transform_texture(false);
	objects.push_back(phi1_bottom_cylinder_ptr);
	
	
	// phi1 top cylinder
	
	Instance* phi1_top_cylinder_ptr = new Instance(new OpenCylinder(0, s2 - s1, rb));
	phi1_top_cylinder_ptr->rotate_x(90);
	phi1_top_cylinder_ptr->rotate_y(phi1);
	phi1_top_cylinder_ptr->translate(xc3, y1 - rb, zc3);
	phi1_top_cylinder_ptr->transform_texture(false);
	objects.push_back(phi1_top_cylinder_ptr);
	
	
	// top flat surface -----------------------------------------------------------------------------------
	
	// main part
	
	Point3D center(0, y1, 0);
	Normal normal(0, 1, 0);
	double r_min = r0 + rb;
	double r_max = r1 - rb;
	phi_min = phi0 + alpha * 180.0 / PI;
	phi_max = phi1 - alpha * 180.0 / PI;
	
	PartAnnulus* top_main_part_ptr = new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max);
	objects.push_back(top_main_part_ptr);
	
	
	// small phi0 side patch
	
	r_min = 0.0;
	r_max = s2 - s1;
	phi_min = 0.0;
	phi_max = alpha * 180.0 / PI;
		
	Instance* top_phi0_patch_ptr = new Instance(new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max));
	top_phi0_patch_ptr->rotate_y(phi0);
	top_phi0_patch_ptr->translate(xc1, 0.0, zc1);
	top_phi0_patch_ptr->transform_texture(false);
	objects.push_back(top_phi0_patch_ptr);
	
	
	// small phi1 side patch
	
	phi_min = 360.0 - alpha * 180.0 / PI;
	phi_max = 360.0;
	
	Instance* top_phi1_patch_ptr = new Instance(new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max));
	top_phi1_patch_ptr->rotate_y(phi1);
	top_phi1_patch_ptr->translate(xc3, 0.0, zc3);
	top_phi1_patch_ptr->transform_texture(false);
	objects.push_back(top_phi1_patch_ptr);
	

	
	// bottom flat surface ---------------------------------------------------------------------------------
	
	// main part
	
	center = Point3D(0, y0, 0);
	normal = Normal(0, -1, 0);
	r_min = r0 + rb;
	r_max = r1 - rb;
	phi_min = phi0 + alpha * 180.0 / PI;
	phi_max = phi1 - alpha * 180.0 / PI;
	
	PartAnnulus* bottom_main_part_ptr = new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max);
	objects.push_back(bottom_main_part_ptr);
	
	
	// small phi0 side patch
	
	r_min = 0.0;
	r_max = s2 - s1;
	phi_min = 0.0;
	phi_max = alpha * 180.0 / PI;
		
	Instance* bottom_phi0_patch_ptr = new Instance(new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max));
	bottom_phi0_patch_ptr->rotate_y(phi0);
	bottom_phi0_patch_ptr->translate(xc1, 0.0, zc1);
	bottom_phi0_patch_ptr->transform_texture(false);
	objects.push_back(bottom_phi0_patch_ptr);
	
	
	// small phi1 side patch
	
	phi_min = 360.0 - alpha * 180.0 / PI;
	phi_max = 360.0;
	
	Instance* bottom_phi1_patch_ptr = new Instance(new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max));
	bottom_phi1_patch_ptr->rotate_y(phi1);
	bottom_phi1_patch_ptr->translate(xc3, 0.0, zc3);
	bottom_phi1_patch_ptr->transform_texture(false);
	objects.push_back(bottom_phi1_patch_ptr);
	
	
	
	// compute the bounding box
	
	double x[4] = {xc1, xc2, xc3, xc4};
	double z[4] = {zc1, zc2, zc3, zc4};
	
	
	// first, assume that the wedge is completely inside a quadrant, which will be true for most wedges
	
	// work out the maximum and minimum values
	
	double x0 = kHugeValue;
	double z0 = kHugeValue;
		
	for (int j = 0; j <= 3; j++)  {
		if (x[j] < x0)
			x0 = x[j];
	}
		
	for (int j = 0; j <= 3; j++) {
		if (z[j] < z0)
			z0 = z[j];
	}
	
	double x1 = -kHugeValue;
	double z1 = -kHugeValue;   
	
	for (int j = 0; j <= 3; j++) {
		if (x[j] > x1)
			x1 = x[j];
	}
		
	for (int j = 0; j <= 3; j++) {
		if (z[j] > z1)
			z1 = z[j];
	}
	
	// assign values to the bounding box
	
	bbox.x0 = x0 - rb;
	bbox.y0 = y0;
	bbox.z0 = z0 - rb;
	bbox.x1 = x1 + rb;
	bbox.y1 = y1;
	bbox.z1 = z1 + rb;
	
	bool spans90 = phi0 < 90 && phi1 > 90;
	bool spans180 = phi0 < 180 && phi1 > 180;
	bool spans270 = phi0 < 270 && phi1 > 270;
	
	if (spans90 && spans180 && spans270) {
		bbox.x0 = -r1;
		bbox.z0 = -r1;
		bbox.x1 = r1;
		bbox.z1 = max(zc2, zc4);
	}
	else if (spans90 && spans180) {
		bbox.x0 = xc4 - rb;
		bbox.z0 = -r1;
		bbox.x1 = r1;
		bbox.z1 = zc2 + rb;
	}
	else if (spans180 && spans270) {
		bbox.x0 = -r1;
		bbox.z0 = -r1;
		bbox.x1 = xc2 + rb;
		bbox.z1 = zc4 + rb;
	}
	else if (spans90) {
		bbox.x0 = min(xc1, xc3);
		bbox.z0 = zc4 - rb;
		bbox.x1 = r1;
		bbox.z1 = zc2 + rb;
	}
	else if (spans180) {
		bbox.x0 = xc4 - rb;
		bbox.z0 = -r1;
		bbox.x1 = xc2 + rb;
		bbox.z1 = max(zc1, zc3);
	}
	else if (spans270) {
		bbox.x0 = -r1;
		bbox.z0 = zc2 - rb;
		bbox.x1 = max(xc1, xc3);
		bbox.z1 = zc4 + rb;
	}	
}


																																																														

// ------------------------------------------------------------------------------ copy constructor

BeveledWedge::BeveledWedge (const BeveledWedge& bw)  			
			: 	Compound(bw),
				y0(bw.y0),
				y1(bw.y1),
				r0(bw.r0),
				r1(bw.r1),
				rb(bw.rb),
				phi0(bw.phi0),
				phi1(bw.phi1),
				bbox(bw.bbox)
{}

// ------------------------------------------------------------------------------ clone

BeveledWedge* 
BeveledWedge::clone (void) const {
	return(new BeveledWedge(*this));
}


// ------------------------------------------------------------------------------ assignment operator

BeveledWedge& 
BeveledWedge::operator= (const BeveledWedge& rhs) {
	if (this == &rhs)
		return (*this);

	Compound::operator=(rhs); 
	
	y0 		= rhs.y0;
	y1 		= rhs.y1;
	r0 		= rhs.r0;
	r1 		= rhs.r1;
	rb 		= rhs.rb;
	phi0 	= rhs.phi0;
	phi1 	= rhs.phi1;
	bbox	= rhs.bbox;
	
	return (*this) ;
}


// ------------------------------------------------------------------------------ destructor
 
BeveledWedge::~BeveledWedge(void) {}



// ------------------------------------------------------------------------------ get_bounding_box

BBox 
BeveledWedge::get_bounding_box(void) {
	return (bbox);
}



// ------------------------------------------------------------------------------ hit

bool 															 
BeveledWedge::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

/*
#include "BeveledWedge.h"

#include "OpenPartCylinder.h"
#include "Annulus.h"
#include "Instance.h"
#include "ConvexPartTorus.h"
#include "Rectangle.h"
#include "ConcavePartCylinder.h"
#include "ConvexPartCylinder.h"
#include "PartAnnulus.h"
#include "Sphere.h"

BeveledWedge::BeveledWedge(const double bottom, const double top, const double i_radius, const double o_radius, const double b_radius, const double min_azimuth, const double max_azimuth)
			: Compound() {
						
	objects.push_back(new PartAnnulus(Point3D(0.0,bottom,0.0),Normal(0,-1,0),i_radius+b_radius,o_radius-i_radius-2*b_radius,min_azimuth,max_azimuth));

	objects.push_back(new PartAnnulus(Point3D(0.0,top,0.0),Normal(0,1,0),i_radius+b_radius,o_radius-i_radius-2*b_radius,min_azimuth,max_azimuth));  

	Instance* bottom_torus_ptr = new Instance(new ConvexPartTorus( o_radius - b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	bottom_torus_ptr->translate(0, top-b_radius, 0);
	bottom_torus_ptr->transform_texture(false);
	objects.push_back(bottom_torus_ptr);

	Instance* bottom_torus_ptr1 = new Instance(new ConvexPartTorus( i_radius + b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	bottom_torus_ptr1->translate(0, top-b_radius, 0);
	bottom_torus_ptr1->transform_texture(false);
	objects.push_back(bottom_torus_ptr1);

	Instance* top_torus_ptr1 = new Instance(new ConvexPartTorus( o_radius - b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	top_torus_ptr1->translate(0, bottom+b_radius, 0);
	top_torus_ptr1->transform_texture(false);
	objects.push_back(top_torus_ptr1);

	Instance* top_torus_ptr = new Instance(new ConvexPartTorus( i_radius + b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	top_torus_ptr->translate(0, bottom+b_radius, 0);
	top_torus_ptr->transform_texture(false);
	objects.push_back(top_torus_ptr);

	objects.push_back(new OpenPartCylinder(bottom+b_radius, top-b_radius, i_radius,min_azimuth,max_azimuth));	// iwall

	objects.push_back(new OpenPartCylinder(bottom+b_radius, top-b_radius, o_radius,min_azimuth,max_azimuth));	// owall

	if( max_azimuth - min_azimuth < 360 )
	{
		double minx = sin(min_azimuth*PI_ON_180)*(i_radius+b_radius);
		double miny = top-b_radius;
		double minz = cos(min_azimuth*PI_ON_180)*(i_radius+b_radius);
		Vector3D a(sin(min_azimuth*PI_ON_180),0,cos(min_azimuth*PI_ON_180));
		a.normalize();
		a = a * ( o_radius - i_radius - 2 * b_radius);

		Vector3D b(0,- (top-bottom-2* b_radius),0);
		Vector3D n = b ^ a;
		n.normalize();
		/////////////////////////
		Instance* rectangle1 = new Instance(new TRectangle( Point3D(minx,miny,minz)+(n*b_radius) , a, b,n));
		objects.push_back(rectangle1);

		Instance* new_cylinder1 = new Instance(new OpenPartCylinder( bottom+b_radius , top-b_radius, b_radius,0,360));
		new_cylinder1->translate(minx, 0, minz);
		new_cylinder1->transform_texture(false);
		objects.push_back(new_cylinder1);

		Instance* new_cylinder2 = new Instance(new OpenPartCylinder( bottom+b_radius , top-b_radius, b_radius,0,360));
		new_cylinder2->translate(minx+a.x, 0, minz+a.z);
		new_cylinder2->transform_texture(false);
		objects.push_back(new_cylinder2);

		Instance* new_cylinderh1 = new Instance(new OpenPartCylinder( 0 , o_radius-i_radius-2*b_radius, b_radius,0,360));
		new_cylinderh1->rotate_x(90);
		new_cylinderh1->translate(0,bottom+b_radius,i_radius+b_radius);		
		new_cylinderh1->rotate_y(min_azimuth);
		new_cylinderh1->transform_texture(false);
		objects.push_back(new_cylinderh1);

		Instance* new_cylinderh2 = new Instance(new OpenPartCylinder( 0, o_radius-i_radius-2*b_radius, b_radius,0,360));
		new_cylinderh2->rotate_x(90);
		new_cylinderh2->translate(0,top-b_radius,i_radius+b_radius);
		new_cylinderh2->rotate_y(min_azimuth);
		new_cylinderh2->transform_texture(false);
		objects.push_back(new_cylinderh2);

		Sphere *sphere1 = new Sphere( Point3D(minx,miny,minz),b_radius);
		objects.push_back(sphere1);
		Sphere *sphere2 = new Sphere( Point3D(minx,miny,minz)+a,b_radius);
		objects.push_back(sphere2);
		Sphere *sphere3 = new Sphere( Point3D(minx,bottom+b_radius,minz),b_radius);
		objects.push_back(sphere3);
		Sphere *sphere4 = new Sphere( Point3D(minx,bottom+b_radius,minz)+a,b_radius);
		objects.push_back(sphere4);

		minx = sin(max_azimuth*PI_ON_180)*(i_radius+b_radius);
		miny = top-b_radius;
		minz = cos(max_azimuth*PI_ON_180)*(i_radius+b_radius);
		a = Vector3D(sin(max_azimuth*PI_ON_180),0,cos(max_azimuth*PI_ON_180));
		a.normalize();
		a = a * ( o_radius - i_radius - 2 * b_radius);

		n = a ^ b;
		n.normalize();
		/////////////////////////

		Instance* new_cylinder3 = new Instance(new OpenPartCylinder( bottom+b_radius , top-b_radius, b_radius,0,360));
		new_cylinder3->translate(minx, 0, minz);
		new_cylinder3->transform_texture(false);
		objects.push_back(new_cylinder3);

		Instance* new_cylinder4 = new Instance(new OpenPartCylinder( bottom+b_radius , top-b_radius, b_radius,0,360));
		new_cylinder4->translate(minx+a.x, 0, minz+a.z);
		new_cylinder4->transform_texture(false);
		objects.push_back(new_cylinder4);
				
		Instance* rectangle2 = new Instance(new TRectangle( Point3D(minx,miny,minz)+(n*b_radius) , a, b,n));
		objects.push_back(rectangle2);

		Instance* new_cylinderh3 = new Instance(new OpenPartCylinder( 0 , o_radius-i_radius-2*b_radius, b_radius,0,360));
		new_cylinderh3->rotate_x(90);
		new_cylinderh3->translate(0,bottom+b_radius,i_radius+b_radius);		
		new_cylinderh3->rotate_y(max_azimuth);
		new_cylinderh3->transform_texture(false);
		objects.push_back(new_cylinderh3);

		Instance* new_cylinderh4 = new Instance(new OpenPartCylinder( 0, o_radius-i_radius-2*b_radius, b_radius,0,360));
		new_cylinderh4->rotate_x(90);
		new_cylinderh4->translate(0,top-b_radius,i_radius+b_radius);
		new_cylinderh4->rotate_y(max_azimuth);
		new_cylinderh4->transform_texture(false);
		objects.push_back(new_cylinderh4);

		Sphere *sphere5 = new Sphere( Point3D(minx,miny,minz),b_radius);
		objects.push_back(sphere5);
		Sphere *sphere6 = new Sphere( Point3D(minx,miny,minz)+a,b_radius);
		objects.push_back(sphere6);
		Sphere *sphere7 = new Sphere( Point3D(minx,bottom+b_radius,minz),b_radius);
		objects.push_back(sphere7);
		Sphere *sphere8 = new Sphere( Point3D(minx,bottom+b_radius,minz)+a,b_radius);
		objects.push_back(sphere8);
	}

	bbox.x0 = -o_radius;
	bbox.y0 = bottom;
	bbox.z0 = -o_radius;
	bbox.x1 = o_radius;
	bbox.y1 = top;
	bbox.z1 = o_radius;
}

// ----------------------------------------------------------------  default constructor

BeveledWedge::BeveledWedge (void)
	: 	Compound()
{
	double bottom = -1.0;		// minimum y value
	float top = 2;			// maximum y value
	float i_radius = 1.5;			// inner radius
	float o_radius = 3;			// outer radius
	float b_radius = 0.25;		// bevel radius
	float min_azimuth = 140;		// minimum azimuth angle in degrees
	float max_azimuth = 350;		// maximum azimuth angle in degrees

	objects.push_back(new PartAnnulus(Point3D(0.0,bottom,0.0),Normal(0,-1,0),i_radius+b_radius,o_radius-i_radius-2*b_radius,min_azimuth,max_azimuth));

	objects.push_back(new PartAnnulus(Point3D(0.0,top,0.0),Normal(0,1,0),i_radius+b_radius,o_radius-i_radius-2*b_radius,min_azimuth,max_azimuth));  
	
	Instance* bottom_torus_ptr = new Instance(new ConvexPartTorus( o_radius - b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	bottom_torus_ptr->translate(0, top-b_radius, 0);
	bottom_torus_ptr->transform_texture(false);
	objects.push_back(bottom_torus_ptr);

	Instance* bottom_torus_ptr1 = new Instance(new ConvexPartTorus( i_radius + b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	bottom_torus_ptr1->translate(0, top-b_radius, 0);
	bottom_torus_ptr1->transform_texture(false);
	objects.push_back(bottom_torus_ptr1);

	Instance* top_torus_ptr1 = new Instance(new ConvexPartTorus( o_radius - b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	top_torus_ptr1->translate(0, bottom+b_radius, 0);
	top_torus_ptr1->transform_texture(false);
	objects.push_back(top_torus_ptr1);

	Instance* top_torus_ptr = new Instance(new ConvexPartTorus( i_radius + b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	top_torus_ptr->translate(0, bottom+b_radius, 0);
	top_torus_ptr->transform_texture(false);
	objects.push_back(top_torus_ptr);

	objects.push_back(new OpenPartCylinder(bottom+b_radius, top-b_radius, i_radius,min_azimuth,max_azimuth));	// iwall

	objects.push_back(new OpenPartCylinder(bottom+b_radius, top-b_radius, o_radius,min_azimuth,max_azimuth));	// owall

	if( max_azimuth - min_azimuth < 360 )
	{
		Instance* rectangle1 = new Instance(new TRectangle( Point3D(b_radius,top-b_radius,o_radius-b_radius) , Vector3D(0,0,-(o_radius-i_radius-2*b_radius)),Vector3D(0,-(top-bottom-2*b_radius),0),Normal(-1,0,0)));
		rectangle1->rotate_y(min_azimuth);
		rectangle1->transform_texture(false);
		objects.push_back(rectangle1);

		Instance* rectangle2 = new Instance(new TRectangle( Point3D(b_radius,top-b_radius,o_radius-b_radius) , Vector3D(0,0,-(o_radius-i_radius-2*b_radius)),Vector3D(0,-(top-bottom-2*b_radius),0),Normal(1,0,0)));
		rectangle2->rotate_y(max_azimuth);
		rectangle2->transform_texture(false);
		objects.push_back(rectangle2);
	}

	bbox.x0 = -o_radius;
	bbox.y0 = bottom;
	bbox.z0 = -o_radius;
	bbox.x1 = o_radius;
	bbox.y1 = top;
	bbox.z1 = o_radius;
}


// ---------------------------------------------------------------- clone

BeveledWedge* 
BeveledWedge::clone(void) const {
	return (new BeveledWedge(*this));
}


// ---------------------------------------------------------------- copy constructor

BeveledWedge::BeveledWedge (const BeveledWedge& c)
	: Compound(c) {
	
	copy_objects(c.objects);					
}



// ---------------------------------------------------------------- assignment operator

BeveledWedge& 
BeveledWedge::operator= (const BeveledWedge& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);						
	
	copy_objects(rhs.objects);				

	return (*this);
}


// ---------------------------------------------------------------- destructor

BeveledWedge::~BeveledWedge(void) {	
	delete_objects();				
}


//------------------------------------------------------------------ set_material
// sets the same material on all objects

void 
BeveledWedge::set_material(Material* material_ptr) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		objects[j]->set_material(material_ptr);
}


//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty 

void
BeveledWedge::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase(objects.begin(), objects.end());
}


//------------------------------------------------------------------ copy_objects

void
BeveledWedge::copy_objects(const vector<GeometricObject*>& rhs_ojects) {
	delete_objects();    	
	int num_objects = rhs_ojects.size();
	
	for (int j = 0; j < num_objects; j++)
		objects.push_back(rhs_ojects[j]->clone());
}


//------------------------------------------------------------------ hit

bool 															 
BeveledWedge::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

// ------------------------------------------------- shadow hit

bool 																						 
BeveledWedge::shadow_hit(const Ray& ray, float& tmin) const
{
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
}

void 
BeveledWedge::set_bottom_material(Material* material_ptr)
{
	objects[0]->set_material(material_ptr);
}	//19.29

void 
BeveledWedge::set_top_material(Material* material_ptr)
{
	objects[1]->set_material(material_ptr);
}	//19.29

void 
BeveledWedge::set_inner_wall_material(Material* material_ptr)
{
	objects[2]->set_material(material_ptr);
}//19.29

void 
BeveledWedge::set_outer_wall_material(Material* material_ptr)
{
	objects[3]->set_material(material_ptr);
}//19.29

BBox 
BeveledWedge::get_bounding_box(void)
{
	return bbox;
}
*/