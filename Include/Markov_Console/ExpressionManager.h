#ifndef EXPRESSIONMANAGER
#define EXPRESSIONMANAGER

#include "Markov_IO/ABC_IO.h"
#include "Markov_IO/buildByTokenTempl.h"
#include "Markov_IO/buildClosureByToken.h"
#include "Markov_IO/buildClosureByToken_Templ.h"

namespace Markov_IO_New {


   class Markov_CommandManagerVar;
   class CommandHistory;



  class ExpressionManager
  {
  public:

    ExpressionManager(Markov_CommandManagerVar *cm);



    void KeyEvent(Markov_CommandManagerVar *cm,ABC_IO * io, CommandHistory& ch, Key k);

  protected:

    bool push_back(Markov_CommandManagerVar *cm, ABC_IO *io, char c, std::string *errorMessage);


    bool push_back(Markov_CommandManagerVar *cm, ABC_IO * io, const std::string& s, std::string *errorMessage);

    char pop_back_char();


    bool isEmpty()const;
    bool isFinal()const;

    void clear();


    // talking with internal representations: token and frame around var

    static std::string suggestRest(const std::set<std::string>& items, Token_New tok);
    static std::set<std::string> conformant(const std::set<std::string>& ids,Token_New tok);





    // talking with the interfase








    // processing input from interfase
    void move_Left(ABC_IO *io);
    void backErase(ABC_IO *io);


    void move_Right(Markov_CommandManagerVar *cm, ABC_IO * io);
    void move_Home(ABC_IO * io);
    void history_up( CommandHistory* ch,ABC_IO * io);

    void history_down( CommandHistory *ch, ABC_IO *io);
    void suggestCompletion(Markov_CommandManagerVar *cm, ABC_IO * io);
    void suggestAlternatives(Markov_CommandManagerVar *cm, ABC_IO * io);


    void putReturn(Markov_CommandManagerVar *cm,ABC_IO * io);

    void putText(Markov_CommandManagerVar *cm, ABC_IO * io, char s);






  private:
    build_StatementNew  bu_;
    Token_New tok_;
    std::vector<Token_New> tokVec_;
    Key previous_key={};
    std::string rejectedChars_;
    std::string errorMessage_;
  };



}


#endif // EXPRESSIONMANAGER

