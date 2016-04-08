/*!
 * @file auxiliarIO.cpp @brief Implementation of Input output methods

 */

#include <iostream>
#include <sstream>

#include <map>
#include <vector>
#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixIO.h"
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/Object.h"
#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/ABC_Noise.h"
#include "Markov_Mol/ABC_PatchModel.h"
#include "Markov_Mol/PatchModelNormalDistribution.h"
#include "Markov_IO/PulsesTrace.h"
#include "Markov_IO/Trace.h"
#include "Markov_IO/ParametersMoments.h"
#include "Markov_IO/Parameters.h"
#include "Markov_Bay/LikelihoodEvaluation.h"
#include "Markov_Bay/SingleOptimizationResult.h"
#include "Markov_Bay/OptimizationResult.h"



/*!
  it waits for an input from io
  */

namespace Markov_IO_New
{
  std::istream& safeGetline(std::istream& is, std::string& t)
  {
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
          case '\r':
            c = sb->sgetc();
            if(c == '\n')
              sb->sbumpc();
            return is;
          case '\n':
            return is;
          case EOF:
            is.setstate(std::ios_base::eofbit);
            return is;
          default:
            t += (char)c;
          }
      }
  }

  char press_any_key_to_continue()
  {
    char ch;
    std::cout<<"\n Press any key to continue....\n";
    std::cin>>ch;
    return ch;
  }
  ;




  std::istream& extract_NaN_safe(std::istream& ss, double& value){
    if (!(ss>>value))
      {
        ss.clear();
        std::string nan_val;
        ss>>nan_val;
        if (nan_val=="nan")
          value=Markov_LA::NaN();
        else if (nan_val=="-nan")
          value=-Markov_LA::NaN();
        else if (nan_val=="inf")
          value=Markov_LA::infinity();
        else if (nan_val=="-inf")
          value=-Markov_LA::infinity();
        else
          ss.setstate(ss.rdstate() | std::ios_base::failbit);
      }
    return ss;
  }



  void removeEndOfLine(std::string& name)
  {
    name.erase(name.find_last_of("\n"));
  }




  /**
@brief Displays in a String the contents of the class T.

@remarks it uses the operator<<() on T
@post Enough information should be in the strign to build the class\n
@post It should be the case that x==stringToClass(ToString(x))

*/
  template <class T>
  std::string ToString(const T& x)
  {
    std::stringstream ss;
    ss.precision(std::numeric_limits<T>::digits10);
    ss<<x;
    std::string str=ss.str();
    return str;
  }


  template<>
  bool ToValue(const std::string& str,double& value)
  {
    if (str.empty())
      return false;

    std::istringstream ss(str);
    extract_NaN_safe(ss,value);
    bool res=(ss.good());
    return res;
  }




  /**
  @brief Extract an object of class T from a string.
  @remarks it uses the operator>>(std::istream&,T)
  \returns true if succesfull
  */
  template<class T>
  bool ToValue(const std::string& str,T& value)
  {
    if (str.empty())
      return false;
    std::istringstream ss(str);
    bool res=bool(ss>>value);
    return res;
  }


  /**
  @brief Extract an object of class Abstract class T from a string.
  @remarks it uses the operator>>(std::istream&,T*)
  \returns true if succesfull

template<class T>
bool ToValue(const std::string& str,T*& value)
{
    if (str.empty())
            return false;
    std::istringstream ss(str);
    bool res=(ss>>value);
    return res;
}



*/



  /**
    Line to words parser. It chop a string line into different words that are
    separeated by specific characters

    @param[in] input_line a string containing words separated by delimiters
    @param[in] delimiters a string with the list of characters used as delimiters
    (all the rest are considered part of the words)
    @returns a vector with the words that compose the input_line


  */
  std::vector < std::string > LineToWords (const std::string& input_line,
                                           const std::string delimiters
                                           )
  {
    std::size_t npos0=input_line.find_first_not_of(delimiters);
    std::size_t npos1=input_line.find_first_of(delimiters,npos0);
    std::vector<std::string> output;
    while (std::string::npos!=npos0)
      {
        output.push_back(input_line.substr(npos0,npos1-npos0));
        npos0=input_line.find_first_not_of(delimiters,npos1);
        npos1=input_line.find_first_of(delimiters,npos0);
      }
    return output;
  }








  /*!
    Implementation for std::size_t
  */
  template
  std::string ToString(const std::size_t& x);


  /*!
    Implementation for std::size_t
  */
  template
  bool ToValue(const std::string& str,size_t& T);


  /*!
    Implementation for Markov_LA::M_Matrix<double>
  */
  template
  bool ToValue(const std::string& str,Markov_LA::M_Matrix<double>& T);



  /*!
    Implementation for Markov_LA::M_Matrix<std::size_t>
  */
  template
  bool ToValue(const std::string& str,Markov_LA::M_Matrix<std::size_t>& T);


  /*!
    Implementation for Markov_LA::M_Matrix<int>
  */
  template
  bool ToValue(const std::string& str,Markov_LA::M_Matrix<int>& T);


  template
  bool ToValue(const std::string& str,bool& T);

  template
  bool ToValue(const std::string& str,Markov_Mol::ABC_Markov_Model*& T);









  template std::string ToString(const double& x);

  template std::string ToString(const Markov_LA::M_Matrix<double>& x);

  template std::string ToString(const Markov_LA::M_Matrix<std::size_t>& x);

  template std::string ToString(const bool& x);

  template std::string ToString(const std::string& x);



  template std::string ToString(const int& x);

}



