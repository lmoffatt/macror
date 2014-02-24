#ifndef QUANTITY_H
#define QUANTITY_H
#include <cstring>
#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/Environment.h"

namespace Markov_Object {

  class Quantity;
  struct MagnitudeCompare
  {
    bool operator()(const Quantity* one, const Quantity* two);
  };


  class Quantity: public Abstract_Named_Object
  {
  public:
    static const char pow='^';
    static  const char mult='*';
    static constexpr const char* allowed="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static constexpr const char* numeric="1234567890+-";

    static  std::string legal(){
      return std::string(allowed)+mult+pow+numeric;
    }

    static constexpr const char* separator=" \t\n";

    static
    std::map<std::string,int> getDefinition(const std::string& defs,std::size_t& cursor)
    {
      std::size_t cursor0=cursor;

      std::map<std::string,int> out;
      Abstract_Named_Object::skipSpaces(defs,cursor);

      auto final=defs.find_first_of(separator,cursor);

      std::string candidate=defs.substr(cursor,final-cursor);
      auto nfin=candidate.find_first_not_of(legal());

      bool validformat=!candidate.empty()&&(nfin==candidate.npos);
      std::size_t pos=0;
      if(validformat)
        {
          while (pos<=candidate.size())
            {
              auto start=candidate.find_first_of(allowed,pos);
              pos=candidate.find_first_not_of(allowed,start);

              std::string current=candidate.substr(start,pos-start);
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
              if ((op==mult)||(op==0)||(std::string(separator).find(op)!=std::string::npos))
                {
                  if (out.find(current)!=out.end())
                    {
                      out[current]+=exponent;
                    }
                  else
                    {
                      out[current]=exponent;
                    }
                  if (op!=mult)
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


    static
    std::map<std::string,int> getDefinition(const std::string& defs)
    {
      std::size_t n=0;
      return getDefinition(defs,n);
    }


    static std::string ClassName();

    virtual std::string myClass()const override;

    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses();

    virtual Quantity *create() const;
    virtual std::string ToString() const;

    virtual bool ToObject(Environment *e, const std::string &text, std::size_t &cursor);


    /// checks for the existance of all refered objects
    virtual bool refersToValidObjects()const;

    std::set<std::string> referencedObjects() const;


    virtual bool ToObject(Environment *e, const std::string &text);


    std::map<const Quantity*, int,MagnitudeCompare> definition()const;


    Quantity();

    Quantity(Environment* e);


    Quantity(Environment* e,
             std::string magnitudeAbbreviation,
             std::map<std::string, int> quatityDefinition,
             std::string longName,
             std::string whatthis);

    Quantity(Environment* e,
             std::string magnitudeAbbreviation,
             std::string quatityDefinition,
             std::string longName,
             std::string whatthis);

  private:

    std::map<std::string, int> def_;

  };
}






#endif // QUANTITY_H
