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










  template std::string ToString(const double& x);

  template std::string ToString(const Markov_LA::M_Matrix<double>& x);

  template std::string ToString(const Markov_LA::M_Matrix<std::size_t>& x);

  template std::string ToString(const bool& x);

  template std::string ToString(const std::string& x);



  template std::string ToString(const int& x);

}



