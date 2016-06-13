#ifndef EXPERIMENTALDATA_H
#define EXPERIMENTALDATA_H

#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/PulsesTrace.h"


namespace Markov_IO_New
{
class ExperimentalData: public ABC_Experiment
{
public:
    virtual ExperimentalData* clone() const;

    virtual ExperimentalData* create() const;

    virtual ~ExperimentalData();

    virtual std::ostream& put(std::ostream& s) const;



    virtual std::size_t total_samples() const;

    virtual std::size_t num_replicates()const;

    virtual const ExperimentalData& replicate(std::size_t i)const;


    virtual const ExperimentalData& trace(std::size_t i)const;

    virtual const ExperimentalData& trace_interval()const;

    virtual std::size_t i_trace()const;


    virtual std::size_t num_traces() const;


    virtual std::size_t i_sample()const;


    virtual const ExperimentalData& operator[](std::size_t i)const;

    virtual const ExperimentalData& operator++()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;


  /*only of ExperimentalData */

  virtual const ExperimentalData &selectPatch(std::string patchLabel)const;
  virtual std::vector<std::string> getPatchs()const ;
  virtual std::string currentPatch()const;






    ExperimentalData(std::string name,
                     std::string fileName,
                     std::string fileNameCode,
                     std::string PatchNameCode,
                     std::string GainCode,
                     std::string SamplingFrequencyCode,
                     std::string AgonistCode,
                     double time_to_exchange,
                     double sub_step_time,
                     double time_to_next_trace
                     );


    ExperimentalData(std::string name,
                     std::string dirName);


    ExperimentalData();


    ExperimentalData(const ExperimentalData& other);


    ExperimentalData& operator=(const ExperimentalData& other);

    friend void swap(ExperimentalData& one, ExperimentalData& two);





    static std::string ClassName();




private:
    void init();
    void initDir();
    std::string name_;
    std::string dirName_;
    std::vector<std::string> fnames_;
    std::map<std::string, std::string> protocols_;

    std::string fileName_;
    std::string fileNameCode_;
    std::string PatchNameCode_;
    std::string GainCode_;
    std::string SamplingFrequencyCode_;
    std::string AgonistCode_;
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
class ExperimentalData: public ABC_Experiment
{
public:
    virtual ExperimentalData* clone() const;

    virtual ExperimentalData* create() const;

    virtual ~ExperimentalData();

    virtual std::ostream& put(std::ostream& s) const;



    virtual std::size_t total_samples() const;

    virtual std::size_t num_replicates()const;

    virtual const ExperimentalData& replicate(std::size_t i)const;


    virtual const ExperimentalData& trace(std::size_t i)const;

    virtual const ExperimentalData& trace_interval()const;

    virtual std::size_t i_trace()const;


    virtual std::size_t num_traces() const;


    virtual std::size_t i_sample()const;


    virtual const ExperimentalData& operator[](std::size_t i)const;

    virtual const ExperimentalData& operator++()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;


  /*only of ExperimentalData */

  virtual const ExperimentalData &selectPatch(std::string patchLabel)const;
  virtual std::vector<std::string> getPatchs()const ;
  virtual std::string currentPatch()const;






    ExperimentalData(std::string name,
                     std::string fileName,
                     std::string fileNameCode,
                     std::string PatchNameCode,
                     std::string GainCode,
                     std::string SamplingFrequencyCode,
                     std::string AgonistCode,
                     double time_to_exchange,
                     double sub_step_time,
                     double time_to_next_trace
                     );


    ExperimentalData(std::string name,
                     std::string dirName);


    ExperimentalData();


    ExperimentalData(const ExperimentalData& other);


    ExperimentalData& operator=(const ExperimentalData& other);

    friend void swap(ExperimentalData& one, ExperimentalData& two);




    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);

    static std::string ClassName();

    virtual std::string id()const;
    virtual std::string myClass()const;



private:
    void init();
    void initDir();
    std::string name_;
    std::string dirName_;
    std::vector<std::string> fnames_;
    std::map<std::string, std::string> protocols_;

    std::string fileName_;
    std::string fileNameCode_;
    std::string PatchNameCode_;
    std::string GainCode_;
    std::string SamplingFrequencyCode_;
    std::string AgonistCode_;
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


#endif // EXPERIMENTALDATA_H
