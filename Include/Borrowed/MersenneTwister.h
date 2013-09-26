// MersenneTwister.h
// Mersenne Twister random number generator -- a C++ class MTRand
// Based on code by Makoto Matsumoto, Takuji Nishimura, and Shawn Cokus
// Richard J. Wagner  v1.1  28 September 2009  wagnerr@umich.edu

// The Mersenne Twister is an algorithm for generating random numbers.  It
// was designed with consideration of the flaws in various other generators.
// The period, 2^19937-1, and the order of equidistribution, 623 dimensions,
// are far greater.  The generator is also fast; it avoids multiplication and
// division, and it benefits from caches and pipelines.  For more information
// see the inventors' web page at
// http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html

// Reference
// M. Matsumoto and T. Nishimura, "Mersenne Twister: A 623-Dimensionally
// Equidistributed Uniform Pseudo-Random Number Generator", ACM Transactions on
// Modeling and Computer Simulation, Vol. 8, No. 1, January 1998, pp 3-30.

// Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
// Copyright (C) 2000 - 2009, Richard J. Wagner
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   1. Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//   2. Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//   3. The names of its contributors may not be used to endorse or promote
//      products derived from this software without specific prior written
//      permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// The original code included the following notice:
//
//     When you use this, send an email to: m-mat@math.sci.hiroshima-u.ac.jp
//     with an appropriate reference to your work.
//
// It would be nice to CC: wagnerr@umich.edu and Cokus@math.washington.edu
// when you write.

#ifndef MERSENNETWISTER_H
#define MERSENNETWISTER_H

// Not thread safe (unless auto-initialization is avoided and each thread has
// its own MTRand object)

#include <iostream>
#include <climits>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <stdint.h>
#include <cstdlib>



#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixAssigmentOp.h"
#include "Markov_LA/matrixIO.h"

namespace Borrowed
{
    namespace MersenneTwister
    {




inline
void EndOfProgram()
{
    // This function takes care of whatever is necessary to do when the
    // program is finished

    // It may be necessary to wait for the user to press a key
    // in order to prevent the output window from disappearing.
    // Remove the #ifdef and #endif lines to unconditionally wait for a key press;
    // Remove all three lines to not wait:
#ifdef _GETCH_DEFINED_
    getch();                             // wait for user to press a key
#endif

    // It may be necessary to end the program with a linefeed:
#if defined (__unix__) || defined (_MSC_VER)
    printf("\n");                        // end program with a linefeed
#endif
}





/**
* Provides a seed for the random number generator. If seed is zero it returns a value of the timer.
* @post if \p seed==0 then  it returns \p time(0);
*/
inline
std::size_t seedinit(std::size_t seed);



inline
void FatalError(const char * ErrorText)
{
    // This function outputs an error message and aborts the program.

    // Important: There is no universally portable way of outputting an
    // error message. You may have to modify this function to output
    // the error message in a way that is appropriate for your system.


    // Check if FatalAppExit exists (this macro is defined in winbase.h)
#ifdef FatalAppExit

    // in Windows, use FatalAppExit:
    FatalAppExit(0, ErrorText);

#else

    // in console mode, print error message
    printf ("\n%s\n", ErrorText);
    EndOfProgram();

#endif

    // Terminate program with error code
    exit(1);
}
// constant for LnFac function:
static const int FAK_LEN = 1024;       // length of factorial table
const double SHAT1 = 2.943035529371538573;    // 8/e
const double SHAT2 = 0.8989161620588987408;   // 3-sqrt(12/e)

/***********************************************************************
Log factorial function
***********************************************************************/
double LnFac(int32_t n);




class MTRand
{
// Data
public:
    typedef unsigned long uint32;  // unsigned integer type, at least 32 bits

    enum { N = 624 };       // length of state vector
    enum { SAVE = N + 1 };  // length of array for save()

protected:
    enum { M = 397 };  // period parameter

    uint32 state[N];   // internal state
    uint32 *pNext;     // next value to get from state
    int left;          // number of values left before reload needed

// Methods
public:
    MTRand( const uint32 oneSeed );  // initialize with a simple uint32
    MTRand( uint32 *const bigSeed, uint32 const seedLength = N );  // or array
    MTRand();  // auto-initialize with /dev/urandom or time() and clock()
    MTRand( const MTRand& o );  // copy

    // Do NOT use for CRYPTOGRAPHY without securely hashing several returned
    // values together, otherwise the generator state can be learned after
    // reading 624 consecutive values.

