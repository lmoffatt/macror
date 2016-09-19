#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include "Markov_IO/Token_New.h"

#include <string>
#include <map>
#include <vector>
#include <deque>



namespace Markov_IO_New
{
class CommandHistory
{
public:
  CommandHistory(const std::string& filename);
  void push_back(std::string commandLine);


  std::string up(const std::string& text);
  std::string down(const std::string& text);


  void textToLook(const std::string& text);

  std::string history()const;

  void reset();

private:
  std::string filename_;
  std::size_t pos;

  std::vector<std::string> lines;

};


}




#endif // COMMANDHISTORY_H
