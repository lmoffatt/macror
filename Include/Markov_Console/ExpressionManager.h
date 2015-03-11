#ifndef EXPRESSIONMANAGER
#define EXPRESSIONMANAGER


#include "Markov_Console/MacorCoreApplication.h"
#include"Markov_Console/Markov_CommandManager.h"
#include "Markov_IO/ABC_Var.h"

#include "Markov_Console/CommandHistory.h"
#include "Markov_IO/ABC_IO.h"




namespace Markov_Console {



class ExpressionManager
{
public:

  ExpressionManager(CommandHistory const *h,
  Markov_CommandManager *cm,
  Markov_IO::ABC_IO* io):
    b_{},currWord_{},p_(0),previous_key(),h_(h),cm_(cm),io_(io)
  {}


  const Markov_IO::Token_New& at(std::size_t i) const
  {
    return b_.getToken()[i];
  }

  Markov_IO::Token_Buffer& tokens()
  {
    return b_;
  }

  const Markov_IO::Token_Buffer& tokens()const
  {
    return b_;
  }

  Markov_IO::Token_New& at(std::size_t i)
  {
    return b_.getToken()[i];
  }

  virtual void KeyEvent(Markov_IO::Key k);



protected:
  void move_Left();

  void backErase();


  void move_Right();
  void move_Home();

  std::string currentLine();

  void history_up();

  void history_down();
  void suggestCompletion();

  bool putSpace();




  bool putReturn();


  bool putText(std::string s);


private:
  /// Internals
  /// b_+currWord_ p_ is a
  Markov_IO::Token_Buffer b_;
  std::string currWord_;  // not added to b_
  std::size_t p_;  // position of cursor on currWord_
  Markov_IO::Key previous_key;
  CommandHistory const *h_;
  Markov_CommandManager *cm_;
  Markov_IO::ABC_IO* io_;
public:

};

}
#endif // EXPRESSIONMANAGER

