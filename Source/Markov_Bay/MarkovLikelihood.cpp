#include "Markov_Bay/MarkovLikelihood.h"

#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixRounding.h"  //isfinite
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_Bay/MacroDRStep.h"
#include "Markov_Bay/MacroRStep.h"
#include "Markov_Bay/MacroNRStep.h"
#include "Markov_Bay/MacroAproxStep.h"



#include "Markov_LA/auxiliarMath.h"

namespace Markov_Bay
{

  Markov_Likelihood* Markov_Likelihood::clone() const
  {
    return new Markov_Likelihood(*this);
  }

  /// default constructors
  Markov_Likelihood* Markov_Likelihood::create() const
  {
    return new Markov_Likelihood();
  }

  Markov_Likelihood::~Markov_Likelihood() {}

  const Markov_IO::ABC_Experiment& Markov_Likelihood::experiment()const
  {
    return *E_A;
  }


  LikelihoodEvaluation Markov_Likelihood::run(const Markov_IO::Parameters& beta)
  {
    if (beta.isValid())
      {

        L_A->apply_parameters(beta);

        return run();
      }
    else
      return infinity();


  }


  PartialLikelihoodEvaluation Markov_Likelihood::run(const Markov_IO::Parameters& beta, const std::string&)
  {
    L_A->apply_parameters(beta);

    return run("dummy");

  }


  YfitLikelihoodEvaluation Markov_Likelihood::run(const Markov_IO::Parameters& beta,
                                                  const std::string& ,
                                                  const std::string& )
  {
    L_A->apply_parameters(beta);
    return run("dummy0","dummy1");

  }




  Markov_LA::M_Matrix<double> Markov_Likelihood::score(const Markov_IO::Parameters& beta)
  {
    Markov_LA::M_Matrix<double> G(beta.size(),1);
    double dx=getOptions().real("Delta_x_for_score");
    double dxx;
    Markov_IO::Parameters p(beta);
    LikelihoodEvaluation L_0=run(p);

    if (Markov_LA::isFinite(L_0.logL()))
    {
#pragma omp parallel for
    for (std::size_t i=0; i<beta.size();++i)
      {
        Markov_IO::Parameters beta_i(beta);
        Markov_LA::M_Matrix<double> x(beta.transformed_values());
        dxx=dx;
        while(dxx>0)
          {
            x[i]+=dxx;
            beta_i.transformed_values(x);
            LikelihoodEvaluation L_i=run(beta_i);

            if (Markov_LA::isFinite(L_i.logL()))
              {
                G[i]=(L_i.logL()-L_0.logL())/dxx;
                break;
              }
            else
              dxx/=2;
          }
      }
    }
    return G;
  }


  double Markov_Likelihood::score(const Markov_IO::Parameters& beta,
                                  const Markov_LA::M_Matrix<double>&  direction)
  {
    Markov_IO::Parameters p(beta);
    LikelihoodEvaluation L_0=run(p);


    double dx=getOptions().real("Delta_x_for_score")/Markov_LA::norm(direction);
    Markov_IO::Parameters beta_d=beta;
    beta_d.transformed_values(beta.transformed_values()+direction*dx);
    LikelihoodEvaluation L_d=run(beta_d);
    while (!Markov_LA::isFinite(L_d.logL()))
      {
        dx/=2;
        beta_d.transformed_values(beta.transformed_values()+direction*dx);
        L_d=run(beta_d);
      }
    double df=(L_d.logL()-L_0.logL())/dx;
    return df;
  }






