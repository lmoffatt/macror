#ifndef ABC_IO_H
#define ABC_IO_H
#include <string>
#include <sstream>

namespace Markov_IO
{

class ABC_IO
{
public:
    /// get a string from the input source
    virtual std::string getline()=0;


    /// put a string to the output source
    virtual void put(const std::string&)=0;


  virtual void putError(const std::string& )=0;

    template <typename T>
  void put(const T& x )
  {
    std::stringstream ss;
    ss<<x;
    put(ss.str());
  }


};
template <typename T>
ABC_IO& operator<<(ABC_IO& s,const T& x )
{
  s.put(x);
  return s;
}



}
#endif // ABC_IO_H
