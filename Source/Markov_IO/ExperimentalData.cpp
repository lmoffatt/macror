#include <fstream>
#include <string>
#include "Tests/AssertPlain.h"
#include "Markov_IO/ExperimentalData.h"
#include "Markov_IO/ABFFile.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/auxiliarMath.h"
#include  "Markov_IO/FileDir.h"


namespace Markov_IO
{

  ExperimentalData* ExperimentalData::clone() const
  {
    return new ExperimentalData(*this);
  }
  /// default constructors
  ExperimentalData* ExperimentalData::create() const
  {
    return new ExperimentalData();
  }
  ExperimentalData::~ExperimentalData() {}

  std::ostream& ExperimentalData::put(std::ostream& s) const
  {
    ABC_Experiment::put(s);
    return s;
  };

  std::size_t ExperimentalData::total_samples() const
  {
    return total_samples_;
  }


  std::size_t ExperimentalData::num_replicates()const
  {
    return Markov_LA::ncols(y_[i_trace()]);
  }

  const ExperimentalData& ExperimentalData::replicate(std::size_t i)const
  {
    ASSERT_LESS(i, num_replicates());

    i_replicate_=i;
    return *this;
  }

  const ExperimentalData& ExperimentalData::selectPatch(std::string patchLabel)const
  {
    if (patch_traces_.find(patchLabel)!=patch_traces_.end())
      {
        current_patch_=patchLabel;
        i_trace_=patch_traces_[current_patch_][0];
      }
    return *this;
  }
  std::vector<std::string> ExperimentalData::getPatchs()const
  {
    return unique_patch_names_;
  }
  std::string ExperimentalData::currentPatch()const
  {
    return trace_fnames_[i_trace_];
  }



  const ExperimentalData& ExperimentalData::trace(std::size_t i)const
  {
    ASSERT_LESS(i, num_traces());
    i_trace_=i;
    return *this;
  }

  const ExperimentalData& ExperimentalData::trace_interval()const
  {
    traces_v[i_trace_].trace_interval();
    return *this;
  }

  std::size_t ExperimentalData::i_trace()const
  {
    return i_trace_;
  }


  std::size_t ExperimentalData::num_traces() const
  {
    return traces_v.size();
  }


  std::size_t ExperimentalData::i_sample()const
  {
    return traces_v[i_trace_].i_sample();
  }




  //     ExperimentalData& set_max_x_trace(double new_x)
  //    {
  //        run_trace_T.set_max_x_trace(new_x);
  //        return *this;
  //    }

  const ExperimentalData& ExperimentalData::operator[](std::size_t i)const
  {
    traces_v[i_trace_][i];
    return *this;
  }

  const ExperimentalData& ExperimentalData::operator++()const
  {
    ++traces_v[i_trace_];
    return (*this);
  }

  std::size_t ExperimentalData::num_measures()const
  {
    return traces_v[i_trace_].num_measures();
  }

  double ExperimentalData::t()const
  {
    return traces_v[i_trace_].t();
  }

  double ExperimentalData::dt()const
  {
    return traces_v[i_trace_].dt();
  };

  double ExperimentalData::x()const
  {
    return traces_v[i_trace_].x();
  }


  double ExperimentalData::y() const
  {
    return y_[i_trace_][i_sample()];
  }

  std::size_t ExperimentalData::num_steps()const
  {
    return traces_v[i_trace_].num_steps();
  }

  const x_dt&  ExperimentalData::sub_step(std::size_t i)const
  {
    return traces_v[i_trace_].sub_step(i);
  }

  ExperimentalData::ExperimentalData(std::string name,
                                     std::string fileName,
                                     std::string fileNameCode,
                                     std::string PatchNameCode,
                                     std::string GainCode,
                                     std::string SamplingFrequencyCode,
                                     std::string AgonistCode,
                                     double time_to_exchange,
                                     double sub_step_time,
                                     double time_to_next_trace)
    :
      name_(name),
      fileName_(fileName),
      fileNameCode_(fileNameCode),
      PatchNameCode_(PatchNameCode),
      GainCode_(GainCode),
      SamplingFrequencyCode_(SamplingFrequencyCode),
      AgonistCode_(AgonistCode),
      time_to_exchange_(time_to_exchange),
      sub_step_time_(sub_step_time),
      time_to_next_trace_(time_to_next_trace),
      patch_traces_{},
      unique_patch_names_{},
      gain_{},
      fs_{},
      fc_{},
      Conc_{},
      traces_v{},
      pulse_concentration_{},
      y_{},
      total_samples_{},
      i_trace_{0},
      i_replicate_{0},
      current_patch_{}
  {
    init();
  }


