#include "Markov_LA/auxiliarMath.h"
#include <cmath>

#include "Markov_LA/ContinuedFraction.h"

namespace Markov_LA
{




/**
  returns the infinity representation for doubles
  */
double infinity()
{
    return std::numeric_limits<double>::infinity();
}


/**
  returns the Not a Number representation for doubles
  */

double NaN()
{
    return std::numeric_limits<double>::quiet_NaN();
}

/**
  checks whether a double is a NaN
  @returns true if it is a NaN()
  @returns false otherwise (including infinite())

  */
bool isNaN(double x)
{
    return std::isnan(x);
}




double erfinv(double P)
{
    double	Y,A,B,X,Z,W,WI,SN,SD,F,Z2,SIGMA;
    double	A1=-.5751703,A2=-1.896513,A3=-.5496261E-1;
    double	B0=-.1137730,B1=-3.293474,B2=-2.374996,B3=-1.187515;
    double	C0=-.1146666,C1=-.1314774,C2=-.2368201,C3=.5073975e-1;
    double	D0=-44.27977,D1=21.98546,D2=-7.586103;
    double	E0=-.5668422E-1,E1=.3937021,E2=-.3166501,E3=.6208963E-1;
    double	F0=-6.266786,F1=4.666263,F2=-2.962883;
    double	G0=.1851159E-3,G1=-.2028152E-2,G2=-.1498384,G3=.1078639E-1;
    double	H0=.9952975E-1,H1=.5211733,H2=-.6888301E-1;
    //	double	RINFM=1.7014E+38;

    X=P;
    if (X>0)
	    SIGMA=1;
    else if (X<0)
	    SIGMA=-1;
    else
	SIGMA=0;
//    it_error_if(X<-1 || X>1,"erfinv : argument out of bounds");
    Z=fabs(X);
    if (Z>.85) {
	A=1-Z;
	B=Z;
	W=sqrt(-log(A+A*B));
	if (W>=2.5) {
	    if (W>=4.) {
		WI=1./W;
		SN=((G3*WI+G2)*WI+G1)*WI;
		SD=((WI+H2)*WI+H1)*WI+H0;
		F=W+W*(G0+SN/SD);
	    } else {
		SN=((E3*W+E2)*W+E1)*W;
		SD=((W+F2)*W+F1)*W+F0;
		F=W+W*(E0+SN/SD);
	    }
	} else {
	    SN=((C3*W+C2)*W+C1)*W;
	    SD=((W+D2)*W+D1)*W+D0;
	    F=W+W*(C0+SN/SD);
	}
    } else {
	Z2=Z*Z;
	F=Z+Z*(B0+A1*Z2/(B1+Z2+A2/(B2+Z2+A3/(B3+Z2))));
    }
    Y=SIGMA*F;
    return Y;
}

template<>
bool isFinite(M_Matrix<double> x)
{
  for (std::size_t i=0; i<size(x); i++)
    {
      if (!isFinite(x[i]))
        return false;
    }
  return true;
}





/**
  checks whether a value is finite
  @returns true if it is finite
  @returns false if it is -infinite(), +infinite() or NaN()
   */

template<typename T>
bool isFinite(T x)
{    return ((x>-std::numeric_limits<T>::infinity())&&
	    (x<std::numeric_limits<T>::infinity())&&
	     !isNaN(x));
}



double exp10(double x)
{
    return std::exp(x*log(10));
}

double Z_WH_approximation(double x, double n)
{
//Wilson   and   Hilferty (1931),

    double Z= (std::pow( x /n,1./3) -  (1.-2./9./n ))/(std::sqrt(2./9./n));
       return Z;
}
template bool isFinite(double x);


double NormalPdf(double x, double mean, double s)
{
assert(s>0);
double result=NormalPdf((x-mean)/s)/s;
return result;
}
;
double NormalPdf(double x)
{
double result=std::exp(-x*x/2)/std::sqrt(2*PI);
return result;
}

double NormalCdf(double x, double mean, double s)
{

assert(s>0);
double result=NormalCdf((x-mean)/s);
return result;
}

double NormalCdf(double x)
{
double result=0.5*(1+erf(x/sqrt(2.)));
return result;
}


double LogMultinomialPdf(const M_Matrix<std::size_t>& x, const M_Matrix<double>& P)
{
    double result=0;
    std::size_t sumN=0;
    for (std::size_t i=0; i<size(x); ++i)
    {
        sumN+=x[i];
        result+=+x[i]*log(P[i])-LogGammaFunction(x[i]);
    }
    result+=LogGammaFunction(sumN);
    return result;
}
double MultinomialPdf(const M_Matrix<std::size_t>& x, const M_Matrix<double>& P)
{
    return exp(LogMultinomialPdf(x,P));
}



double NormalCdfInv(double p, double mean, double s)
{
 double result=NormalCdfInv(p)*s+mean;
return result;
}

double NormalCdfInv(double p)
{
double result=erfinv(2*p-1)*std::sqrt(2.);
return result;
}





double ChiSqrCdf(double x, double k)
{

std::size_t n=10;

double result0=GammaRegularized(0.5*k,0.5*x,n);
double result1=GammaRegularized(0.5*k,0.5*x,n*2);
double resultz=NormalCdf(Z_WH_approximation(x,k));

const std::size_t nmax=256;

while((std::abs(result0-resultz)>0.053)||(std::abs(result0-result1)>1e-5))
{
n*=2;
result0=result1;
result1=GammaRegularized(0.5*k,0.5*x,n*2);

if (n>nmax)
return resultz;
}
return result1;

}




double GammaRegularized(double s, double z, std::size_t n)
{
std::vector<double> a(n);

std::vector<double> b(n);

double loga0=s*log(z)-z-LogGammaFunction(s);
a[0]=exp(loga0);
b[0]=0;
a[1]=-s*z;

for (std::size_t i=1;i<n;i++)
{
    b[i]=s+i-1;
 }
for (std::size_t i=1;i<n/2;i++)
{
    a[i*2]=i*z;
    a[i*2+1]=-(s+i)*z;
}


return Markov_LA::ContinuedFraction(a,b)();


}

double LogGammaFunction(double z)
{
    /*
Nemes, Gergo (2010), "New asymptotic expansion for the Gamma function",
Archiv der Mathematik 95 (2): 161–169, doi:10.1007/s00013-010-0146-9, ISSN 0003-889X.
*/

    if (z<9)
    {

        std::size_t g = 7;
        double p[] = {0.99999999999980993, 676.5203681218851, -1259.1392167224028,
                      771.32342877765313, -176.61502916214059, 12.507343278686905,
                      -0.13857109526572012, 9.9843695780195716e-6, 1.5056327351493116e-7};

        if (z < 0.5)
        {
            return log(PI)-log(sin(PI*z))+(LogGammaFunction(1-z));
        }
        else
        {
            z -= 1;
            double x = p[0];
            for (std::size_t i=1;i<g+2;i++)
                x += p[i]/(z+i);
            double t = z + g + 0.5;
            double logg= log(sqrt(2*PI) * std::pow(t,(z+0.5)) * exp(-t) * x);
            return logg;
        }
    }
    else
    {

        double logg=0.5*(log(2*PI)-log(z))+
                z*(log(z+1.0/(12.0*z-1.0/10.0/z))-1);


        return logg;
    }
}

double GammaFunction(double x)
{
    return exp(LogGammaFunction(x));
}


double ChiSqrPdf(double x, double k)
{
    return exp(
		-0.5*k*log(2.0)-
		LogGammaFunction(0.5*k)+
		(0.5*k-1)*log(x)-0.5*x
		);
}



double floorSafe(double x)
{
    return floor(x*(1.0+1E-9));
}

double ceilSafe(double x)
{
    return ceil(x*(1.0-1E-9));
}









}