  Markov_LA::M_Matrix<double>
  Markov_Likelihood::FisherInformationMatrix(const Markov_IO::Parameters& beta)
  {
    double dx=getOptions().real("Delta_x_for_score");
    PartialLikelihoodEvaluation pL_0=run(beta,":");

    Markov_LA::M_Matrix<double> JL(pL_0.nsamples(),beta.size());
    for (std::size_t i=0; i<beta.size();++i)
      {
        Markov_IO::Parameters beta_i(beta);
        Markov_LA::M_Matrix<double> x(beta.transformed_values());
        x[i]+=dx;
        beta_i.transformed_values(x);
        PartialLikelihoodEvaluation pL_i=run(beta_i,":");
        JL=JL(":",i,((pL_i.plogL()-pL_0.plogL())/dx));
      }
    Markov_LA::M_Matrix<double> FIM=Markov_LA::TranspMult(JL,JL);
    return FIM;

  }


  Markov_LA::M_Matrix<double>
  Markov_Likelihood::HessianAproximationMatrix(const Markov_IO::Parameters& beta)
  {
    double dx=getOptions().real("Delta_x_for_score");
    YfitLikelihoodEvaluation pL_0=run(beta,":",":");

    Markov_LA::M_Matrix<double> Dy(pL_0.nsamples(),beta.size());
    Markov_LA::M_Matrix<double> Ds2(pL_0.nsamples(),beta.size());

    for (std::size_t i=0; i<beta.size();++i)
      {
        Markov_IO::Parameters beta_i(beta);
        Markov_LA::M_Matrix<double> x(beta.transformed_values());
        x[i]+=dx;
        beta_i.transformed_values(x);
        YfitLikelihoodEvaluation pL_i=run(beta_i,":",":");
        Dy=Dy(":",i,((pL_i.yfit()-pL_0.yfit())/dx));
        Ds2=Ds2(":",i,((pL_i.s2()-pL_0.s2())/dx));

      }
    Markov_LA::M_Matrix<double> Hy=Markov_LA::zeros<double>(beta.size(),beta.size());
    for (std::size_t i=0; i<beta.size();++i)
      for (std::size_t j=0; j<beta.size();++j)
        for (std::size_t k=0; k<pL_0.nsamples();++k)
            Hy(i,j)+= (Dy(k,i)*Dy(k,j)/pL_0.s2()(k,0))
                +(Ds2(k,i)*Ds2(k,j)/pL_0.s2()(k,0)/pL_0.s2()(k,0)/2.0);




    return Hy;

  }




