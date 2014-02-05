#include "Markov_GUI/MacrorExitWindow.h"
#include "Markov_GUI/MacrorMainWindow.h"
///  destructor
MacrorExitCommand::~MacrorExitCommand(){}



MacrorExitCommand::MacrorExitCommand(Markov_Console::Markov_CommandManager* cm, MacrorMainWindow *mainw):
    ExitCommand(cm),
    mw(mainw)
{}



bool MacrorExitCommand::run(std::deque<Markov_Console::Token>& )
{
    return mw->close();

}









