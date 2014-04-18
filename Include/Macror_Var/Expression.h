#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "Macror_Var/Token.h"


namespace Macror_Var
{

   class Expressions
  {
  public:

    Expressions& operator<<(const Expressions& other)
    {
      expr_.insert(expr_.end(),other.expr_.begin(),other.expr_.end());
      return *this;
    }
    Expressions& operator<<(const std::deque<Token>& other)
    {
      expr_.insert(expr_.end(),other.begin(),other.end());
      return *this;
    }

    void push_back(const Token& other)
    {
      expr_.push_back(other);
    }





    Expressions(const std::deque<Token>& exp): expr_(exp){}

    Expressions(std::deque<Token>&& exp): expr_(std::move(exp)){}


    std::deque<Token> toTokens()const{ return expr_;}

  private:
    std::deque<Token> expr_;

  };

}









#endif // EXPRESSION_H