namespace Markov_IO
{

  char press_any_key_to_continue()
  {
    char ch;
    std::cout<<"\n Press any key to continue....\n";
    std::cin>>ch;
    return ch;
  }
  ;


  // temporarily removed
  ///**
  //  @brief Vector of class Insert Operator.
  //It inserts the formatted contents of the vector
  //  into an ostream.
  //  @remarks It uses the operator<<(std::ostream&,T) for formatting the elements
  //of the vector
  //  @post formatted the elements of the vector are in different lines

  //   */
  //template<class T>
  //std::ostream& operator<< (std::ostream& s,const std::vector<T>& v)
  //{
  //    for (size_t i=0,n=v.size(); i<n; ++i)
  //	s<<v[i]<<"\n";
  //    return s;
  //}



  ///**
  //  @brief Vector of doubles Insert Operator.
  //It inserts the formatted contents of the vector
  //  into an ostream.
  //  @remarks It uses the operator<<(std::ostream&,double) for formatting the elements
  //of the vector
  //  @post formatted the elements of the vector are in different lines

  //   */
  //template<>
  //std::ostream& operator<< (std::ostream& s,const std::vector<double>& v)
  //{
  //    for (size_t i=0,n=v.size(); i<n; ++i)
  //	s<<v[i]<<"   ";
  //    return s;
  //}

  ///**
  //  @brief Vector of std::size_t Insert Operator.
  //It inserts the formatted contents of the vector
  //  into an ostream.
  //  @remarks It uses the operator<<(std::ostream&,double) for formatting the elements
  //of the vector
  //  @post formatted the elements of the vector are in different lines

  //   */
  //template<>
  //std::ostream& operator<< (std::ostream& s,const std::vector<std::size_t>& v)
  //{
  //    for (size_t i=0,n=v.size(); i<n; ++i)
  //	s<<v[i]<<"   ";
  //    return s;
  //}


  ///**
  //  @brief Map Insert Operator. It inserts the formatted contents of the map
  //  into an ostream, with one line per mapped element.
  //  @remarks It uses the operator<<(std::ostream&,T) (T=K,D) for formatting the
  //keys and the element values of the map
  //  @post the keys are separated from the elements by a space,
  //   */
  //template<typename K, typename D>
  //std::ostream& operator<< (std::ostream& s,const std::map<K, D>& x)
  //{

  //    for(typename std::map<K,D>::const_iterator  it=x.begin(); it!=x.end(); ++it)
  //	s<<(*it).first<<"\n"<<it->second<<"\n";
  //    return s;
  //}


  ///**
  //  @brief Pair Insert Operator. It inserts the formatted contents of the a pair
  //  into an ostream.
  //  @remarks It uses the operator<<(std::ostream&,T) (T=T1,T2) for formatting the
  //keys and the element values of the map
  //  @post each element is separated by a space
  //   */

  //template<typename T1, typename T2>
  //inline
  //std::ostream& operator<< (std::ostream& s,const std::pair<T1, T2>& x)
  //{

  //    s<<x.first<<"    "<<x.second<<std::endl;
  //    return s;
  //}



