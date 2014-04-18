#include "Markov_Console/CommandHistory_old.h"

#include <fstream>
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Console
{

  CommandHistory::CommandHistory(const std::string& filename)
    :filename_(filename),
      pos(0),
      lines()
  {
    if (filename_.empty())
      filename_="commandHistory.txt";
    std::fstream fs(filename_);
    if (!fs)
      {
        fs.close();
        filename_="commandHistory.txt";
        fs.open(filename_);
      }
    std::string line;
    while (Markov_IO::safeGetline(fs,line))
      {
       // if (line.substr(0,3)!="%--")
          {
            lines.push_back(line);
            pos++;
          }
      }

  }


  void CommandHistory::push_back(std::string commandLine)
  {
    lines.push_back(commandLine);
    std::fstream fs(filename_,std::ios_base::app|std::ios_base::out);

    if (!fs.is_open())
    fs.open(filename_,std::ios_base::app|std::ios_base::out);
    fs<<commandLine<<std::endl;
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


  std::string CommandHistory::up(const std::string& startText)
  {
    if (startText.empty())
      {
        if (pos>0) pos--;
        else
            return "";
        if (lines.empty())
          return "";
        else
          if (pos<lines.size())
          return lines[pos];
         else
            return "";
      }
    else
      {
        std::size_t n=startText.size();
        if (pos==0)
            return "";
        while((pos>0)&&(startText.compare(lines.at(pos-1).substr(0,n))!=0))
          --pos;
        if (pos>0)
          --pos;

        if (startText.compare(lines.at(pos).substr(0,n))==0)
          return lines[pos].substr(n);
        else
            return "";
      }
  }
  std::string CommandHistory::down(const std::string& startText)
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
        while((pos+1<lines.size())&&(startText.compare(lines.at(pos+1).substr(0,n))!=0))
          ++pos;
        if (pos<lines.size()) ++pos;
        if ((pos<lines.size())&&(startText.compare(lines.at(pos).substr(0,n))==0))
          return lines[pos].substr(n);
        else
          return std::string();
      }
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


