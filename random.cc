/*
 *  Scheduling Simulator: random.cc
 *  Author: Manuel Rojas
 */

// This file contains the random number generators.  They must be linked by using -lm

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"


//short seed [3] = {14, 44, 7};  	// for the random number generator 

long int seed;


Random::Random()
      {
	long cur, x;

	cur = (long) 1;
	x = time(&cur) % 16384;
	//  seed[0] = (short) ((25173 * x + 13849 ) % 16384) & 0x7f;
	//  seed[1] = (short) ((25173 * seed[0] + 13849 ) % 16384) & 0x7f;
	//  seed[2] = (short) ((25173 * seed[1] + 13849 ) % 16384 ) & 0x7f;
	seed = (25173 * x + 13849) % 65536;
	srand48(seed);
      }

/* this is the uniform distribution random number generator */
double rnd()
      {
	static long seed = 17;
	seed = (25173 * seed + 13849) % 65536;
	if (seed == 0)
	      seed = 17;
	return ((double) seed) / 65536.0;
      }


/* this makes exponentially distributed random numbers, with 
  average of u */

double Random::rnexp(double u)
      {
	return (-u)*(double) log(drand48());
      }


