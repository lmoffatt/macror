#include "Markov_Console/ExpressionManager.h"
#include"Markov_Console/Markov_CommandManager.h"
#include "Markov_Console/CommandHistory.h"

namespace Markov_IO_New {


  void ExpressionManager::move_Left(ABC_IO * io)
  {
    if (!io->isLineBegin())
      {
        std::string s=io->move_cursor(-1);
        pop_back_char();
      }
  }

  void ExpressionManager::move_Right(Markov_CommandManagerVar *cm,ABC_IO * io)
  {
    if (!io->isLineEnd())
      {
        std::string errorMessage;
        char c=io->pop_next_char();
        push_back(cm,io,c,&errorMessage);
      }
  }


  void ExpressionManager::backErase(ABC_IO * io)
  {
    if (!io->isLineBegin())
      {
        char c=io->backErase();
        pop_back_char();
      }
  }  // else "beep?"



  void ExpressionManager::move_Home(ABC_IO * io)
  {
    if (!bu_.isInitial()||!tok_.isInitial())
      {
        while ((tok_.tok()!=Token_New::EOL)&&(!bu_.isInitial()))
          {
            bu_.popBackToken();
            tok_=tokVec_.back();
            tokVec_.pop_back();
          }

      }
    io->move_home();
  }



  void ExpressionManager::history_up( CommandHistory* ch,ABC_IO * io)
  {
    std::string line=io->currentLine();
    std::string tail=ch->up(line);
    io->putTail(tail);
  }

  void ExpressionManager::history_down( CommandHistory* ch,ABC_IO * io)
  {
    std::string line=io->currentLine();
    std::string tail=ch->down(line);
    io->putTail(tail);
  }


  void ExpressionManager:: suggestCompletion(Markov_CommandManagerVar* cm,ABC_IO * io)
  {
    auto n=bu_.alternativesNext();
    std::string s=suggestRest(n.second,tok_);
    if (!s.empty())
      {
        std::string errorMessage;
        push_back(cm,io,s,&errorMessage);
      }

  }

  void ExpressionManager::suggestAlternatives(Markov_CommandManagerVar *cm, ABC_IO * io)
  {
    std::pair<std::string,std::set<std::string>> pos;
    if (tok_.isInitial())
      {
        pos=bu_.alternativesNext();
      }
    else
      {
        auto n=bu_.alternativesNext();
        pos={n.first,conformant(n.second,tok_)};
      }
    if (!pos.second.empty())
      {
        if (pos.second.size()==1)
          {
            auto n=tok_.str().size();
            std::string sel=*pos.second.begin();
            std::string s=removeHint(sel).substr(n);
            bool ok;
            if (s.empty())
              {
                io->getItemFromList(pos.first,{pos.second.begin(),pos.second.end()},ok,0);
              }
            else
              {
                std::string err;
                push_back(cm,io,s,&err);
              }
          }
        else
          {
            bool ok;
            auto sel=io->getItemFromList(pos.first,{pos.second.begin(),pos.second.end()},ok,0);
            std::string err;
            if (ok)
              {
                auto n=tok_.str().size();
                std::string s=removeHint(sel).substr(n);
                push_back(cm,io,s,&err);
              }
          }
      }

  }



  void ExpressionManager::putReturn(Markov_CommandManagerVar *cm, ABC_IO * io)
  {

    std::string t=io->getTail();
    io->cleanToEndLine();
    std::string errorTail;
    if (!push_back(cm,io,t,&errorTail))
      io->showMessage(errorTail);

    if (!push_back(cm,io,'\n',&errorMessage_))
      {
        if (previous_key==Key_Return)
          {
            io->putError(errorTail+errorMessage_);
            clear();
            io->hideMessage();
            io->freshLine();
          }
        else
          io->showMessage(errorTail+errorMessage_);

      }
    else  if (bu_.isFinal())
      {
        if (bu_.isFunction())
          {
            auto cmd=bu_.unloadClosure();
            cmd->evalData(cm);
          }
        else
          {
            cm->pushVar(bu_.unloadVar());
          }
        clear();
        io->freshLine();

      }
  }






  void ExpressionManager::putText(Markov_CommandManagerVar *cm,ABC_IO *io,char c)       // here lies the core of the logic
  {
    io->hideMessage();
    std::string err;
    if (!push_back(cm,io,c,&err))
      io->showMessage(err);


  }






  ExpressionManager::ExpressionManager(Markov_CommandManagerVar *cm):
    bu_(cm,cm->getVarType(),cm->getFnType())
  ,tok_{},tokVec_{},previous_key(),rejectedChars_(),errorMessage_()
  {}

