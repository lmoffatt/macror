#include "Markov_IO/StructureEnv.h"
#include"Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/StructureEnv_templ.h"

namespace Markov_IO_New
{

  void StructureEnv_New::pushVoidType()
  {
    std::string id=Cls<void>::name();
    idTypes_.push_back(id);
    types_[id]=new Implements_Data_Type_New<void>();


  }

  StructureEnv_New::StructureEnv_New(const StructureEnv_New *parent, const std::__cxx11::string &idType):
    StructureEnv_New(parent,parent->idToTyped<StructureEnv_New*>(idType)){}

  bool StringInput::getLine(std::__cxx11::string &line, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective)
  {
    if (std::getline(ss_,line))
      return true;
    else return false;
  }

  bool StringInput::get(std::__cxx11::string &s, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) {
    ss_>>s;
    return ss_.good();
  }

  void StringInput::put_back(const std::__cxx11::string &s)
  {
    std::string o=s;
    if (o.back()!=' ') o.push_back(' ');
    std::string l;
    while (std::getline(ss_,l)){o+=l+"\n";}
    std::istringstream(o).swap(ss_);
  }

  bool StringInput::get(double &x, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) {
    ss_>>x;
    return ss_.good();
  }

  bool StringInput::get(int &n, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) {
    ss_>>n;
    return ss_.good();
  }

  bool StringInput::get(bool &n, std::__cxx11::string *, const std::__cxx11::string &) {
    ss_>>n;
    return ss_.good();
  }

  bool StringInput::get(std::size_t &n, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) {
    ss_>>n;
    return ss_.good();
  }

  bool StringInput::get(char &c, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective)
  {
    ss_.get(c);
    return ss_.good();
  }

  bool StringInput::get(char &c)
  {
    ss_.get(c);
    return ss_.good();

  }

  bool StringInput::nextCharIs(char c, char &found)
  {
    while ((ss_.get(found))&&(found==' ')) {}
    if (found==c)
      return true;
    else
      {
        ss_.putback(found);
        return false;
      }
  }

  bool StringInput::nextCharIs(char c, bool advanceInFailure)
  {
    char d=' ';
    while ((ss_.get(d))&&(d==' ')) {}
    if (d==c)
      return true;
    else if (!advanceInFailure)
      ss_.putback(d);
    return false;
  }

  bool StringInput::testIfNextCharIs(char c)
  {
    char d=' ';
    while ((ss_.get(d))&&(d==' ')) {}
    ss_.putback(d);
    return  d==c;
  }

  bool StringInput::eof() const
  {
    return ss_.eof();
  }

  StringInput::~StringInput(){}

  StringInput::StringInput(const std::__cxx11::string &s, char spacer)
    : spacer_(spacer),ss_(s){}

  void StringInput::setSpacer(char c){spacer_=c;}

  char StringInput::getSpacer() const {return spacer_;}

}
