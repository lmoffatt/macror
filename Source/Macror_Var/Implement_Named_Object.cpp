#include "Macror_Var/Implement_Named_Object.h"
#include "Macror_Var/Measurement_Unit.h"

#include "Macror_Var/Environment.h"
#include "Macror_Var/IdentifierName.h"

namespace  Macror_Var {


  Implement_Named_Object::Implement_Named_Object(const Implement_Named_Object &other):
    Abstract_Refers_Environment(other.getEnvironment()),
    variableName_(other.variableName_),
    tip_(other.tip_),
    whatThis_(other.whatThis_){}

  std::string Implement_Named_Object::idName()const
  {
    return variableName_;
  }

  /// hint about of the class nature
  std::string Implement_Named_Object::Tip()const
  {
    return tip_;
  }

  /// a short description of the class
  std::string Implement_Named_Object::WhatThis()const
  {
    return whatThis_;
  }

  void Implement_Named_Object::setTip(const std::string &newTip){
    tip_=newTip;
  }

  void Implement_Named_Object::setWhatThis(const std::string& whatthis)
  {
    whatThis_=whatthis;

  }


  std::string Implement_Named_Object::ToString()const
  {
    std::string out;
    if (!idName().empty())
      {
        out+=idName();
        if (!Tip().empty())
          {
            out+="//";
            out+=Tip();
          }
        if(!WhatThis().empty())
          {
            out+="\n";
            std::string whathis=WhatThis();
            std::size_t wpos=0;
            std::string wline=nextLine(whathis,wpos);
            out+="//"+wline;

            while (wpos!=std::string::npos)
              {
                wline=nextLine(whathis,wpos);
                out+="//"+wline;
              }

          }
        out+="\n";
      }
    return out;
  }



  Implement_Named_Object*
  Implement_Named_Object::ToObject(const std::string& text, std::size_t& cursor)
  {
    std::size_t c0=cursor;
    std::string name=IdentifierName::get(text,cursor);
    std::string tip=getTip(text,cursor);
    std::string whatthis=getWhatThis(text,cursor);
    if (name.empty()&&tip.empty()&&whatthis.empty())
      {
        cursor=c0;
        return nullptr;
      }


    if (!name.empty())
      {
        variableName_=name;
        if (!tip.empty())
          setTip(tip);
        if(!whatthis.empty())
          setWhatThis(whatthis);
        return this;
      }
    else
      return nullptr;
  }




  Implement_Named_Object::Implement_Named_Object(Environment*  e,
                                               std::string variablename,
                                               std::string tip,
                                               std::string whatthis)
    :
      Abstract_Refers_Environment(e),
      variableName_{variablename},tip_{tip},whatThis_{whatthis}

  {
  }


   Implement_Named_Object::Implement_Named_Object()
    :
      Abstract_Refers_Environment(),
      variableName_{},
      tip_{},
      whatThis_{}{}





  std::string Implement_Named_Object::getTip(const std::string& multiplelines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    std::size_t i=multiplelines.find("//",pos);
    std::size_t endline=multiplelines.find_first_of("\r\n",pos);
    pos=multiplelines.find_first_of("\n",pos);
    if (i<endline)
      {
        if (pos!=std::string::npos) pos++;
        std::string tip=multiplelines.substr(i+2,endline-i-2);
        return tip;
      }
    else
      {
        pos=pos0;

        return "";
      }
  }

  std::string Implement_Named_Object::removeInitialSpaces(const std::string& line)
  {
    auto n=line.find_first_not_of(" \t");
    if (n==line.npos)
      return "";
    else
      return line.substr(n);
  }





  std::string Implement_Named_Object::getTip(const std::string &multiplelines)
  {
    std::size_t n=0;
    return getTip(multiplelines,n);
  }

  std::string Implement_Named_Object::getWhatThis(const std::string &multiplelines)
  {
    std::size_t n=0;
    return getWhatThis(multiplelines,n);
  }

  std::string Implement_Named_Object::nextLine(const std::string &lines, std::size_t &n)
  {
    std::size_t n0=n;
    std::size_t nlast=lines.find_first_of("\r\n",n0);
    n=lines.find_first_of("\n",n0);
    if (n!=std::string::npos) n++;
    return lines.substr(n0,nlast-n0);
  }

  std::string Implement_Named_Object::getWhatThis(const std::string& multiplelines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    std::string whatthis;
    while(pos!=std::string::npos)
      {
        std::string line=nextLine(multiplelines,pos);
        line=removeInitialSpaces(line);
        if (line.find("//")!=0)
          break;
        whatthis+=line.substr(2);
        pos0=pos;
      }
    pos=pos0;
    return whatthis;
  }





}