  void ExpressionManager::KeyEvent(Markov_CommandManagerVar *cm
                                   , ABC_IO * io
                                   , CommandHistory& ch
                                   , Key k)
  {
    switch(k)
      {
      case Key_Home:
        move_Home(io);
        break;
      case Key_Left:
        move_Left(io);
        break;
      case Key_Backspace:
        backErase(io);
        break;
      case Key_Right:
        move_Right(cm,io);
        break;
      case Key_Up:

        history_up(&ch,io);
        break;
      case Key_Down:
        history_down(&ch,io);
        break;

      case Key_Tab:
        if (previous_key!=Key_Tab)
          suggestCompletion(cm,io);
        else
          suggestAlternatives(cm,io);
        break;
      case Key_PageUp:
      case Key_PageDown:
        break;
      case Key_Space:
        putText(cm,io,' ');
        break;
      case Key_Return:
        putReturn(cm,io);
        break;
      default:
        if (isText(k))
          putText(cm,io,toText(k));
        break;
      }
    previous_key=k;
  }

  bool ExpressionManager::push_back(Markov_CommandManagerVar* cm, ABC_IO * io, char c,  std::string *error)
  {
    const std::string objective="";

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
            if(!bu_.pushToken(tok_,error,""))           //  does the var reject the token ?
              {
                rejectedChars_=tok_.str();
                tok_.clear();
                io->erase_from_cursor_backward(rejectedChars_);
                rejectedChars_.push_back(c);
                io->putError(rejectedChars_);
                return false;
              }
            else
              {
                tokVec_.push_back(tok_);
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
                    if(!bu_.pushToken(tok_,error,objective))          // is the full token rejected  ?
                      {
                        tok_.clear();
                        io->putError(c);
                        rejectedChars_.push_back(c);

                        return false;
                      }
                    else                               // token accepted
                      {
                        io->put(c);
                        tokVec_.push_back(tok_);
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

        else if ((tok_.tok()==Token_New::EMPTY)&&(c==' '))
          {
            if (tokVec_.back().CharIsSuccesfullyFeed(c))
              {
                io->put(c);
                return true;

              }
            else
              {
                rejectedChars_.push_back(c);
                io->putError(c);
                return false;

              }
          }
        else
          // the given char is invalid, the token is still being filled
          {
            rejectedChars_.push_back(c);
            io->putError(c);
            return false;

          }
      }
    else                                // char is incorporated into token
      if (tok_.isFinal())                 // is the token full?
        {

          if(!bu_.pushToken(tok_,error,objective))           //  does the var reject the token ?
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
              tokVec_.push_back(tok_);
              tok_.clear();

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

  bool ExpressionManager::push_back
  (Markov_CommandManagerVar *cm
   ,ABC_IO * io
   , const std::string &s
   ,std::string* errorMessage)
  {
    bool result=true;
    for (auto c:s)
      result=push_back(cm,io,c,errorMessage);
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
      {
        return tok_.popLastChar();
      }
    else
      {
        bu_.popBackToken();
        if (!tokVec_.empty())
          {
            tok_=tokVec_.back();
            tokVec_.pop_back();
          }
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

  void ExpressionManager::clear()
  {
    bu_.clear();
    errorMessage_.clear();
    previous_key={};
    rejectedChars_.clear();
    tokVec_.clear();
    tok_.clear();

  }

  std::string ExpressionManager::suggestRest(const std::set<std::string> &items, Token_New tok)
  {
    if (items.empty())
      return {};
    else if (tok.str().empty()&&items.size()==1)
      {
        auto s=*items.begin();
        s=removeHint(s);
        return s;
      }
    else
      {
        std::string hint=tok.str();
        std::size_t nh=hint.size();

        auto lo=items.lower_bound(hint);
        std::string hintup=hint;
        if (hintup.empty())
          hintup=*items.rbegin();
        hintup.back()++;
        auto up=items.upper_bound(hintup);
        while ((lo==up)&& !hint.empty())
          {
            hint.pop_back();
            lo=items.lower_bound(hint);
            hintup=hint;
            if (hintup.empty())
              hintup=*items.rbegin();
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
                out=removeHint(out);
                return out.substr(hint.size());

              }
            else
              {
                std::string los=removeHint(*lo);
                std::string ups=removeHint(*up);
                std::size_t i=0;
                std::size_t n=std::min(los.size(), ups.size());
                while((i<n) &&(los[i]==ups[i])) ++i;
                std::string out;
                if(nh<i)
                  out=los.substr(nh,i-nh);
                return out;
              }

          }
      }
  }
  std::set<std::string> ExpressionManager::conformant(const std::set<std::string> &items, Token_New tok)
  {
    std::string hint=tok.str();
    if (hint==" ")
      hint.clear();
    if (hint.empty())
      return items;
    else{
        auto lo=items.lower_bound(hint);
        std::string hintup=hint;
        hintup.back()++;
        auto up=items.upper_bound(hintup);

        return {lo,up};
      }
  }



}








