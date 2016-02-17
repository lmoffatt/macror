#include "Markov_Console/ExpressionManager.h"
#include"Markov_Console/Markov_CommandManager.h"


namespace Markov_Console {


  void ExpressionManager::move_Left(Markov_IO::ABC_IO * io)
  {
    if (!io->isLineBegin())
      {
        pop_back_char();
        io->move_cursor(-1);
      }
  }

  void ExpressionManager::move_Right(Markov_CommandManagerVar *cm,Markov_IO::ABC_IO * io)
  {
    if (!io->isLineEnd())
      {
        char c=io->pop_next_char();
        push_back(cm,io,c);
      }
  }


  void ExpressionManager::backErase(Markov_IO::ABC_IO * io)
  {
    if (!io->isLineBegin())
      {
        pop_back_char();
        io->backErase();
      }
  }  // else "beep?"



  void ExpressionManager::move_Home(Markov_IO::ABC_IO * io)
  {
    if (!bu_.isInitial()||!tok_.isInitial())
      {
        while ((tok_.tok()!=Markov_IO::Token_New::EOL)&&(!bu_.isInitial()))
          {
            tok_=bu_.popBackToken();
          }

      }
    io->move_home();
  }



  void ExpressionManager::showErrorMessage(const std::__cxx11::string &s)
  {

  }

  void ExpressionManager::showSuggestionMessage(const std::__cxx11::string &s)
  {

  }

  void ExpressionManager::history_up( CommandHistory* ch,Markov_IO::ABC_IO * io)
  {
    std::string line=io->currentLine();
    std::string tail=ch->up(line);
    io->putTail(tail);
  }

  void ExpressionManager::history_down( CommandHistory* ch,Markov_IO::ABC_IO * io)
  {
    std::string line=io->currentLine();
    std::string tail=ch->down(line);
    io->putTail(tail);
  }


  void ExpressionManager::suggestCompletion(Markov_Console::Markov_CommandManagerVar* cm,Markov_IO::ABC_IO * io)
  {
    auto n=bu_.alternativesNext(cm);
    std::string s=this->suggestRest(n.second,tok_);
    if (!s.empty())
      {
        push_back(cm,io,s);
      }

  }

  void ExpressionManager::suggestAlternatives(Markov_CommandManagerVar *cm, Markov_IO::ABC_IO * io)
  {
    std::pair<std::string,std::set<std::string>> pos;
    if (tok_.isInitial())
      {
        pos=bu_.alternativesNext(cm);
      }
    else{
        auto n=bu_.alternativesNext(cm);

        pos={n.first,conformant(n.second,tok_)};
      }
    if (!pos.second.empty())
      {
        bool ok;
        auto sel=io->getItemFromList(pos.first,{pos.second.begin(),pos.second.end()},ok,0);
        if (ok)
          push_back(cm,io,sel);
      }

  }



  void ExpressionManager::putReturn(Markov_CommandManagerVar *cm, Markov_IO::ABC_IO * io)
  {

    std::string t=io->getTail();
    io->cleanToEndLine();
    push_back(cm,io,t);
    push_back(cm,io,'\n');
    if (bu_.isFinal())
      {
        if (bu_.isCommand())
          {
            auto cmd=bu_.unloadCommand();
            cm->run(cmd);
          }
        else
          {
            cm->add_var(bu_.unloadVar());
          }
        bu_.clear();
        io->freshLine();

      }
    else if (!bu_.errorMessage().empty())
      {
        io->putNewLine();
        io->putError(bu_.errorMessage());
      }
    tok_.clear();
    rejectedChars_.clear();
  }


  bool ExpressionManager::check()
  {
  }




  void ExpressionManager::putText(Markov_CommandManagerVar *cm,Markov_IO::ABC_IO *io,char c)       // here lies the core of the logic
  {
    push_back(cm,io,c);

  }






  ExpressionManager::ExpressionManager(Markov_CommandManagerVar *cm):
    bu_(cm),tok_{},previous_key(),rejectedChars_()
  {}

  void ExpressionManager::KeyEvent(Markov_CommandManagerVar *cm, Markov_IO::ABC_IO * io, CommandHistory& ch, Markov_IO::Key k)
  {
    switch(k)
      {
      case Markov_IO::Key_Home:
        move_Home(io);
        break;
      case Markov_IO::Key_Left:
        move_Left(io);
        break;
      case Markov_IO::Key_Backspace:
        backErase(io);
        break;
      case Markov_IO::Key_Right:
        move_Right(cm,io);
        break;
      case Markov_IO::Key_Up:
        history_up(&ch,io);
        break;
      case Markov_IO::Key_Down:
        history_down(&ch,io);
        break;

      case Markov_IO::Key_Tab:
        if (previous_key!=Markov_IO::Key_Tab)
          suggestCompletion(cm,io);
        else
          suggestAlternatives(cm,io);
        break;
      case Markov_IO::Key_PageUp:
      case Markov_IO::Key_PageDown:
        break;
      case Markov_IO::Key_Space:
        putText(cm,io,' ');
        break;
      case Markov_IO::Key_Return:
        putReturn(cm,io);
        break;
      default:
        if (Markov_IO::isText(k))
          putText(cm,io,Markov_IO::toText(k));
        break;
      }
    previous_key=k;
  }

