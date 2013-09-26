#include "Markov_Console/CommandHistory.h"

namespace Markov_Console
{
  void CommandHistory::push_back(std::string commandLine)
  {
    lines.push_back(commandLine);
    reset();
  }

  void CommandHistory::push_back(const std::deque<Token> &tokens)
  {
    std::string commandLine;
    for (std::size_t i=0;i<tokens.size(); i++)
      {
        commandLine+=tokens[i].get_tokenString();
      }
    push_back(commandLine);
  }


  std::string CommandHistory::up()
  {
    if (startText.empty())
      {
       if (pos>0) pos--;
       if (lines.empty())
         return "";
       else
       return lines[pos];
      }
    else
      {
        std::size_t n=startText.size();
        while((pos>0)&&(startText.compare(lines.at(pos-1).substr(0,n))!=0))
           --pos;
        if ((pos!=0)||(startText.compare(lines.at(pos).substr(0,n))==0))
          return lines[pos];
        else
          return std::string();
       }
  }
  std::string CommandHistory::down()
  {
    if (startText.empty())
      {
        if (pos<lines.size()) pos++;
        if (pos!=lines.size())
       return lines[pos];
        else
          return "";
      }
    else
      {
        std::size_t n=startText.size();
        while((pos<lines.size())&&(startText.compare(lines.at(pos+1).substr(0,n))!=0))
           ++pos;
        if ((pos!=lines.size())||(startText.compare(lines.at(pos).substr(0,n))==0))
          return lines[pos];
        else
          return std::string();
       }
  }

  void CommandHistory::textToLook(const std::string& text)
  {
   startText= text;
  }

  std::string CommandHistory::history()const
  {
    std::string out;
    for (std::size_t i=0; i<lines.size(); i++)
      {
      out+=lines[i];
      out+="\n";
      }
    return out;
  }


  void CommandHistory::reset()
  {
    pos=lines.size();
  }

}


