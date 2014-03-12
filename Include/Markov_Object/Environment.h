#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <map>
#include <set>
#include <memory>

#include "Markov_Object/ScaledExpression.h"


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
  std::shared_ptr<Abstract_Named_Object> idN(const std::string& variablename, const std::string &className);


  std::shared_ptr<Measurement_Unit> U(const std::string& unitAbreviation);
  std::shared_ptr<Abstract_Variable_Object > V(const std::string& variablename);
  std::shared_ptr<Quantity> Q(const std::string& quantityName);

  std::shared_ptr<const Measurement_Unit > U(const std::string& unitAbreviation)const;
  std::shared_ptr<const Abstract_Variable_Object > V(const std::string& variablename)const;
  std::shared_ptr<const Quantity > Q(const std::string& quantityName)const;

  std::shared_ptr< Measurement_Unit > Ud(const ScaledExpression& definition);
  std::shared_ptr< Quantity > Qd(const QuantityExpression& definition);

  std::shared_ptr<const Measurement_Unit > Ud(const ScaledExpression& definition)const;
  std::shared_ptr<const Quantity > Qd(const QuantityExpression& definition)const;




  std::set<std::string> idNames()const;
  std::set<std::string> Variables()const;
  std::set<std::string> Units()const;
  std::set<std::string> Magnitudes()const;


  void add(std::shared_ptr<Abstract_Named_Object> n);

  void add(std::shared_ptr<Quantity> q);
  void add(std::shared_ptr<Measurement_Unit> u);


  bool addDef(std::shared_ptr<Quantity> q);
  bool addDef(std::shared_ptr<Measurement_Unit> u);



  Abstract_Object* create(std::string classname);


  bool doesDynCast(const Abstract_Object* o,std::string classname);

  std::set<std::string> getSuperClasses(const std::string& classname);

  bool empty()const;

  Environment();

  ~Environment();

private:
  std::map<std::string,std::shared_ptr<Abstract_Variable_Object>> V_;  //only owner
  std::map<std::string,std::shared_ptr<Quantity>> Q_;  //only owner
  std::map<std::string,std::shared_ptr<Measurement_Unit>> U_;  //only owner

  std::map<QuantityExpression,std::shared_ptr<Quantity>> QQ_;  //only owner
  std::map<ScaledExpression,std::shared_ptr<Measurement_Unit>> SU_;  //only owner


  std::map<std::string,Abstract_Object*> classes_;

};
}


#endif // ENVIRONMENT_H
