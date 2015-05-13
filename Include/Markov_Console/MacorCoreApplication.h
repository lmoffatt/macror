#ifndef MACORCOREAPPLICATION
#define MACORCOREAPPLICATION

#include "Markov_IO/ABC_Var.h"

#include "Markov_Console/CommandHistory.h"
#include "Markov_CommandManager.h"
#include "Markov_IO/ABC_IO.h"

//#include "Markov_GUI/MyInputDialog.h"

//#include <QCoreApplication>
//#include <QKeyEvent>

#include <string>
#include <vector>



namespace  Markov_Console {

  class ExpressionManager;

  class MacrorKeyEvent
  {
  public:
    explicit MacrorKeyEvent(Markov_IO::Key key);



    MacrorKeyEvent(const MacrorKeyEvent &other);
    virtual ~MacrorKeyEvent();
    MacrorKeyEvent &operator=(const MacrorKeyEvent &other);
    inline Markov_IO::Key key() const { return static_cast<Markov_IO::Key>(k); }

    inline std::string text()const
    {
      return {static_cast<char>(k)};
    }
    //    inline bool spontaneous() const { return spont; }

    //    inline void setAccepted(bool accepted) { m_accept = accepted; }
    //    inline bool isAccepted() const { return m_accept; }

    //    inline void accept() { m_accept = true; }
    //    inline void ignore() { m_accept = false; }

  protected:
    int k;

  };





  class CommandManager: public Markov_IO::ABC_Value
  {
    CommandHistory *h;
  public:
    CommandManager();
    virtual ~CommandManager();

    // self reference

    std::string buildVersion()const;
    std::string buildDate()const;
    std::string uncommitedFiles()const;

    virtual std::string version()const;
    virtual std::string wellcomeMessage(unsigned ncols=80)const;



    virtual CommandHistory& getH(){return *h;}


    virtual std::string check(const ExpressionManager& e);

    virtual  std::vector<std::string> complete(const ExpressionManager& e);




    //execuete line
    virtual bool runLine(std::string commandLine);



    virtual void printErrorMessage(const std::string& errorMessage);





  };




 }





#endif // MACORCOREAPPLICATION

