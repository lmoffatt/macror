#ifndef QMARKOVMODEL_H
#define QMARKOVMODEL_H

#include <string>

#include "Markov_Mol/ABC_MarkovModel.h"

#include "Markov_Mol/BufferedFunction.h"
#include "Markov_IO/x_dt.h"
#include "Markov_IO/auxiliarIO.h"

#include<set>
#include<map>





namespace Markov_Mol_New
{

  using Markov_IO_New::x_dt;
  //  using Markov_IO::ClassDescription;

  ///Concrete implementation of ABC_Markov_Model
  class Q_Markov_Model: public ABC_Markov_Model
  {
  public:


    virtual void setPatch(const ABC_PatchModel* newPatch);

    virtual std::size_t k()const;

    virtual const M_Matrix<double>& Q() const;
    virtual const M_Matrix<double>& Q0() const;
    virtual const M_Matrix<double>& Q1() const;

    virtual const M_Matrix<size_t>& n_bound_agonists() const;
    virtual const M_Matrix<double>& g() const;

    virtual double gamma()const;

    virtual M_Matrix<double> Peq(double agonist_concentration) const;


    virtual  Markov_Transition_step Q_step(const Markov_IO::ABC_measure_step& ,
                                           bool is_averaging,
                                           bool two_anchor=false)const;

    //    virtual  Markov_Transition_step Q_dt(
    //	    const Markov_IO::ABC_measure_point& xdt,
    //	    const Markov_Bay::ABC_Markov_Likelihood_step& likelihood)const;


    virtual  Markov_Transition_step Q_dt (const Markov_IO::ABC_measure_point&,
                                          bool is_averaging,
                                          bool varying_x,
                                          bool two_anchor=false)const;

    virtual Markov_Transition_rate Q_x (double agonist_concentrarion,
                                        bool isavergaing)const;

    virtual Markov_state start(double equilibrium_concentration,
                               std::size_t Nchannels,
                               Borrowed::MersenneTwister::MTRand& sto)const;

    virtual Markov_state_ext start(double equilibrium_concentration,
                                   std::size_t Nchannels,
                                   Borrowed::MersenneTwister::MTRand& sto,
                                   bool /*dummy*/)const;

    virtual Markov_state& run(const Markov_IO::ABC_measure_point& xdt,
                              Markov_state& M,
                              std::size_t n_steps,
                              Borrowed::MersenneTwister::MTRand& sto)const;

    virtual Markov_state& run(const Markov_IO::ABC_measure_step& xdt,
                              Markov_state& M,
                              std::size_t n_steps,
                              Borrowed::MersenneTwister::MTRand& sto)const;

    virtual Markov_state_ext& run(const Markov_IO::ABC_measure_point& xdt,
                                  Markov_state_ext& M,
                                  std::size_t n_steps,
                                  Borrowed::MersenneTwister::MTRand& sto)const;

    virtual Markov_state_ext& run(const Markov_IO::ABC_measure_step& xdt,
                                  Markov_state_ext& M,
                                  std::size_t n_steps,
                                  Borrowed::MersenneTwister::MTRand& sto)const;



    Q_Markov_Model(const std::string& idName,
                   const std::string& idVarName,
                   const M_Matrix<double>& Q_matrix,
                   const M_Matrix<double>& conductance_vector,
                   const M_Matrix<std::size_t>& agonist_vector,
                   double unitary_conductance,
                   const ABC_PatchModel* mypatch=0,
                   const std::string& tip="",
                   const std::string& whatthis="");

    Q_Markov_Model()//:
 //   Implements_ValueId(ClassName(),ClassName(),"General Markov ////Model","Raw class describing the Markov model")
    {}

    Q_Markov_Model(const Q_Markov_Model& other)=default;

    Q_Markov_Model(Q_Markov_Model&& other)=default;


    Q_Markov_Model& operator=(const Q_Markov_Model& x)=default;
    Q_Markov_Model& operator=(Q_Markov_Model&& x)=default;

    virtual ~Q_Markov_Model();




    static std::string ClassName();


    static std::string kij_Label(std::size_t i,
                                 std::size_t j);

    static bool get_states_from_kij_Label(std::string kij,
                                          std::size_t& i,
                                          std::size_t& j);

    static std::string gamma_Label();

