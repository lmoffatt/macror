#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <map>
#include <set>



namespace Markov_Object {

class Quantity;
class Abstract_Object;
class Abstract_Named_Object;
class Abstract_Variable_Object;
class Measurement_Unit;


class Environment
{
public:
  const Abstract_Named_Object* idN(const std::string& variablename)const;
  const Measurement_Unit* U(const std::string& unitAbreviation)const;
  const Abstract_Variable_Object* V(const std::string& variablename)const;
  const Quantity* Q(const std::string& quantityName)const;




  std::set<std::string> idNames()const;
  std::set<std::string> Variables()const;
  std::set<std::string> Units()const;
  std::set<std::string> Magnitudes()const;


  void add(Abstract_Named_Object* n);


  Abstract_Object* create(std::string classname);


  bool doesDynCast(const Abstract_Object* o,std::string classname);

  std::set<std::string> getSuperClasses(const std::string& classname);

  bool empty()const;

  Environment();

  ~Environment();

private:
  std::map<std::string,Abstract_Named_Object*> idNames_;  //only owner

  std::map<std::string,Abstract_Object*> classes_;

};
}


#endif // ENVIRONMENT_H