  ExperimentalData::ExperimentalData(std::string name,
                                     std::string dirName)
    :
      name_(name),
      dirName_(dirName),
      fileName_(),
      fileNameCode_(),
      PatchNameCode_(),
      GainCode_(),
      SamplingFrequencyCode_(),
      AgonistCode_(),
      time_to_exchange_(),
      sub_step_time_(),
      time_to_next_trace_(),
      patch_traces_{},
      unique_patch_names_{},
      gain_{},
      fs_{},
      fc_{},
      Conc_{},
      traces_v{},
      pulse_concentration_{},
      y_{},
      total_samples_{},
      i_trace_{0},
      i_replicate_{0},
      current_patch_{}
  {
    initDir();
  }


  void ExperimentalData::initDir()
  {

    FileDir dir(dirName_);

    for (dir.begin();dir.NotEnd();dir.next())
      {
        std::string fname=dir.FileName();
        if (ABFFile::isValid(fname))
          ABFFile d(fname);


      }
    std::size_t pos=fileName_.find_last_of('.');
    std::string ext;
    if ((pos!=fileName_.npos))
      ext=fileName_.substr(pos+1,pos+3);
    if (ext=="abf")
      {
        ABFFile abf(fileName_);

      }
    if ((pos!=fileName_.npos)&&(fileName_.substr(pos,pos+3))=="abf")
      {
        //ABFFile abf(fileName_);

      }

    std::ifstream f(fileName_.c_str());
    std::string line;
    std::vector< std::vector< double> > yr;
    while (std::getline(f,line))
      {
        std::stringstream ss(line);
        std::string fieldcode, cellcontent;
        std::getline(ss,fieldcode,',');
        if (fieldcode.find_first_of("[1234567890qwertyuiopasdfghjklñzxcvbnm")==fieldcode.npos)
          {
            std::vector<double> v;
            while(std::getline(ss,cellcontent,','))
              {
                double value;
                if (ToValue(cellcontent,value))
                  {
                    v.push_back(value);
                    total_samples_++;
                  }
                else
                  v.push_back(Markov_LA::NaN());
              }
            yr.push_back(v);
          }

        else if (fieldcode==fileNameCode_)
          {
            while(std::getline(ss,cellcontent,','))
              {
                this->trace_fnames_.push_back(cellcontent);
              }
          }
        else if (fieldcode==PatchNameCode_)
          {
            while(std::getline(ss,cellcontent,','))
              {
                this->patch_names_.push_back(cellcontent);
                patch_traces_[cellcontent].push_back(patch_names_.size()-1);
              }
          }
        else if (fieldcode==GainCode_)
          {
            while(std::getline(ss,cellcontent,','))
              {
                double value;
                int firstNumber=cellcontent.find_first_of("0123456789");
                int lastNumber=cellcontent.find_first_not_of("0123456789.eE-");
                if (firstNumber>=0)
                  {
                    if(ToValue(cellcontent.substr(firstNumber,lastNumber),value))
                      {
                        this->gain_.push_back(value);
                      }
                    else gain_.push_back(1.0);
                  }
                else gain_.push_back(1.0);
              }
          }
        else if (fieldcode==SamplingFrequencyCode_)
          {
            while(std::getline(ss,cellcontent,','))
              {
                double value;
                int firstNumber=cellcontent.find_first_of("0123456789");
                int lastNumber=cellcontent.find_first_not_of("0123456789.eE-");
                if (ToValue(cellcontent.substr(firstNumber,lastNumber),value))
                  this->fs_.push_back(value);
              }
          }
        else if (fieldcode==AgonistCode_)
          {
            while(std::getline(ss,cellcontent,','))
              {
                double value;
                int firstNumber=cellcontent.find_first_of("0123456789");
                int lastNumber=cellcontent.find_first_not_of("0123456789.eE-",firstNumber);
                int lastLetter=cellcontent.find_first_not_of(
                      "qwertyuiopasdfghjklñzxcvbnm1234567890",
                      lastNumber);
                ToValue(cellcontent.substr(firstNumber,lastNumber),value);
                std::string units=cellcontent.substr(lastNumber,lastLetter);
                if (units=="uM")
                  value*=1e-6;

                this->pulse_concentration_.push_back(value);
              }
          }


      }

    for (std::map<std::string,std::vector<std::size_t> >::const_iterator
         it=patch_traces_.begin();
         it!=patch_traces_.end(); it++)
      {
        unique_patch_names_.push_back((*it).first);
      }


    std::size_t ntraces=fs_.size();
    for (std::size_t i=0; i<ntraces;i++)
      {
        std::vector<double> yv;
        for (std::size_t j=0; j<yr.size(); j++)
          {
            if (!Markov_LA::isNaN(yr[j][i]))
              yv.push_back(yr[j][i]);
          }
        Markov_LA::M_Matrix<double> m(yv.size(),1);
        for (std::size_t j=0; j<yv.size(); j++)
          {
            m[j]=yv[j]*this->gain_[i];
          }
        std::string name=trace_fnames_[i];
        double trace_duration=yv.size()/fs_[i];
        double frequency_of_sampling=fs_[i];
        Markov_LA::M_Matrix<double> time_of_each_concentration_change(1,3);
        Markov_LA::M_Matrix<double> concentration_at_each_time(1,3);
        time_of_each_concentration_change(0,0)=0;
        time_of_each_concentration_change(0,1)=trace_duration*0.2;
        time_of_each_concentration_change(0,2)=trace_duration*0.3;
        concentration_at_each_time(0,0)=0;
        concentration_at_each_time(0,1)=pulse_concentration_[i];
        concentration_at_each_time(0,2)=0;






        Pulses_trace atrace(name,
                            time_of_each_concentration_change,
                            concentration_at_each_time,
                            trace_duration,
                            frequency_of_sampling,
                            time_to_exchange_,
                            sub_step_time_,
                            time_to_next_trace_);

        traces_v.push_back(atrace);
        y_.push_back(m);
      }




  }



