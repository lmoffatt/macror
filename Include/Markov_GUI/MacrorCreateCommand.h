#ifndef MACRORCREATECOMMAND_H
#define MACRORCREATECOMMAND_H
#include "Markov_LA/Matrix.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Console/ABC_Command.h"

#include "Markov_Console/CreateCommand.h"
#include "Markov_GUI/EditWidgetField.h"

class MacrorCreateCommand:public Markov_Console::CreateCommand
{
public:
    MacrorCreateCommand(Markov_Console::Markov_CommandManager* cm);

    /// virtual destructor
    virtual ~MacrorCreateCommand();


    /// runs the command for a list of parameters
    virtual bool run(const std::string &typeName,const std::string &varname);


};



#endif // MACRORCREATECOMMAND_H
