#include "Markov_Console/ExpressionManager.h"
#include"Markov_Console/Markov_CommandManager.h"


namespace Markov_Console {


  void ExpressionManager::move_Left()
  {
    if (!isEmpty())
      {
        char c=pop_back_char();
        str_.insert(str_.begin(),c);
        move_cursor(-1);
      }
  }

  void ExpressionManager::move_Right()
  {
    if (!str_.empty())
      {
        char c=str_.front();
        str_.erase(0,1);
        push_back(c);
      }
  }


  void ExpressionManager::backErase()
  {
    cleanFromCursor();
    pop_back_char();
    erase_from_cursor(-1);

  }  // else "beep?"



  void ExpressionManager::move_Home()
  {
    if (!isEmpty())
      {
        int n0=str_.size();
        while ((tok_.tok()!=Markov_IO::Token_New::EOL)&&(!bu_.isInitial()))
          {
            str_.insert(0,tok_.str());
            tok_=bu_.popBackToken();
          }
        move_cursor(-(str_.size())+n0);
      }
  }

  std::string ExpressionManager::currentLine()
  {
    std::string line;
    std::vector<Markov_IO::Token_New> tv;
    Markov_IO::Token_New to=tok_;
    if (!isEmpty())
      {
        while ((to.tok()!=Markov_IO::Token_New::EOL)&&(!bu_.isInitial()))
          {
            line.insert(0,to.str());
            to=bu_.popBackToken();
            tv.push_back(to);
          }
        for (int i=tv.size(); i>0; --i)
          {
            bu_.pushToken(tv[i-1]);
          }
      }
    return line;
  }

  void ExpressionManager::move_cursor(int i)
  {
    return cm_->getIO()->move_cursor(i);
  }

  void ExpressionManager::erase_from_cursor(int i)
  {
    return cm_->getIO()->erase_from_cursor(i);
  }


  void ExpressionManager::appendText(const std::string &s)
  {
    cm_->getIO()->put(s);

  }

  void ExpressionManager::insertText(const std::string &s)
  {
    if (str_.empty())
      {
        str_=s;
      }
    else
      {
        erase_from_cursor(str_.size());
        str_.insert(0,s);
      }
    cm_->getIO()->insertText(s);

  }

  void ExpressionManager::appendText(char c)
  {
    std::string s;
    s.push_back(c);
    appendText(s);
  }

  void ExpressionManager::insertText(char c)
  {
    std::string s;
    s.push_back(c);
    insertText(s);
  }

  void ExpressionManager::insertErrorText(const std::string &s)
  {
    if (str_.empty())
      {
        str_=s;
      }
    else
      {
        erase_from_cursor(str_.size());
        str_.insert(0,s);
      }
    cm_->getIO()->insertErrorText(s);

  }

  void ExpressionManager::insertErrorText(char c)
  {
    std::string s;
    s.push_back(c);
    insertErrorText(s);
  }

  void ExpressionManager::history_up()
  {
    std::string line=currentLine();
    cleanFromCursor();
    std::string tail=getHistoryUp(line);
    insertText(tail);
    str_=tail;
  }

  void ExpressionManager::history_down()
  {
    std::string line=currentLine();
    cleanFromCursor();
    std::string tail=getHistoryDown(line);
    insertText(tail);
    str_=tail;
  }

  void ExpressionManager::cleanFromCursor()
  {
    std::size_t n=str_.size();
    str_.clear();
    erase_from_cursor(n);
  }


  void ExpressionManager::suggestCompletion()
  {
  }



  void ExpressionManager::putReturn()
  {
    putText('\n');
  }


  bool ExpressionManager::check()
  {
  }

  void ExpressionManager::processVar()
  {
    if (bu_.isFinal())
      cm_->add_var(bu_.unloadVar());
  }

  std::string ExpressionManager::getHistoryUp(const std::string &line) const
  {
    return cm_->getH().up(line);
  }

  std::string ExpressionManager::getHistoryDown(const std::string &line) const
  {
    return cm_->getH().down(line);
  }


  void ExpressionManager::putText(char c)       // here lies the core of the logic
  {
    if (!str_.empty())
       cleanFromCursor();
    push_back(c);

  }






  ExpressionManager::ExpressionManager(Markov_CommandManagerVar *cm):
    bu_(cm),tok_{},str_(),previous_key(),cm_(cm)
  {}

  void ExpressionManager::KeyEvent(Markov_IO::Key k)
  {
    switch(k)
      {
      case Markov_IO::Key_Home:
        move_Home();
        break;
      case Markov_IO::Key_Left:
        move_Left();
        break;
      case Markov_IO::Key_Backspace:
        backErase();
        break;
      case Markov_IO::Key_Right:
        move_Right();
        break;
      case Markov_IO::Key_Up:
        history_up();
        break;
      case Markov_IO::Key_Down:
        history_down();
        break;

      case Markov_IO::Key_Tab:
        suggestCompletion();
        break;
      case Markov_IO::Key_PageUp:
      case Markov_IO::Key_PageDown:
        break;
      case Markov_IO::Key_Space:
        putText(' ');
        break;
      case Markov_IO::Key_Return:
        putReturn();
        break;
      default:
        putText(Markov_IO::toText(k));
        break;
      }
    previous_key=k;
  }

  bool ExpressionManager::push_back(char c)
  {
    if ((!tok_.CharIsSuccesfullyFeed(c)))  // either token is full or char is invalid
      {
        if (tok_.isFinal())                  // token is full
          //(but char remains to be processed)
          {
            if(!bu_.pushToken(tok_))           //  does the var reject the token ?
              {
                std::string to=tok_.str();
                int n=-to.size();
                erase_from_cursor(n);
                to.push_back(c);
                insertErrorText(to);         // write error, wrong token as tail
                tok_.clear();
              }
            else
              {
                if (bu_.isFinal())              // var accepts token, is var  complete?
                  {
                    processVar();
                  }
                tok_.clear();
                if (!tok_.CharIsSuccesfullyFeed(c))     // this means it is an invalid char
                  // an empty token always accept
                  //a valid chars
                  {
                    insertErrorText(c);
                  }
                else if (tok_.isFinal())              // char is accepted,
                  //is the token full?
                  {
                    if(!bu_.pushToken(tok_))          // is the full token rejected  ?
                      {
                        insertErrorText(c);  // write error, wrong token as tail
                        tok_.clear();
                      }
                    else                               // token accepted
                      {
                        appendText(c);
                        if (bu_.isFinal())
                          {
                            processVar();
                          }
                      }
                  }
                else                // token is partial
                  {
                    appendText(c);
                  }
              }
          }

        else                  // the given char is invalid, the token is still being filled
          {
            insertErrorText(c);
          }
      }
    else                                // char is incorporated into token
      if (tok_.isFinal())                 // is the token full?
        {
          if(!bu_.pushToken(tok_))           //  does the var reject the token ?
            {
              str_=tok_.str();
              int n=-str_.size()+1;          // +1 because of the incorporated char
              erase_from_cursor(n);
              insertErrorText(str_);         // write error, wrong token as tail
              tok_.clear();
            }
          else                                  // the token is good
            {
              appendText(c);                    // print new char
              if (bu_.isFinal())              // var accepts token, is var  complete?
                {
                  processVar();               // var is complete , execute it
                }

            }
        }
      else                   // token is partial
        {
          appendText(c);
        }

  }

  char ExpressionManager::pop_back_char()
  {
    if (isEmpty())
      return {};
    else  if (!tok_.isInitial())
      return tok_.popLastChar();
    else
      {
        tok_=bu_.popBackToken();
        return tok_.popLastChar();
      }

  }




}


