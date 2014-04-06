#include "Macror_Var/ExpressionProduct.h"
#include "Macror_Var/IdentifierName.h"


namespace Macror_Var {
  std::string ExpressionProduct::legal(){
    return std::string(allowed)+mult+pow+numeric+div;
  }

  std::map<std::string, int> ExpressionProduct::getDefinition(const std::string &defs)
  {
    std::size_t n=0;
    return getDefinition(defs,n);
  }

  std::string ExpressionProduct::getName(const std::string text,std::size_t& cursor)
  {
    IdentifierName::skipSpaces(text,cursor);
    auto start=text.find_first_of(allowed,cursor);
    cursor=text.find_first_not_of(allowed,start);

    std::string current=text.substr(start,cursor-start);
    return current;
  }
  std::string ExpressionProduct::getName(const std::string text)
  {
    std::size_t n=0; return getName(text,n);
  }


  std::map<std::string, int> ExpressionProduct::getDefinition(const std::string &defs,
                                                              std::size_t &cursor)
  {
    if (defs.empty())
      {
        return {};
      }
    else
      {
        std::size_t cursor0=cursor;

        std::map<std::string,int> out;
        IdentifierName::skipSpaces(defs,cursor);
        if (cursor==defs.npos)
          {
            cursor=cursor0;
            return {};
          }
        else
          {
            auto final=defs.find_first_of(separator,cursor);

            std::string candidate=defs.substr(cursor,final-cursor);
            auto nfin=candidate.find_first_not_of(legal());

            bool validformat=!candidate.empty()&&(nfin==candidate.npos);
            std::size_t pos=0;
            if(validformat)
              {
                while (pos<=candidate.size())
                  {

                    std::string current=getName(candidate,pos);
                    if (current.empty())
                      break;

                    char op;
                    if (pos==candidate.npos)
                      op=0;
                    else
                      op=candidate[pos];
                    int exponent=1;
                    if (op==pow)
                      {
                        ++pos;
                        std::size_t npos=0;
                        if (pos>=candidate.size())
                          {
                            validformat=false;
                            break;
                          }
                        try
                        {
                          exponent=std::stoi(candidate.substr(pos),&npos);
                        }
                        catch (std::exception& e)
                        {
                          validformat=false;
                          break;
                        }
                        pos+=npos;
                        while (pos<candidate.size()-1&&candidate[pos]==' ')
                          ++pos;
                        op=candidate[pos];
                      }
                    if ((op==mult)||
                        (op==div)||
                        (op==0)||
                        (std::string(separator).find(op)!=std::string::npos))
                      {
                        if (out.find(current)!=out.end())
                          {
                            if (op==div)
                              out[current]-=exponent;
                            else
                              out[current]+=exponent;

                          }
                        else
                          {
                            out[current]=exponent;
                          }
                        if ((op!=mult)&&(op!=div))
                          break;
                      }
                    else
                      {
                        validformat=false;
                        break;
                      }
                  }
              }

            if (validformat)
              {
                cursor=final;
                return out;
              }
            else
              {
                cursor=cursor0;
                return std::map<std::string,int>();
              }
          }
      }
  }

  ExpressionProduct &ExpressionProduct::operator+=(const ExpressionProduct &other)
  {
    for (auto t:other.expr_)
      {
        if (expr_.find(t.first)!=expr_.end())
          expr_[t.first]+=t.second;
        else
          expr_[t.first]=t.second;
      }
    return *this;
  }

  ExpressionProduct &ExpressionProduct::operator*=(int n)
  {
    for (auto t:expr_)
      {
        expr_[t.first]*=n;
      }
    return *this;
  }



  bool ExpressionProduct::operator<(const ExpressionProduct &other)const
  {
    auto it=expr_.begin();
    auto itOther=other.expr_.begin();
    while ((it!=expr_.end())&&
           (itOther!=other.expr_.end())&&
           (it->first==itOther->first)&&
           (it->second==itOther->second))
      {
        ++it;
        ++itOther;
      }
    if (it!=expr_.end()&&itOther!=other.expr_.end())
      {
        if (it->first!=itOther->first)
          return it->first<itOther->first;
        else
          return it->second<itOther->second;
      }

    else if ((itOther!=other.expr_.end()))
      return true;
    else
      return false;
  }


  ExpressionProduct *ExpressionProduct::create() const
  {
    return new ExpressionProduct;
  }


  std::string ExpressionProduct::ToString() const
  {
    std::string o;
    auto m0=expr_.begin();
    for (auto m=m0;m!=expr_.end();++m)
      {
        if (m!=m0)
          o+=mult;
        o+=m->first;
        if (m->second==0)
          {
            o+=div+m->first;
          }
        else if (m->second!=1)
          {
            o+=pow+std::to_string(m->second);
          }
      }
    return o;
  }

  ExpressionProduct *ExpressionProduct::CreateObject(const std::string &text, std::size_t &cursor) const
  {
    auto tmp=create();
    auto out=tmp->ToObject(text,cursor);
    if (out==nullptr)
      delete tmp;
    return out;
  }

  ExpressionProduct::ExpressionProduct():
    expr_(){}

  const std::map<std::string, int> &ExpressionProduct::value() const
  {
    return expr_;
  }

   std::map<std::string, int> &ExpressionProduct::value()
  {
    return expr_;
   }

   ExpressionProduct &ExpressionProduct::removeUnitTerms()
   {
     for (auto it=value().begin(); it!=value().end();)
       if (it->second==0)
         {
           value().erase(it++);
         }
       else
         ++it;
     return *this;
   }

   ExpressionProduct::ExpressionProduct(std::map<std::string, int> expression):
     expr_(expression){}

   ExpressionProduct::ExpressionProduct(std::string exp)
     : expr_(getDefinition(exp)){}


   ExpressionProduct*  ExpressionProduct::
   ToObject(const std::string &text, std::size_t &cursor)
  {
    auto def=getDefinition(text,cursor);
    if (def.find("")!=def.end())
      return nullptr;
    expr_=def;
    return this;
  }

  bool ExpressionProduct::empty() const
  {
    return expr_.empty();
  }


  std::string ExpressionProduct::myClass() const
  {
    return ClassName();
  }

  std::set<std::string> ExpressionProduct::mySuperClasses() const
  {
    return SuperClasses();
  }

  std::set<std::string> ExpressionProduct::SuperClasses()
  {
    auto out=Abstract_Object::SuperClasses();
    out.insert(ClassName());
    return out;
  }



  std::string ExpressionProduct::ClassName()
  {
    return "ExpressionProduct";
  }

  ExpressionProduct operator*(const ExpressionProduct &one, int n)
  {
    ExpressionProduct out(one);
    return out*=n;
  }

  ExpressionProduct operator+(const ExpressionProduct &one, const ExpressionProduct &other)
  {
    ExpressionProduct out(one);
    return out+=other;
  }





}

