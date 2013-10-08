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
  CommandHistory(const std::string& filename);
  void push_back(std::string commandLine);
  void push_back(const std::deque<Token>& tokens);


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
