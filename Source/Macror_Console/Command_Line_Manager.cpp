#include "Macror_Console/Command_Line_Manager.h"
#include <cmath>
#include "Macror_Console/Macror_CommandManager.h"
#include "Macror_Console/KeyEvent.h"
#include "Macror_Console/Autocomplete.h"
#include "Macror_Console/CommandHistory.h"

namespace Macror_Console {
  std::string incolumns(std::vector<std::string> list,std::size_t colwidth)
  {
    std::size_t maxlength=0;
    auto n=list.size();
    for (std::size_t i=0; i< list.size(); ++i)
      if (list.at(i).size()>maxlength)
        maxlength=list.at(i).size();
    maxlength+=2;
    std::size_t ncols=colwidth/maxlength;
    std::size_t nrows=std::ceil(n*1.0/ncols);

    std::string result;
    for (std::size_t i=0; i< nrows; ++i)
      {
        for (std::size_t j=0; j<ncols && i+j*nrows<list.size();j++)
          {

            std::string name=list[i+j*nrows];
            result+=name+std::string(maxlength-name.size(),' ');

          }
        result+="\n";
      }
    return result;


  }

  bool Command_Line_Manager::eventKey(KeyEvent *k)
  {
     currChar_=k->getChar();
    currKey_=k->getKey();

    if (currKey_== KeyEvent::Key_Tab)  //
      {
        std::vector<std::string> res=cm_->complete(commandWord_);
        if ((res.size()==1)&&(res.front()[0]!='<')&&(res.front()[0]!='['))
          /* this means there is only one legal completion */
          {
            tail_=Autocomplete::suggestedCharacters(res,commandWord_);
            cm_->myIostream()<<tail_;
            commandWord_+=tail_;
          }
        else if(res.size()>0)  // more than one possibility
          {
            if (previousKey_== KeyEvent::Key_Tab)
              // two \t in a row indicates we want to choose between alternatives
              {

                suggestAlternatives(res);
              }
          }

      }
    else if (currKey_== KeyEvent::Key_Backspace)
      {
        if (!commandWord_.empty())
          {
            commandWord_.pop_back();
            cm_->myIostream()<<'\b';
            cm_->myIostream()<<' ';
            cm_->myIostream()<<'\b';
          }
      }
    else if ((currKey_== KeyEvent::Key_Up)||(currKey_== KeyEvent::Key_Down))
      {
        std::string tail0=tail_;
        if (currKey_== KeyEvent::Key_Up)
          tail_=cm_->getH()->up(commandWord_);
        else
          tail_=cm_->getH()->down(commandWord_);

        if (tail0.size()>tail_.size())
          {
            cm_->myIostream()<<tail_<<std::string(tail0.size()-tail_.size(),' ');
            if (currChar_[0]=='\033')
              for (std::size_t i=0; i<tail0.size(); ++i)
                cm_->myIostream()<<'\033'<<'['<<'D';
            else
              for (std::size_t i=0; i<tail0.size(); ++i)
                cm_->myIostream()<<'\b';
          }
        else
          {
            cm_->myIostream()<<tail_;
            if (currChar_[0]=='\033')
              for (std::size_t i=0; i<tail_.size(); ++i)
                cm_->myIostream()<<'\033'<<'['<<'D';
            else
              for (std::size_t i=0; i<tail_.size(); ++i)
                cm_->myIostream()<<'\b';

          }
      }
    else  if (currKey_== KeyEvent::Key_Right) // rightkey
      {
        if (!tail_.empty())
          {
            if (currChar_[0]=='\033')
              cm_->myIostream()<<'\033'<<'['<<'C';
            else
              cm_->myIostream()<<tail_.front();
            commandWord_+=tail_.front();
            tail_=tail_.substr(1);
          }

      }
    else  if (currKey_== KeyEvent::Key_Left) // leftkey
      {
        if (!commandWord_.empty())
          {
            if (currChar_[0]=='\033')
              cm_->myIostream()<<'\033'<<'['<<'D';
            else
              cm_->myIostream()<<'\b';
            tail_=commandWord_.back()+tail_;
            commandWord_.pop_back();
          }
      }
   else if (currKey_==KeyEvent::Key_Space)
      {
        cm_->myIostream()<<' ';
        std::string err=cm_->add_single_token(commandWord_);
        if (!err.empty())
          {
            cm_->myIostream()<<"\n"<<err<<">>"<<commandLine_;
          }
        else
          commandLine_+=commandWord_+currChar_[0];
        commandWord_.clear();

      }
    else if (currKey_!=KeyEvent::Key_Return)

      {
        cm_->myIostream()<<currChar_[0];
        commandWord_+=currChar_[0];
      }
    else  // new line
      {
        cm_->myIostream()<<'\n';
        commandLine_+=commandWord_+tail_;
        tail_.clear();
        commandWord_.clear();
        cm_->getH()->reset();
      }
    previousKey_=currKey_;
    return true;
  }


  void Command_Line_Manager::suggestAlternatives(const std::vector<std::string>& res)
  {
    tail_=Autocomplete::suggestedCharacters(res,commandWord_);
    commandWord_+=tail_;
    cm_->myIostream()<<"\n"<<incolumns(res,cm_->ncols_)<<">>"<<commandLine_+commandWord_;

  }



}

