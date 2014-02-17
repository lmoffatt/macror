#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <map>

#include "Markov_Object/Abstract_Object.h"
#include "Markov_Object/Abstract_Value_Object.h"
#include "Markov_Object/Abstract_Variable_Object.h"



namespace Markov_Object {



class Environment
{
public:
  const Measurement_Unit* U(const std::string& unitAbreviation)const;
  const Abstract_Named_Object* V(const std::string& variablename)const;

  std::set<std::string> Variables()const;

  void addUnit(Measurement_Unit* u);

  void addVariable(Abstract_Named_Object* v);

  void add(Abstract_Named_Object* v);




  Abstract_Object* create(std::string classname);


  bool doesDynCast(const Abstract_Object* o,std::string classname);

  std::set<std::string> getSuperClasses(const std::string& classname);

  bool empty()const;

  Environment();

  ~Environment();

private:
  std::map<std::string,Measurement_Unit*> units_;
  std::map<std::string,Abstract_Named_Object*> variables_;
  std::map<std::string,Abstract_Object*> classes_;

};
}


#endif // ENVIRONMENT_H
