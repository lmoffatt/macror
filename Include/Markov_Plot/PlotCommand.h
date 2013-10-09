#ifndef PLOTCOMMAND_H
#define PLOTCOMMAND_H
#include "Markov_Console/ABC_Command.h"

class MacrorMainWindow;


namespace Markov_Plot
{


class PlotCommand:public Markov_Console::ABC_Command
{
public:
    PlotCommand(Markov_Console::Markov_CommandManager* cm,
                MacrorMainWindow* mw);

    /// virtual destructor
    virtual ~PlotCommand();


    virtual std::string commandName()const;

    /// runs the command on the command manager and returns true if succeeds
    virtual bool run(std::deque<Markov_Console::Token>& tokenList);

    /// runs the command for a list of parameters
    virtual bool run(const std::string& varName);

 private:
    MacrorMainWindow* mw_;


};


}




#endif // PLOTCOMMAND_H
