#ifndef EXPRESSIONMANAGER
#define EXPRESSIONMANAGER


#include "Markov_Console/MacorCoreApplication.h"
#include "Markov_IO/ABC_Var.h"

#include "Markov_Console/CommandHistory.h"
#include "Markov_IO/ABC_IO.h"




namespace Markov_Console {





class Markov_CommandManagerVar;

  class ExpressionManager
  {
  public:

    ExpressionManager(Markov_CommandManagerVar *cm):
      b_{},p_(0),previous_key(),categories_(),cm_(cm),v_(nullptr)
    {}


    const Markov_IO::Token_New& at(std::size_t i) const
    {
      return b_.at(i);
    }



    Markov_IO::Token_Stream tokens()
    {
      return Markov_IO::Token_Stream(b_);
    }

    Markov_IO::Token_New& at(std::size_t i)
    {
      return b_[i];
    }

    virtual void KeyEvent(Markov_IO::Key k);

    void clear();

    void clean();



  protected:
    void move_Left();

    void backErase();


    void move_Right();
    void move_Home();

    std::string currentLine() const;

    void history_up();

    void history_down();
    void suggestCompletion();

    //bool putSpace();




    bool putReturn();


    bool putText(char s);




    friend class ABC_CommandVar;
    void getStringandCleanFromCursor();
    bool check();
  private:
    /// Internals
    /// b_+currWord_ p_ is a
    std::deque<Markov_IO::Token_New>  b_;
    std::string currWord_;
    std::size_t p_;  // position of cursor on the line
    Markov_IO::Key previous_key;
    std::vector<std::vector<std::pair<std::string,bool>>> categories_;
    Markov_CommandManagerVar *cm_;
    Markov_IO::ABC_Value* v_;
  public:

  };



}
#endif // EXPRESSIONMANAGER