  LikelihoodEvaluation Markov_Likelihood::run()
  {
    double logL=0;
    double elogL=0;
    std::size_t ns=0;
    double s2logL=0;
    //  std::cerr<<"inside run \n"<<patch();

    if (!Options_.boolean("run_Approximation"))
      {
        for (std::size_t i_r=0; i_r<E_A->num_replicates(); i_r++)
          {
            E_A->replicate(i_r);
            L_A->start(this->E_A->trace(0)[0].sub_step(0).x());
            for (std::size_t i=0; i<E_A->num_traces(); i++)
              {
                E_A->trace(i);
                for (std::size_t j=0; j<E_A->num_measures(); j++)
                  {
                    L_A->run((*E_A)[j]);
                    if (!((L_A->P_mean())>=0.0)||(!Markov_LA::isFinite(L_A->plogL())))
                      if (!Markov_LA::isFinite(L_A->plogL()))
                        {
                          std::cout<<"\n (!isfinite(L_A->plogL()))\n";
                          std::cout<<" \nreplicate "<<i_r<<" trace "<<i<<" j "<<j<<" t "<<E_A->t();
                          std::cout<<" dt "<<E_A->dt()<<" x "<<E_A->x()<<" y "<<E_A->y()<<"\n";
                          std::cout<<*L_A;
                          std::cout<<this->patch();
                          return infinity();
                          //    press_any_key_to_continue();
                        };
                    logL+=L_A->plogL();
                    elogL+=L_A->eplogL();
                    s2logL+=std::pow((L_A->plogL()-L_A->eplogL()),2);
                    ns++;

                  };
                L_A->run(E_A->trace_interval());
              };
          };

        return LikelihoodEvaluation(name_,logL,elogL,ns,s2logL);

      }
    else
      {
        for (std::size_t i_r=0; i_r<E_A->num_replicates(); i_r++)
          {
            E_A->replicate(i_r);
            L_A->start(this->E_A->trace(0)[0].sub_step(0).x());
            Macro_Aprox_step As(*L_A,
                                Options_.count("num_samples"),
                                Options_.count("num_steps"),
                                0);
            for (std::size_t i=0; i<E_A->num_traces(); i++)
              {
                E_A->trace(i);
                for (std::size_t j=0; j<E_A->num_measures(); j++)
                  {
                    L_A->run((*E_A)[j]);
                    As.run((*E_A)[j]);
                    std::cout<<L_A->myClass();
                    L_A->put(std::cout);
                    std::cout<<As.myClass();
                    As.put(std::cout);
                    if (!((L_A->P_mean())>=0.0)||(Markov_LA::isFinite(L_A->plogL())))
                      if (!Markov_LA::isFinite(L_A->plogL()))
                        {
                          std::cout<<"\n (!isfinite(L_A->plogL()))\n";
                          std::cout<<" \nreplicate "<<i_r<<" trace "<<i<<" j "<<j<<" t "<<E_A->t();
                          std::cout<<" dt "<<E_A->dt()<<" x "<<E_A->x()<<" y "<<E_A->y()<<"\n";
                          std::cout<<*L_A;
                          std::cout<<this->model();
                          return LikelihoodEvaluation();
                          //    press_any_key_to_continue();
                        };
                    logL+=L_A->plogL();
                    elogL+=L_A->eplogL();
                    s2logL+=std::pow((L_A->plogL()-L_A->eplogL()),2);
                    ns++;

                  };
                L_A->run(E_A->trace_interval());
              };
          };

        return LikelihoodEvaluation(name_,logL,elogL,ns,s2logL);

      }

  }

  LikelihoodEvaluation Markov_Likelihood::infinity()
  {
    double logL=Markov_LA::NaN();
    double elogL=0;
    std::size_t ns=0;
    double s2logL=0;
    //  std::cerr<<"inside run \n"<<patch();

    return LikelihoodEvaluation(name_,logL,elogL,ns,s2logL);


  }


  PartialLikelihoodEvaluation Markov_Likelihood::run(const std::string& /*dummy*/)
  {
    double logL=0;
    double elogL=0;
    double s2logL=0;
    Markov_LA::M_Matrix<double> pLogL(E_A->total_samples(),1);
    std::size_t i_run=0;
    for (std::size_t i_r=0; i_r<E_A->num_replicates(); i_r++)
      {
        E_A->replicate(i_r);
        L_A->start(this->E_A->trace(0)[0].sub_step(0).x());
        for (std::size_t i=0; i<E_A->num_traces(); i++)
          {
            E_A->trace(i);
            for (std::size_t j=0; j<E_A->num_measures(); j++)
              {
                L_A->run((*E_A)[j]);
                if (!((L_A->P_mean())>=0.0)||(Markov_LA::isFinite(L_A->plogL())))
                  if (!Markov_LA::isFinite(L_A->plogL()))
                    {
                      std::cout<<"\n (!isfinite(L_A->plogL()))\n";
                      std::cout<<" \nreplicate "<<i_r<<" trace "<<i<<" j "<<j<<" t "<<E_A->t();
                      std::cout<<" dt "<<E_A->dt()<<" x "<<E_A->x()<<" y "<<E_A->y()<<"\n";
                      std::cout<<*L_A;
                      std::cout<<this->model();
                      return PartialLikelihoodEvaluation();
                      //    press_any_key_to_continue();
                    };
                logL+=L_A->plogL();
                elogL+=L_A->eplogL();
                s2logL+=std::pow((L_A->plogL()-L_A->eplogL()),2);
                pLogL[i_run]=L_A->plogL();
                i_run++;

              };
            L_A->run(E_A->trace_interval());
          };
      };

    return PartialLikelihoodEvaluation(name_,logL,elogL,s2logL,pLogL);

  }


