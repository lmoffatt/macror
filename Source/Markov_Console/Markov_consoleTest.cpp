#include <fstream>

#include "Markov_Console/Markov_consoleTest.h"
#include "Markov_Console/Help_File.h"
#include "Markov_Console/Markov_Script.h"


namespace Markov_Console
{

/**
  Until user types exit execute the typed commands
  in stdin
  */
Markov_ConsoleTest::Markov_ConsoleTest(const std::string& fileCommandName)
{
  std::string commandLine;

  std::cout<<"MacroRConsole_Test 0.1."<<cm.ver()<<"\n";
  if (fileCommandName.empty())
    {
      std::cout <<HelpFile("wellcome.txt");
      while(true)
        {
          std::cout<<">>";
          getline(std::cin,commandLine);
          cm.add_tokens(commandLine);
          cm.next_instruction();
        }
    }

  else
    {
      Markov_Script ms(cm,fileCommandName);
      commandLine="exit";
      cm.add_tokens(commandLine);
      cm.next_instruction();
    }
}
}
