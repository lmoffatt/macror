#include "Markov_Plot/PlotCommand.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_Plot/GraphWindow.h"
#include "Markov_Plot/GraphView.h"

#include "Markov_Plot/XY_PlotData.h"
#include "Markov_GUI/MacrorMainWindow.h"


namespace Markov_Plot
{
///  destructor
PlotCommand::~PlotCommand(){}



PlotCommand::PlotCommand(Markov_Console::Markov_CommandManager* cm,
                         MacrorMainWindow* mw)
  :Markov_Console::ABC_Command(cm,
               "plot",{{
               "variable",Markov_Console::ABC_Command::varName(),true}},{}),
    mw_(mw)
{}

std::string PlotCommand::commandName()const
{
    return "plot";
}
/// runs the command on the command manager and returns true if succeeds
bool PlotCommand::run(std::deque<Markov_Console::Token> & tokenList)
{
    std::string varName;
    if (tokenList.empty())
    {
        errorMessage_="variable to plot is missing";
        return false;
    }
    else switch(tokenList.front().get_token())
    {
    case Markov_Console::Token::IDENTIFIER:
        varName=tokenList.front().Name();
        tokenList.pop_front();
        return run(varName);
        break;
    default:
        output_.clear();
        errorMessage_="unexpected Token; expected NAME or PATH, found "+
                tokenList.front().get_tokenString();
        return false;
    }
}


/// runs the command for a list of parameters
bool PlotCommand::run(const std::string& varName)
{
    output_.clear();
    if (getCommandManager()->checkVariable(varName,Markov_IO::ABC_Experiment::ClassName()))
      {
        Markov_IO::ABC_Experiment* e=dynamic_cast<Markov_IO::ABC_Experiment*>(
              getCommandManager()->getVar(varName));
        Markov_Plot::GraphWindow* g=plot(0,*e);
        mw_->createGraph(g);


        return true;

      }
    else return false;
    }

}