    // Access to 32-bit random numbers
    uint32 randInt();                     // integer in [0,2^32-1]
    uint32 randInt( const uint32 n );     // integer in [0,n] for n < 2^32
    double rand();                        // real number in [0,1]
    double rand( const double n );        // real number in [0,n]
    double randExc();                     // real number in [0,1)
    double randExc( const double n );     // real number in [0,n)
    double randDblExc();                  // real number in (0,1)
    double randDblExc( const double n );  // real number in (0,n)
    double operator()();                  // same as rand()

    // Access to 53-bit random numbers (capacity of IEEE double precision)
    double rand53();  // real number in [0,1)

    // Access to nonuniform random number distributions
    double randNorm( const double mean = 0.0, const double stddev = 1.0 );

    // Re-seeding functions with same behavior as initializers
    void seed( const uint32 oneSeed );
    void seed( uint32 *const bigSeed, const uint32 seedLength = N );
    void seed();

    // Saving and loading generator state
    void save( uint32* saveArray ) const;  // to array of size SAVE
    void load( uint32 *const loadArray );  // from such array
    friend std::ostream& operator<<( std::ostream& os, const MTRand& mtrand );
    friend std::istream& operator>>( std::istream& is, MTRand& mtrand );
    MTRand& operator=( const MTRand& o );


    /***********************************************************************
    Binomial distribution
    ***********************************************************************/
    int32_t Binomial (int n, double p)
    {
        /*
        This function generates a random variate with the binomial distribution.

        Uses inversion by chop-down method for n*p < 35, and ratio-of-uniforms
        method for n*p >= 35.

        For n*p < 1.E-6 numerical inaccuracy is avoided by poisson approximation.
        */
        int inv = 0;                        // invert
        int32_t x;                          // result
        double np = n * p;

        if (p > 0.5)                        // faster calculation by inversion
        {
            p = 1. - p;
            inv = 1;
        }
        if (n <= 0 || p <= 0)
        {
            if (n == 0 || p == 0)
            {
                return inv * n;  // only one possible result
            }
            // error exit
            std::cerr<<"n="<<n<<" p="<<p<<"\n";
            FatalError("Parameter out of range in binomial function");
        }

        //------------------------------------------------------------------
        //                 choose method
        //------------------------------------------------------------------
        if (np < 35.)
        {
            if (np < 1.E-6)
            {
                // Poisson approximation for extremely low np
                x = PoissonLow(np);
            }
            else
            {
                // inversion method, using chop-down search from 0
                x = BinomialInver(n, p);
            }
        }
        else
        {
            // ratio of uniforms method
            x = BinomialRatioOfUniforms(n, p);
        }
        if (inv)
        {
            x = n - x;      // undo inversion
        }
        return x;
    }


    /***********************************************************************
    Subfunctions used by binomial
    ***********************************************************************/

    int32_t BinomialInver (int n, double p)
    {
        /*
        Subfunction for Binomial distribution. Assumes p < 0.5.

        Uses inversion method by search starting at 0.

        Gives overflow for n*p > 60.

        This method is fast when n*p is low.
        */
        double f0, f, q;
        int32_t bound;
        double pn, r, rc;
        int32_t x, n1, i;

        // f(0) = probability of x=0 is (1-p)^n
        // fast calculation of (1-p)^n
        f0 = 1.;
        pn = 1.-p;
        n1 = n;
        while (n1)
        {
            if (n1 & 1) f0 *= pn;
            pn *= pn;
            n1 >>= 1;
        }
        // calculate safety bound
        rc = (n + 1) * p;
        bound = (int32_t)(rc + 11.0*(sqrt(rc) + 1.0));
        if (bound > n) bound = n;
        q = p / (1. - p);

        while (1)
        {
            r = rand();
            // recursive calculation: f(x) = f(x-1) * (n-x+1)/x*p/(1-p)
            f = f0;
            x = 0;
            i = n;
            do
            {
                r -= f;
                if (r <= 0) return x;
                x++;
                f *= q * i;
                r *= x;       // it is faster to multiply r by x than dividing f by x
                i--;
            }
            while (x <= bound);
        }
    }


