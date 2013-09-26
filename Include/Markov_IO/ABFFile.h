#ifndef ABFFILE_H
#define ABFFILE_H
#include <string>
#include <cstdlib>

#include "Markov_LA/Matrix.h"
#include "Markov_IO/ABF2_Headers.h"

namespace Markov_IO
{

  class ABFFile{

  public:

    ABFFile(const std::string& path);


static    bool isValid(const std::string path);

    double version()const;
    std::string protocol()const;
    std::string dataFile()const;
    double dayCreated()const;
    double timeCreated()const;
    std::size_t nTotalSamples()const;

    std::size_t nTrialsPerRun()const;
    std::size_t nSweepsPerRun()const;
    double sweepDuration()const;

    double SamplingRate()const;

    double timeBetweenRuns()const;

    double timeBetweenSweeps()const;

    const Markov_LA::M_Matrix<double>& t();
    const Markov_LA::M_Matrix<double>& y(std::size_t channel);

    const Markov_LA::M_Matrix<double>& DAC(std::size_t channel);


    std::string AcquisitionMode()const;





  private:
    void init();
    template <typename T>
    T getValuePos(char *H,uint32_t offset,std::string type);
    template <typename T>
    void getValuePos(T* result,char* H, int offset, std::string type,int nrep);

    void build_y();
    void build_t();
    void build_DAC();

    std::string getStringPos(char* H,int offset,int length);
    bool inited_;
    std::string path_;
    double ver_;

    std::string protocol_;

    std::string dataFile_;
    double dayCreated_;
    double timeCreated_;
    std::size_t nTotalSamples_;
    std::size_t nSignals_;

    std::size_t nTraceSamples_;

    std::size_t nTrialsPerRun_;
    std::size_t nSweepsPerRun_;
    double sweepDuration_;

    double SamplingRate_;
    double SampleInterval_;

    double TrialStartToStart_;

    double SweepStartToStart_;

    std::vector<double> yScale_;

    Markov_LA::M_Matrix<double> t_;
    std::vector<Markov_LA::M_Matrix<double> > y_;

    std::vector<Markov_LA::M_Matrix<double> >DAC_;


    std::string AcquisitionMode_;





   // ABF <2.0

    ABFFileHeader* H1_;


    // ABF 2.0
    ABF_FileInfo* H2_;

    std::vector<ABF_ProtocolInfo> HP_;
    std::vector<ABF_ADCInfo> HADC_;
    std::vector<ABF_DACInfo> HDAC_;
    std::vector<ABF_EpochInfo> HEp_;
    std::vector<ABF_EpochInfoPerDAC> H_EDAC_; //not implemented

    std::vector<std::string> s2_;
    std::size_t iStrClampex_;  //hack for shifting the clampex string



  };
}

#endif // ABFFILE_H
