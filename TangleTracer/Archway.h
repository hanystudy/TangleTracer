// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the declaration of the class Archway
// This is a door with a semi-circular arch at the top
// The door sides are beveled boxes, and the arch is beveled wedges
// An un-transformed archway is parallel to the (x, z) plane with its 
// minimum (x, y, z) corner at the origin

// The parameters are: 
//					width - x dimension
//					height - y dimension
//					depth - z dimension
//					column_width - width of the side columns and archway
//					num_blocks - number of blocks in the side columns
//					num_wedges - number of wedges in the archway
//					rb - common bevel radius of the block and wedges

// This class seems to have some problem with it

#include "Grid.h"

//-------------------------------------------------------------------------------- class Archway

class Archway: public Grid {
	public:
	
		Archway(	const double width,		
					const double height,		
					const double depth,	
					const double column_width,
					const double num_blocks,
					const double num_wedges,
					const double rb);		
								
		Archway(const Archway& aw); 				
		
		virtual Archway* 								
		clone(void) const;

		virtual Archway& 								
		operator= (const Archway& rhs);		
		
		virtual 											
		~Archway(void);  
		
		void
		construct_archway(void);
				
	private:
	
		double 	width;		
		double 	height;		
		double 	depth;	
		double 	column_width;
		int 	num_blocks;
		int 	num_wedges;
		double 	rb;
};
