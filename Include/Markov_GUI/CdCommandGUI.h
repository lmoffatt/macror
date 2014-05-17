#ifndef CDCOMMANDGUI_H
#define CDCOMMANDGUI_H
#include "Markov_Console/CdCommand.h"
#include "Markov_GUI/MacrorMainWindow.h"

namespace Markov_GUI
{
class CdCommandGUI:public Markov_Console::CdCommand
{
public:
    CdCommandGUI(Markov_Console::Markov_CommandManager* cm,
                 MacrorMainWindow *mw);

    /// virtual destructor
    virtual ~CdCommandGUI();

    /// runs the command for a list of parameters
    virtual bool run(const std::string& dirName);

private:
    MacrorMainWindow*  mw_;
};



}

#endif // CDCOMMANDGUI_H
