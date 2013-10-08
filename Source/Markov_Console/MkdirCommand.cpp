#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>

#ifndef __linux__
  #include <direct.h>
#endif

#include "Markov_Console/MkdirCommand.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_IO/Object.h"

namespace Markov_Console
{
///  destructor
MkdirCommand::~MkdirCommand(){}



MkdirCommand::MkdirCommand(Markov_CommandManager* cm)
  :ABC_Command(cm,
               "mkdir",{{
               "dirName",Markov_IO::Object<std::string>::ClassName(),true}},{}){}

/// hint about of the class nature
std::string MkdirCommand::Tip()const
{
    return "Displays help on subject";
}

/// a short description of the class
std::string MkdirCommand::WhatThis()const
{
    return "Help command\n"
            " returns help on subject\n"
            " subject can be either a command";
}

std::string MkdirCommand::commandName()const
{
    return "mkdir";
}
/// runs the command on the command manager and returns true if succeeds
bool MkdirCommand::run(std::deque<Token> & tokenList)
{
    output_.clear();
    errorMessage_.clear();
    std::string dirName;
    if (tokenList.empty())
    {
        errorMessage_=" missing name of the directory";
        return false;
    }
    else switch(tokenList.front().get_token())
    {
    case Token::IDENTIFIER:
        dirName=tokenList.front().Name();
        tokenList.pop_front();
        return run(dirName);
        break;
    case Token::STRING:
        dirName=tokenList.front().Path();
        tokenList.pop_front();
        return run(dirName);
        break;
    default:
        output_.clear();
        errorMessage_="unexpected Token; expected NAME or PATH, found "+
                tokenList.front().get_tokenString();
        return false;
    }
}


/// runs the command for a list of parameters
bool MkdirCommand::run(const std::string& dirName)
{
  Markov_IO::FileDir d(getCommandManager()->getDir());
    std::string path=d.DirName()+ "/"+dirName;
    output_.clear();
    errorMessage_.clear();
    if (dirName.empty())
    {
        errorMessage_=" missing name of directory";
        return false;
    }
    else  if (Markov_IO::IsDir(path))
    {
        errorMessage_=path +" is already there";
        return false;
    }
    else
    {
        int res;

#ifdef __linux__
        res=mkdir(path.c_str(), 777);
#else
        res=_mkdir(path.c_str());
#endif
        if (res==-1)
        {
            std::stringstream ss;
            ss<<"Error :  "<<strerror(errno);
            errorMessage_=ss.str();
            return false;
        }
        else
        {
            output_=path+" was created successfully";
            return true;
        }

    }
}
}


