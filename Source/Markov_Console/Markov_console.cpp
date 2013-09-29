#include "Markov_Console/Markov_console.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Console
{

/**
  Until user types exit execute the typed commands
  in stdin
  */
Markov_Console::Markov_Console()
{
    std::string commandLine;

    std::cout <<cm.wellcomeMessage();
    //std::cout<<cm.version()<<"  "<<cm.verDate()<<"   build  "<<cm.ver()<<"\n";
    while(true)
    {
        std::cout<<">>";
        getline(std::cin,commandLine);
	cm.add_tokens(commandLine);
        cm.next_instruction();
    }
}



}
