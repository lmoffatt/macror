#ifndef SCALEDEXPRESSION_H
#define SCALEDEXPRESSION_H

#include "Markov_Object/QuantityExpression.h"
#include <cmath>

namespace Markov_Object {



class ScaledExpression: public QuantityExpression
{
  // Abstract_Object interface
public:
  static  std::string ClassName();
 static
  std::set<std::string> SuperClasses();

  static Class_info classInfo();

//overrides

  virtual Class_info myClassInfo() const override;
  virtual std::string myClass() const override;

  virtual bool empty() const override;
  virtual bool invalid() const override;
  virtual ScaledExpression *create() const override;
  virtual std::string ToString() const override;

  virtual ScaledExpression *
  CreateObject(const std::string &text, std::size_t &cursor) const override;


  //new methods

   virtual double scale()const;

   virtual void setScale(double newScale);

  // regular methods
  // new methods non virtual
   ScaledExpression &operator+=(const ScaledExpression& other);

   ScaledExpression& operator*=(int n);

   bool operator<(const ScaledExpression& other)const;




  // constructors and destructors
  ScaledExpression();


  ScaledExpression(double scale,
                   QuantityExpression def);


  ~ScaledExpression();


  ScaledExpression(const ScaledExpression& other);


protected:
  virtual ScaledExpression *ToObject(const std::string &text, std::size_t &cursor) override;


private:
  double scale_;

};


ScaledExpression operator*(const ScaledExpression &one, int n);

ScaledExpression operator+(const ScaledExpression &one, const ScaledExpression &other);

}

#endif // SCALEDEXPRESSION_H