  void ExperimentalData::init()
  {
    std::size_t pos=fileName_.find_last_of('.');
    std::string ext;
    if ((pos!=fileName_.npos))
      ext=fileName_.substr(pos+1,pos+3);
    if (ext=="abf")
      {
        ABFFile abf(fileName_);

      }
    if ((pos!=fileName_.npos)&&(fileName_.substr(pos,pos+3))=="abf")
      {
        ABFFile abf(fileName_);

      }

    std::ifstream f(fileName_.c_str());
    std::string line;
    std::vector< std::vector< double> > yr;
    while (std::getline(f,line))
      {
        std::stringstream ss(line);
        std::string fieldcode, cellcontent;
        std::getline(ss,fieldcode,',');
        if (fieldcode.find_first_of("[1234567890qwertyuiopasdfghjklñzxcvbnm")==fieldcode.npos)
          {
            std::vector<double> v;
            while(std::getline(ss,cellcontent,','))
              {
                double value;
                if (ToValue(cellcontent,value))
                  {
                    v.push_back(value);
                    total_samples_++;
                  }
                else
                  v.push_back(Markov_LA::NaN());
              }
            yr.push_back(v);
          }

        else if (fieldcode==fileNameCode_)
          {
            while(std::getline(ss,cellcontent,','))
              {
                this->trace_fnames_.push_back(cellcontent);
              }
          }
        else if (fieldcode==PatchNameCode_)
          {
            while(std::getline(ss,cellcontent,','))
              {
                this->patch_names_.push_back(cellcontent);
                patch_traces_[cellcontent].push_back(patch_names_.size()-1);
              }
          }
        else if (fieldcode==GainCode_)
          {
            while(std::getline(ss,cellcontent,','))
              {
                double value;
                int firstNumber=cellcontent.find_first_of("0123456789");
                int lastNumber=cellcontent.find_first_not_of("0123456789.eE-");
                if (firstNumber>=0)
                  {
                    if(ToValue(cellcontent.substr(firstNumber,lastNumber),value))
                      {
                        this->gain_.push_back(value);
                      }
                    else gain_.push_back(1.0);
                  }
                else gain_.push_back(1.0);
              }
          }
        else if (fieldcode==SamplingFrequencyCode_)
          {
            while(std::getline(ss,cellcontent,','))
              {
                double value;
                int firstNumber=cellcontent.find_first_of("0123456789");
                int lastNumber=cellcontent.find_first_not_of("0123456789.eE-");
                if (ToValue(cellcontent.substr(firstNumber,lastNumber),value))
                  this->fs_.push_back(value);
              }
          }
        else if (fieldcode==AgonistCode_)
          {
            while(std::getline(ss,cellcontent,','))
              {
                double value;
                int firstNumber=cellcontent.find_first_of("0123456789");
                int lastNumber=cellcontent.find_first_not_of("0123456789.eE-",firstNumber);
                int lastLetter=cellcontent.find_first_not_of(
                      "qwertyuiopasdfghjklñzxcvbnm1234567890",
                      lastNumber);
                ToValue(cellcontent.substr(firstNumber,lastNumber),value);
                std::string units=cellcontent.substr(lastNumber,lastLetter);
                if (units=="uM")
                  value*=1e-6;

                this->pulse_concentration_.push_back(value);
              }
          }


      }

    for (std::map<std::string,std::vector<std::size_t> >::const_iterator
         it=patch_traces_.begin();
         it!=patch_traces_.end(); it++)
      {
        unique_patch_names_.push_back((*it).first);
      }


    std::size_t ntraces=fs_.size();
    for (std::size_t i=0; i<ntraces;i++)
      {
        std::vector<double> yv;
        for (std::size_t j=0; j<yr.size(); j++)
          {
            if (!Markov_LA::isNaN(yr[j][i]))
              yv.push_back(yr[j][i]);
          }
        Markov_LA::M_Matrix<double> m(yv.size(),1);
        for (std::size_t j=0; j<yv.size(); j++)
          {
            m[j]=yv[j]*this->gain_[i];
          }
        std::string name=trace_fnames_[i];
        double trace_duration=yv.size()/fs_[i];
        double frequency_of_sampling=fs_[i];
        Markov_LA::M_Matrix<double> time_of_each_concentration_change(1,3);
        Markov_LA::M_Matrix<double> concentration_at_each_time(1,3);
        time_of_each_concentration_change(0,0)=0;
        time_of_each_concentration_change(0,1)=trace_duration*0.2;
        time_of_each_concentration_change(0,2)=trace_duration*0.3;
        concentration_at_each_time(0,0)=0;
        concentration_at_each_time(0,1)=pulse_concentration_[i];
        concentration_at_each_time(0,2)=0;






        Pulses_trace atrace(name,
                            time_of_each_concentration_change,
                            concentration_at_each_time,
                            trace_duration,
                            frequency_of_sampling,
                            time_to_exchange_,
                            sub_step_time_,
                            time_to_next_trace_);

        traces_v.push_back(atrace);
        y_.push_back(m);
      }




  }

