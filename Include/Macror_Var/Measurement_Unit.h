#ifndef MEASUREMENT_UNIT_H
#define MEASUREMENT_UNIT_H
#include "Macror_Var/Implement_Named_Object.h"
#include "Macror_Var/Implement_Refer_Environment.h"
#include "ExpressionProduct.h"

namespace Macror_Var {

  class Measurement_Unit:public Implement_Named_Object
  {
  public:
    static
    int abbrToN(char c);
    static
    std::string nToFullName(int n);

    static char nToAbbr(int n);


    static std::string ClassName();

    static std::set<std::string> SuperClasses();



    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;



    class Expression: public Implement_Refer_Environment
    {
    public:

      static std::string ClassName();

      static std::set<std::string> SuperClasses();



      // Abstract_Object interface
      virtual std::set<std::string> mySuperClasses() const override;
      virtual std::string myClass() const override;

      virtual bool empty() const override;
      virtual std::string ToString() const override;


      virtual Expression *create() const override;


      virtual Expression*
      CreateObject(const std::string &text, std::size_t &cursor) const override;

      // new methods non virtual

      Expression dimensionless();


      Expression& removeUnitTerms();


      std::map<std::string, int>& value();


      const std::map<std::string, int>& value()const;

      double scale()const;
      void setScale(double x)
       {
        scale_=x;
      }


      Expression &operator+=(const Expression& other);

      Expression& operator*=(int n);

      bool operator<(const Expression& other)const;

      Expression(Environment* e,std::map<std::string,int> expression,double sc);
      Expression(Environment* e,std::string exp, double sc);


      Expression(const Expression& E);


      Expression();


     protected:
      virtual Expression*
      ToObject(const std::string &text, std::size_t &cursor)  override;
      friend class Measurement_Unit;




    private:
      ExpressionProduct ep_;
      double scale_;

    };


    Expression self()const;

    virtual Expression definition()const;


    virtual Expression baseDefinition()const;


    virtual bool empty()const override;


    ///
    /// \brief ToString
    /// \return
    ///
    ///
    ///

    virtual std::string ToString()const override;

    virtual Measurement_Unit *
    CreateObject(const std::string &text, std::size_t &cursor) const override;


    virtual Measurement_Unit* create()const override;

    virtual std::set<std::string> referencedObjects()const override;


    bool operator<(const Measurement_Unit& rh)const;


    Measurement_Unit();



    Measurement_Unit(std::string idName,
                     Expression definition,
                     std::string fullname,
                     std::string whatthis);

    Measurement_Unit(Environment*  E,
                     std::string idName,
                     double scale,
                     std::string definition,
                     std::string fullname,
                     std::string whatthis);


    Measurement_Unit( Environment*  e);

    Environment* getEnvironment()const override
    {
      return def_.getEnvironment();
    }

  protected:
    virtual Measurement_Unit *
    ToObject(const std::string& multipleLines,std::size_t& pos) override;
    void setEnvironment(Environment* E)
    {
      def_.setEnvironment(E);
    }

 private:
    Expression def_;

    Expression baseDefinition(std::set<std::string> upstream) const;
  };


inline  Measurement_Unit::Expression
  operator*(const Measurement_Unit::Expression& one,
            int n)
  {
    Measurement_Unit::Expression out(one);
    out*=n;
    return out;
  }

 inline Measurement_Unit::Expression
  operator+(const Measurement_Unit::Expression& one,
            const Measurement_Unit::Expression& two)
  {
    Measurement_Unit::Expression out(one);
    out+=two;
    return out;
  }

  class Measurement_Unit_Expression: public Measurement_Unit::Expression
  {
  public:
    Measurement_Unit_Expression(const Measurement_Unit::Expression& one):
    Measurement_Unit::Expression(one){}
  };




}












#endif // MEASUREMENT_UNIT_H
