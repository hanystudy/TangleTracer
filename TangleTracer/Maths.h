// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This is a header file for the mathematics utility functions
// The prototypes of any inlined functions must be placed here

#pragma once

#include <stdlib.h>

#include "stdafx.h"

#include "Constants.h"
#include "RGBColor.h"


// prototypes

double
min(double x0, double x1);

double
max(double x0, double x1);

int							
rand_int(void);

float
rand_float(void);

void
set_rand_seed(const int seed);

float 						// for multi-jittered sampling
rand_float(int l, float h);	

int							// for multi-jittered sampling
rand_int(int l, int h);   

double
clamp(const double x, const double min, const double max);

int
SolveQuadric(double c[3], double s[2]);

int 
SolveCubic(double c[4], double s[3]);

int 
SolveQuartic(double c[5], double s[4]);

// Below definition are noise based texture needed
// Add the following prototypes to the Maths.h file.

double
mod(double a, const double b); 

double 
smooth_pulse(double e0, double e1, double e2, double e3, double x);

double 
smooth_pulse_train(double e0, double e1, double e2, double e3, double period, double x);

double
smooth_step(double a, double b, double x);

RGBColor
mix_color(const RGBColor& c0, const RGBColor& c1, const double f);

double
mix_double(const double a, const double b, const double f);


// inlined functions

// ----------------------------------------------------------------- min

inline double
min(double x0, double x1) {
	return ((x0 < x1) ? x0 : x1);
}


// ----------------------------------------------------------------- max

inline double
max(double x0, double x1) {
	return ((x0 > x1) ? x0 : x1);
}


// ---------------------------------------------------- rand_int
// a wrapper for rand()

inline int
rand_int(void) {
	return(rand());
}


// ---------------------------------------------------- rand_float

inline float
rand_float(void) {
	return((float)rand_int() * invRAND_MAX);
}


// ---------------------------------------------------- set_rand_seed

inline void
set_rand_seed(const int seed) {
	srand(seed);
}


// The following two functions are only for multi-jittered sampling
// I had trouble getting them to compile in the MultiJittered class
// The overloading confused my compiler

// ---------------------------------------------------- rand_float with arguments

inline float 
rand_float(int l, float h) {
	return (rand_float() * (h - l) + l);
}

// ---------------------------------------------------- rand_int with arguments

inline int
rand_int(int l, int h) {
	return ((int) (rand_float(0, h - l) + l));
}


// ---------------------------------------------------- clamp

inline double
clamp(const double x, const double min, const double max) {
	return (x < min ? min : (x > max ? max : x));
}

// Below are Noise based Texture needed

// Add the following function definitions to the Maths.cpp file.

// -------------------------------------------------------------------------- mod

inline double
mod(double a, const double b) {
	int n = (int) (a / b);
	
	a -= n * b;
	if (a < 0.0)
		a += b;
	
	return (a);
}


// -------------------------------------------------------------------------- smooth_pulse

inline double 
smooth_pulse(double e0, double e1, double e2, double e3, double x) {
	return (smooth_step (e0, e1, x) - smooth_step (e2, e3, x));
}


// -------------------------------------------------------------------------- smooth_pulse_train
// calls smooth_pulse and mod

inline double 
smooth_pulse_train(double e0, double e1, double e2, double e3, double period, double x) {
	return (smooth_pulse(e0, e1, e2, e3, mod(x, period)));
}


// -------------------------------------------------------------------------- smooth_step

inline double
smooth_step(double a, double b, double x) {
	if (x < a)
		return (0.0);
	
	if (x >= b)
		return (1.0);
		
	double y = (x - a) / ( b - a);  // normalise to [0, 1]
	
	return (y * y * (3.0 - 2.0 * y));
}


// -------------------------------------------------------------------------- mix_color

inline RGBColor
mix_color(const RGBColor& c0, const RGBColor& c1, const double f) {
	return ((1.0 - f) * c0 + f * c1);
}


// -------------------------------------------------------------------------- mix_double

inline double
mix_double(const double a, const double b, const double f) {
	return ((1.0 - f) * a + f * b);
}