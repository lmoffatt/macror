#ifndef QMARKOVMODEL_H
#define QMARKOVMODEL_H

#include <string>

#include "Markov_Mol/ABC_MarkovModel.h"

#include "Markov_Mol/BufferedFunction.h"

#include "Markov_IO/x_dt.h"
#include "Markov_IO/ClassDescription.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_IO/Parameters.h"

#include "Markov_IO/ABC_Var.h"

namespace Markov_Mol
{

  using Markov_IO::x_dt;
  using Markov_IO::ClassDescription;
  using Markov_IO::ToValue;




  ///Concrete implementation of ABC_Markov_Model
  class Q_Markov_Model:public ABC_Markov_Model, public Markov_IO::Implements_Complex_Var
  {
  public:
    virtual Q_Markov_Model* clone() const;

    virtual Q_Markov_Model* create() const;

    virtual int apply_parameters(const Markov_IO::Parameters& p);

    virtual const Markov_IO::Parameters& get_parameters()const;

    virtual std::string name()const;

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



    Q_Markov_Model(Markov_IO::ABC_Var* parent,
                   const std::string& model_name,
                   const M_Matrix<double>& Q_matrix,
                   const M_Matrix<double>& conductance_vector,
                   const M_Matrix<std::size_t>& agonist_vector,
                   double unitary_conductance,
                   ABC_PatchModel* mypatch=0,
                   const std::string& tip="",
                   const std::string& whatthis="");

    Q_Markov_Model(const std::string &model_name,
                   std::size_t n, ABC_PatchModel *mypatch=0);


    Q_Markov_Model();

    Q_Markov_Model(const Q_Markov_Model& other);

    Q_Markov_Model(const ABC_Markov_Model& M);

    Q_Markov_Model& operator=(const Q_Markov_Model& x);

    friend void swap(Q_Markov_Model& X,Q_Markov_Model& y);

    virtual ~Q_Markov_Model();



    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);
    virtual bool LoadFromStringDescription(const ClassDescription& classDes);

    static std::string ClassName();
    virtual std::string myName()const;
    virtual std::string myClass()const;




    //    virtual std::string save(const std::string& dirName,
    //			     const std::string& extension);


    std::string kij_Label(std::size_t i,
                          std::size_t j);

    bool get_states_from_kij_Label(std::string kij,
                                   std::size_t& i,
                                   std::size_t& j);

    std::string gamma_Label();


    virtual bool load_from_ABC_Var(const ABC_Var* source)override
    {

    }

    virtual ABC_Var* get_ABC_Var() const override
    {
      Markov_IO::Implements_Complex_Var* v=varClone();

      v->push_backVar("Q_matrix",
               Q_M,
               "",
               "rate constant matrix in a 1 micromolar solution",
               "Q-matrix is a square matrix of k dimensions, where Q(i,j) represents the"
               "rate constant for going from the state i to the state j in a 1 micromolar"
               "solution of the agonist");
      v->push_backVar("conductance_vector",
               g0_M,
               "",
               "current for each state, a zero value for the closed states, "
               "one for fully open, between zero and one for partially open states",
               "a column vector of k elements g(i) representing the single "
               "channel current for the state i, expressed as the ratio of "
               "the maximal current generated by any state");
      v->push_backVar("agonist_vector",
               a_M,
               ""
               "number of agonist bound to each state",
               "this information is used to determine which rate constants are dependent "
               "upon the agonist concentration");
      v->push_backVar("unitary_conductance",
               gamma_d,
               "",
               "current of the most conductive state",
               "the current that goes through each state "
               "results from multplying the conductance vector by this value");
      return v;
    }





  protected:
    void buildParameters();
    void Q_conn_K_to_tau_QC();

    void QC_to_Q0_Q1();
    void Q_to_conn_K_tau_QC();
    void K_conn_tau_to_Q();
    void update();

  private:
    const ABC_PatchModel* patch_;

    std::string name_;
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



  std::multimap<std::size_t,std::size_t>
  getConnectionMap(const M_Matrix<double>& Q);

  Markov_LA::M_Matrix<double>
  getPartitionVector(Markov_LA::M_Matrix<double>& Q,
                     const std::multimap<std::size_t,std::size_t>&conn_Map,
                     bool &hasloops,
                     bool removeLoops=false);


}

#endif // QMARKOVMODEL_H
