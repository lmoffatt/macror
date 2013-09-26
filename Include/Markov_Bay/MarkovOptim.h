#ifndef MARKOVOPTIM_H
#define MARKOVOPTIM_H

#include <cstddef>
#include <string>

#include "Markov_LA/Matrix.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixInverse.h"

namespace Markov_Bay
{



template <typename F>
class Markov_Optim
{
    /**

    this class contains all the optimization functions I would like to make up.

    */
    /**  THE function to be optimized*/
public:
    F f;

    /**
      Hessian approximation
      */

    enum  hessian_update {BFGS,FIM,TaylorLL};

    /**
       first declare the parameters independent on the function to be optimized
       */

    std::size_t maxiter,maxfeval,maxfevalLoop;   // maximun number of iterations and of function evaluations
    double resx,resf,resg,resa;          // maximal resolution in x (parameters), f (function) and g(gradient)
    double eps;                     // epsilon increment for the obtention of the derivative

    /** variables common to all optimizations independent from the function */
    std::size_t iter,ifeval,ifevalLoop;   // algorithm iteration and number of function evaluations counter
    std::string termination;  // message indicating the termination mode
    std::size_t n; // number of parameters
    double y0,y1,y2;

    /** variables for Levenberg-Marquardt algorithm*/
    double landa,v;

    /**variables specific of the Hessian update  */
    double sigma;

    /**  parameters specific of Linear search */
    double c1,c2; // Wolf conditions constants

    /**   variables specific of Linear search */
    double alfa,beta,df0,df1,a,b1,b2;

    /**    parameters, function evaluations, gradients and hessian       */
    Markov_LA::M_Matrix<double> x0,x1,x2;  //this is the value to be optimized
    Markov_LA::M_Matrix<double> dx,di,delta; // this is the increment in x for the calculation of the derivative
    Markov_LA::M_Matrix<double> d; // direction of seach

    Markov_LA::M_Matrix<double> G0,G1,G0T; //gradient Df(x)
    Markov_LA::M_Matrix<double> Hinv; //inverse of hessian =D2f(x)

    //  Markov_LA::M_Matrix<double> fminBFGS(double (*myfunc) (Markov_LA::M_Matrix<double>),Markov_LA::M_Matrix<double>& x);


    std::ostream& put(std::ostream& s)const
    {
	s<<"\n Optimization \n";
	s<<"\n Function \n"<<f;
	s<<"\n finalization\n"<<termination;
	s<<"\n niter="<<this->iter<<"\t nfeval="<<this->ifeval<<"\n";
	s<<"\n exp(x)\n"<<exp10(x1);
	s<<"\n LL=\n"<<y1;
	s<<"\nHinv=\n"<<Hinv;
	s<<"\nG0=\n"<<Transpose(G0);
	return s;
    }