  ExperimentalData::ExperimentalData():
    name_(),
    fileName_(),
    fileNameCode_(),
    PatchNameCode_(),
    GainCode_(),
    SamplingFrequencyCode_(),
    AgonistCode_(),
    time_to_exchange_(),
    sub_step_time_(),
    time_to_next_trace_(),
    trace_fnames_(),
    patch_names_(),
    gain_(),
    fs_(),
    fc_(),
    Conc_(),
    traces_v(),
    pulse_concentration_(),
    y_(),
    total_samples_(),
    i_trace_(),
    i_replicate_()

  {}


  ExperimentalData::ExperimentalData(const ExperimentalData& other):
    name_(other.name_),
    fileName_(other.fileName_),
    fileNameCode_(other.fileNameCode_),
    PatchNameCode_(other.PatchNameCode_),
    GainCode_(other.GainCode_),
    SamplingFrequencyCode_(other.SamplingFrequencyCode_),
    AgonistCode_(other.AgonistCode_),
    time_to_exchange_(other.time_to_exchange_),
    sub_step_time_(other.sub_step_time_),
    time_to_next_trace_(other.time_to_next_trace_),
    trace_fnames_(other.trace_fnames_),
    patch_names_(other.patch_names_),
    patch_traces_(other.patch_traces_),
    unique_patch_names_(other.unique_patch_names_),
    gain_(other.gain_),
    fs_(other.fs_),
    fc_(other.fc_),
    Conc_(other.Conc_),
    traces_v(other.traces_v),
    pulse_concentration_(other.pulse_concentration_),
    y_(other.y_),
    total_samples_(other.total_samples_),
    i_trace_(other.i_trace_),
    i_replicate_(other.i_replicate_)

  {}


