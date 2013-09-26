#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_Console/HelpCommand.h"
#include "Markov_Console/SimulateCommand.h"
#include "Markov_Console/CdCommand.h"
#include "Markov_Console/DirCommand.h"
#include "Markov_Console/OptimizeCommand.h"
#include "Markov_Console/SaveCommand.h"
#include "Markov_Console/LikelihoodCommand.h"
#include "Markov_Console/LoadCommand.h"
#include "Markov_Console/ExportCommand.h"
#include "Markov_Console/MkdirCommand.h"
#include "Markov_Console/ExitCommand.h"
#include "Markov_Console/EditCommand.h"
#include "Markov_Console/WhoCommand.h"
#include "Markov_Console/ClearCommand.h"
#include "Markov_Console/CreateCommand.h"
#include "Markov_Console/ShowCommand.h"
#include "Markov_Console/ModelCommand.h"
#include "Markov_Console/Average_Command.h"



namespace Markov_Console
{

void Markov_CommandManager::Loadcommands()
{
    HelpCommand* hlp=new HelpCommand(this);
    cmds[hlp->commandName()]=hlp;

    SimulateCommand* sim=new SimulateCommand(this);
    cmds[sim->commandName()]=sim;

    OptimizeCommand* optcm=new OptimizeCommand(this);
    cmds[optcm->commandName()]=optcm;

    CdCommand* cdCmd=new CdCommand(this);
    cmds[cdCmd->commandName()]=cdCmd;

    DirCommand* dircmd=new DirCommand(this);
    cmds[dircmd->commandName()]=dircmd;

    SaveCommand* savecmd=new SaveCommand(this);
    cmds[savecmd->commandName()]=savecmd;

    LikelihoodCommand* likcmd=new LikelihoodCommand(this);
    cmds[likcmd->commandName()]=likcmd;

    LoadCommand* loadcmd=new LoadCommand(this);
    cmds[loadcmd->commandName()]=loadcmd;

    ExportCommand* exportmd=new ExportCommand(this);
    cmds[exportmd->commandName()]=exportmd;

    MkdirCommand* mkdircmd=new MkdirCommand(this);
    cmds[mkdircmd->commandName()]=mkdircmd;

    ExitCommand* exitcmd=new ExitCommand(this);
    cmds[exitcmd->commandName()]=exitcmd;

  //  EditCommand* editcmd=new EditCommand(this);
  //  cmds[editcmd->commandName()]=editcmd;

    WhoCommand* whocmd=new WhoCommand(this);
    cmds[whocmd->commandName()]=whocmd;

    ClearCommand* clearcmd=new ClearCommand(this);
    cmds[clearcmd->commandName()]=clearcmd;

//    CreateCommand* createcmd=new CreateCommand(this);
//    cmds[createcmd->commandName()]=createcmd;

    ShowCommand* showcmd=new ShowCommand(this);
    cmds[showcmd->commandName()]=showcmd;


    ModelCommand* modelcmd=new ModelCommand(this);
    cmds[modelcmd->commandName()]=modelcmd;


    AverageCommand* avgcmd=new AverageCommand(this);
    cmds[avgcmd->commandName()]=avgcmd;




}



}
