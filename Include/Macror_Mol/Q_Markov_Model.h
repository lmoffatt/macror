#ifndef Q_MARKOV_MODEL_H
#define Q_MARKOV_MODEL_H

#include "Macror_Var/Macror_Matrix.h"


namespace MacroR_Mol {
  using Macror_Var::Matrix;
  
  
  class Variable
  {
  public:
    class Data
    {

    };
  };


  
  class Q_Transition_rate 
  {
    public:
        
    
        M_Matrix<double> Qrun;// transition rate matrix at time zero
        M_Matrix<double> V;// eigenvector of Qrun
        M_Matrix<double> W;// eigenvector of Qrun
        M_Matrix<double> landa; // eigenvalues
    
        M_Matrix<double> Wg;
        M_Matrix<double> WgV;
    
        Markov_Transition_rate(const M_Matrix<double>& Qrun_,
                               const M_Matrix<double>& V_,
                               const M_Matrix<double>& W_,
                               const M_Matrix<double>& landa_);
    
        Markov_Transition_rate(const M_Matrix<double>& Qrun_,
                               const M_Matrix<double>& V_,
                               const M_Matrix<double>& W_,
                               const M_Matrix<double>& landa_,
                               const M_Matrix<double>& Wg_,
                               const M_Matrix<double>& WgV_);
    
        Markov_Transition_rate& operator=(const Markov_Transition_rate& other);
    
        friend void swap(Markov_Transition_rate& one, Markov_Transition_rate& other);
    
        explicit Markov_Transition_rate(std::size_t n, bool is_averaging);
    
        Markov_Transition_rate();
    
    };
    
    
  };
  
  
  
  class Q_Markov_Model
      {
      public:

        virtual const DoubleMatrixVal* Q() const;
        virtual const Matrix<double>& Q0() const;
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



        Q_Markov_Model(const std::string& model_name,
                       const M_Matrix<double>& Q_matrix,
                       const M_Matrix<double>& conductance_vector,
                       const M_Matrix<std::size_t>& agonist_vector,
                       double unitary_conductance,
                       ABC_PatchModel* mypatch=0);

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




#endif // Q_MARKOV_MODEL_H