    int32_t BinomialRatioOfUniforms (int32_t n, double p)
    {
        /*
        Subfunction for Binomial distribution. Assumes p < 0.5.

        Uses the Ratio-of-Uniforms rejection method.

        The computation time hardly depends on the parameters, except that it matters
        a lot whether parameters are within the range where the LnFac function is
        tabulated.

        Reference: E. Stadlober: "The ratio of uniforms approach for generating
        discrete random variates". Journal of Computational and Applied Mathematics,
        vol. 31, no. 1, 1990, pp. 181-189.
        */
        double u;                           // uniform random
        double q1;                          // 1-p
        double np;                          // n*p
        double var;                         // variance
        double lf;                          // ln(f(x))
        double x;                           // real sample
        int32_t k;                          // integer sample

        if(bino_n_last != n || bino_p_last != p)      // Set_up
        {
            bino_n_last = n;
            bino_p_last = p;
            q1 = 1.0 - p;
            np = n * p;
            bino_mode = (int32_t)(np + p);             // mode
            bino_a = np + 0.5;                         // hat center
            bino_r1 = log(p / q1);
            bino_g = LnFac(bino_mode) + LnFac(n-bino_mode);
            var = np * q1;                             // variance
            bino_h = sqrt(SHAT1 * (var+0.5)) + SHAT2;  // hat width
            bino_bound = (int32_t)(bino_a + 6.0 * bino_h);// safety-bound
            if (bino_bound > n) bino_bound = n;        // safety-bound
        }

        while (1)                                     // rejection loop
        {
            u = rand();
            if (u == 0) continue;                      // avoid division by 0
            x = bino_a + bino_h * (rand() - 0.5) / u;
            if (x < 0. || x > bino_bound) continue;    // reject, avoid overflow
            k = (int32_t)x;                            // truncate
            lf = (k-bino_mode)*bino_r1+bino_g-LnFac(k)-LnFac(n-k);// ln(f(k))
            if (u * (4.0 - u) - 3.0 <= lf) break;      // lower squeeze accept
            if (u * (u - lf) > 1.0) continue;          // upper squeeze reject
            if (2.0 * log(u) <= lf) break;             // final acceptance
        }
        return k;
    }


    int32_t PoissonLow(double L)
    {
        /*
        This subfunction generates a random variate with the poisson
        distribution for extremely low values of L.

        The method is a simple calculation of the probabilities of x = 1
        and x = 2. Higher values are ignored.

        The reason for using this method is to avoid the numerical inaccuracies
        in other methods.
        */
        double d, r;
        d = sqrt(L);
        if (rand() >= d) return 0;
        r = rand() * d;
        if (r > L * (1.-L)) return 0;
        if (r > 0.5 * L*L * (1.-L)) return 1;
        return 2;
    }



    /***********************************************************************
    Multinomial distribution
    ***********************************************************************/
    Markov_LA::M_Matrix<std::size_t> Multinomial (const Markov_LA::M_Matrix<double>& P,
						  std::size_t n,
						  std::size_t i_row=0)
    {
        /*
        This function generates a vector of random variates, each with the
        binomial distribution.

        The multinomial distribution is the distribution you get when drawing
        balls from an urn with more than two colors, with replacement.

        Parameters:
        destination:    An output array to receive the number of balls of each
        color. Must have space for at least 'colors' elements.
        source:         An input array containing the probability or fraction
        of each color in the urn. Must have 'colors' elements.
        All elements must be non-negative. The sum doesn't have
        to be 1, but the sum must be positive.
        n:              The number of balls drawn from the urn.
        colors:         The number of possible colors.
        */
        double p, psum=0;
        std::size_t x;
        std::size_t i;
        std::size_t colors=ncols(P);
        Markov_LA::M_Matrix<std::size_t> destination=Markov_LA::zeros<std::size_t>(1,colors);
        if (colors == 0) return destination;

        // compute sum of probabilities
        for (i=0; i<colors; i++)
        {
            p = P(i_row,i);
            if (p < 0)
                std::cerr<<"Parameter negative in multinomial function \n"<<P;
            psum += p;
        }



	if (psum == 0 && n > 0)
	{
	    std::cerr<<" psum"<<psum<<"\nP\n"<<P<<"n\n"<<n;
	    FatalError("Zero sum in multinomial function");
	}

        for (i=0; i<colors-1; i++)
        {
            // generate output by calling binomial (colors-1) times
            p = P(i_row,i);
            if (psum <= p)
            {
                // this fixes two problems:
                // 1. prevent division by 0 when sum = 0
                // 2. prevent s/sum getting bigger than 1 in case of rounding errors
                x = n;
            }
            else
            {
                x = Binomial(n, p/psum);
            }
            n -= x;
            psum -= p;
            destination[i] = x;
        }
        // get the last one
        destination[i] = n;
        return destination;
    }