    Markov_LA::M_Matrix<double> fmin(Markov_LA::M_Matrix<double>& x, hessian_update hu=BFGS);
    Markov_Optim(const F& f0,Markov_LA::M_Matrix<double>& x):
	f(f0),
	maxiter(1000),
	maxfeval(2000),
	maxfevalLoop(50),
	resx(1e-12),
	resf(1e-7),
	resg(1e-5),
	resa(1e-14),
	eps(1e-7),
	n(size(x)),
	c1(0.1),
	c2(0.5),
	x0(size(x),1),
	x1(size(x),1),
	x2(size(x),1),
	dx(size(x),1),
	di(size(x),1),
	delta(size(x),1),
	d(size(x),1),
	G0(size(x),1),
	G1(size(x),1),
	G0T(1,size(x)),
	Hinv(size(x),size(x)) {}
};




template <class F>
std::ostream& operator<< (std::ostream& s,const Markov_Optim<F>& x)
{
    return x.put(s);
}



//class Markov_LA::M_Matrix<double>;

template <class F>
Markov_LA::M_Matrix<double>  Markov_Optim<F>::fmin(Markov_LA::M_Matrix<double>& x,hessian_update hu)
{

    /****

    it has to do the following:

    1. return a value of y=f(xi)
    2. return a value of G=Df(xi)
    3. update a value of H(xi) using y=G1-G0 and s=x1-x0
    4. obtain a value of d using d=-Hinv*G
    5  perform a linear search of f(xi) over d using wolf conditions and cubic interpolation
    6. obtain xi+1
    7. set stop conditions:

    format x(n,1) G(n,1) H(n,n)

    8*/

    /** this procedure actualizes the gradient                                            */

    iter=0;
    ifeval=0;
    x1=x;
    /* for (i=0; i<n; i++){
	x1[i]=x[i];
    }
    */
    //f=f0;
   // Markov_LA::M_Matrix<double> G4(G0);
    Markov_LA::M_Matrix<double> H;
    a=1e-5;
    landa=1000;
    v=2;
    while (true)
    {
	y1=f(x1);
	if (!std::isfinite(y1))
	{
	    termination=" initial infinite Likelihood";
	    break;
	}
	ifeval++;
	std::cout<<"\niter="<<iter<<"   "<< ifeval<<"   y1=  "<<y1<<"   df0="<<df0;
	std::cout<< "\n  d= "<<Transpose(d);
	std::cout<<"\n   x1=  "<<Transpose(exp10(x1));
	if (!std::isfinite(y1))
	{
	    std::cout<<" \n infinite Likelihood \n";
	    break;
	}
	//std::cout<<"\n   G0=  "<<T(G1);
	switch (hu)
	{
	case BFGS:
	{
	    for (std::size_t i=0; i<size(x0); i++)
	    {
		di=0.0;
		di[i]=eps;
		Markov_LA::M_Matrix<double> xrun=x1+di;
		G1[i]=(f(xrun)-y1)/di[i];
		ifeval++;
		//     G4[i]=(1./di[i]/12)*(f(x1-(di*2))-8*f(x1-di)+8*f(x1+di)-f(x1+(di*2))); ifeval+=4;
	    }
	    std::cout<<"\n   G1=  "<<Transpose(G1);
	    // std::cout<<"\n  G4="<<G4;
	    /**   stop conditions
	    1. how much is the rounding error?
	    2. G.norm_inf
	    3. GT Hinv G
	    4 max( HinvG)

	    */

	    if (iter==0)
	    {
		Hinv=Markov_LA::eye<double>(n);
		a=std::min(a,0.01/norm_inf(G1));
		std::cout<<"\n a=\t"<<a<<"\n";
	    }
	    else   /**                     BFGS inverse of hessian update */
	    {
		Markov_LA::M_Matrix<double> y,yT;  //used for the hessian update
		Markov_LA::M_Matrix<double> s,sT;
		y=G1-G0;
		s=x1-x0;
		std::cout<<"\n   x1-x0=  "<<Transpose(s)<<"\n";

		//    sT=T(s);
		//    yT=T(y);
		if ((Transpose(s)*y)[0]>0)
		{
		    sigma=pow((Transpose(s)*y)[0],0.5);
		    //     std::cerr<<"sigma"<<sigma;
		    s=s/sigma;
		    y=y/sigma;
		    sT=Transpose(s);
		    yT=Transpose(y);

		    //Hinv=Hinv+(s*sT)*(sT*y+yT*Hinv*y)/pow(flatten(sT*y),2)-(Hinv*y*sT+s*yT*Hinv)/flatten(sT*y);
		    Hinv=Hinv+
			 (s-(Hinv*y))*sT + s * Transpose( s - (Hinv*y) )-
			 (s*sT)*(Transpose(s - (Hinv * y ) )* y)[0];

		    /**     last formula is from
		     http://www.math.washington.edu/~burke/crs/408f/notes/nlp/direction.pdf

		     */
		}
	    }
	    //std::cout<<"\  Hinv=\n"<<Hinv;
	    G0=G1;
	    G0T=Transpose(G0);
	    d=-Hinv*G0; //that determine the direction of search.
	    df0=(G0T*d)[0];
	}
	break;
	case FIM:
	{
	    Markov_LA::M_Matrix<double> pL(f.nsamples(),1);
	    pL=f.plogL();
	    Markov_LA::M_Matrix<double> JL(f.nsamples(),n);
	    for (std::size_t i=0; i<size(x0); i++)
	    {
		di=0.0;
		di[i]=eps;
		Markov_LA::M_Matrix<double> xrun=x1+di;
		G1[i]=(f(xrun)-y1)/di[i];
		// JL=JL(":",i,((f.plogL()-pL)/di[i])-(G1[i]/f.nsamples()));
		JL=JL(":",i,((f.plogL()-pL)/di[i]));
		ifeval++;
		//     G4[i]=(1./di[i]/12)*(f(x1-(di*2))-8*f(x1-di)+8*f(x1+di)-f(x1+(di*2))); ifeval+=4;
	    }
	    std::cout<<"\n   G1=  "<<Transpose(G1);
	    // std::cout<<"\n  G4="<<G4;
	    /**   stop conditions
	    1. how much is the rounding error?
	    2. G.norm_inf
	    3. GT Hinv G
	    4 max( HinvG)

	    */
	    /* for (std::size_t i=0; i<f.nsamples(); i++)
		 for (std::size_t j=0; j<n; j++)
		     JL(i,j)-=G1[j]/f.nsamples();
	    */
	    H=TranspMult(JL,JL);
	    Hinv=inv(H+(diag(H)*landa));
	    //  std::cout<<"\  Hinv=\n"<<Hinv;
	    G0=G1;
	    G0T=Transpose(G0);
	    d=-Hinv*G0; //that determine the direction of search.
	    df0=(G0T*d)[0];
	}
	break;
	case TaylorLL:
	{
	    Markov_LA::M_Matrix<double> s2(f.nsamples(),1);
	    Markov_LA::M_Matrix<double> yf(f.nsamples(),1);
	    Markov_LA::M_Matrix<double> y(f.nsamples(),1);
	    s2=f.s2();
	    yf=f.yf();
	    y=f.y();
	    Markov_LA::M_Matrix<double> Js2(f.nsamples(),n);
	    Markov_LA::M_Matrix<double> Jyf(f.nsamples(),n);

	    for (std::size_t i=0; i<size(x0); i++)
	    {
		di=0.0;
		di[i]=eps;
		Markov_LA::M_Matrix<double> xrun=x1+di;
		G1[i]=(f(xrun)-y1)/di[i];
		Js2=Js2(":",i,(f.s2()-s2)/di[i]);
		Jyf=Jyf(":",i,(f.yf()-yf)/di[i]);
		ifeval++;
		//     G4[i]=(1./di[i]/12)*(f(x1-(di*2))-8*f(x1-di)+8*f(x1+di)-f(x1+(di*2))); ifeval+=4;
	    }
	    std::cout<<"\n kj  G1=  "<<Transpose(G1);
	    //     std::cout<<"\n  G4="<<G4;
	    /**   stop conditions
	    1. how much is the rounding error?
	    2. G.norm_inf
	    3. GT Hinv G
	    4 max( HinvG)

	    */
	    H=Markov_LA::zeros<double>(n,n);
	    for (std::size_t k=0; k<f.nsamples(); k++)
	    {
		double ass=0.5/std::pow(s2[k],2)-std::pow((y[k]-yf[k]),2)/std::pow(s2[k],3);
		double asy=-(y[k]-yf[k])/std::pow(s2[k],2);
		double ayy=-1.0/s2[k];
		for (std::size_t i=0; i<n; i++)
		    for (std::size_t j=0; j<n; j++)
			H(i,j)-=ass*Js2(k,i)*Js2(k,j)+
				asy*(Js2(k,i)*Jyf(k,j)+Jyf(k,i)*Js2(k,j))+
				ayy*(Jyf(k,i)*Jyf(k,j));
	    };

	    Hinv=inv(H+diag(H)*landa);
	    //   std::cout<<"\  Hinv=\n"<<Hinv;
	    G0=G1;
	    G0T=Transpose(G0);
	    d=-Hinv*G0; //that determine the direction of search.
	    df0=(G0T*d)[0];
	}
	break;

	};
	if (std::abs(norm_inf(x1-x0))<resx)
	{
	    termination=" delta resx";
	    std::cout<<"\nfinaliza delta resx=\n"<<x1-x0<<"\n";
	    break;
	};
	x0=x1;
	y0=y1;

	if (std::abs(norm_inf(d))<resx)
	{
	    termination="resx";
	    std::cout<<"\nfinaliza resx=\n"<<d<<"\n";
	    break;
	};
	if (std::abs(df0)<resf)
	{
	    termination="resf";
	    std::cout<<"\nfinaliza resf="<<std::abs(df0) <<"\n";
	    break;
	};
	if(a<resa)
	{
	    termination="resa";
	    std::cout<<"\nfinaliza a="<<std::abs(a) <<"< resa="<<resa<<"\n";

	    break;
	};
	if (ifeval>maxfeval)
	{
	    termination="maxfeval";
	    std::cout<<"\nfinaliza maxfeval\n";
	    break;
	};
	if (iter>maxiter)
	{
	    termination="maxiter";
	    std::cout<<"\nfinaliza maxiter\n";
	    break;
	};

	switch (hu)
	{
	case FIM:
	case TaylorLL:
	    if (landa>1e-5)
	    {

		x1=x0+d;
		y1=f(x1);
		ifeval++;
		Markov_LA::M_Matrix<double> Hinv_0;
		Markov_LA::M_Matrix<double> d_0;
		double y_0=Markov_LA::NaN();
		// std::cout<<"\n H \n"<<H;
		// std::cout<<"\n H+diag(H)*(landa*v) \n"<<H+diag(H)*(landa*v);
		Markov_LA::M_Matrix<double> Hinv_1=inv(H+diag(H)*(landa*v));
		Markov_LA::M_Matrix<double> d_1=-Hinv_1*G0; //that determine the direction of search.
		double y_1=f(x0+d_1);
		ifeval++;
		//  std::cout<<"\n y_0 y1 y_1"<<y_0<<" "<<y1<<" "<<y_1;
		while ((y_1>=y0)|| (!std::isfinite(y_1))||(!std::isfinite(y1)))
		{
		    Hinv_0=Hinv;
		    d_0=d;
		    y_0=y1;
		    x1=x0+d_1;
		    y1=y_1;
		    landa=landa*v;
		    Hinv_1=inv(H+diag(H)*(landa*v));
		    d_1=-Hinv_1*G0; //that determine the direction of search.
		    y_1=f(x0+d_1);
		    ifeval++;
		    //    std::cout<<"\n y_1 "<<y_1<<"y0"<<y0;
		};
		while (y1>=y_1)
		{
		    Hinv_0=Hinv;
		    d_0=d;
		    y_0=y1;
		    x1=x0+d_1;
		    y1=y_1;
		    landa=landa*v;
		    Hinv_1=inv(H+diag(H)*(landa*v));
		    d_1=-Hinv_1*G0; //that determine the direction of search.
		    y_1=f(x0+d_1);
		    ifeval++;
		};
		if (Markov_LA::isNaN(y_0))
		{
		    Hinv_0=inv(H+diag(H)*(landa/v));
		    d_0=-Hinv_0*G0; //that determine the direction of search.
		    y_0=f(x0+d_0);
		    ifeval++;
		}
		// std::cout<<"\n y_0 y1 y_1"<<y_0<<" "<<y1<<" "<<y_1;

		while (y1>y_0)
		{
		    Hinv_1=Hinv;
		    d_1=d;
		    y_1=y1;
		    x1=x0+d_0;
		    y1=y_0;
		    landa=landa/v;
		    Hinv_0=inv(H+diag(H)*(landa/v));
		    d_0=-Hinv_0*G0; //that determine the direction of search.
		    y_0=f(x0+d_0);
		    ifeval++;
		}
		std::cout<<"\n \n landa y_0 y1 y_1  "<<landa<<"   "<<y_0<<"   "<<y1<<"   "<<y_1<<"\n\n";
		//     break;
	    }

	case BFGS:
	{

	    /** cuadratic line search used by matlab
		    */

	    /**   Bracketing phase
	    */
	   // c1=0.1;

	   // c2=0.5;

	    // Nocedal gives example values of c1 = 10 - 4 and c2 = 0.9 for Newton or quasi-Newton methods
	    //c1=1e-4;
	    //c2=0.9;
	    alfa=0;
	    beta=INFINITY;
	    ifevalLoop=0;
	    // this loop look after a value of a that satisfy Wolfe conditions
	    while (true)
	    {
		if (!(Markov_LA::isFinite(a)))
		    a=resa*1000;
		x1=x0+d*a;
		//     std::cout<<"\nx1"<<x1<<"y1"<<y1;
		      std::cout<<"\na="<<a<<"\n";
		y1=f(x1);
		ifeval++;
		ifevalLoop++;
		// std::cout<<"\n ifevalLoop \n"<<ifevalLoop;

		//Armijo rule
		if (((y1>y0+df0*c1*a)||(!Markov_LA::isFinite(y1)))&&(ifevalLoop<maxfevalLoop))
		{
		    std::cout<<" y1-y0="<<y1-y0;
		    beta=a;
		    a=0.5*(alfa+beta);
		}
		else
		{
		    double ffeps=eps/norm(d);
		    double ff1=f(x1+d*ffeps);

		    while (!Markov_LA::isFinite(ff1))
		    {
			ffeps/=2;
			ff1=f(x1+d*ffeps);

		    }
		    df1=(ff1-y1)/ffeps;
		    ifeval++;
		    ifevalLoop++;
		    //     std::cout<<"\n ifevalLoop \n"<<ifevalLoop;
		    //  df1=(f(x1-(d*(eps*2)))-8*f(x1-(d*eps))+8*f(x1+(d*eps))-f(x1+(d*(eps*2))))/12/eps;

		    //curvature conditions
		    if ((df1<c2*df0)&&ifevalLoop<maxfevalLoop)
		    {
			alfa=a;
			if (beta==INFINITY)
			{
			    a=2*alfa;
			}
			else
			{
			    a=0.5*(alfa+beta);
			};
		    }
		    else break;
		}
	    }

	    /** if it is possible, apply a cubic interpolation phase                                                                              */

	    b1=df0+df1-3*(y1-y0)/a;
	    Markov_LA::ToleranceComparison<double> tol;
	    if (((b1*b1-df0*df1)>0)&&(!tol.isEqual((df1-df0+2*b2),0.0)))
	    {
		b2=pow((b1*b1-df0*df1),0.5);
		a=a-a*(df1+b2-b1)/(df1-df0+2*b2);
	    }
	    x2=x0+d*a;
	    y2=f(x2);
	    ifeval++;
	    if ((y2==y2)&&(y2<y1))
	    {
		y1=y2;
		x1=x2;
	    }
	}
	break;
	}
	iter++;
    };
    std::cout<<"\n LL=\n"<<y1;
    std::cout<<"\n exp10 x1=\n"<<exp10(x1);
    std::cout<<"\nHinv=\n"<<Hinv;
    std::cout<<"\nsigma\n"<<sigma;
    std::cout<<"\nG0=\n"<<Transpose(G0);
    std::cout<<"\na=\n"<<a;
// std::cout<<"\ns=\n"<<s;
// std::cout<<"\ny=\n"<<y;

    return x1;
}

}
#endif // MARKOVOPTIM_H
