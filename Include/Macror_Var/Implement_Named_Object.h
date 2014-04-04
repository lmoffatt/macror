#ifndef IMPLEMENT_NAMED_OBJECT_H
#define IMPLEMENT_NAMED_OBJECT_H
#include "Abstract_Named_Object.h"

namespace Macror_Var {
  class Implement_Named_Object : public Abstract_Named_Object
  {
  public:


    // static helper methods
      static std::string getTip(const std::string& multiplelines, std::size_t& pos);
      static std::string getWhatThis(const std::string& multiplelines,std::size_t& pos);

      static std::string getTip(const std::string& multiplelines);
      static std::string getWhatThis(const std::string& multiplelines);


      static std::string nextLine(const std::string& lines,std::size_t& n);
      static std::string removeInitialSpaces(const std::string& line);



    Implement_Named_Object(const Implement_Named_Object &other);


    std::string idName() const;
    std::string Tip() const;
    std::string WhatThis() const;
    void setTip(const std::string &newTip);
    void setWhatThis(const std::string &whatthis);
    std::string ToString() const;


    Implement_Named_Object(Environment *e, std::string variablename, std::string tip, std::string whatthis);


    Implement_Named_Object();
  protected:
    Implement_Named_Object *ToObject(const std::string &text, std::size_t &cursor);

  private:
   std::string   variableName_;
   std::string tip_;
   std::string whatThis_;


  };

}


#endif // IMPLEMENT_NAMED_OBJECT_H
