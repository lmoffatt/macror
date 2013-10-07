#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H
#include <string>
#include <vector>
#include <deque>
#include "Markov_Console/Token.h"
namespace Markov_Console
{
class CommandHistory
{
public:
  //CommandHistory();
  void push_back(std::string commandLine);
  void push_back(const std::deque<Token>& tokens);

  std::string up();
  std::string down();

  void textToLook(const std::string& text);

  std::string history()const;

  void reset();

private:
  std::vector<std::string> lines;
  std::string startText;
  std::size_t pos;

};


}



#endif // COMMANDHISTORY_H
