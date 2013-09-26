#ifndef TESTS_H
#define TESTS_H



//class Class_Test;






//template<class T,
//	class UnaryFunction,
//	class EqualityOnArguments,
//	class EqualityOnResults>
//bool Regular_Function_Test(const T& x,
//		  const T& y,
//		  UnaryFunction F,
//		  EqualityOnArguments areArgumentsEqual,
//		  EqualityOnResults areResultsEqual)
//{
//    if (areArgumentsEqual(x,y))
//	assert(areResultsEqual(F(x),F(y)));
//}


//template<class T,
//	class DereferenceOperator, // operator*()
//	class ReferenceFunction,
//	class EqualityPredicateArguments,
//	class EqualityPredicateResults>
//	bool Dereference_Regular_Function_Tests(
//		const T& x,
//		const T& y,
//		DereferenceOperator Deref,
//		ReferenceFunction F,
//		EqualityPredicateArguments EqAr,
//		EqualityPredicateResults EqR)
//{
//    if (EqAr(x,y))
//	assert(EqR(Deref(F(x)),Deref(F(y)));

//};


//template<typename T>
//struct Equality
//{
//    bool operator()(const T& x,const T&y)
//    {
//	return x==y;
//    }
//};





///**
//  Performs tests for regular type
//*/


//template<class T>
//void Equality_tests(const T& x,const  T& y, const T& z)
//{
//    Equality<T> IsEqual;

//    assert(Reflexive_Test(x,IsEqual));

//    assert(Simmetric_Test(x,y,IsEqual));
//    {
//	return(Op(x,y)==Op(y,z));
//    }

//    template<class T,class BinaryPredicate>
//    bool Transitive_Test(const T& x,const T& y,const T& z,BinaryPredicate Pr)
//    {
//	if (Pr(x,y)&&Pr(y,z))
//	    assert(Op(x,z));
//    }



//}




//template <typename T>
//class RegularType_Test
//{
//public:
//     /**

//     */
//      bool RelationalOperators_Consistency(const T& x,const T& y)
//     {
//	 if (x<y)
//	 {
//	     assert(y>x);
//	     assert(!x>=y);
//	     assert((!x>y)&&(!x==y));

//	 }
//	 else if(x>y)
//	 {
//	     assert(y<x);
//	     assert(!x<=y);
//	     assert((!x<y)&&(!x==y));

//	 }
//	 else
//	 {
//	     assert(x==y);
//	     assert(!x!=y);
//	 }
//     }


//     bool Aritmetic_zero(const T& x)
//     {
//	 T z=zero(x);
//	 assert(z==-z);
//	 assert(x+z==x);
//	 assert(x+(-x)==z);
//	 assert(-(-x)==x);

//     }


//      bool Aritmetic_Consistency(const T& x, const T& y)
//     {
//	assert(x+y==y+x);


//	T a=x+y;
//	assert(a-x==y);
//	assert(a-y==x);

//	assert(x+(-y)==x-y);
//	assert(-(x-y)==y-x);

//     }







//     template<class ReferenceFunction>
//     bool Dereference_Regular_Function_Tests(const T& x,
//					     const T& y,
//					     ReferenceFunction F)
//     {
//	 if (x==y)
//	     assert(*(F(x))==*(F(y)));

//     };






// };






#endif // TESTS_H