  YfitLikelihoodEvaluation Markov_Likelihood::run(const std::string& , const std::string&)
  {
    double logL=0;
    double elogL=0;
    double s2logL=0;
    Markov_LA::M_Matrix<double> pLogL(E_A->total_samples(),1);
    Markov_LA::M_Matrix<double> yfit(E_A->total_samples(),1);
    Markov_LA::M_Matrix<double> y(E_A->total_samples(),1);
    Markov_LA::M_Matrix<double> s2(E_A->total_samples(),1);

    std::size_t i_run=0;
    for (std::size_t i_r=0; i_r<E_A->num_replicates(); i_r++)
      {
        E_A->replicate(i_r);
        L_A->start(this->E_A->trace(0)[0].x());
        for (std::size_t i=0; i<E_A->num_traces(); i++)
          {
            E_A->trace(i);
            for (std::size_t j=0; j<E_A->num_measures(); j++)
              {
                L_A->run((*E_A)[j]);
                if (!((L_A->P_mean())>=0.0)||(Markov_LA::isFinite(L_A->plogL())))
                  if (!Markov_LA::isFinite(L_A->plogL()))
                    {
                      std::cout<<"\n (!isfinite(L_A->plogL()))\n";
                      std::cout<<" \nreplicate "<<i_r<<" trace "<<i<<" j "<<j<<" t "<<E_A->t();
                      std::cout<<" dt "<<E_A->dt()<<" x "<<E_A->x()<<" y "<<E_A->y()<<"\n";
                      std::cout<<*L_A;
                      std::cout<<this->model();
                      return YfitLikelihoodEvaluation();
                      //    press_any_key_to_continue();
                    };
                logL+=L_A->plogL();
                elogL+=L_A->eplogL();
                s2logL+=std::pow((L_A->plogL()-L_A->eplogL()),2);
                pLogL[i_run]=L_A->plogL();
                yfit[i_run]=L_A->y_mean();
                y[i_run]=E_A->y();
                s2[i_run]=L_A->y_var();
                i_run++;

              };
            L_A->run(E_A->trace_interval());
          };
      };

    return YfitLikelihoodEvaluation(name_,logL,elogL,s2logL,pLogL,yfit,y,s2);

  }



  Markov_Likelihood::Markov_Likelihood(const Markov_Mol::ABC_PatchModel &P,
                                       const Markov_IO::ABC_Experiment &E,
                                       const Markov_IO::ABC_Options &O):
    name_(P.myName()+"_on_"+E.myName()+"_with_"+O.myName()),
    L_A(0),
    E_A(&E),
    Options_(O)
  {
    std::string alg=Options_.name("Likelihood_Algorithm");
    if (Options_.name("Likelihood_Algorithm")=="MacroNR")
      {
        this->L_A= new Macro_NR_step(P,Options_.boolean("Is_Averaging"));
      }
    else if (Options_.name("Likelihood_Algorithm")=="MacroR")
      {
        this->L_A= new Macro_R_step(P,
                                    Options_.boolean("Is_Averaging"),
                                    Options_.boolean("Use_Zero_Guard"));
      }
    else if (Options_.name("Likelihood_Algorithm")=="MacroDR")
      {
        this->L_A= new Macro_DR_step(P,
                                     Options_.boolean("Use_Zero_Guard"));
      }


  }


  Markov_Likelihood::Markov_Likelihood(const Markov_Likelihood& ML):
    name_(ML.name_),
    L_A(ML.L_A->clone()),
    E_A(ML.E_A),
    Options_(ML.Options_)
  {
  }

  Markov_Likelihood::Markov_Likelihood():
    name_(),
    L_A(NULL),
    E_A(NULL),
    Options_()

  {
  }


