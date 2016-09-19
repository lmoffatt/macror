#include "Markov_Console/CommandHistory.h"

#include <fstream>
#include "Markov_IO/auxiliarIO.h"


namespace Markov_IO_New
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
    while (Markov_IO_New::safeGetline(fs,line))
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




  std::string CommandHistory::up(const std::string& startText)
  {
    if (lines.empty())
      return "";
    else
      {
        if (startText.empty())
          {
            std::string prev{};
            if (pos<lines.size())
              prev=lines[pos];
            else
              pos=lines.size()-1;
            while ((pos>0)&&(lines[pos].empty()||lines[pos][0]=='%'||lines[pos]==prev))
              --pos;
            if (lines[pos][0]=='%')
              return "";
            else
              return lines[pos];
          }

        else
          {
            std::size_t n=startText.size();
            if (pos==0)
              return "";
            std::string prev{};
            if (pos<lines.size())
              prev=lines[pos];
            else
              pos=lines.size()-1;
            while((pos>0)&&((lines[pos]==prev)||(startText.compare(lines.at(pos).substr(0,n))!=0)))
              --pos;

            if (startText.compare(lines.at(pos).substr(0,n))==0)
              return lines[pos].substr(n);
            else
              return "";
          }

      }
  }
  std::string CommandHistory::down(const std::string& startText)
  {
    if (lines.empty())
      return "";
    else
      {
        if (startText.empty())
          {
            std::string prev{};
            if (pos<lines.size())
              prev=lines[pos];
            else
              pos=lines.size()-1;
            while ((pos<lines.size())&&(lines[pos].empty()||lines[pos][0]=='%'||prev==lines[pos])) pos++;
            if (pos!=lines.size())
              return lines[pos];
            else
              return "";
          }
        else
          {
            std::size_t n=startText.size();
            std::string prev{};
            if (pos<lines.size())
              prev=lines[pos];
            while((pos<lines.size())&&((prev==lines[pos])||(startText.compare(lines.at(pos).substr(0,n))!=0)))
              ++pos;
            if ((pos<lines.size())&&(startText.compare(lines.at(pos).substr(0,n))==0))
              return lines[pos].substr(n);
            else
              return std::string();
          }
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


