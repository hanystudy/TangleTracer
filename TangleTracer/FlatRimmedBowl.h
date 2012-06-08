// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the declaration of the class FlatRimmedBowl
// The bowl is centered on the world origin

#pragma once

#include "Compound.h"

class FlatRimmedBowl: public Compound {
	public:
		
		FlatRimmedBowl(void);   							

		FlatRimmedBowl(	const double inner_radius, const double outer_radius);

		FlatRimmedBowl(const FlatRimmedBowl& fb); 				
		
		virtual FlatRimmedBowl* 							
		clone(void) const;

		virtual FlatRimmedBowl& 							
		operator= (const FlatRimmedBowl& rhs);		
		
		virtual 									
		~FlatRimmedBowl(void); 
		
		void
		build_components(void);
		
		void
		set_material(Material* m_ptr);
		
	protected:
	
		double inner_radius;		// radius of the inside glass surface
		double outer_radius;
};
