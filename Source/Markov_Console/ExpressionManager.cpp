#include "Markov_Console/ExpressionManager.h"


namespace Markov_Console {



  void ExpressionView::KeyEvent(Markov_IO::Key k)
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


  void ExpressionManager::move_Left()
  {
    if(!b_.empty()&&(b_.back().tok()==Markov_IO::Token_New::EMPTY))
      b_.pop_back();

    if((!b_.empty())&&(b_.back().tok()!=Markov_IO::Token_New::EOL))
      {
        Markov_IO::Token_New &t=b_.back();
        char ch=t.popLastChar();
        currWord_.insert(currWord_.begin(),ch);
        cm_->getIO()->move_cursor(-1);
      }  // else "beep?"

  }


  void ExpressionManager::backErase()
  {
    if(!b_.empty()&&(b_.back().tok()==Markov_IO::Token_New::EMPTY))
      b_.pop_back();

    if((!b_.empty())&&(b_.back().tok()!=Markov_IO::Token_New::EOL))
      {
        cm_->getIO()->erase_from_cursor(currWord_.size());
        currWord_.clear();
        Markov_IO::Token_New &t=b_.back();
        t.popLastChar();
        cm_->getIO()->move_cursor(-1);
      }  // else "beep?"

  }
  void ExpressionManager::move_Right()
  {
    if (!currWord_.empty())
      {
        char c=currWord_.front();
        currWord_.erase(0,1);
        if (b_.empty())
          b_.push_back(Markov_IO::Token_New(c));
        else
          {
            Markov_IO::Token_New &t=b_.back();
            if (!t.CharIsSuccesfullyFeed(c))
              b_.push_back(Markov_IO::Token_New(c));

          }
        cm_->getIO()->move_cursor(1);
      }
  }

  void ExpressionManager::move_Home()
  {
    int n=0;
    if (!b_.empty())
      {
        std::size_t pos=b_.size()-1;
        while (pos>0&&(b_[pos].tok()!=Markov_IO::Token_New::EOL))
          {
            auto pr=b_[pos].str();
            --pos;
            n-=pr.size();
            currWord_.insert(0,pr);
          }

        cm_->getIO()->move_cursor(n);
      }
  }
  std::string ExpressionManager::currentLine()const
  {
    std::size_t pos=b_.size()-1;
    while ((pos>0)&& b_.at(pos-1).tok()!=Markov_IO::Token_New::EOL)
      --pos;

    std::string buffline;
    while (pos<b_.size())
      {
        buffline.append(b_.at(pos).str());
        ++pos;

      }
    return buffline;
  }

  void ExpressionManager::history_up()
  {
    std::string line=currentLine();
    getStringandCleanFromCursor();
    std::string tail=cm_->getH().up(line);
    cm_->getIO()->put(tail);
    b_<<tail;
  }

  void ExpressionManager::history_down()
  {
    std::string line=currentLine();
    getStringandCleanFromCursor();
    std::string tail=cm_->getH().down(line);
    cm_->getIO()->put(tail);
    b_<<tail;
  }

  void ExpressionManager::getStringandCleanFromCursor()
  {
    std::size_t n=currWord_.size();
    currWord_.clear();
    cm_->getIO()->erase_from_cursor(n);
  }


  void ExpressionManager::suggestCompletion()

  {
    getStringandCleanFromCursor();
    auto n=b_.size()-1;

    std::string w=b_.back().str();
    std::map<std::string,std::vector<std::string>>
        res=cm_->complete(b_.back().str(),categories_[n]);
    if ((res.size()==1)&&(res.begin()->second.size()==1))
      {

        auto tail=Markov_Console::Autocomplete::suggestedCharacters(res,w);
        cm_->getIO()->put(tail);
        b_<<tail;
      }
    else  if ((previous_key==Markov_IO::Key_Tab)&&(res.size()>0))
      {
        auto tail=Markov_Console::Autocomplete::suggestedCharacters(res,w);
        cm_->getIO()->put(tail);
        b_<<tail;
        bool ok;
        std::string fieldselect = cm_->getIO()->getItemFromSeveralLists(w,res,ok,0);
        if (ok && !fieldselect.empty())
          {
            auto tail=Markov_Console::Autocomplete::suggestedCharacters(
            {fieldselect},w);
            cm_->getIO()->put(tail);
            b_<<tail;
          }
      }
    else
      {
        std::string fields;
        for (std::pair<std::string,bool>e:categories_[n])
          {
            if (e.second)
              {
                fields.push_back('<');
                fields.append(e.first);
                fields.append("> ,");
              }
            else
              {
                fields.push_back('[');
                fields.append(e.first);
                fields.append("] ,");
              }
          }
        fields.pop_back();
        cm_->getIO()->showMessage(fields);
      }
  }


  //  bool ExpressionManager::putSpace()
  //  {
  //    getStringandCleanFromCursor();
  //    w.push_back(' ');
  //    std::string err=cm_->check(w,categories_[cursorTok_]);
  //    if (!err.empty())
  //      {
  //        cm_->getIO()->showMessage(err);
  //        return false;
  //      }
  //    else
  //      {
  //        b_<<w;
  //        cursorTok_=b_.size()-1;
  //        p_=b_.back().str().size()-1;
  //        return true;
  //      }
  //  }

  bool ExpressionManager::putReturn()
  {
    if (!putText('\n'))
      return false;
    else
      {
        Markov_IO::Token_Stream p(b_);
        return cm_->processTokens(p);
      }
  }



  bool ExpressionManager::putText(char c)
  {
    Markov_IO::Token_New told;
    if (b_.empty())
      {
        b_.push_back(Markov_IO::Token_New(c));
      }
    else
      {
        Markov_IO::Token_New &t=b_.back();
        told=t;
        if (!t.CharIsSuccesfullyFeed(c))
          b_.push_back(Markov_IO::Token_New(c));
      }
    std::string err=cm_->check(b_.back().str(),categories_[b_.size()-1]);
    if (!err.empty())
      {
        b_.back()=told;
        cm_->getIO()->showMessage(err);
        return false;
      }
    else
      {

        std::string o;
        o.push_back(c);
        cm_->getIO()->put(o);
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

  void ExpressionManager::clean()
  {
    int n=0;
    if (!b_.empty())
      {
        std::size_t pos=b_.size()-1;
        while (pos>0&&(b_[pos].tok()!=Markov_IO::Token_New::EOL))
          {
            auto pr=b_[pos].str();
            --pos;
            n-=pr.size();
          }

        cm_->getIO()->erase_from_cursor(n);
      }
  }

  bool ExpressionParser::run()
  {

  }

  void ExpressionParser::clear()
  {

  }

  void ExpressionParser::assignVar()
  {
    Markov_IO::Token_New &t=t_.currToken();
    auto pos=t_.pos();
    if (t.tok()==Markov_IO::Token_New::IDENTIFIER)
      {
        auto id=t.id();
        std::string myclass;

        if (cm_->has_command(id))
          {
            v_=cm_->getCommand(id);
            if (v_!=nullptr)
              v_->setTokens(&t_);
          }
        else if (cm_->has_var(id)&&(t_.nextToken(1).tok()==Markov_IO::Token_New::EOL))
          {
            v_= cm_->getCommand("show");
            if (v_!=nullptr)
              v_->setTokens(&t_);
          }
        else if (t_.toIdClass(id,myclass))

          {
            t_.setPos(pos);
            v_=cm_->getClass(myclass);
            if (v_!=nullptr)
              v_->setTokens(&t_);

          }
      }
    else
      v_=nullptr;
  }

}


