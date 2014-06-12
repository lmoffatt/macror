#include "Tests/Markov_LA/ToleranceComparison_Test.h"
#include "Tests/AssertPlain.h"
#include "Tests/MultipleTests.h"
#include "Tests/ElementaryTest.h"




namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;

   MultipleTests ToleranceComparison_Test::AllTests(Markov_Console::Markov_CommandManager* ,
                                 const std::string )
   {
     return AllTests();
   }
 // virtual MultipleTests AllTests()=0;
   std::string ToleranceComparison_Test::TestName()
   {
     return "ToleranceComparison_Test";
   }

   std::string ToleranceComparison_Test::myTest()const
   {
     return TestName();
   }

   std::string ToleranceComparison_Test::testedClass()const
   {
     return "";
   }



/**
  Equality Operator Test


 */




MultipleTests ToleranceComparison_Test::isEqual_Test() const
{
    double eps=std::numeric_limits<double>::epsilon();

    // check for the default constructor

    double x=1.0;
    ToleranceComparison<double> tol;
    MultipleTests result("ToleranceComparison::isEqual",
			 "check different conditions one by one");

    result.push_back(EqualValue_Test(
			 "AbsoluteTolerance equal to numeric_limits::epsilon",
			 tol.AbsoluteTolerance(),eps));
    result.push_back(EqualValue_Test("RelativeTolerance() default",
				     tol.RelativeTolerance(),eps));


    result.push_back(ElementaryTest(
			 "isEqual()",
			 "isEqual(x,x+eps)",
			 tol.isEqual(x,x+eps)));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "isEqual(x,x-eps)",
			 tol.isEqual(x,x-eps)));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "isEqual(-x,-x+eps)",
			 tol.isEqual(-x,-x+eps)));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "isEqual(-x,-x-eps)",
			 tol.isEqual(-x,-x-eps)));

    result.push_back(ElementaryTest(
			 "isEqual()",
			 "isEqual(x,x+2*eps) is false",
			 !(tol.isEqual(x,x+2*eps))));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "isEqual(x,x-2*eps) is false",
			 !(tol.isEqual(x,x-2*eps))));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "isEqual(-x,-x+2*eps) is false",
			 !(tol.isEqual(-x,-x+2*eps))));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "isEqual(-x,-x-2*eps) is false",
			 !(tol.isEqual(-x,-x-2*eps))));

    //  when x>>1 it compares with the relative tolerance

    x=4.738765423E8;

    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.738765423E8 isEqual(x,x*(1+0.5*eps))",
			 tol.isEqual(x,x*(1+0.5*eps))));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.738765423E8 isEqual(x,x*(1-0.5*eps))",
			 tol.isEqual(x,x*(1-0.5*eps))));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.738765423E8 isEqual(-x,-x*(1+0.5*eps))",
			 tol.isEqual(-x,-x*(1+0.5*eps))));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.738765423E8 isEqual(-x,-x*(1-0.5*eps))",
			 tol.isEqual(-x,-x*(1-0.5*eps))));

    result.push_back(ElementaryTest(
			 "isEqual",
			 "x=4.738765423E8 isEqual(x,x*(1+2*eps)) is false",
			 !(tol.isEqual(x,x*(1+2*eps)))));

    result.push_back(ElementaryTest(
			 "isEqual",
			 "x=4.738765423E8 isEqual(x,x*(1-2*eps)) is false",
			 !(tol.isEqual(x,x*(1-2*eps)))));
    result.push_back(ElementaryTest(
			 "isEqual",
			 "x=4.738765423E8 isEqual(-x,-x*(1+2*eps)) is false",
			 !(tol.isEqual(-x,-x*(1+2*eps)))));
    result.push_back(ElementaryTest(
			 "isEqual",
			 "x=4.738765423E8 isEqual(-x,-x*(1-2*eps)) is false",
			 !(tol.isEqual(-x,-x*(1-2*eps)))));

    // when x<<1 it uses the absolute tolerance
    x=4.536267348932E-9;
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 isEqual(x,x+eps)",
			 tol.isEqual(x,x+eps)));

    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 isEqual(x,x-eps)",
			 tol.isEqual(x,x-eps)));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 isEqual(-x,-x+eps)",
			 tol.isEqual(-x,-x+eps)));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 isEqual(-x,-x-eps)",
			 tol.isEqual(-x,-x-eps)));


    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 isEqual(x,x+2*eps) is false",
			 !(tol.isEqual(x,x+2*eps))));

    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 isEqual(x,x-2*eps) is false",
			 !(tol.isEqual(x,x-2*eps))));

    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 isEqual(-x,-x+2*eps) is false",
			 !(tol.isEqual(-x,-x+2*eps))));

    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 isEqual(-x,-x-2*eps) is false",
			 !(tol.isEqual(-x,-x-2*eps))));
    // with absolute tolerance cero, it uses the relative tolerance
    tol.AbsoluteTolerance()=0;

    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isEqual(x,x*(1+0.5*eps))",
			 tol.isEqual(x,x*(1+0.5*eps))));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isEqual(x,x*(1-0.5*eps))",
			 tol.isEqual(x,x*(1-0.5*eps))));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isEqual(-x,-x*(1+0.5*eps))",
			 tol.isEqual(-x,-x*(1+0.5*eps))));
    result.push_back(ElementaryTest(
			 "isEqual()",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isEqual(-x,-x*(1-0.5*eps))",
			 tol.isEqual(-x,-x*(1-0.5*eps))));

    result.push_back(ElementaryTest(
			 "isEqual",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isEqual(x,x*(1+2*eps)) is false",
			 !(tol.isEqual(x,x*(1+2*eps)))));

    result.push_back(ElementaryTest(
			 "isEqual",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isEqual(x,x*(1-2*eps)) is false",
			 !(tol.isEqual(x,x*(1-2*eps)))));
    result.push_back(ElementaryTest(
			 "isEqual",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isEqual(-x,-x*(1+2*eps)) is false",
			 !(tol.isEqual(-x,-x*(1+2*eps)))));
    result.push_back(ElementaryTest(
			 "isEqual",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isEqual(-x,-x*(1-2*eps)) is false",
			 !(tol.isEqual(-x,-x*(1-2*eps)))));



    x=5.3572346689483E4;
    tol.AbsoluteTolerance()=x*eps;
    tol.RelativeTolerance()=std::sqrt(eps);
    double y=x*std::sqrt(eps);

    //double relTol=std::sqrt(eps);

    double absTol=x*eps;

    result.push_back(ElementaryTest("isEqual()",
				    "isEqual(y,y+absTol) x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps); absTol=x*eps",
				     tol.isEqual(y,y+absTol)));

    result.push_back(ElementaryTest("isEqual()",
				    "isEqual(y,y-absTol) x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps);absTol=x*eps ",
				     tol.isEqual(y,y-absTol)));
    result.push_back(ElementaryTest("isEqual()",
				    "isEqual(-y,-y+absTol) x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps); absTol=x*eps",
				     tol.isEqual(-y,-y+absTol)));
    result.push_back(ElementaryTest("isEqual()",
				    "isEqual(-y,-y-absTol) x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps); absTol=x*eps",
				     tol.isEqual(-y,-y-absTol)));


    result.push_back(ElementaryTest("isEqual()",
				    "isEqual(y,y+2*absTol) is false"
				    " x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps); absTol=x*eps",
				     !tol.isEqual(y,y+2*absTol)));


    result.push_back(ElementaryTest("isEqual()",
				    "isEqual(y,y-2*absTol) is false"
				    " x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps); absTol=x*eps",
				     !tol.isEqual(y,y-2*absTol)));

    result.push_back(ElementaryTest("isEqual()",
				    "isEqual(-y,-y-2*absTol) is false"
				    " x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps); absTol=x*eps",
				     !tol.isEqual(-y,y-2*absTol)));

    result.push_back(ElementaryTest("isEqual()",
				    "isEqual(-y,-y+2*absTol) is false"
				    " x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps); absTol=x*eps",
				     !tol.isEqual(-y,-y+2*absTol)));

    return result;

}