  std::istream& extract_NaN_safe(std::istream& ss, double& value){
    if (!(ss>>value))
      {
        ss.clear();
        std::string nan_val;
        ss>>nan_val;
        if (nan_val=="nan")
          value=Markov_LA::NaN();
        else if (nan_val=="-nan")
          value=-Markov_LA::NaN();
        else if (nan_val=="inf")
          value=Markov_LA::infinity();
        else if (nan_val=="-inf")
          value=-Markov_LA::infinity();
        else
          ss.setstate(ss.rdstate() | std::ios_base::failbit);
      }
    return ss;
  }



  void removeEndOfLine(std::string& name)
  {
    name.erase(name.find_last_of("\n"));
  }


  std::istream& safeGetline(std::istream& is, std::string& t)
  {
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
          case '\r':
            c = sb->sgetc();
            if(c == '\n')
              sb->sbumpc();
            return is;
          case '\n':
            return is;
          case EOF:
            is.setstate(std::ios_base::eofbit);
            return is;
          default:
            t += (char)c;
          }
      }
  }



  /**
@brief Displays in a String the contents of the class T.

@remarks it uses the operator<<() on T
@post Enough information should be in the strign to build the class\n
@post It should be the case that x==stringToClass(ToString(x))

*/
  template <class T>
  std::string ToString(const T& x)
  {
    std::stringstream ss;
    ss.precision(std::numeric_limits<T>::digits10);
    ss<<x;
    std::string str=ss.str();
    return str;
  }
  template <>
  std::string ToString(const ABC_Put& x)
  {
    std::stringstream ss;
      x.put(ss);
    std::string str=ss.str();
    return str;
  }


  template <>
  std::string ToString(const ABC_Object& x)
  {
    std::stringstream ss;
    if (x.mySuperClass()==ABC_Object::ClassName())
      x.put(ss);
    else
      {
        const ABC_Saveable*p= dynamic_cast<const ABC_Saveable*> (&x);
        ss<<p->GetDescription();
      }
    std::string str=ss.str();
    return str;
  }

  template<>
  bool ToValue(const std::string& str,double& value)
  {
    if (str.empty())
      return false;

    std::istringstream ss(str);
    extract_NaN_safe(ss,value);
    bool res=(ss.good());
    return res;
  }




  /**
  @brief Extract an object of class T from a string.
  @remarks it uses the operator>>(std::istream&,T)
  \returns true if succesfull
  */
  template<class T>
  bool ToValue(const std::string& str,T& value)
  {
    if (str.empty())
      return false;
    std::istringstream ss(str);
    bool res=bool(ss>>value);
    return res;
  }


  /**
  @brief Extract an object of class Abstract class T from a string.
  @remarks it uses the operator>>(std::istream&,T*)
  \returns true if succesfull

template<class T>
bool ToValue(const std::string& str,T*& value)
{
    if (str.empty())
            return false;
    std::istringstream ss(str);
    bool res=(ss>>value);
    return res;
}



*/

  /**
  @brief Extract an object of class T from a pointer to an Object.
  @remarks it uses the operator>>(std::istream&,T)
  \returns true if succesfull
  */
  template<class T>
  bool ToValue_regular(const ABC_Object* o,T& value)
  {
    if (o->myClass()!=Object<T>::ClassName())
      return false;
    const Object<T>* oT=dynamic_cast<const Object<T>*> (o);
    value=oT->Value();
    return true;
  }

  template<class T>
  bool ToValue_object(const ABC_Object* o,T& value)
  {
    T a;
    if (o==0)
      return false;
    a=dynamic_cast<T>(o->clone());
    if ((o->mySuperClass()==a->myClass())||(o->myClass()==a->myClass()))
      {
        value=a;
        return true;
      }
    else
      {
        delete a;
        return false;
      }

  }
  bool ToObject(const std::string& s, ABC_Object*& o)
  {
    if (o->myClass()==Object<double>::ClassName())
      {
        double value;
        if (!ToValue(s,value))
          {
            if (s=="nan")
              {
                value=Markov_LA::NaN();
              }
            else if (s=="-nan")
              {
                value=-Markov_LA::NaN();
              }
            else
              return false;
          }
        o= new Object<double>(value);
        return true;
      }
    else if (o->myClass()==Object<std::size_t>::ClassName())
      {
        std::size_t value;
        if (!ToValue(s,value))
          return false;
        o= new Object<std::size_t>(value);
        return true;
      }
    else if (o->myClass()==Object<bool>::ClassName())
      {
        bool value;
        if (!ToValue(s,value))
          return false;
        o= new Object<bool>(value);
        return true;
      }else if (o->myClass()==Object<std::string>::ClassName())
      {
        o= new Object<std::string>(s);
        return true;
      }
    else if (o->myClass()==Object<Markov_LA::M_Matrix<double> >::ClassName())
      {
        Markov_LA::M_Matrix<double> value;
        if (!ToValue(s,value))
          return false;
        o= new Object<Markov_LA::M_Matrix<double> >(value);
        return true;
      }
    else if (o->myClass()==Object<Markov_LA::M_Matrix<std::size_t> >::ClassName())
      {
        Markov_LA::M_Matrix<std::size_t> value;
        if (!ToValue(s,value))
          return false;
        o= new Object<Markov_LA::M_Matrix<std::size_t> >(value);
        return true;
      }
    else if (o->mySuperClass()==ABC_Experiment::ClassName())
      {
        ABC_Experiment* value;
        if (!ToValue(s,value))
          return false;
        o= value;
        return true;
      }
    else if (o->mySuperClass()==ABC_trace::ClassName())
      {
        ABC_trace* value;
        if (!ToValue(s,value))
          return false;
        o= value;
        return true;
      }
    else if (o->mySuperClass()==Markov_Mol::ABC_noise::ClassName())
      {
        Markov_Mol::ABC_noise* value;
        if (!ToValue(s,value))
          return false;
        o= value;
        return true;
      }
    else if (o->mySuperClass()==Markov_Mol::ABC_PatchModel::ClassName())
      {
        Markov_Mol::ABC_PatchModel* value;
        if (!ToValue(s,value))
          return false;
        o= value;
        return true;
      }
    else if (o->mySuperClass()==Parameters::ClassName())
      {
        Parameters* value;
        if (!ToValue(s,value))
          return false;
        o= value;
        return true;
      }
    else if (o->mySuperClass()==Markov_Bay::ABC_Distribution::ClassName())
      {
        Markov_Bay::ABC_Distribution* value;
        if (!ToValue(s,value))
          return false;
        o= value;
        return true;
      }
    else if (o->mySuperClass()==Markov_Bay::ABC_Result::ClassName())
      {
        Markov_Bay::ABC_Result* value;
        if (!ToValue(s,value))
          return false;
        o= value;
        return true;
      }
    else
      return false;

  }




  /**
    Line to words parser. It chop a string line into different words that are
    separeated by specific characters

    @param[in] input_line a string containing words separated by delimiters
    @param[in] delimiters a string with the list of characters used as delimiters
    (all the rest are considered part of the words)
    @returns a vector with the words that compose the input_line


  */
  std::vector < std::string > LineToWords (const std::string& input_line,
                                           const std::string delimiters
                                           )
  {
    std::size_t npos0=input_line.find_first_not_of(delimiters);
    std::size_t npos1=input_line.find_first_of(delimiters,npos0);
    std::vector<std::string> output;
    while (std::string::npos!=npos0)
      {
        output.push_back(input_line.substr(npos0,npos1-npos0));
        npos0=input_line.find_first_not_of(delimiters,npos1);
        npos1=input_line.find_first_of(delimiters,npos0);
      }
    return output;
  }







  ///*!
  //    Implementation for std::map<std::size_t,std::size_t>
  //  */
  //template
  //std::ostream& operator<< (std::ostream& s,
  //			  const std::map<std::size_t, std::size_t>& x);

  ///*!
  //    Implementation for std::pair<std::size_t,std::size_t>
  //  */
  //template
  //std::ostream& operator<< (std::ostream& s,
  //			  const std::pair<std::size_t, std::size_t>& x);

  /*!
    Implementation for std::size_t
  */
  template
  std::string ToString(const std::size_t& x);


  /*!
    Implementation for std::size_t
  */
  template
  bool ToValue(const std::string& str,size_t& T);


  /*!
    Implementation for Markov_LA::M_Matrix<double>
  */
  template
  bool ToValue(const std::string& str,Markov_LA::M_Matrix<double>& T);



  /*!
    Implementation for Markov_LA::M_Matrix<std::size_t>
  */
  template
  bool ToValue(const std::string& str,Markov_LA::M_Matrix<std::size_t>& T);


  /*!
    Implementation for Markov_LA::M_Matrix<int>
  */
  template
  bool ToValue(const std::string& str,Markov_LA::M_Matrix<int>& T);


  template
  bool ToValue(const std::string& str,bool& T);

  template
  bool ToValue(const std::string& str,Markov_Mol::ABC_Markov_Model*& T);


  template
  bool ToValue(const std::string& str,ABC_Experiment*& T);


  template
  bool ToValue(const std::string& str,Parameters*& T);




  template
  bool ToValue(const std::string& str,Markov_Mol::ABC_noise*& T);


  template
  bool ToValue(const std::string& str,Markov_Bay::SingleOptimizationResult*& T);

  template
  bool ToValue(const std::string& str,Markov_Bay::OptimizationResult*& T);



  template
  bool ToValue(const std::string& str,Markov_Mol::ABC_PatchModel*& T);


  template
  bool ToValue(const std::string& str,ParametersMoments*& T);



  //---//
  /*!
    Implementation for std::size_t
  */
  template<>
  bool ToValue(const ABC_Object* o,size_t& value)
  {return ToValue_regular(o,value);}


  template<>
  bool ToValue(const ABC_Object* o,std::string& value)
  {return ToValue_regular(o,value);}



  /*!
    Implementation for Markov_LA::M_Matrix<double>
  */
  template<>
  bool ToValue(const ABC_Object* o,Markov_LA::M_Matrix<double>& value)
  {return ToValue_regular(o,value);}




  /*!
    Implementation for Markov_LA::M_Matrix<std::size_t>
  */
  template<>
  bool ToValue(const ABC_Object* o,Markov_LA::M_Matrix<std::size_t>& value)
  {return ToValue_regular(o,value);}

  template<>
  bool ToValue(const ABC_Object* o,double& value)
  {return ToValue_regular(o,value);}


  template<>
  bool ToValue(const ABC_Object* o,bool& value)
  {return ToValue_regular(o,value);}

  template<>
  bool ToValue(const ABC_Object* o,Markov_Mol::ABC_Markov_Model*& value)
  {return ToValue_object<Markov_Mol::ABC_Markov_Model*>(o,value);}


  template<>
  bool ToValue(const ABC_Object* o,Markov_Mol::PatchModelNormalDistribution*& value)
  {return ToValue_object<Markov_Mol::PatchModelNormalDistribution*>(o,value);}


  template<>
  bool ToValue(const ABC_Object* o,Markov_Bay::LikelihoodEvaluation*& value)
  {return ToValue_object<Markov_Bay::LikelihoodEvaluation*>(o,value);}


  template<>
  bool ToValue(const ABC_Object* o,Markov_Bay::SingleOptimizationResult*& value)
  {return ToValue_object<Markov_Bay::SingleOptimizationResult*>(o,value);}


  template<>
  bool ToValue(const ABC_Object* o,Markov_Bay::OptimizationResult*& value)
  {return ToValue_object<Markov_Bay::OptimizationResult*>(o,value);}



  template<>
  bool ToValue(const ABC_Object* o,ABC_Experiment*& value)
  {return ToValue_object(o,value);}


  template<>
  bool ToValue(const ABC_Object* o,ParametersMoments*& value)
  {return ToValue_object(o,value);}

  template<>
  bool ToValue(const ABC_Object* o,Parameters*& value)
  {return ToValue_object(o,value);}



  template<>
  bool ToValue(const ABC_Object* o,Markov_Mol::ABC_noise*& value)
  {return ToValue_object(o,value);}

  template<>
  bool ToValue(const ABC_Object* o,Markov_Mol::ABC_PatchModel*& value)
  {
    if (o->mySuperClass()==Markov_Mol::ABC_PatchModel::ClassName())
      return ToValue_object(o,value);
    else
      return false;
  }




  template<>
  bool ToValue(const ABC_Object* o,Pulses_trace*& value)
  {return ToValue_object(o,value);}


  template<>
  bool ToValue(const ABC_Object* o,Trace*& value)
  {return ToValue_object(o,value);}





  template std::string ToString(const double& x);

  template std::string ToString(const Markov_LA::M_Matrix<double>& x);

  template std::string ToString(const Markov_LA::M_Matrix<std::size_t>& x);

  template std::string ToString(const bool& x);

  template std::string ToString(const std::string& x);



  template std::string ToString(const int& x);

  template std::string ToString(const ABC_Object& x);

  template std::string ToString(const ABC_Put& x);

}
