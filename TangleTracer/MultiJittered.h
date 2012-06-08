// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Sampler.h"

class MultiJittered: public Sampler {
	public:
		
		MultiJittered(void);								
		
		MultiJittered(const int num_samples);				
		
		MultiJittered(const int num_samples, const int m);	

		MultiJittered(const MultiJittered& mjs);			

		MultiJittered& 
		operator= (const MultiJittered& rhs);				

		virtual MultiJittered*								
		clone(void) const;			

		virtual
		~MultiJittered(void);								
		
	private:
		
		virtual void										
		generate_samples(void);		
};
