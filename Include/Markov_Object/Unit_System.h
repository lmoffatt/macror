#ifndef UNIT_SYSTEM_H
#define UNIT_SYSTEM_H

#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/Quantity.h"

namespace Markov_Object {

  class Unit_System: public Abstract_Named_Object
  {


    // Abstract_Object interface
  public:


    static std::string ClassName();

    static Class_info classInfo();

    static std::set<std::string> SuperClasses();



    virtual Class_info myClassInfo() const override;
    virtual std::string myClass() const override;
    virtual bool empty() const override;
    virtual bool isValid() const override;
    virtual std::string selfInvariant()const override
    {
      std::string out="";


    }
    virtual Unit_System *create() const override;
    virtual std::string ToString() const override;
    virtual Unit_System *CreateObject(const std::string &text, std::size_t &cursor) const override;
    virtual std::string stdUnit(const std::string& idQuantity)const;

    virtual std::vector<std::string> unitList(const std::string& idQuantity)const;

    virtual bool isStdQuantity(const std::string idQuantity)const;
    virtual std::set<std::string> stdQuantities()const;


    virtual std::set<std::string> quantities()const;

    virtual std::set<std::string> referencedObjects() const override;

    Unit_System(Environment* e,
                const std::string& name,
                const std::set<std::string>& stdQuantities,
                const std::map<std::string,std::vector<std::string>>& quantity2Units);

    Unit_System();

  protected:
    virtual Unit_System *ToObject(const std::string &text, std::size_t &cursor) override;




  private:
    std::set<std::string> stdQ_;
    std::map<std::string,std::vector<std::string>> q2Us_;

  };

}




#endif // UNIT_SYSTEM_H