    Markov_LA::M_Matrix<std::size_t> Markov_run(const Markov_LA::M_Matrix<double> P,const Markov_LA::M_Matrix<std::size_t> Ns)
    {
      int  n=nrows(P);
          Markov_LA::M_Matrix<std::size_t> N_out=Markov_LA::zeros(Ns);
//#pragma omp parallel for
          for (int j=0; j<n; j++)
            {
              N_out+=Multinomial(P,Ns[j],j);
            }

          return N_out;

        }



protected:
    void initialize( const uint32 oneSeed );
    void reload();
    uint32 hiBit( const uint32 u ) const
    {
        return u & 0x80000000UL;
    }
    uint32 loBit( const uint32 u ) const
    {
        return u & 0x00000001UL;
    }
    uint32 loBits( const uint32 u ) const
    {
        return u & 0x7fffffffUL;
    }
    uint32 mixBits( const uint32 u, const uint32 v ) const
    {
        return hiBit(u) | loBits(v);
    }
    uint32 magic( const uint32 u ) const
    {
        return loBit(u) ? 0x9908b0dfUL : 0x0UL;
    }
    uint32 twist( const uint32 m, const uint32 s0, const uint32 s1 ) const
    {
        return m ^ (mixBits(s0,s1)>>1) ^ magic(s1);
    }
    static uint32 hash( time_t t, clock_t c );



    // Variables used by Binomial distribution
    int32_t bino_n_last;                                    // last n
    double bino_p_last;                                     // last p
    int32_t bino_mode;                                      // mode
    int32_t bino_bound;                                     // upper bound
    double bino_a;                                          // hat center
    double bino_h;                                          // hat width
    double bino_g;                                          // value at mode
    double bino_r1;                                         // p/(1-p) or ln(p/(1-p))


    //variables used by normal distribution

