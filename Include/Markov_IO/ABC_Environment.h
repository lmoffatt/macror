#ifndef ABC_ENVIRONMENT_H
#define ABC_ENVIRONMENT_H

#include <string>
#include <vector>
#include <map>
#include "Markov_IO/ABC_Var.h"


namespace  Markov_IO {

  class ABC_Saveable;


  class ABC_Environment:public Implements_Complex_Var
  {
  public:
    ~ABC_Environment(){}


    virtual void putOut(const std::string& m)const=0;
    virtual void putErrorOut(const std::string& m)const=0;

    virtual std::string getLineIn()=0;


    virtual ABC_Saveable* getVar(const std::string& varName)=0;
    virtual const ABC_Saveable* getType(const std::string& varName)const=0;

    virtual bool getVar(const std::string& varName,ABC_Saveable*& varType)=0;

    virtual bool getVarCopy(const std::string& varName,ABC_Saveable*& varType)const=0;

    virtual std::vector<std::string> getVarsList()=0;
    virtual std::vector<std::string> getVarsList(ABC_Saveable* varType)const=0;
    virtual std::vector<std::string> getVarsList(std::string className)const=0;

    virtual std::vector<std::string> getTypesList()=0;

    virtual void add_type(const std::string& name, const ABC_Saveable *s)=0;

    virtual void add_var(std::string name, ABC_Saveable* s)=0;

    virtual  bool checkVariable(std::string var, std::string superClass) const=0;

    virtual std::vector<std::string> getSiblings(std::string name) const=0;
    virtual std::vector<std::string> getVarSiblings(std::string name) const=0;

    virtual  std::vector<std::string> getChilds(std::string name)const=0;


    virtual  bool has_var(const std::string& name) const=0;
    virtual  bool has_type(const std::string& name) const=0;
    virtual  bool has_superType(const std::string& name) const=0;

    virtual  void delete_var(const std::string& name)=0;


  };


}



#endif // ABC_ENVIRONMENT_H
