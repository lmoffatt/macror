#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <map>
#include <set>
#include <memory>


namespace Markov_Object {

class Quantity;
class Abstract_Object;
class Abstract_Named_Object;
class Abstract_Variable_Object;
class Measurement_Unit;


class Environment
{
public:
  std::shared_ptr<const Abstract_Named_Object> idN(const std::string& variablename)const;
  std::shared_ptr<Abstract_Named_Object> idN(const std::string& variablename);


  std::shared_ptr<Measurement_Unit> U(const std::string& unitAbreviation);
  std::shared_ptr<Abstract_Variable_Object > V(const std::string& variablename);
  std::shared_ptr<Quantity> Q(const std::string& quantityName);




  std::set<std::string> idNames()const;
  std::set<std::string> Variables()const;
  std::set<std::string> Units()const;
  std::set<std::string> Magnitudes()const;


  void add(std::shared_ptr<Abstract_Named_Object> n);


  Abstract_Object* create(std::string classname);


  bool doesDynCast(const Abstract_Object* o,std::string classname);

  std::set<std::string> getSuperClasses(const std::string& classname);

  bool empty()const;

  Environment();

  ~Environment();

private:
  std::map<std::string,std::shared_ptr<Abstract_Named_Object>> idNames_;  //only owner

  std::map<std::string,Abstract_Object*> classes_;

};
}


#endif // ENVIRONMENT_H