  ClassDescription ExperimentalData::GetDescription()const
  {
    ClassDescription desc(myClass(),mySuperClass());

    desc.push_back("name",name_);

    desc.push_back("fileName",fileName_);

    desc.push_back("fileNameCode",fileNameCode_);
    desc.push_back("PatchNameCode",PatchNameCode_);
    desc.push_back("GainCode",GainCode_);
    desc.push_back("SamplingFrequencyCode",SamplingFrequencyCode_);
    desc.push_back("AgonistCode",AgonistCode_);
    desc.push_back("time_to_exchange",time_to_exchange_);
    desc.push_back("sub_step_time",sub_step_time_);
    desc.push_back("time_to_next_trace",time_to_next_trace_);


    return desc;
  }


  bool ExperimentalData::LoadFromDescription(
      const ClassDescription& classDes)

  {
    if (classDes.ClassName()!=myClass())
      return false;
    std::string name;
    if (!ToValue(classDes["name"],name))
      return false;

    std::string fileName;
    if (!ToValue(classDes["fileName"],fileName))
      return false;
    std::string fileNameCode;
    if (!ToValue(classDes["fileNameCode"],fileNameCode))
      return false;
    std::string PatchNameCode;
    if (!ToValue(classDes["PatchNameCode"],PatchNameCode))
      return false;
    std::string GainCode;
    if (!ToValue(classDes["GainCode"],GainCode))
      return false;

    std::string SamplingFrequencyCode;
    if (!ToValue(classDes["SamplingFrequencyCode"],SamplingFrequencyCode))
      return false;

    std::string AgonistCode;
    if (!ToValue(classDes["AgonistCode"],AgonistCode))
      return false;

    double time_to_exchange;
    if (!ToValue(classDes["time_to_exchange"],time_to_exchange))
      return false;
    double sub_step_time;
    if (!ToValue(classDes["sub_step_time"],sub_step_time))
      return false;
    double time_to_next_trace;
    if (!ToValue(classDes["time_to_next_trace"],time_to_next_trace))
      return false;


    *this=ExperimentalData( name,
                            fileName,
                            fileNameCode,
                            PatchNameCode,
                            GainCode,
                            SamplingFrequencyCode,
                            AgonistCode,
                            time_to_exchange,
                            sub_step_time,
                            time_to_next_trace);

    return true;

  }







  std::string ExperimentalData::ClassName()
  {
    return "ExperimentalData";
  }





  std::string ExperimentalData::id()const
  {
    return name_;
  }

  std::string ExperimentalData::myClass()const
  {
    return ClassName();
  }


  ExperimentalData& ExperimentalData::operator=(const ExperimentalData& other)
  {
    if (this!=&other)
      {
        ExperimentalData tmp(other);
        swap(*this,tmp);

      }
    return *this;
  }

  void swap(ExperimentalData& one, ExperimentalData& two)
  {
    std::swap(one.name_,two.name_);
    std::swap(one.fileName_,two.fileName_);
    std::swap(one.fileNameCode_,two.fileNameCode_);
    std::swap(one.PatchNameCode_,two.PatchNameCode_);
    std::swap(one.GainCode_,two.GainCode_);
    std::swap(one.SamplingFrequencyCode_,two.SamplingFrequencyCode_);
    std::swap(one.AgonistCode_,two.AgonistCode_);
    std::swap(one.time_to_exchange_,two.time_to_exchange_);
    std::swap(one.sub_step_time_,two.sub_step_time_);
    std::swap(one.time_to_next_trace_,two.time_to_next_trace_);
    std::swap(one.trace_fnames_,two.trace_fnames_);
    std::swap(one.patch_traces_,two.patch_traces_);
    std::swap(one.unique_patch_names_,two.unique_patch_names_);
    std::swap(one.patch_names_,two.patch_names_);
    std::swap(one.gain_,two.gain_);
    std::swap(one.fs_,two.fs_);
    std::swap(one.fc_,two.fc_);
    std::swap(one.Conc_,two.Conc_);
    std::swap(one.traces_v,two.traces_v);
    std::swap(one.pulse_concentration_,two.pulse_concentration_);
    std::swap(one.y_,two.y_);
    std::swap(one.total_samples_,two.total_samples_);
    std::swap(one.i_trace_,two.i_trace_);
    std::swap(one.i_replicate_,two.i_replicate_);
  }



}