    double norm_x, norm_y;
    bool norm_y_valid;

};

// Functions are defined in order of usage to assist inlining

inline MTRand::uint32 MTRand::hash( time_t t, clock_t c )
{
    // Get a uint32 from t and c
    // Better than uint32(x) in case x is floating point in [0,1]
    // Based on code by Lawrence Kirby (fred@genesis.demon.co.uk)

    static uint32 differ = 0;  // guarantee time-based seeds will change

    uint32 h1 = 0;
    unsigned char *p = (unsigned char *) &t;
    for( size_t i = 0; i < sizeof(t); ++i )
    {
        h1 *= UCHAR_MAX + 2U;
        h1 += p[i];
    }
    uint32 h2 = 0;
    p = (unsigned char *) &c;
    for( size_t j = 0; j < sizeof(c); ++j )
    {
        h2 *= UCHAR_MAX + 2U;
        h2 += p[j];
    }
    return ( h1 + differ++ ) ^ h2;
}

inline void MTRand::initialize( const uint32 seed )
{
    // Initialize generator state with seed
    // See Knuth TAOCP Vol 2, 3rd Ed, p.106 for multiplier.
    // In previous versions, most significant bits (MSBs) of the seed affect
    // only MSBs of the state array.  Modified 9 Jan 2002 by Makoto Matsumoto.
    register uint32 *s = state;
    register uint32 *r = state;
    register int i = 1;
    *s++ = seed & 0xffffffffUL;
    for( ; i < N; ++i )
    {
        *s++ = ( 1812433253UL * ( *r ^ (*r >> 30) ) + i ) & 0xffffffffUL;
        r++;
    }
}

inline void MTRand::reload()
{
    // Generate N new values in state
    // Made clearer and faster by Matthew Bellew (matthew.bellew@home.com)
    static const int MmN = int(M) - int(N);  // in case enums are unsigned
    register uint32 *p = state;
    register int i;
    for( i = N - M; i--; ++p )
        *p = twist( p[M], p[0], p[1] );
    for( i = M; --i; ++p )
        *p = twist( p[MmN], p[0], p[1] );
    *p = twist( p[MmN], p[0], state[0] );

    left = N, pNext = state;
}

inline void MTRand::seed( const uint32 oneSeed )
{
    // Seed the generator with a simple uint32
    initialize(oneSeed);
    reload();
    norm_y_valid=false;

}

inline void MTRand::seed( uint32 *const bigSeed, const uint32 seedLength )
{
    // Seed the generator with an array of uint32's
    // There are 2^19937-1 possible initial states.  This function allows
    // all of those to be accessed by providing at least 19937 bits (with a
    // default seed length of N = 624 uint32's).  Any bits above the lower 32
    // in each element are discarded.
    // Just call seed() if you want to get array from /dev/urandom
    initialize(19650218UL);
    register int i = 1;
    register uint32 j = 0;
    register int k = ( int(N) > seedLength ? int(N) : seedLength );
    for( ; k; --k )
    {
        state[i] =
            state[i] ^ ( (state[i-1] ^ (state[i-1] >> 30)) * 1664525UL );
        state[i] += ( bigSeed[j] & 0xffffffffUL ) + j;
        state[i] &= 0xffffffffUL;
        ++i;
        ++j;
        if( i >= N )
        {
            state[0] = state[N-1];
            i = 1;
        }
        if( j >= seedLength ) j = 0;
    }
    for( k = N - 1; k; --k )
    {
        state[i] =
            state[i] ^ ( (state[i-1] ^ (state[i-1] >> 30)) * 1566083941UL );
        state[i] -= i;
        state[i] &= 0xffffffffUL;
        ++i;
        if( i >= N )
        {
            state[0] = state[N-1];
            i = 1;
        }
    }
    state[0] = 0x80000000UL;  // MSB is 1, assuring non-zero initial array
    reload();
    norm_y_valid=false;
}

inline void MTRand::seed()
{
    // Seed the generator with an array from /dev/urandom if available
    // Otherwise use a hash of time() and clock() values

    // First try getting an array from /dev/urandom
    FILE* urandom = fopen( "/dev/urandom", "rb" );
    if( urandom )
    {
        uint32 bigSeed[N];
        register uint32 *s = bigSeed;
        register int i = N;
        register bool success = true;
        while( success && i-- )
            success = fread( s++, sizeof(uint32), 1, urandom );
        fclose(urandom);
        if( success )
        {
            seed( bigSeed, N );
            return;
        }
    }

    // Was not successful, so use time() and clock() instead
    seed( hash( time(NULL), clock() ) );
}

inline MTRand::MTRand( const uint32 oneSeed )
{
    seed(oneSeed);
}

inline MTRand::MTRand( uint32 *const bigSeed, const uint32 seedLength )
{
    seed(bigSeed,seedLength);
}

inline MTRand::MTRand()
{
    seed();
}

inline MTRand::MTRand( const MTRand& o )
{
    register const uint32 *t = o.state;
    register uint32 *s = state;
    register int i = N;
    for( ; i--; *s++ = *t++ ) {}
    left = o.left;
    pNext = &state[N-left];
    norm_y_valid=false;
}

inline MTRand::uint32 MTRand::randInt()
{
    // Pull a 32-bit integer from the generator state
    // Every other access function simply transforms the numbers extracted here

    if( left == 0 ) reload();
    --left;

    register uint32 s1;
    s1 = *pNext++;
    s1 ^= (s1 >> 11);
    s1 ^= (s1 <<  7) & 0x9d2c5680UL;
    s1 ^= (s1 << 15) & 0xefc60000UL;
    return ( s1 ^ (s1 >> 18) );
}

inline MTRand::uint32 MTRand::randInt( const uint32 n )
{
    // Find which bits are used in n
    // Optimized by Magnus Jonsson (magnus@smartelectronix.com)
    uint32 used = n;
    used |= used >> 1;
    used |= used >> 2;
    used |= used >> 4;
    used |= used >> 8;
    used |= used >> 16;

    // Draw numbers until one is found in [0,n]
    uint32 i;
    do
        i = randInt() & used;  // toss unused bits to shorten search
    while( i > n );
    return i;
}

inline double MTRand::rand()
{
    return double(randInt()) * (1.0/4294967295.0);
}

inline double MTRand::rand( const double n )
{
    return rand() * n;
}

inline double MTRand::randExc()
{
    return double(randInt()) * (1.0/4294967296.0);
}

inline double MTRand::randExc( const double n )
{
    return randExc() * n;
}

inline double MTRand::randDblExc()
{
    return ( double(randInt()) + 0.5 ) * (1.0/4294967296.0);
}

inline double MTRand::randDblExc( const double n )
{
    return randDblExc() * n;
}

inline double MTRand::rand53()
{
    uint32 a = randInt() >> 5, b = randInt() >> 6;
    return ( a * 67108864.0 + b ) * (1.0/9007199254740992.0);  // by Isaku Wada
}

inline double MTRand::randNorm( const double mean, const double stddev )
{
    // Return a real number from a normal (Gaussian) distribution with given
    // mean and standard deviation by polar form of Box-Muller transformation
    if (norm_y_valid)
    {
	norm_y_valid=false;
        return mean + norm_y  * stddev;
    }
    double r;
    do
    {
        norm_x = 2.0 * rand() - 1.0;
        norm_y = 2.0 * rand() - 1.0;
        r = norm_x * norm_x + norm_y * norm_y;
    }
    while ( r >= 1.0 || r == 0.0 );
    double s = sqrt( -2.0 * log(r) / r );
    norm_x *= s;
    norm_y *= s;
    norm_y_valid=true;
    return mean + norm_x * stddev;
}

inline double MTRand::operator()()
{
    return rand();
}

inline void MTRand::save( uint32* saveArray ) const
{
    register const uint32 *s = state;
    register uint32 *sa = saveArray;
    register int i = N;
    for( ; i--; *sa++ = *s++ ) {}
    *sa = left;
}

inline void MTRand::load( uint32 *const loadArray )
{
    register uint32 *s = state;
    register uint32 *la = loadArray;
    register int i = N;
    for( ; i--; *s++ = *la++ ) {}
    left = *la;
    pNext = &state[N-left];
}

inline std::ostream& operator<<( std::ostream& os, const MTRand& mtrand )
{
    register const MTRand::uint32 *s = mtrand.state;
    register int i = mtrand.N;
    for( ; i--; os << *s++ << "\t" ) {}
    return os << mtrand.left;
}

inline std::istream& operator>>( std::istream& is, MTRand& mtrand )
{
    register MTRand::uint32 *s = mtrand.state;
    register int i = mtrand.N;
    for( ; i--; is >> *s++ ) {}
    is >> mtrand.left;
    mtrand.pNext = &mtrand.state[mtrand.N-mtrand.left];
    return is;
}

inline MTRand& MTRand::operator=( const MTRand& o )
{
    if( this == &o ) return (*this);
    register const uint32 *t = o.state;
    register uint32 *s = state;
    register int i = N;
    for( ; i--; *s++ = *t++ ) {}
    left = o.left;
    pNext = &state[N-left];
    return (*this);
}

inline
std::size_t seedinit(std::size_t seed)
{
    if (seed==0) return time(NULL)+clock();
    else return seed;
}
}
}