    static std::string Q_Label(){return "Q_matrix";}
    static std::string g_Label(){return "conductance_vector";}
    static std::string a_Label(){return "agonist_vector";}

    static std::string patch_Label(){return "patch";}





  protected:
    void buildParameters();
    void Q_conn_K_to_tau_QC();

    void QC_to_Q0_Q1();
    void Q_to_conn_K_tau_QC();
    void K_conn_tau_to_Q();
    void update();

  private:

    const ABC_PatchModel* patch_;

    std::size_t k_u;
    M_Matrix<double> Q_M;  // no completed cycles, for parameters extraction
    M_Matrix<double> Q0_M; //par
    M_Matrix<double> Q1_M; //par

    M_Matrix<double> QC_M; // cycles completed
    M_Matrix<double> K_M;// --> indicates the equilibrium function

    std::multimap<std::size_t,std::size_t> conn_Map;

    std::map<std::pair<std::size_t,std::size_t> ,double> tau_Map; // exchange times

    M_Matrix<double> g_M; //par
    M_Matrix<double> g0_M; //par
    double gamma_d;
    M_Matrix<size_t> a_M; //par
    Markov_IO::Parameters parameters_Map; //->par




  private:
    Markov_Transition_rate
    get_Q_x_not_avg(double agonist_concentrarion)const;

    Markov_Transition_rate&
    get_Q_x_avg(Markov_Transition_rate& Q_x)const;

    Markov_Transition_step
    get_Q_dt_no_avg(const Markov_IO::ABC_measure_point& xdt)const;

    Markov_Transition_step&
    get_Q_dt_avg(const Markov_IO::ABC_measure_point& xdt,
                 Markov_Transition_step& Q_dt)const;

    Markov_Transition_step&
    get_Q_dt_avg_var(const Markov_IO::ABC_measure_point& xdt,
                     Markov_Transition_step& Q_dt)const;

    Markov_Transition_step&
    get_Q_dt_two_anchor(const Markov_IO::ABC_measure_point& xdt,
                        Markov_Transition_step& Q_dt)const;

    mutable buffered_function<Markov_IO::x_dt,Markov_Transition_step>
    Q_dt_buff_two_anchor;

    mutable buffered_function<Markov_IO::x_dt,Markov_Transition_step>
    Q_dt_buff_avg_varx;

    mutable buffered_function<x_dt,Markov_Transition_step>
    Q_dt_buff_avg;

    mutable buffered_function<x_dt,Markov_Transition_step>
    Q_dt_buff_not_avg;
    mutable buffered_function<double,Markov_Transition_rate>
    Q_x_buff_avg;
    mutable buffered_function<double,Markov_Transition_rate>
    Q_x_buff_not_avg;
  };


  template<typename T>
  class UndirectedGraph
  {
  public:
    std::size_t numNodes()const
    {
      return m_.size();
    }

    std::size_t numEdges()const
    {
      std::size_t count=0;
      for (auto itp:m_)
        {
          count+=itp.second.size();
        }
      return count/2;
    }

    const std::set<T>& connectedTo(std::size_t i)const
    {

      return m_.find(i)->second;

    }
    bool isEdge(T i, T j)const
    {
      auto itp=m_.find(i);
      if (itp!=m_.end())
        return itp->second.find(j)!=itp->second.end();
      else
        return false;
    }

    void push_back(T i, T j)
    {
      if (i!=j)
        {
          m_[i].insert(j);
          m_[j].insert(i);
        }
    }

    UndirectedGraph<T> ( std::map <T, std::set< T> >  pairList)
    {
      for (auto p:pairList)
        {
          std::size_t i=p.first;
          for (auto j: p.second)
            push_back(i,j);
        }

    }


    UndirectedGraph():m_(){}

    std::string toString()const
    {
      std::string out;
      std::stringstream ss(out);
      ss<<" { ";
      for (auto itp:m_)
        {
          T i=itp.first;
          ss<<i<<": {";
          for (auto it=itp.second.find(i); it!=itp.second.end(); ++it)
            ss<<*it <<" ";
          ss<<"}";
        }
      ss<<" } ";
      return ss.str();
    }

    std::map<T,std::set<T>>  getMap( )const {return m_;}

  private:

    std::map<T,std::set<T>> m_;

  };




