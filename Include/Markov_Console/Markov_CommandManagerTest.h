#ifndef MARKOV_COMMANDMANAGERTEST_H
#define MARKOV_COMMANDMANAGERTEST_H
#include "Include/Markov_Console/Markov_CommandManager.h"
#include "Include/Tests/All_Tests.h"
#include "Include/Tests/MultipleTests.h"

namespace Markov_Console
{
class Markov_CommandManagerTest : public Markov_CommandManager
{

public:
    Markov_CommandManagerTest();
    virtual bool next_instruction();
    virtual std::string version()const;

    virtual Markov_Test::All_Tests * getTest(const std::string& testName);
private:
    std::map<std::string, Markov_Test::All_Tests*> tests;


};

}

#endif // MARKOV_COMMANDMANAGERTEST_H
