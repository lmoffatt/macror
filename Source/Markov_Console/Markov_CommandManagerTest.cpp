#include "Markov_Console/Markov_CommandManagerTest.h"
#include "Include/Markov_Console/TestCommand.h"


namespace Markov_Console
{

Markov_CommandManagerTest::Markov_CommandManagerTest():
    Markov_CommandManager()
{
  TestCommand* testcmd=new TestCommand(this);
  cmds[testcmd->commandName()]=testcmd;


 }

std::string Markov_CommandManagerTest::version()
{
  return "MacroConsoleTest 0.1";

}





bool Markov_CommandManagerTest::next_instruction()
{
    // Else try with all other commands
    return Markov_CommandManager::next_instruction();
}

}


