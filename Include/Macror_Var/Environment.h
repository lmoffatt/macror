#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <map>
#include <set>
#include <memory>
#include <sstream>



namespace Macror_Var {

class Quantity;
class Quantity_Expression;

class Abstract_Object;
class Abstract_Named_Object;
class Abstract_Variable_Object;
class Measurement_Unit;
class Measurement_Unit_Expression;
class Unit_System;


class Environment
{
public:
  std::shared_ptr<const Abstract_Named_Object> idN(const std::string& variablename)const;
  std::shared_ptr<Abstract_Named_Object> idN(const std::string& variablename, const std::string &className) const;


  std::shared_ptr<Measurement_Unit> U(const std::string& unitAbreviation);
  std::shared_ptr<Abstract_Variable_Object > V(const std::string& variablename);
  std::shared_ptr<Quantity> Q(const std::string& quantityName);

  std::shared_ptr<const Measurement_Unit > U(const std::string& unitAbreviation)const;
  std::shared_ptr<const Abstract_Variable_Object > V(const std::string& variablename)const;
  std::shared_ptr<const Quantity > Q(const std::string& quantityName)const;

  std::shared_ptr< Measurement_Unit > Ud(const Measurement_Unit_Expression& definition);
  std::shared_ptr< Quantity > Qd(const Quantity_Expression& definition);

  std::shared_ptr<const Measurement_Unit > Ud(const Measurement_Unit_Expression& definition)const;
  std::shared_ptr<const Quantity > Qd(const Quantity_Expression& definition)const;




  std::set<std::string> idNames()const;
  std::set<std::string> Variables()const;
  std::set<std::string> Units()const;
  std::set<std::string> Magnitudes()const;


  void add(std::shared_ptr<Abstract_Named_Object> n);

  void add(std::shared_ptr<Quantity> q);
  void add(std::shared_ptr<Measurement_Unit> u);


  bool addDef(std::shared_ptr<Quantity> q);
  bool addDef(std::shared_ptr<Measurement_Unit> u);


  Unit_System* getUnit_System();

  const Unit_System* getUnit_System()const;


  Abstract_Object* create(std::string classname);



  bool empty()const;

  Environment();

  ~Environment();

   template<typename T>
   std::string ToString(const T& x)
   {
     std::stringstream ss;
     ss<<x;
     std::string str=ss.str();
     return str;

   }



private:
  std::map<std::string,std::shared_ptr<Abstract_Variable_Object>> V_;  //only owner
  std::map<std::string,std::shared_ptr<Quantity>> Q_;  //only owner
  std::map<std::string,std::shared_ptr<Measurement_Unit>> U_;  //only owner

  std::map<Quantity_Expression,std::shared_ptr<Quantity>> QQ_;  //only owner
  std::map<Measurement_Unit_Expression,std::shared_ptr<Measurement_Unit>> SU_;  //only owner


  std::map<std::string,Abstract_Object*> classes_;
  Unit_System* us_;

};
}


#endif // ENVIRONMENT_H
