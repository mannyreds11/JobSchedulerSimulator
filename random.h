#ifndef RANDOM_H
#define RANDOM_H

class Random 
    {
      public:
      Random();

      // generate exponentially distributed numbers that average u
      double rnexp(double u );
    };

#endif