  bool ExpressionManager::push_back(Markov_CommandManagerVar* cm,Markov_IO::ABC_IO * io,char c)
  {
    if (!rejectedChars_.empty())
      {
        rejectedChars_.push_back(c);
        io->putError(c);
        return false;
      }
    else if ((!tok_.CharIsSuccesfullyFeed(c)))  // either token is full or char is invalid
      {
        if (tok_.isFinal())                  // token is full
          //(but char remains to be processed)
          {
            if(!bu_.pushToken(cm,tok_))           //  does the var reject the token ?
              {
                rejectedChars_=tok_.str();
                tok_.clear();
                io->erase_from_cursor_backward(rejectedChars_);
                if (c!='\n')
                  {
                    rejectedChars_.push_back(c);
                    // write error, wrong token as tail
                  }
                io->putError(rejectedChars_);
                return false;
              }
            else
              {
                tok_.clear();
                if (!tok_.CharIsSuccesfullyFeed(c))     // this means it is an invalid char
                  // an empty token always accept
                  //a valid chars
                  {
                    io->putError(c);
                    rejectedChars_.push_back(c);
                    return false;
                    //    io->putError(c);
                  }
                else if (tok_.isFinal())              // char is accepted,
                  //is the token full?
                  {
                    if(!bu_.pushToken(cm,tok_))          // is the full token rejected  ?
                      {
                        tok_.clear();
                        io->putError(c);
                        rejectedChars_.push_back(c);

                        return false;
                        //  io->putError(c);  // write error, wrong token as tail
                      }
                    else                               // token accepted
                      {
                        io->put(c);
                        tok_.clear();
                        return true;
                      }
                  }
                else                // token is partial
                  {
                    io->put(c);
                    return true;
                  }
              }
          }

        else                  // the given char is invalid, the token is still being filled
          {
            rejectedChars_.push_back(c);
            io->putError(c);
            return false;

          }
      }
    else                                // char is incorporated into token
      if (tok_.isFinal())                 // is the token full?
        {
          if(!bu_.pushToken(cm,tok_))           //  does the var reject the token ?
            {
              tok_.popLastChar();
              rejectedChars_=tok_.str();
              io->erase_from_cursor_backward(rejectedChars_);
              rejectedChars_.push_back(c);
              io->putError(rejectedChars_);         // write error, wrong token as tail
              tok_.clear();
              return false;

            }
          else                                  // the token is good
            {
              tok_.clear();
              if (c!='\n')
                io->put(c);                    // print new char
              return true;

            }
        }
      else                   // token is partial
        {
          io->put(c);
          return true;
        }

  }

  bool ExpressionManager::push_back(Markov_CommandManagerVar *cm,Markov_IO::ABC_IO * io, const std::__cxx11::string &s)
  {
    bool result=true;
    for (auto c:s)
      result=push_back(cm,io,c);
    return result;

  }

  char ExpressionManager::pop_back_char()
  {
    if (isEmpty())
      return {};
    else if (!rejectedChars_.empty())
      {
        char r=rejectedChars_.back();
        rejectedChars_.pop_back();
        return r;
      }
    else if (!tok_.isInitial())
      return tok_.popLastChar();
    else
      {
        tok_=bu_.popBackToken();
        return tok_.popLastChar();
      }

  }

  bool ExpressionManager::isEmpty() const
  {
    return bu_.isInitial()&&tok_.isInitial()&&rejectedChars_.empty();
  }

  bool ExpressionManager::isFinal() const
  {
    return bu_.isFinal();
  }

  std::string ExpressionManager::suggestRest(const std::set<std::string> &items, Markov_IO::Token_New tok)
  {

    std::string hint=tok.str();
    std::size_t nh=hint.size();
    auto lo=items.lower_bound(hint);
    std::string hintup=hint;
    hintup.back()++;
    auto up=items.upper_bound(hintup);
    while ((lo==up)&& !hint.empty())
      {
        hint.pop_back();
        lo=items.lower_bound(hint);
        hintup=hint;
        hintup.back()++;
        items.upper_bound(hintup);

      }
    if (lo==up)
      return {};
    else
      {
        --up;

        if (lo==up)
          {
            std::string out=*lo;
            if (hint.size()==nh)
              out.push_back(' ');
            return out.substr(hint.size());

          }
        else
          {
            std::string los=*lo;
            std::string ups=*up;
            std::size_t i=0;
            std::size_t n=std::min(los.size(), ups.size());
            while((i<n) &&(los[i]==ups[i])) ++i;
            std::string out=los.substr(0,n);
            return out;
          }

      }
  }

  std::set<std::__cxx11::string> ExpressionManager::conformant(const std::set<std::__cxx11::string> &items, Markov_IO::Token_New tok)
  {
    std::string hint=tok.str();
    auto lo=items.lower_bound(hint);
    std::string hintup=hint;
    hintup.back()++;
    auto up=items.upper_bound(hintup);

    return {lo,up};
  }



}