MultipleTests ToleranceComparison_Test::isLess_Test() const
{
    double eps=std::numeric_limits<double>::epsilon();

    // check for the default constructor



    double x=1.0;
    ToleranceComparison<double> tol;
    MultipleTests result("ToleranceComparison::isLess",
			 "check different conditions one by one");



    result.push_back(ElementaryTest(
			 "isLess()",
			 "isLess(x,x+eps) is false",
			 !tol.isLess(x,x+eps)));
    result.push_back(ElementaryTest(
			 "isLess()",
			 "isLess(-x,-x+eps) is false",
			 !tol.isLess(-x,-x+eps)));

    result.push_back(ElementaryTest(
			 "isLess()",
			 "isLess(x,x+2*eps) is true",
			 (tol.isLess(x,x+2*eps))));
    result.push_back(ElementaryTest(
			 "isLess()",
			 "isLess(-x,-x+2*eps) is true",
			 (tol.isLess(-x,-x+2*eps))));

    //  when x>>1 it compares with the relative tolerance

    x=4.738765423E8;

    result.push_back(ElementaryTest(
			 "isLess()",
			 "x=4.738765423E8 isLess(x,x*(1+0.5*eps)) is false",
			 !tol.isLess(x,x*(1+0.5*eps))));
    result.push_back(ElementaryTest(
			 "isLess()",
			 "x=4.738765423E8 isLess(-x,-x*(1-0.5*eps)) is false",
			 !tol.isLess(-x,-x*(1-0.5*eps))));

    result.push_back(ElementaryTest(
			 "isLess",
			 "x=4.738765423E8 isLess(x,x*(1+2*eps)) is true",
			 (tol.isLess(x,x*(1+2*eps)))));

    result.push_back(ElementaryTest(
			 "isLess",
			 "x=4.738765423E8 isLess(-x,-x*(1-2*eps)) is true",
			 (tol.isLess(-x,-x*(1-2*eps)))));

    // when x<<1 it uses the absolute tolerance
    x=4.536267348932E-9;
    result.push_back(ElementaryTest(
			 "isLess()",
			 "x=4.536267348932E-9 isLess(x,x+eps) is false" ,
			 !tol.isLess(x,x+eps)));
    result.push_back(ElementaryTest(
			 "isLess()",
			 "x=4.536267348932E-9 isLess(-x,-x+eps)is false",
			 !tol.isLess(-x,-x+eps)));


    result.push_back(ElementaryTest(
			 "isLess()",
			 "x=4.536267348932E-9 isLess(x,x+2*eps) is true",
			 (tol.isLess(x,x+2*eps))));


    result.push_back(ElementaryTest(
			 "isLess()",
			 "x=4.536267348932E-9 isLess(-x,-x+2*eps) is true",
			 (tol.isLess(-x,-x+2*eps))));

    // with absolute tolerance cero, it uses the relative tolerance
    tol.AbsoluteTolerance()=0;

    result.push_back(ElementaryTest(
			 "isLess()",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isLess(x,x*(1+0.5*eps)) is false"
			 " is false",
			 !tol.isLess(x,x*(1+0.5*eps))));
    result.push_back(ElementaryTest(
			 "isLess()",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isLess(-x,-x*(1-0.5*eps)) is false"
			 " is false",
			 !tol.isLess(-x,-x*(1-0.5*eps))));

    result.push_back(ElementaryTest(
			 "isLess",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isLess(x,x*(1+2*eps)) is true",
			 (tol.isLess(x,x*(1+2*eps)))));

    result.push_back(ElementaryTest(
			 "isLess",
			 "x=4.536267348932E-9 AbsoluteTolerance()=0 isLess(-x,-x*(1-2*eps)) is true",
			 (tol.isLess(-x,-x*(1-2*eps)))));



    x=5.3572346689483E4;
    tol.AbsoluteTolerance()=x*eps;
    tol.RelativeTolerance()=std::sqrt(eps);
    double y=x*std::sqrt(eps);


    double absTol=x*eps;

    result.push_back(ElementaryTest("isLess()",
				    "isLess(y,y+absTol) x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps); absTol=x*eps"
				    " is false",
				     !tol.isLess(y,y+absTol)));

     result.push_back(ElementaryTest("isLess()",
				    "isLess(-y,-y+absTol) x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps); absTol=x*eps"
				     " is false",
				     !tol.isLess(-y,-y+absTol)));


    result.push_back(ElementaryTest("isLess()",
				    "isLess(y,y+2*absTol) is true"
				    " x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps); absTol=x*eps",
				     tol.isLess(y,y+2*absTol)));



    result.push_back(ElementaryTest("isLess()",
				    "isLess(-y,-y-2*absTol) is true"
				    " x=5.3572346689483E4"
				    "AbsoluteTolerance()=x*eps; "
				    "RelativeTolerance()=std::sqrt(eps); "
				     "y=x*std::sqrt(eps); absTol=x*eps",
				     tol.isLess(-y,y-2*absTol)));


    return result;


    }


MultipleTests ToleranceComparison_Test::AllTests()const
{
    MultipleTests result("ToleranceComparison",
		  "all the tests");
    result.push_back(isEqual_Test());
    result.push_back(isLess_Test());
    return result;
}
}
}
