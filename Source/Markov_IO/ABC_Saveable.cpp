#include "Markov_IO/ABC_Saveable.h"
#include <fstream>
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/ABC_Options.h"
#include "Markov_IO/ABC_Parametrizable.h"
#include "Markov_Bay/ABC_Result.h"
#include "Markov_IO/ABC_Trace.h"






namespace Markov_IO
{

std::string ABC_Saveable::mySuperClass()const
{
    return ClassName();
}


std::string ABC_Saveable::ClassName()
{
    return "ABC_Saveable";
}


std::ostream& ABC_Saveable::put(std::ostream& s)const
{
    s<<GetState();
    return s;
}



ClassDescription ABC_Saveable::GetState()const
{
    return GetDescription();
}

bool ABC_Saveable::Save(const std::string& path)
{
	std::ofstream f(path.c_str());
	if(!f) return false;
	f<<this->GetDescription();
	if (!f) return false;
	f.close();
	return true;
    }


bool ABC_Saveable::Load(const std::string& fileName)
{

    ClassDescription classDes;
    // load the ClassDescription

	std::ifstream f(fileName.c_str());
	if(!f) return false;
	if (!(f>>classDes))
	{
	    f.close();
	    return false;
	}
	f.close();
	return this->LoadFromDescription(classDes);
 }


 bool ABC_Saveable::operator ==(const ABC_Saveable& other)const
{
    return this->GetDescription()==other.GetDescription();
}


  bool  create(ABC_Saveable*& v,const std::string& childClass)
  {
       ABC_Options* o;
       if (create(o,childClass))
       {
           v=o;
           return true;
       }
       ABC_Parametrizable* p;
       if (create(p,childClass))
       {
           v=p;
           return true;
       }
       Markov_Bay::ABC_Result* r;
       if (create(r,childClass))
       {
           v=r;
           return true;
       }
       ABC_trace* t;
       if (create(t,childClass))
       {
           v=t;
           return true;
       }

      return false;
  }

  bool LoadFromDescription(ABC_Saveable*& v,
               const Markov_IO::ClassDescription& classDesc)
  {

      ABC_Options* o;
      if (LoadFromDescription(o,classDesc))
      {
          v=o;
          return true;
      }
      ABC_Parametrizable* p;
      if (LoadFromDescription(p,classDesc))
      {
          v=p;
          return true;
      }
      Markov_Bay::ABC_Result* r;
      if (LoadFromDescription(r,classDesc))
      {
          v=r;
          return true;
      }
      ABC_trace* t;
      if (LoadFromDescription(t,classDesc))
      {
          v=t;
          return true;
      }

      return false;

  }


 ABC_Saveable* ABC_Saveable::create(const std::string& childClass)
 {
     ABC_Saveable* o;
     if (Markov_IO::create(o,childClass))
         return o;
     else
         return 0;
 }






}



#ifdef MACRO_TEST



#include "Tests/ElementaryTest.h"
#include "Tests/Markov_IO/ClassDescription_Test.h"
#include "Markov_Console/Markov_CommandManager.h"

namespace Markov_Test
{
namespace Markov_IO_Test
{
   MultipleTests ABC_Saveable_Test::AllTests(Markov_Console::Markov_CommandManager* cm,
                                             const std::string varNameTested)
   {
     ABC_Saveable* s;
     if (!cm->getVar(varNameTested,s))
       return MultipleTests();
     else
       {
         this->sample_=s;
         this->saveable_=s;
         return classInvariant();
       }
   }



  std::string ABC_Saveable_Test::TestName()
  {
    return "Saveable_Test";
  }

   std::string ABC_Saveable_Test::myTest()const
  {
    return TestName();
  }


    std::string ABC_Saveable_Test::testedClass()const
   {
     return ABC_Saveable::ClassName();
   }

ABC_Saveable_Test::ABC_Saveable_Test(){}


MultipleTests ABC_Saveable_Test::classInvariant()const
{
    MultipleTests results("ABC_Saveable ",
                          "Class Invariant");

    results.push_back(ABC_Put_Test::classInvariant());

    MultipleTests pGD("GetDescription()",
                      "conform invariant and class");

    ClassDescription des=saveable_->GetDescription();
    pGD.push_back(ClassDescription_Test(des).classInvariant());
    pGD.push_back(ElementaryTest("myClass()",
                                 "right in GetDescription",
                                 des.ClassName()==saveable_->myClass()));
    pGD.push_back(ElementaryTest("mySuperClass()",
                                 "right in GetDescription",
                                 des.SuperClass()==saveable_->mySuperClass()));
    pGD.push_back(ElementaryTest("myName()",
                                 "right in GetDescription",
                                 des.ElementValue(des.NameIndex("name"))==
                                 saveable_->id()));

    results.push_back(pGD);
    MultipleTests pGS("GetState()",
                      "conform invariant and class");

    ClassDescription st=saveable_->GetState();
    pGS.push_back(ClassDescription_Test(st).classInvariant());
    pGS.push_back(ElementaryTest("myClass()",
                                 "right in GetDescription",
                                 st.ClassName()==saveable_->myClass()));
    pGS.push_back(ElementaryTest("mySuperClass()",
                                 "right in GetDescription",
                                 st.SuperClass()==saveable_->mySuperClass()));
    pGS.push_back(ElementaryTest("myName()",
                                 "right in GetDescription",
                                 st.ElementValue(des.NameIndex("name"))==
                                 saveable_->id()));


    results.push_back(pGS);
    MultipleTests pLD("LoadFromDescription()",
                      "recover rigth object");

    ABC_Saveable *empty=saveable_->create();

    pLD.push_back(ElementaryTest(
                      "GetDescription()",
                      "fill an empty object",
                      empty->LoadFromDescription(des)));

    pLD.push_back(ElementaryTest(
                      "GetDescription()",
                      "recover the same object",
                      *empty==*saveable_));
    results.push_back(pLD);

// test on those is not implemented since nobody uses them
    // bool Save(const std::string& path);

//     bool Load(const std::string& path);



    return results;


}

ABC_Saveable_Test::ABC_Saveable_Test(const ABC_Saveable& sample):
    ABC_Put_Test(sample),
    saveable_(dynamic_cast<const ABC_Saveable*>(sample_))
{

}

ABC_Saveable_Test::~ABC_Saveable_Test()
{

}

}
}


#endif //MACRO_TEST



