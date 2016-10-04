#ifndef LIKELIHOODEVALUATION_H
#define LIKELIHOODEVALUATION_H
#include "Markov_LA/Matrix.h"
#include "Markov_Mol/ABC_PatchModel.h"

namespace Markov_Bay_New
{

  class LikelihoodEvaluation
  {
  public:
    ///virtual copy constructors
    virtual LikelihoodEvaluation* clone() const;
    ///virtual default constructors
    virtual LikelihoodEvaluation* create() const;



    static std::string ClassName();



    virtual std::string myClass()const;



    virtual double logL()const;
    virtual double elogL()const;
    virtual double s2logL()const;
    virtual std::size_t nsamples()const;

    virtual double zScore()const;

    virtual double pzScore()const;

    virtual double zs2Score()const;

    virtual double pzs2Score()const;


    LikelihoodEvaluation();
    LikelihoodEvaluation(double logL,
                         double elogL,
                         std::size_t ns,
                         double s2logL);

    LikelihoodEvaluation& operator=(const LikelihoodEvaluation& other);

    friend void swap(LikelihoodEvaluation& oner,LikelihoodEvaluation& other);


  protected:

    double logL_;
    double elogL_;
    std::size_t nsamples_;
    double s2logL_;
  };

}


#endif // LIKELIHOODEVALUATION_H
