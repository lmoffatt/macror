#ifndef EXPRESSIONPRODUCT_H
#define EXPRESSIONPRODUCT_H
#include <string>
#include <set>
#include <map>
#include "Macror_Var/Abstract_Object.h"


namespace Macror_Var {
  class ExpressionProduct:  public virtual Abstract_Object
  {
  public:
    static const char pow='^';
    static  const char mult='*';
    static  const char div='/';
   // static  const char lb='(';
   // static  const char rb=')';


    static constexpr const char* allowed="abcdefghijklmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static constexpr const char* numeric="1234567890+-";

    static  std::string legal();

    static constexpr const char* separator=" \t\n";

    static    std::string getName(const std::string text, std::size_t &cursor);
    static    std::string getName(const std::string text);

    static
    std::map<std::string,int> getDefinition(const std::string& defs,std::size_t& cursor);


    static
    std::map<std::string,int> getDefinition(const std::string& defs);



    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    // Abstract_Object interface
    virtual std::set<std::string> mySuperClasses() const override;
    virtual std::string myClass() const override;

    virtual bool empty() const override;


    virtual ExpressionProduct *create() const override;

    virtual std::string ToString() const override;

    virtual ExpressionProduct*
    CreateObject(const std::string &text, std::size_t &cursor) const override;



    // new methods non virtual
    ExpressionProduct &operator+=(const ExpressionProduct& other);
    ExpressionProduct& operator*=(int n);

    bool operator<(const ExpressionProduct& other)const;




    ExpressionProduct(std::map<std::string,int> expression);
    ExpressionProduct(std::string exp);
    ExpressionProduct();

    virtual const std::map<std::string, int>& value()const;
    virtual std::map<std::string, int>& value();

    ExpressionProduct& removeUnitTerms();


   protected:
    virtual ExpressionProduct*
    ToObject(const std::string &text, std::size_t &cursor)  override;

  private:
    std::map<std::string, int> expr_;

  };

}

#endif // EXPRESSIONPRODUCT_H
