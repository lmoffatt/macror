#include "MersenneTwister.h"
#include "Markov_LA/matrixSum.h"
namespace Borrowed
{
  namespace MersenneTwister
  {


    double LnFac(int32_t n)
    {
      // log factorial function. gives natural logarithm of n!

      // define constants
      const double                 // coefficients in Stirling approximation
          C0 =  0.918938533204672722,      // ln(sqrt(2*pi))
          C1 =  1./12.,
          C3 = -1./360.;
      // C5 =  1./1260.,                  // use r^5 term if FAK_LEN < 50
      // C7 = -1./1680.;                  // use r^7 term if FAK_LEN < 20
      //  variables
      double fac_table[FAK_LEN];   // table of ln(n!):
      int initialized = 0;         // remember if fac_table has been initialized

      if (n < FAK_LEN)
        {
          if (n <= 1)
            {
              if (n < 0) FatalError("Parameter negative in LnFac function");
              return 0;
            }
          if (!initialized)                // first time. Must initialize table
            {
              // make table of ln(n!)
              double sum = fac_table[0] = 0.;
              for (int i=1; i<FAK_LEN; i++)
                {
                  sum += log(double(i));
                  fac_table[i] = sum;
                }
              initialized = 1;
            }
          return fac_table[n];
        }
      // not found in table. use Stirling approximation
      double  n1, r;
      n1 = n;
      r  = 1. / n1;
      return (n1 + 0.5)*log(n1) - n1 + C0 + r*(C1 + r*r*C3);
    }





  }



}