  std::multimap<std::size_t,std::size_t>
  getConnectionMap(const M_Matrix<double>& Q);

  Markov_LA::M_Matrix<double>
  getPartitionVector(Markov_LA::M_Matrix<double>& Q,
                     const std::multimap<std::size_t,std::size_t>&conn_Map,
                     bool &hasloops,
                     bool removeLoops=false);











  class Q_Markov_Scheme
  {
    UndirectedGraph<std::size_t> ug_;
    Markov_LA::M_Matrix<double> g_;
    Markov_LA::M_Matrix<std::size_t> a_;
    ABC_PatchModel *p_=nullptr;
  public:

    static std::string connections_Label()
    {
      return "connectons_between_states";
    }


    Q_Markov_Scheme(const UndirectedGraph<std::size_t>& connections,
                    const Markov_LA::M_Matrix<double>& g,
                    const Markov_LA::M_Matrix<std::size_t> agonistVector):
    ug_(connections),
    g_(g),
    a_(agonistVector),
    p_(nullptr){}



    Q_Markov_Scheme():
    ug_(),g_(),a_(),p_(nullptr){}






//    Q_Markov_Model* toMeasure(const ABC_Value *source) const
//    {
//      double gamma;
//      bool gammaOk=false;
//      std::size_t numStates=Markov_LA::size(g_);
//      Markov_LA::M_Matrix<double> Qc=Markov_LA::zeros<double>(numStates,numStates);
//      for (std::size_t i=0; i<source->numChilds(); i++)
//        {
//          std::string par=source->ith_ChildName(i);
//          size_t state_i, state_j;
//          if (par==Q_Markov_Model::gamma_Label())
//            {
//              gammaOk=source->getVal(Q_Markov_Model::gamma_Label(),gamma);
//              if (!gammaOk)
//                {
//                  putErrorOut("\n gamma not found \n:");
//                  putErrorOut(source->toString()+"\n");
//                }
//            }
//          else if (!Q_Markov_Model::get_states_from_kij_Label(par,state_i,state_j))
//            {
//              putErrorOut(par+" no in kij format");
//            }
//          else
//            {
//              if (!ug_.isEdge(state_i,state_j))
//                {
//                  putErrorOut(par +"not a connection. Allowed connections ");
//                  putErrorOut(ug_.toString());
//                }
//              else
//                {
//                  bool kok=source->getVal(par,Qc(state_i,state_j));
//                  if (!kok)
//                    {
//                      std::string msg="error in parameter value"+par+"="+source->idToValue(par)->toString();
//                      putErrorOut(msg);
//                    }
//                }

//            }
//        };

//      return new Q_Markov_Model(source->id(),id(),Qc,g_,a_,gamma,p_,source->Tip(),source->WhatThis());

//    }





  };




}




#include <string>

#include "Markov_Mol/ABC_MarkovModel.h"

#include "Markov_Mol/BufferedFunction.h"

#include "Markov_IO/x_dt.h"
#include "Markov_IO/ClassDescription.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_IO/Parameters.h"

#include "Markov_IO/ABC_Var.h"

#include<set>
#include<map>

namespace Markov_Mol
{

  using Markov_IO::x_dt;
  //  using Markov_IO::ClassDescription;

  ///Concrete implementation of ABC_Markov_Model
  class Q_Markov_Model: public ABC_Markov_Model
  {
  public:

    class Q_matrix:public Markov_IO::Implements_Simple_Class<Markov_LA::M_Matrix<double>>
    {
    public:
      static std::string ClassName(){return "Q_matrix";}
        Q_matrix();
    };

    class g_matrix:public Markov_IO::Implements_Simple_Class<Markov_LA::M_Matrix<double>>
    {
    public:
      static std::string ClassName(){return "g_matrix";}
        g_matrix():
      //    Implements_ValueId(ClassName(),ClassName(),"",""),
      Implements_Simple_Class(g_matrix::ClassName(),"1=max conductance",{"NOT_ALL_ZERO"}){}
    };

    class a_matrix:public Markov_IO::Implements_Simple_Class<Markov_LA::M_Matrix<std::size_t>>
    {
    public:
      static std::string ClassName(){return "a_matrix";}
        a_matrix():
      //    Implements_ValueId(ClassName(),ClassName(),"",""),
      Implements_Simple_Class(g_matrix::ClassName(),"agonist_count",{"NOT_ALL_ZERO"}){}
    };




