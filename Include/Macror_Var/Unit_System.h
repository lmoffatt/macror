#ifndef UNIT_SYSTEM_H
#define UNIT_SYSTEM_H


#include "Macror_Var/Quantity.h"

namespace Macror_Var {

  class Unit_System: public Implement_Named_Object,
      public Implement_Refer_Environment
  {


    // Abstract_Object interface
  public:


    static std::string ClassName();


    static std::set<std::string> SuperClasses();



    virtual std::set<std::string> mySuperClasses() const override;
    virtual std::string myClass() const override;
    virtual bool empty() const override;
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
