#ifndef EXPRESSIONMANAGER
#define EXPRESSIONMANAGER


#include "Markov_Console/MacorCoreApplication.h"
#include "Markov_IO/ABC_Var.h"

#include "Markov_Console/CommandHistory.h"
#include "Markov_IO/ABC_IO.h"
#include "Markov_IO/buildByToken.h"



namespace Markov_Console {





class Markov_CommandManagerVar;

  class ExpressionManager
  {
  public:

    ExpressionManager(Markov_CommandManagerVar *cm);



    virtual void KeyEvent(Markov_IO::Key k);


    bool push_back(char c);
    bool push_back(Markov_IO::Token_New t);

    char pop_back_char();
    Markov_IO::Token_New pop_back_Token();


    bool isEmpty()const
    {
      return bu_.isInitial();
    }
    bool isFinal()const
    {
      return bu_.isFinal();
    }

  protected:

    // talking with internal representations: token and frame around var


    std::string currentLine();



    // talking with the interfase
    void move_cursor(int i);

    void erase_from_cursor(int i);

    void appendText(const std::string& s);
    void insertText(const std::string& s);

    void appendText(char c);

    void insertText(char c);


    void appendErrorText(const std::string& s);
    void insertErrorText(const std::string& s);

    void appendErrorText(char c)
    {
      std::string s;
      s.push_back(c);
      appendErrorText(s);
    }

    void insertErrorText(char c);



    // processing input from interfase
    void move_Left();
    void backErase();


    void move_Right();
    void move_Home();
    void history_up();

    void history_down();
    void suggestCompletion();
    void putReturn();

    void putText(char s);
    void cleanFromCursor();
    bool check();


    // talking with command manager
    void processVar();


    //talking with history
    std::string getHistoryUp(const std::string& line)const;
    std::string getHistoryDown(const std::string& line)const;





    //bool putSpace();









  private:
    Markov_IO::build_ABC_Value  bu_;
    Markov_IO::Token_New tok_;
    std::string str_;
    Markov_IO::Key previous_key={};
    Markov_CommandManagerVar *cm_;
  };



}
#endif // EXPRESSIONMANAGER

