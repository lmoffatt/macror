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



    virtual void KeyEvent(Markov_CommandManagerVar *cm,Markov_IO::ABC_IO * io, CommandHistory& ch, Markov_IO::Key k);

  protected:

    bool push_back(Markov_IO::ABC_IO *io, char c);
    bool push_back(Markov_IO::ABC_IO * io, const std::string& s);

    char pop_back_char();


    bool isEmpty()const;
    bool isFinal()const;


    // talking with internal representations: token and frame around var

    static std::string suggestRest(const std::set<std::string>& items, Markov_IO::Token_New tok);
    static std::set<std::string> conformant(const std::set<std::string>& ids,Markov_IO::Token_New tok);




    // talking with the interfase





    void showErrorMessage(const std::string& s);

    void showSuggestionMessage(const std::string& s);


    // processing input from interfase
    void move_Left(Markov_IO::ABC_IO *io);
    void backErase(Markov_IO::ABC_IO *io);


    void move_Right(Markov_IO::ABC_IO * io);
    void move_Home(Markov_IO::ABC_IO * io);
    void history_up( CommandHistory* ch,Markov_IO::ABC_IO * io);

    void history_down( CommandHistory *ch, Markov_IO::ABC_IO *io);
    void suggestCompletion(Markov_CommandManagerVar *cm, Markov_IO::ABC_IO * io);
    void suggestAlternatives(Markov_CommandManagerVar *cm, Markov_IO::ABC_IO * io);


    void putReturn(Markov_CommandManagerVar *cm,Markov_IO::ABC_IO * io);

    void putText(Markov_IO::ABC_IO * io, char s);
    void cleanFromCursor(Markov_IO::ABC_IO * io);
    bool check();




    //talking with history
    std::string getHistoryUp(const CommandHistory* ch,const std::string& line)const;
    std::string getHistoryDown(const CommandHistory *ch, const std::string& line)const;





    //bool putSpace();









  private:
    Markov_IO::build_Statement  bu_;
    Markov_IO::Token_New tok_;
    Markov_IO::Key previous_key={};
    std::string rejectedChars_;
     // Markov_CommandManagerVar *cm_;

  };



}
#endif // EXPRESSIONMANAGER