  Markov_Likelihood& Markov_Likelihood::operator=(const Markov_Likelihood& other)
  {
    if (this!=&other)
      {
        Markov_Likelihood tmp(other);
        swap(*this,tmp);
      }
    return *this;
  }
  void swap(Markov_Likelihood& x,Markov_Likelihood& y){
    std::swap(x.name_,y.name_);
    std::swap(x.L_A,y.L_A);
    std::swap(x.E_A,y.E_A);
    swap(x.Options_,y.Options_);

  }


  const Markov_Mol::ABC_Markov_Model& Markov_Likelihood::model()const
  {
    return L_A->model();
  }

  const Markov_Mol::ABC_PatchModel& Markov_Likelihood::patch()const
  {
    return L_A->patch();
  }



  const Markov_IO::ABC_Options& Markov_Likelihood::getOptions()const
  {
    return this->Options_;
  }
  bool Markov_Likelihood::setOptions(const Markov_IO::ABC_Options &options)
  {
    //Options_(options);
    return true;
  }


  Markov_Likelihood::Options::Options():
    BaseOptions("default")
  {
    push_back("Likelihood_Algorithm",std::string("MacroDR"));
    push_back("Is_Averaging",true);
    push_back("Use_Zero_Guard",true);
    push_back("Delta_x_for_score", 1e-7);
    push_back("show_partialLikelihood",false);
    push_back("show_predictedValue",false);
    push_back("run_Approximation",false);
    push_back("num_steps",std::size_t(100));
    push_back("num_samples",std::size_t(1000));


  }
  Markov_Likelihood::Options::Options(const std::string& myname,
                                      const std::string algorithm,
                                      bool isaveraging,
                                      bool zeroGuard,
                                      double dxForScore,
                                      bool showPartialLikelihood,
                                      bool showPredictedValue,
                                      bool runApproximation,
                                      std::size_t numSteps,
                                      std::size_t numSamples):
    BaseOptions(myname)
  {
    push_back("Likelihood_Algorithm",algorithm);
    push_back("Is_Averaging",isaveraging);
    push_back("Use_Zero_Guard",zeroGuard);
    push_back("Delta_x_for_score",dxForScore);
    push_back("show_partialLikelihood",showPartialLikelihood);
    push_back("show_predictedValue",showPredictedValue);
    push_back("run_Approximation",runApproximation);
    push_back("num_steps",numSteps);
    push_back("num_samples",numSamples);

  }

  Markov_Likelihood::Options::Options(const Markov_IO::ABC_Options& options):
    BaseOptions(options.myName())
  {
    push_back("Likelihood_Algorithm",options.name("Likelihood_Algorithm"));
    push_back("Is_Averaging",options.boolean("Is_Averaging"));
    push_back("Use_Zero_Guard",options.boolean("Use_Zero_Guard"));
    push_back("Delta_x_for_score",options.real("Delta_x_for_score"));
    push_back("show_partialLikelihood",options.boolean("show_partialLikelihood"));
    push_back("show_predictedValue",options.boolean("show_predictedValue"));
    push_back("run_Approximation",options.boolean("run_Approximation"));
    push_back("num_steps",options.count("num_steps"));
    push_back("num_samples",options.count("num_samples"));



  }

  std::string Markov_Likelihood::Options::myClass()const
  {
    return ClassName();
  }

  std::string Markov_Likelihood::Options::ClassName()
  {
    return "Markov_Likelihood_Options";
  }




  std::ostream& Markov_Likelihood::put(std::ostream& s) const
  {
    s<<name_;
    s<<"\n"<<*L_A;
    s<<"\nExperiment name \t"<<E_A->myName();
    s<<"\n Options\n"<<Options_;
    return s;
  }

  bool Markov_Likelihood::operator==(const Markov_Likelihood& other)const
  {     if (name_!=other.name_) return false;
    if (!(*L_A== *other.L_A)) return false;
    if (!(Options_==other.Options_)) return false;
    if (!(E_A->ABC_Object::operator ==(*other.E_A))) return false;
    return true;
  }






}
