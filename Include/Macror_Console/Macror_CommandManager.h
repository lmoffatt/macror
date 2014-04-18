#ifndef MACROR_COMMANDMANAGER_H
#define MACROR_COMMANDMANAGER_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Macror_Console/KeyEvent.h"
#include "Macror_Console/Command_Line_Manager.h"

namespace Macror_Console {

  class CommandHistory;


  class ABC_IO
  {
  public:
    /// get a string from the input source
    virtual std::string getline()=0;


    /// put a string to the output source
    virtual void put(const std::string&)=0;


    virtual void putError(const std::string& )=0;

    template <typename T>
    void put(const T& x )
    {
      std::stringstream ss;
      ss<<x;
      put(ss.str());
    }


  };
  template <typename T>
  ABC_IO& operator<<(ABC_IO& s,const T& x )
  {
    s.put(x);
    return s;
  }

  class Macror_Command_Manager;




  class Macror_Command_Manager: public Abstract_Handle_Events
  {
  public:


    virtual bool event(Base_Event *e);

    virtual std::vector<std::string> complete(const std::string& hint)const{}

    virtual ABC_IO& myIostream(){}

    virtual CommandHistory* getH(){}

    std::string add_single_token(std::string commandWord){}
    Macror_Command_Manager(std::size_t width=80):
      currentLine_(this),
      ncols_{width}{}

    virtual ~Macror_Command_Manager()
    {
    }

    std::size_t ncols_;

  private:
    Command_Line_Manager currentLine_;



  };




}
#endif // MACROR_COMMANDMANAGER_H
