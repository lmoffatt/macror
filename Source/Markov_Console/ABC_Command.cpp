#include "Markov_Console/ABC_Command.h"
namespace Markov_Console
{


ABC_Command::~ABC_Command(){}
///  formated output

///  formated output
std::ostream& ABC_Command::put(std::ostream& s) const
{
    s<<this->commandName();
    return s;
}

bool ABC_Command::operator==(const ABC_Command& other)const
{
    return this->commandName()==other.commandName();
}

/// hint about of the class nature
std::string ABC_Command::Tip()const
{
    return "Some command";
}

/// a short description of the class
std::string ABC_Command::WhatThis()const
{
    return "Base class of all console commands\n"
            "This commands are also used in scripts\n";

}

/// checks if commandName ref   ers to the actual command
bool ABC_Command::IsCommand(const std::string& ACommandName)const
{
    return ACommandName==this->commandName();
}
/// error message, empty string if succeeded
std::string ABC_Command::errorMessage()const
{
    return errorMessage_;
}
/// printed output, empty string if command fails
std::string ABC_Command::output()const
{
    return output_;
}

Markov_CommandManager* ABC_Command::getCommandManager()
{
    return cm_;
}



}


