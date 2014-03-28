#include "Markov_Object/Unit_System.h"


namespace Markov_Object {

  std::string Unit_System::ClassName()
  {
    return "Unit_System";
  }


  std::set<std::string> Unit_System::SuperClasses()
  {
    auto mySC=Abstract_Named_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;

  }

  std::set<std::string> Unit_System::mySuperClasses() const
  {
    return SuperClasses();
  }

  std::string Unit_System::myClass() const
  {
    return ClassName();
  }

  bool Unit_System::empty() const
  {
    return Abstract_Named_Object::empty() &&
        stdQ_.empty() &&
        q2Us_.empty();
  }


  Unit_System *Unit_System::create() const
  {
    return new Unit_System;
  }

  std::string Unit_System::ToString() const
  {
    if (Abstract_Named_Object::idName().empty())
      return "";
    else
      {
        std::string o=ClassName()+" "+ Abstract_Named_Object::ToString();
        o+="Standard Quantities\n";
        for (auto q:stdQuantities())
          o+=q+"  ";
        o+="\n";
        for (auto qu:q2Us_)
          {
            o+=qu.first+"    ";
            for (auto u:qu.second)
              o+=u+"  ";
            o+="\n";

          }
        return o;
      }
  }

  Unit_System *Unit_System::CreateObject(const std::string &text, std::size_t &cursor) const
  {
    auto tmp=create();
    auto out=tmp->ToObject(text,cursor);
    if (out==nullptr)
      delete tmp;
    return out;
  }

  std::string Unit_System::stdUnit(const std::string &idQuantity) const
  {
    auto s=q2Us_.find(idQuantity);
    if (s!=q2Us_.end())
      return s->second[0];
    else
      return {};
  }

  std::vector<std::string> Unit_System::unitList(const std::string &idQuantity) const
  {
    auto s=q2Us_.find(idQuantity);
    if (s!=q2Us_.end())
      return s->second;
    else
      return {};
  }

  bool Unit_System::isStdQuantity(const std::string idQuantity) const
  {
    return stdQ_.find(idQuantity)!=stdQ_.end();
  }

  std::set<std::string> Unit_System::stdQuantities() const
  {
    return stdQ_;
  }

  std::set<std::string> Unit_System::quantities() const
  {
    std::set<std::string> out;
    for (auto q:q2Us_)
      out.insert(q.first);
    return out;

  }

  std::set<std::string> Unit_System::referencedObjects() const
  {
    std::set<std::string> out;
    for (auto q:q2Us_)
      {
        out.insert(q.first);
        for (auto u:q.second)
          out.insert(u);
      }
    return out;


  }

  Unit_System::Unit_System():
    Abstract_Named_Object(),
    stdQ_(),
    q2Us_()
  {}

  Unit_System::Unit_System(Environment *e, const std::string &name, const std::set<std::string> &stdQuantities, const std::map<std::string, std::vector<std::string> > &quantity2Units)
    :
      Abstract_Named_Object(e,name,"",""),
      stdQ_(stdQuantities),
      q2Us_(quantity2Units){}

  Unit_System *Unit_System::ToObject(const std::string &text, std::size_t &cursor)
  {
    std::size_t cursor0=cursor;
    IdentifierName::skipSpaces(text,cursor);
    auto clsnms=ClassName().size();

    // it should have the classname
    if ((!text.empty())&&(text.substr(cursor,clsnms)==ClassName()))
      {
        cursor+=clsnms;
        if (Abstract_Named_Object::ToObject(text,cursor))
          {
            std::string line=Abstract_Named_Object::nextLine(text,cursor);
            if (line=="Standard Quantities")
              {
                std::string stdLine=nextLine(text,cursor);
                std::set<std::string> stq=IdentifierName::getSet(stdLine);
                if (!stq.empty())
                  this->stdQ_=stq;
                else
                  return nullptr;
              }
            else
              return nullptr;
            std::map<std::string,std::vector<std::string>> q2u;
            line=Abstract_Named_Object::nextLine(text,cursor);
            while (!line.empty())
              {
                std::size_t pos=0;
                std::string q=IdentifierName::get(line,pos);
                if (!q.empty())
                  {
                    std::vector<std::string> u=IdentifierName::getVector(line,pos);
                    if (!u.empty())
                      q2u[q]=u;
                    else
                      break;

                  }
                else
                  break;
                line=nextLine(text,cursor);
              }
            if (!q2u.empty())
              {
                this->q2Us_=q2u;
                return this;
              }
            else
              return nullptr;

          }
      }
    cursor=cursor0;
    return nullptr;

  }





}