#endif  // MERSENNETWISTER_H

// Change log:
//
// v0.1 - First release on 15 May 2000
//      - Based on code by Makoto Matsumoto, Takuji Nishimura, and Shawn Cokus
//      - Translated from C to C++
//      - Made completely ANSI compliant
//      - Designed convenient interface for initialization, seeding, and
//        obtaining numbers in default or user-defined ranges
//      - Added automatic seeding from /dev/urandom or time() and clock()
//      - Provided functions for saving and loading generator state
//
// v0.2 - Fixed bug which reloaded generator one step too late
//
// v0.3 - Switched to clearer, faster reload() code from Matthew Bellew
//
// v0.4 - Removed trailing newline in saved generator format to be consistent
//        with output format of built-in types
//
// v0.5 - Improved portability by replacing static const int's with enum's and
//        clarifying return values in seed(); suggested by Eric Heimburg
//      - Removed MAXINT constant; use 0xffffffffUL instead
//
// v0.6 - Eliminated seed overflow when uint32 is larger than 32 bits
//      - Changed integer [0,n] generator to give better uniformity
//
// v0.7 - Fixed operator precedence ambiguity in reload()
//      - Added access for real numbers in (0,1) and (0,n)
//
// v0.8 - Included time.h header to properly support time_t and clock_t
//
// v1.0 - Revised seeding to match 26 Jan 2002 update of Nishimura and Matsumoto
//      - Allowed for seeding with arrays of any length
//      - Added access for real numbers in [0,1) with 53-bit resolution
//      - Added access for real numbers from normal (Gaussian) distributions
//      - Increased overall speed by optimizing twist()
//      - Doubled speed of integer [0,n] generation
//      - Fixed out-of-range number generation on 64-bit machines
//      - Improved portability by substituting literal constants for long enum's
//      - Changed license from GNU LGPL to BSD
//
// v1.1 - Corrected parameter label in randNorm from "variance" to "stddev"
//      - Changed randNorm algorithm from basic to polar form for efficiency
//      - Updated includes from deprecated <xxxx.h> to standard <cxxxx> forms
//      - Cleaned declarations and definitions to please Intel compiler
//      - Revised twist() operator to work on ones'-complement machines
//      - Fixed reload() function to work when N and M are unsigned
//      - Added copy constructor and copy operator from Salvador Espana
