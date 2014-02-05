#ifndef MACROREXITWINDOW_H
#define MACROREXITWINDOW_H



#include "Markov_Console/ExitCommand.h"



class MacrorMainWindow;


class MacrorExitCommand:public Markov_Console::ExitCommand
{
public:
    MacrorExitCommand(Markov_Console::Markov_CommandManager* cm,
                      MacrorMainWindow* mainw);

    /// virtual destructor
    virtual ~MacrorExitCommand();


    /// runs the command for a list of parameters
    virtual bool run(std::deque<Markov_Console::Token>&);

private:
    MacrorMainWindow* mw;

};








#endif // MACROREXITWINDOW_H
