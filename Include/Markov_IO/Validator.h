#ifndef VALIDATOR
#define VALIDATOR


#include <string>
#include <vector>
namespace Markov_IO {

  class ABC_Validator
  {
  public:

    enum State { Invalid, Intermediate, Acceptable };

    virtual ~ABC_Validator(){}
    virtual void fixup(std::string & ) const {}
    virtual State	validate(std::string & input, std::size_t & pos) const = 0;


  };


  class ABC_Id_Validator: public ABC_Validator
  {
    virtual ~ABC_Id_Validator(){}



    virtual void fixup(std::string & ) const=0;

    virtual std::vector<std::string> alternativesNext(const std::string &hint) const=0;

  };

}

#endif // VALIDATOR

