#ifndef ABFEXPERIMENT_H
#define ABFEXPERIMENT_H

#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/PulsesTrace.h"


namespace Markov_IO_New
{
class ABFExperiment: public ABC_Experiment
{
public:
    virtual ABFExperiment* clone() const;

    virtual ABFExperiment* create() const;

    virtual ~ABFExperiment();

    virtual std::ostream& put(std::ostream& s) const;



    virtual std::size_t total_samples() const;

    virtual std::size_t num_replicates()const;

    virtual const ABFExperiment& replicate(std::size_t i)const;


    virtual const ABFExperiment& trace(std::size_t i)const;

    virtual const ABFExperiment& trace_interval()const;

    virtual std::size_t i_trace()const;


    virtual std::size_t num_traces() const;


    virtual std::size_t i_sample()const;


    virtual const ABFExperiment& operator[](std::size_t i)const;

    virtual const ABFExperiment& operator++()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;




    ABFExperiment(std::string name,
                     std::vector<std::string> fileNames
                   );


    ABFExperiment();


    ABFExperiment(const ABFExperiment& other);


    ABFExperiment& operator=(const ABFExperiment& other);

    friend void swap(ABFExperiment& one, ABFExperiment& two);




    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);

    static std::string ClassName();
    virtual std::string myClass()const {return ClassName();}

    virtual std::string id()const;
    virtual std::string myClass()const;



private:
    void init();
    void initDir();
    double time_to_exchange_;
    double sub_step_time_;
    double time_to_next_trace_;
    std::vector<std::string> trace_fnames_;
    std::vector<std::string> patch_names_;
    mutable std::map<std::string, std::vector<std::size_t> > patch_traces_;
    std::vector<std::string> unique_patch_names_;
    std::vector<double> gain_;
    std::vector<double> fs_;
    std::vector<double> fc_;
    std::vector<double> Conc_;

    std::vector<Pulses_trace> traces_v;
    std::vector<double> pulse_concentration_;

    std::vector< Markov_LA::M_Matrix<double> > y_;



    std::size_t total_samples_;

    mutable std::size_t i_trace_;
    mutable std::size_t i_replicate_;
    mutable std::string current_patch_;



};
}




#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/PulsesTrace.h"


namespace Markov_IO
{
class ABFExperiment: public ABC_Experiment
{
public:
    virtual ABFExperiment* clone() const;

    virtual ABFExperiment* create() const;

    virtual ~ABFExperiment();

    virtual std::ostream& put(std::ostream& s) const;



    virtual std::size_t total_samples() const;

    virtual std::size_t num_replicates()const;

    virtual const ABFExperiment& replicate(std::size_t i)const;


    virtual const ABFExperiment& trace(std::size_t i)const;

    virtual const ABFExperiment& trace_interval()const;

    virtual std::size_t i_trace()const;


    virtual std::size_t num_traces() const;


    virtual std::size_t i_sample()const;


    virtual const ABFExperiment& operator[](std::size_t i)const;

    virtual const ABFExperiment& operator++()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;




    ABFExperiment(std::string name,
                     std::vector<std::string> fileNames
                   );


    ABFExperiment();


    ABFExperiment(const ABFExperiment& other);


    ABFExperiment& operator=(const ABFExperiment& other);

    friend void swap(ABFExperiment& one, ABFExperiment& two);




    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);

    static std::string ClassName();

    virtual std::string id()const;
    virtual std::string myClass()const;



private:
    void init();
    void initDir();
    double time_to_exchange_;
    double sub_step_time_;
    double time_to_next_trace_;
    std::vector<std::string> trace_fnames_;
    std::vector<std::string> patch_names_;
    mutable std::map<std::string, std::vector<std::size_t> > patch_traces_;
    std::vector<std::string> unique_patch_names_;
    std::vector<double> gain_;
    std::vector<double> fs_;
    std::vector<double> fc_;
    std::vector<double> Conc_;

    std::vector<Pulses_trace> traces_v;
    std::vector<double> pulse_concentration_;

    std::vector< Markov_LA::M_Matrix<double> > y_;



    std::size_t total_samples_;

    mutable std::size_t i_trace_;
    mutable std::size_t i_replicate_;
    mutable std::string current_patch_;



};
}



#endif // ABFEXPERIMENT_H
