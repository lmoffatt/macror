#ifndef MULTIPLETESTS_H
#define MULTIPLETESTS_H

#include <vector>
#include <string>
#include "Tests/ABC_Test.h"

namespace Markov_Test_New
{
class MultipleTests: public ABC_Test
{
public:
    virtual MultipleTests* clone() const;
    virtual MultipleTests* create()const;

    virtual std::ostream& put(std::ostream &s) const;


    void push_back(const ABC_Test& aTest);

    virtual bool result()const;

    virtual std::string functionalityUnderTest()const;
    virtual std::string Rationale()const;


    MultipleTests(const std::string& functionalityUnderTest, const std::string& expected);


    virtual std::size_t numSubTests()const;

    virtual std::size_t numFailures()const;

    virtual std::size_t numElementayTests()const;

    virtual std::size_t numElementayFailures()const;


    virtual ABC_Test& operator[](std::size_t i);
    virtual const ABC_Test& operator[](std::size_t i)const;

    virtual const MultipleTests& VerboseLevel(bool verboseLevel)const;

    MultipleTests();
    virtual ~MultipleTests();

    MultipleTests(const MultipleTests& other);

    MultipleTests& operator =(const MultipleTests& other);

    friend void swap(MultipleTests& one, MultipleTests & two);



private:
    bool result_;
    std::string functionality_;
    std::string rationale_;

    std::vector<ABC_Test*> tests_;
    std::size_t numFailures_;

    std::size_t numElemTests_;
    std::size_t numElemFailures_;
    mutable bool verboseLevel_;

};





}


#include <vector>
#include <string>
#include "Tests/ABC_Test.h"

namespace Markov_Test
{
class MultipleTests: public ABC_Test
{
public:
    virtual MultipleTests* clone() const;
    virtual MultipleTests* create()const;

    virtual std::ostream& put(std::ostream &s) const;


    void push_back(const ABC_Test& aTest);

    virtual bool result()const;

    virtual std::string functionalityUnderTest()const;
    virtual std::string Rationale()const;


    MultipleTests(const std::string& functionalityUnderTest, const std::string& expected);


    virtual std::size_t numSubTests()const;

    virtual std::size_t numFailures()const;

    virtual std::size_t numElementayTests()const;

    virtual std::size_t numElementayFailures()const;


    virtual ABC_Test& operator[](std::size_t i);
    virtual const ABC_Test& operator[](std::size_t i)const;

    virtual const MultipleTests& VerboseLevel(bool verboseLevel)const;

    MultipleTests();
    virtual ~MultipleTests();

    MultipleTests(const MultipleTests& other);

    MultipleTests& operator =(const MultipleTests& other);

    friend void swap(MultipleTests& one, MultipleTests & two);



private:
    bool result_;
    std::string functionality_;
    std::string rationale_;

    std::vector<ABC_Test*> tests_;
    std::size_t numFailures_;

    std::size_t numElemTests_;
    std::size_t numElemFailures_;
    mutable bool verboseLevel_;

};





}


#endif // MULTIPLETESTS_H