    virtual Markov_IO::Implements_Complex_Value* to_PlainValue()const;

    Q_Markov_Model* toMeasure(const ABC_Value *source) const
    {
      return toSameVar(source);
    }


    virtual Markov_IO::Token_Stream toTokens()const override
    {
      auto p=to_PlainValue();
      auto t=p->toTokens();
      delete p;
      return t;
    }

    virtual Q_Markov_Model* clone() const;

    virtual Q_Markov_Model* create() const;

    virtual Q_Markov_Model* toSameVar(const ABC_Value *source) const;



    virtual const ABC_PatchModel* patch()const;

    virtual void setPatch(const ABC_PatchModel* newPatch);

    //    virtual std::ostream& put(std::ostream& s) const;

    //    virtual std::istream& get(std::string&,
    //		     std::istream& s);


    //    virtual std::string author()const;

    //    virtual std::string date()const;

    //    virtual std::string fname()const;


    //    virtual const Publication& pub()const;

    virtual std::size_t k()const;

    virtual const M_Matrix<double>& Q() const;
    virtual const M_Matrix<double>& Q0() const;
    virtual const M_Matrix<double>& Q1() const;

    virtual const M_Matrix<size_t>& n_bound_agonists() const;
    virtual const M_Matrix<double>& g() const;

    virtual double gamma()const;

    virtual M_Matrix<double> Peq(double agonist_concentration) const;

    //    virtual Markov_Transition_step  Q_step (
    //	    const Markov_IO::ABC_measure_step& xdt ,
    //	    const Markov_Bay::ABC_Markov_Likelihood_step& likelihood)const;

    virtual  Markov_Transition_step Q_step(const Markov_IO::ABC_measure_step& ,
                                           bool is_averaging,
                                           bool two_anchor=false)const;

    //    virtual  Markov_Transition_step Q_dt(
    //	    const Markov_IO::ABC_measure_point& xdt,
    //	    const Markov_Bay::ABC_Markov_Likelihood_step& likelihood)const;


    virtual  Markov_Transition_step Q_dt (const Markov_IO::ABC_measure_point&,
                                          bool is_averaging,
                                          bool varying_x,
                                          bool two_anchor=false)const;

    virtual Markov_Transition_rate Q_x (double agonist_concentrarion,
                                        bool isavergaing)const;

    virtual Markov_state start(double equilibrium_concentration,
                               std::size_t Nchannels,
                               Borrowed::MersenneTwister::MTRand& sto)const;

    virtual Markov_state_ext start(double equilibrium_concentration,
                                   std::size_t Nchannels,
                                   Borrowed::MersenneTwister::MTRand& sto,
                                   bool /*dummy*/)const;

    virtual Markov_state& run(const Markov_IO::ABC_measure_point& xdt,
                              Markov_state& M,
                              std::size_t n_steps,
                              Borrowed::MersenneTwister::MTRand& sto)const;

    virtual Markov_state& run(const Markov_IO::ABC_measure_step& xdt,
                              Markov_state& M,
                              std::size_t n_steps,
                              Borrowed::MersenneTwister::MTRand& sto)const;

    virtual Markov_state_ext& run(const Markov_IO::ABC_measure_point& xdt,
                                  Markov_state_ext& M,
                                  std::size_t n_steps,
                                  Borrowed::MersenneTwister::MTRand& sto)const;

    virtual Markov_state_ext& run(const Markov_IO::ABC_measure_step& xdt,
                                  Markov_state_ext& M,
                                  std::size_t n_steps,
                                  Borrowed::MersenneTwister::MTRand& sto)const;



    Q_Markov_Model(const std::string& idName,
                   const std::string& idVarName,
                   const M_Matrix<double>& Q_matrix,
                   const M_Matrix<double>& conductance_vector,
                   const M_Matrix<std::size_t>& agonist_vector,
                   double unitary_conductance,
                   const ABC_PatchModel* mypatch=0,
                   const std::string& tip="",
                   const std::string& whatthis="");

    Q_Markov_Model():
    Implements_ValueId(ClassName(),ClassName(),"General Markov Model","Raw class describing the Markov model")
    {}

