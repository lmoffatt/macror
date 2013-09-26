#include "Tests/Markov_IO/ClassDescription_Test.h"

#include "Tests/ElementaryTest.h"
#include "Markov_IO/ABC_Saveable.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Test
{
namespace Markov_IO_Test
{

MultipleTests ClassDescription_Test::classInvariant()const
{
    MultipleTests results("ClassDescription ",
			  "Class Invariant");

    results.push_back(ABC_Put_Test::classInvariant());



    //first invariant: Names should be different




    ClassDescription emptyCD(classDes_->ClassName(),
		     classDes_->SuperClass());

    MultipleTests pC("Constructor based on class and superClass",
		     "check if recovers the given values");

    pC.push_back(ElementaryTest(
			  "Constructor, ClassName()",
			  "recovers the ClassName provided in constructor",
			  emptyCD.ClassName()==classDes_->ClassName())
		      );

    pC.push_back(ElementaryTest(
			  "Constructor, SuperClass()",
			  "recovers the SuperClass provided in constructor",
			  emptyCD.SuperClass()==classDes_->SuperClass())
		      );

    results.push_back(pC);

    MultipleTests pPushBack("push_back",
			    "recovers the inserted objects");

    MultipleTests pName("ElementName()",
		   " recovers the inserted object name");

    MultipleTests pHas("HasElementName()",
		   " the element Name is recovered after it is inserted and not before");



    MultipleTests pOb("operator[]",
		   " recovers the inserted object value");

    MultipleTests pValue("ElementValue()",
		   " recovers the inserted object string representation");


    MultipleTests pIndex("NameIndex()",
			 "recovers the right index");

    MultipleTests pCl("ElementClass()",
		      " recovers the rigth object");

    for (std::size_t i=0; i<classDes_->size(); i++)
    {
	pHas.push_back(ElementaryTest(
			   classDes_->ElementName(i),
			   "before inserting: should not be here",
			   !emptyCD.HasElementName(classDes_->ElementName(i)))
		       );
	emptyCD.push_back(classDes_->ElementName(i),
			  *(*classDes_)[classDes_->ElementName(i)]);

	pHas.push_back(ElementaryTest(
			   classDes_->ElementName(i),
			   "after inserting: it should  be here",
			   emptyCD.HasElementName(classDes_->ElementName(i)))
		       );

	pName.push_back(ElementaryTest(
			    classDes_->ElementName(i),
			    "recovers actual Name",
			    classDes_->ElementName(i)==emptyCD.ElementName(i))
			);
	pOb.push_back(ElementaryTest(
			  classDes_->ElementName(i),
                          "the recovered object is the same\n"
                          "original\n"+
                          Markov_IO::ToString(
                              *(*classDes_)[classDes_->ElementName(i)])+"\n"
                          "inserted\n"+
                          Markov_IO::ToString(
                              *emptyCD[classDes_->ElementName(i)])+"\n",
                          *(*classDes_)[classDes_->ElementName(i)]==
                          *emptyCD[classDes_->ElementName(i)])
		      );

	pValue.push_back(ElementaryTest(
			     classDes_->ElementName(i),
			     "the recovered Value is the same",
			     classDes_->ElementValue(i)==emptyCD.ElementValue(i))
			 );
	pIndex.push_back(ElementaryTest(
			     classDes_->ElementName(i),
			     "recovers the right index",
			     emptyCD.NameIndex(classDes_->ElementName(i))==i)
			 );
	if (classDes_->IsComplexObject(i))
	    pCl.push_back(ElementaryTest(
			      classDes_->ElementName(i),
			      "the recovered object is the same",
			      *(classDes_->ElementClass(classDes_->ElementName(i)))==
			      *(emptyCD.ElementClass(classDes_->ElementName(i))))
			  );

    }


    pPushBack.push_back(pHas);
    pPushBack.push_back(pName);
    pPushBack.push_back(pOb);
    pPushBack.push_back(pValue);
    pPushBack.push_back(pIndex);
    pPushBack.push_back(pCl);


    pPushBack.push_back(ElementaryTest(
			    "operator==",
			    "recovers the whole ClassDescription",
			    emptyCD==*classDes_)
			);


    // we still have to check
    //bool ReplaceElement(const std::string& elementName, const ABC_Object& newValue);
    //bool ReplaceElement(const std::string& elementName, const std::string& newValue);


    results.push_back(pPushBack);
    return results;


}

ClassDescription_Test::ClassDescription_Test(const ClassDescription& sample):
    ABC_Put_Test(sample),
    classDes_(dynamic_cast<const ClassDescription*>(sample_))
{

}

ClassDescription_Test::~ClassDescription_Test()
{

}

}
}



