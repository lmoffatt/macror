#include "Markov_Console/ExpressionManager.h"


namespace Markov_Console {

  void ExpressionManager::move_Left()
  {
    if (p_>0)
      {
        --p_;
        io_->move_cursor(-1);
      }
    else if (b_.currToken().tok()!=Markov_IO::Token_New::EOL)
      {
        auto pr=b_.currToken().toString();
        b_.pop_back();
        currWord_.insert(0,pr+" ");
        p_=pr.size();
        --p_;
        io_->move_cursor(-1);
      }
  }

  void ExpressionManager::backErase()
  {
    if (p_>0)
      {
        --p_;
        io_->erase_from_cursor(-1);
        currWord_.erase(p_);
      }
    else if (b_.currToken().tok()!=Markov_IO::Token_New::EOL)
      {
        auto pr=b_.currToken().toString();
        b_.pop_back();
        currWord_.insert(0,pr);
        p_=pr.size();
        --p_;
        io_->erase_from_cursor(-1);
        currWord_.erase(p_);
      }
  }

  void ExpressionManager::move_Right()
  {
    if ((!currWord_.empty())&&(p_<currWord_.size()-1))
      {
        ++p_;
        io_->move_cursor(+1);
      }
  }

  void ExpressionManager::move_Home()
  {
    int n=p_;
    while (b_.currToken().tok()!=Markov_IO::Token_New::EOL)
      {
        auto pr=b_.currToken().toString();
        b_.pop_back();
        currWord_.insert(0,pr);
        n+=pr.size();
      }
    io_->move_cursor(n);
    p_=0;
  }

  std::string ExpressionManager::currentLine()
  {
    std::string buffline=b_.moveStartLine().tailString();
    buffline.append(currWord_.substr(0,p_));
    return buffline;

  }

  void ExpressionManager::history_up()
  {

    std::string line=currentLine();
    io_->erase_from_cursor(currWord_.size()-p_);
    currWord_.erase(p_);
    std::string tail=cm_->getH().up(line);
    io_->put(tail);
    currWord_+=tail;
  }

  void ExpressionManager::history_down()
  {

    std::string line=currentLine();
    io_->erase_from_cursor(currWord_.size()-p_);
    currWord_.erase(p_);
    std::string tail=cm_->getH().down(line);
    io_->put(tail);
    currWord_+=tail;
  }

  void ExpressionManager::suggestCompletion()

  {
    std::vector<std::string> res=cm_->complete(*this);

    currWord_.erase(p_);
    if ((res.size()==1)&&(res.front()[0]!='<')&&(res.front()[0]!='['))
      {
        auto tail=Markov_Console::Autocomplete::suggestedCharacters(
              res,currWord_);
        currWord_+=tail;
        io_->put(tail);
        p_+=tail.size();

      }
    else if(res.size()>0)
      {
        if (previous_key==Markov_IO::Key_Tab)
          {

            auto tail=Markov_Console::Autocomplete::suggestedCharacters(res,currWord_);
            //auto pp=c.position();
            currWord_+=tail;
            io_->put(tail);
            p_+=tail.size();
            std::vector<std::string> list;
            std::string field;
            for (auto item:res)
              {
                if ((item.front()=='<')||(item.front()=='['))
                  field=item.substr(1,item.size()-2);
                else
                  list.push_back(item);
              }
            if (list.size()>0)
              {
                bool ok;
                std::string fieldselect = io_->getItemFromList(currWord_,list,ok,0);
                if (ok && !fieldselect.empty())
                  {
                    auto tail=Markov_Console::Autocomplete::suggestedCharacters({fieldselect},currWord_);
                    currWord_+=tail;
                    io_->put(tail);
                    p_+=tail.size();

                  }
              }
            else
              {
                std::string fields;
                for (std::size_t i=0;i<res.size()-1; i++)
                  {
                    if ((res[i].front()=='<')||(res[i].front()=='['))
                      fields+=res[i]+",";

                  }

                io_->showMessage(field);
              }
          }
      }

  }

  bool ExpressionManager::putSpace()
  {
    currWord_.erase(p_);
    std::string err=cm_->check(*this);
    if (!err.empty())
      {
        io_->showMessage(err);
        return false;

      }
    else
      {
        b_<<currWord_;
        b_.setPosEnd();
        currWord_.clear();
        p_=0;
        return true;
      }

  }

  bool ExpressionManager::putReturn()
  {
    if (!putSpace())
      return false;
    else
      {
        currWord_="\n";
        p_=1;
        if (!putSpace())
          return false;
        else
          {
          cm_->process(*this);
          return true;
          }
      }
  }

  bool ExpressionManager::putText(std::string s)
  {
    currWord_.erase(p_);
    auto old=currWord_;
    currWord_+=s;
    std::string err=cm_->check(*this);
    if (!err.empty())
      {
        currWord_=old;
        io_->showMessage(err);
        return false;

      }
    else
      {
        p_+=s.size();
        return true;
      }
  }

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
        putSpace();
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





















}