    Q_Markov_Model(const Q_Markov_Model& other)=default;

    Q_Markov_Model(Q_Markov_Model&& other)=default;


    Q_Markov_Model& operator=(const Q_Markov_Model& x)=default;
    Q_Markov_Model& operator=(Q_Markov_Model&& x)=default;

    virtual ~Q_Markov_Model();



    //virtual ClassDescription GetDescription()const;

    // virtual bool LoadFromDescription(const ClassDescription& classDes);
    //  virtual bool LoadFromStringDescription(const ClassDescription& classDes);

    static std::string ClassName();


    static std::string kij_Label(std::size_t i,
                                 std::size_t j);

    static bool get_states_from_kij_Label(std::string kij,
                                          std::size_t& i,
                                          std::size_t& j);

    static std::string gamma_Label();

    static std::string Q_Label(){return "Q_matrix";}
    static std::string g_Label(){return "conductance_vector";}
    static std::string a_Label(){return "agonist_vector";}

    static std::string patch_Label(){return "patch";}





  protected:
    void buildParameters();
    void Q_conn_K_to_tau_QC();

    void QC_to_Q0_Q1();
    void Q_to_conn_K_tau_QC();
    void K_conn_tau_to_Q();
    void update();

  private:

    const ABC_PatchModel* patch_;

    std::size_t k_u;
    M_Matrix<double> Q_M;  // no completed cycles, for parameters extraction
    M_Matrix<double> Q0_M; //par
    M_Matrix<double> Q1_M; //par

    M_Matrix<double> QC_M; // cycles completed
    M_Matrix<double> K_M;// --> indicates the equilibrium function

    std::multimap<std::size_t,std::size_t> conn_Map;

    std::map<std::pair<std::size_t,std::size_t> ,double> tau_Map; // exchange times

    M_Matrix<double> g_M; //par
    M_Matrix<double> g0_M; //par
    double gamma_d;
    M_Matrix<size_t> a_M; //par
    Markov_IO::Parameters parameters_Map; //->par




  private:
    Markov_Transition_rate
    get_Q_x_not_avg(double agonist_concentrarion)const;

    Markov_Transition_rate&
    get_Q_x_avg(Markov_Transition_rate& Q_x)const;

    Markov_Transition_step
    get_Q_dt_no_avg(const Markov_IO::ABC_measure_point& xdt)const;

    Markov_Transition_step&
    get_Q_dt_avg(const Markov_IO::ABC_measure_point& xdt,
                 Markov_Transition_step& Q_dt)const;

    Markov_Transition_step&
    get_Q_dt_avg_var(const Markov_IO::ABC_measure_point& xdt,
                     Markov_Transition_step& Q_dt)const;

    Markov_Transition_step&
    get_Q_dt_two_anchor(const Markov_IO::ABC_measure_point& xdt,
                        Markov_Transition_step& Q_dt)const;

    mutable buffered_function<Markov_IO::x_dt,Markov_Transition_step>
    Q_dt_buff_two_anchor;

    mutable buffered_function<Markov_IO::x_dt,Markov_Transition_step>
    Q_dt_buff_avg_varx;

    mutable buffered_function<x_dt,Markov_Transition_step>
    Q_dt_buff_avg;

    mutable buffered_function<x_dt,Markov_Transition_step>
    Q_dt_buff_not_avg;
    mutable buffered_function<double,Markov_Transition_rate>
    Q_x_buff_avg;
    mutable buffered_function<double,Markov_Transition_rate>
    Q_x_buff_not_avg;
  };


  template<typename T>
  class UndirectedGraph
  {
  public:
    std::size_t numNodes()const
    {
      return m_.size();
    }

    std::size_t numEdges()const
    {
      std::size_t count=0;
      for (auto itp:m_)
        {
          count+=itp.second.size();
        }
      return count/2;
    }

    const std::set<T>& connectedTo(std::size_t i)const
    {

      return m_.find(i)->second;

    }
    bool isEdge(T i, T j)const
    {
      auto itp=m_.find(i);
      if (itp!=m_.end())
        return itp->second.find(j)!=itp->second.end();
      else
        return false;
    }

    void push_back(T i, T j)
    {
      if (i!=j)
        {
          m_[i].insert(j);
          m_[j].insert(i);
        }
    }

