#include "Tests/MultipleTests.h"
#include "Tests/ElementaryTest.h"
#include <iostream>
#include <limits>
namespace Markov_Test
{
    void MultipleTests::push_back(const ABC_Test& aTest)
    {
        tests_.push_back(aTest.clone());

        numElemTests_+=aTest.numElementayTests();
        numElemFailures_+=aTest.numElementayFailures();

	if (this->result())
	    result_=aTest.result();

	if (!aTest.result())
	{
	    numFailures_++;

	}


    }


     MultipleTests* MultipleTests::clone() const
     {
	 return new MultipleTests(*this);
     }
     MultipleTests* MultipleTests::create()const
     {
	 return new MultipleTests();
     }

      const MultipleTests& MultipleTests::VerboseLevel(bool verboseLevel)const
     {
	 verboseLevel_=verboseLevel;
	 return *this;
     }
     std::ostream& MultipleTests::put(std::ostream &s) const
     {
         s<<"--------------------------------------------------------------------------------\n";
         s<<"Functionality under test:  \t"<<functionalityUnderTest()<<"\n";
         s<<"Test rationale:            \t "<<Rationale()<<"\n";
         s<<"Number of sub tests:       \t"<<this->numSubTests()<<"\n";
         for (std::size_t i=0; i<numSubTests(); i++)
         {
             s<<"\t"<<i<<". "<<(*this)[i].functionalityUnderTest()<<"\t";
             if ((*this)[i].result())
                 s<<"All Passed. \n";
             else
             {
                 s<<(*this)[i].numElementayFailures()<<" tests in ";
                 s<<(*this)[i].numFailures()<<" sets Failed. \n";
             }

         }

         s<<"\nNumber of elementary tests:\t"<<this->numElementayTests()<<"\n";
         s<<"Result:                  \t";
	 if (result())
	     s<<"All Passed. \n";
	 else
	 {
             s<<numElementayFailures()<<" tests in ";
             s<<numFailures()<<" sets Failed. \n";
	 }
	 if ((!result())||verboseLevel_)
	     for (std::size_t i=0; i<numSubTests(); i++)
	     {
                 const ABC_Test& iTest=(*this)[i];

		 if (!iTest.result()||verboseLevel_)
		 {
                         iTest.VerboseLevel(verboseLevel_);
                         s<<iTest;
		 }
	     }

	 return s;
     }

     bool MultipleTests::result()const
     {
	 return result_;
     }

     std::string MultipleTests::functionalityUnderTest()const
     {
	 return functionality_;
     }
     std::string MultipleTests::Rationale()const
     {return rationale_;
     }

     std::size_t MultipleTests::numFailures()const{
	 return numFailures_;
     }


     MultipleTests::MultipleTests(const std::string& functionality,
				  const std::string& rationale):
	 result_(true),
	 functionality_(functionality),
	 rationale_(rationale),
	 tests_(std::vector<ABC_Test*>()),
	 numFailures_(0),
         numElemTests_(0),
         numElemFailures_(0),
	 verboseLevel_(false)
     {}

    MultipleTests::MultipleTests():
	result_(true),
	functionality_(),
	rationale_(""),
        tests_(std::vector<ABC_Test*>()),
	numFailures_(0),
        numElemTests_(0),
        numElemFailures_(0),

	verboseLevel_(false)
	{}
    MultipleTests::~MultipleTests()
    {
	 for (std::size_t i=0; i<numSubTests(); i++)
         {
             delete (tests_[i]);
         }
    }
    MultipleTests::MultipleTests(const MultipleTests& other):
	result_(other.result_),
	functionality_(other.functionality_),
	rationale_(other.rationale_),
	tests_(),
	numFailures_(other.numFailures_),
        numElemTests_(other.numElemTests_),
        numElemFailures_(other.numElemFailures_),
	verboseLevel_(other.verboseLevel_)
    {
	for (std::size_t i=0; i<other.tests_.size(); ++i)
            tests_.push_back((other.tests_[i])->clone());
    }


    MultipleTests& MultipleTests::operator =(const MultipleTests& other)
    {
	if (this!=&other)
	{
	    MultipleTests tmp(other);
	    swap(tmp,*this);
	}
	return *this;
    }

    void swap(MultipleTests& one, MultipleTests & two){

	std::swap(one.result_,two.result_);
	std::swap(one.functionality_, two.functionality_);
	std::swap(one.rationale_, two.rationale_);
	std::swap(one.tests_, two.tests_);
	std::swap(one.numFailures_, two.numFailures_);
        std::swap(one.numElemTests_,two.numElemTests_);
        std::swap(one.numElemFailures_,two.numElemFailures_);

	std::swap(one.verboseLevel_,two.verboseLevel_);
    }

    std::size_t MultipleTests::numSubTests()const
    {
	return tests_.size();
    }

    ABC_Test& MultipleTests::operator[](std::size_t i)
    {

        return *(tests_[i]);
    }

    const ABC_Test& MultipleTests::operator[](std::size_t i)const
    {
        return *(tests_[i]);
    }

     std::size_t MultipleTests::numElementayTests()const
    {
        return numElemTests_;
    }

     std::size_t MultipleTests::numElementayFailures()const
    {
        return numElemFailures_;
    }


}

