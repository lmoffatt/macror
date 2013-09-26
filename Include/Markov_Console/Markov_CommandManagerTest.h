#ifndef MARKOV_COMMANDMANAGERTEST_H
#define MARKOV_COMMANDMANAGERTEST_H
#include "Markov_Console/Markov_CommandManager.h"


namespace Markov_Console
{
class Markov_CommandManagerTest : public Markov_CommandManager
{

protected:
    virtual void test(const std::string& testedEntity,
	      const std::string& mode="");


public:
    Markov_CommandManagerTest();
    virtual bool next_instruction();


};

}

#endif // MARKOV_COMMANDMANAGERTEST_H