    UndirectedGraph<T> ( std::map <T, std::set< T> >  pairList)
    {
      for (auto p:pairList)
        {
          std::size_t i=p.first;
          for (auto j: p.second)
            push_back(i,j);
        }

    }


    UndirectedGraph():m_(){}

    std::string toString()const
    {
      std::string out;
      std::stringstream ss(out);
      ss<<" { ";
      for (auto itp:m_)
        {
          T i=itp.first;
          ss<<i<<": {";
          for (auto it=itp.second.find(i); it!=itp.second.end(); ++it)
            ss<<*it <<" ";
          ss<<"}";
        }
      ss<<" } ";
      return ss.str();
    }

    std::map<T,std::set<T>>  getMap( )const {return m_;}

  private:

    std::map<T,std::set<T>> m_;

  };




  std::multimap<std::size_t,std::size_t>
  getConnectionMap(const M_Matrix<double>& Q);

  Markov_LA::M_Matrix<double>
  getPartitionVector(Markov_LA::M_Matrix<double>& Q,
                     const std::multimap<std::size_t,std::size_t>&conn_Map,
                     bool &hasloops,
                     bool removeLoops=false);











  class Q_Markov_Scheme: public Markov_IO::Implements_ValueId
  {
    UndirectedGraph<std::size_t> ug_;
    Markov_LA::M_Matrix<double> g_;
    Markov_LA::M_Matrix<std::size_t> a_;
    ABC_PatchModel *p_=nullptr;
  public:

    static std::string connections_Label()
    {
      return "connectons_between_states";
    }


    Q_Markov_Scheme(const std::string& idName,
                    const std::string& idVarName,
                    const UndirectedGraph<std::size_t>& connections,
                    const Markov_LA::M_Matrix<double>& g,
                    const Markov_LA::M_Matrix<std::size_t> agonistVector,
                    const std::string& tip,
                    const std::string& whatthis):
    Implements_ValueId(idName,idVarName,tip,whatthis),
    ug_(connections),
    g_(g),
    a_(agonistVector),
    p_(nullptr){}



    Q_Markov_Scheme():
    ug_(),g_(),a_(),p_(nullptr){}






    Q_Markov_Model* toMeasure(const ABC_Value *source) const
    {
      double gamma;
      bool gammaOk=false;
      std::size_t numStates=Markov_LA::size(g_);
      Markov_LA::M_Matrix<double> Qc=Markov_LA::zeros<double>(numStates,numStates);
      for (std::size_t i=0; i<source->numChilds(); i++)
        {
          std::string par=source->ith_ChildName(i);
          size_t state_i, state_j;
          if (par==Q_Markov_Model::gamma_Label())
            {
              gammaOk=source->getVal(Q_Markov_Model::gamma_Label(),gamma);
              if (!gammaOk)
                {
                  putErrorOut("\n gamma not found \n:");
                  putErrorOut(source->toString()+"\n");
                }
            }
          else if (!Q_Markov_Model::get_states_from_kij_Label(par,state_i,state_j))
            {
              putErrorOut(par+" no in kij format");
            }
          else
            {
              if (!ug_.isEdge(state_i,state_j))
                {
                  putErrorOut(par +"not a connection. Allowed connections ");
                  putErrorOut(ug_.toString());
                }
              else
                {
                  bool kok=source->getVal(par,Qc(state_i,state_j));
                  if (!kok)
                    {
                      std::string msg="error in parameter value"+par+"="+source->idToValue(par)->toString();
                      putErrorOut(msg);
                    }
                }

            }
        };

      return new Q_Markov_Model(source->id(),id(),Qc,g_,a_,gamma,p_,source->Tip(),source->WhatThis());

    }



    Q_Markov_Scheme* toSameVar(const ABC_Value *source) const;


    Markov_IO::Implements_Complex_Value* to_PlainValue() const;



    Markov_IO::Implements_Complex_Value *to_PlainValue(const ABC_Value* source) const;
    // ABC_Put interface
  public:
    virtual Q_Markov_Scheme *clone() const
    {
      return new Q_Markov_Scheme(*this);
    }
    virtual Q_Markov_Scheme *create() const
    {
      return new Q_Markov_Scheme;
    }
    // ABC_Value interface

  };




}

#endif // QMARKOVMODEL_H
