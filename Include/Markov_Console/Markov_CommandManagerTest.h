#ifndef MARKOV_COMMANDMANAGERTEST_H
#define MARKOV_COMMANDMANAGERTEST_H
#include "Markov_Console/Markov_CommandManager.h"


namespace Markov_Console
{
class Markov_CommandManagerTest : public Markov_CommandManager
{

public:
    Markov_CommandManagerTest();
    virtual bool next_instruction();
    virtual std::string version();


};

}

#endif // MARKOV_COMMANDMANAGERTEST_H
