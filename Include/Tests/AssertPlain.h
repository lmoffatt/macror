


#ifndef ASSERTPLAIN_H
#define ASSERTPLAIN_H
#include <cstdlib>
#include <iostream>
#include <limits>


inline void catchExit(int message)
{
  std::exit(message);
}


#define ASSERT_VERBOSE false

#if ASSERT_VERBOSE

#ifndef NDEBUG
#   define ASSERT_TRUE(condition) \
    do { \
	if (! (condition)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #condition "` is true failed.\n" \
	    <<__FILE__ << " line " << __LINE__ << ": " << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
	else\
	{ \
	  std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	  std::cerr << "Assertion `" #condition "` is true succed.\n \n"; \
	  std::cerr.precision(6);\
	} \
       } while (false)
#else
#   define ASSERT_TRUE(condition) do { } while (false)
#endif


#ifndef NDEBUG
#   define ASSERT_TRUE_M(condition,message) \
    do { \
	if (! (condition)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #condition "` is true failed.\n" \
	    <<" `" #message "` -> "<<message<<"\n"\
	    <<__FILE__ << " line " << __LINE__ << ": " << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
	else\
	{ \
	std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	std::cerr << "Assertion `" #condition "` is true succed.\n" \
	<<" `" #message "` -> "<<message<<"\n \n";\
	std::cerr.precision(6);\
	} \
       } while (false)
#else
#   define ASSERT_TRUE_M(condition,message) do { } while (false)
#endif

#ifndef NDEBUG
#   define ASSERT_FALSE(condition) \
    do { \
	if (condition) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #condition "` is false  failed.\n" \
	    <<__FILE__ << " line " << __LINE__ << ": " << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
	else\
	{ \
	  std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	  std::cerr << "Assertion `" #condition "` is false  succed.\n"; \
	  std::cerr.precision(6);\
	} \
       } while (false)
#else
#   define ASSERT_FALSE(condition) do { } while (false)
#endif


#ifndef NDEBUG
#   define ASSERT_FALSE_M(condition,message) \
    do { \
	if (condition) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #condition "` is false  failed.\n" \
	    <<" `" #message "` -> "<<message<<"\n"\
	    <<__FILE__ << " line " << __LINE__ << ": " << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
	else\
	{ \
	  std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	  std::cerr << "Assertion `" #condition "` is false  succed.\n" \
	  <<" `" #message "` -> "<<message<<"\n \n";\
	  std::cerr.precision(6);\
	} \
       } while (false)
#else
#   define ASSERT_FALSE_M(condition,message) do { } while (false)
#endif


#ifndef NDEBUG
#   define ASSERT_EQ(expected, actual) \
    do { \
	if (! (expected==actual)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion`" #expected "==" #actual "` failed.\n" \
	    <<" `" #expected  "` ="; \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr<<expected<<" `" #actual  "`  ="<<actual<<"\n"\
	    <<__FILE__ << " line " << __LINE__  << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
	else\
	{ \
	  std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	  std::cerr << "Assertion `" #expected "==" #actual "` succed.\n" \
	  <<" `" #expected  "` ="; \
	  std::cerr<<expected<<" `" #actual  "`  ="<<actual<<"\n \n";\
	  std::cerr.precision(6);\
	} \
       } while (false)
#else
#   define ASSERT_EQ(expected, actual) do { } while (false)
#endif

#ifndef NDEBUG
#   define ASSERT_EQ_M(expected, actual, message) \
    do { \
	if (! (expected==actual)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #expected "==" #actual "` succed.\n" \
	    <<" `" #expected  "`  ="<<expected<<" `" #actual  "`  ="<<actual<<"\n"\
	    <<" `" #message "` -> "<<message<<"\n"\
	    <<__FILE__ << " line " << __LINE__  << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
	else\
	{ \
	  std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	  std::cerr << "Assertion `" #expected "==" #actual "` succed.\n" \
	  <<" `" #expected  "`  ="<<expected<<" `" #actual  "`  ="<<actual<<"\n"\
	  <<" `" #message "` -> "<<message<<"\n \n";\
	  std::cerr.precision(6);\
	} \
       } while (false)
#else
#   define ASSERT_EQ_M(expected, actual,message) do { } while (false)
#endif



#ifndef NDEBUG
#   define ASSERT_NE(expected, actual) \
    do { \
	if ((expected==actual)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #expected "!=" #actual "` failed. \n" \
	    <<" `" #expected  "`  ="<<expected<<" `" #actual  "`  ="<<actual<<"\n"\
	    <<__FILE__ << " line " << __LINE__  << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
	else\
	{ \
	  std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	  std::cerr << "Assertion `" #expected "!=" #actual "` succed. \n" \
	  <<" `" #expected  "`  ="<<expected<<" `" #actual  "`  ="<<actual<<"\n \n";\
	  std::cerr.precision(6);\
	} \
       } while (false)
#else
#   define ASSERT_NE(expected, actual) do { } while (false)
#endif

#ifndef NDEBUG
#   define ASSERT_NE_M(expected, actual, message) \
    do { \
	if ((expected==actual)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #expected "!=" #actual "` failed.\n" \
	    <<" `" #expected  "`  ="<<expected<<" `" #actual  "`  ="<<actual<<"\n"\
	    <<" `" #message "` -> "<<message<<"\n"\
	    <<__FILE__ << " line " << __LINE__  << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
	else\
	{ \
	  std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	  std::cerr << "Assertion `" #expected "!=" #actual "` succed.\n" \
	  <<" `" #expected  "`  ="<<expected<<" `" #actual  "`  ="<<actual<<"\n"\
	  <<" `" #message "` -> "<<message<<"\n \n";\
	  std::cerr.precision(6);\
	} \
       } while (false)
#else
#   define ASSERT_NE_M(expected, actual,messge) do { } while (false)
#endif




#else  //ASSERT_VERBOSE


#ifndef NDEBUG
#   define ASSERT_TRUE(condition) \
    do { \
	if (! (condition)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #condition "` is true failed.\n" \
	    <<__FILE__ << " line " << __LINE__ << ": " << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
       } while (false)
#else
#   define ASSERT_TRUE(condition) do { } while (false)
#endif


#ifndef NDEBUG
#   define ASSERT_TRUE_M(condition,message) \
    do { \
	if (! (condition)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #condition "` is true failed.\n" \
	    <<" `" #message "` -> "<<message<<"\n"\
	    <<__FILE__ << " line " << __LINE__ << ": " << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
       } while (false)
#else
#   define ASSERT_TRUE_M(condition,message) do { } while (false)
#endif

#ifndef NDEBUG
#   define ASSERT_FALSE(condition) \
    do { \
	if (condition) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #condition "` is false  failed.\n" \
	    <<__FILE__ << " line " << __LINE__ << ": " << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
       } while (false)
#else
#   define ASSERT_FALSE(condition) do { } while (false)
#endif


#ifndef NDEBUG
#   define ASSERT_FALSE_M(condition,message) \
    do { \
	if (condition) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #condition "` is false  failed.\n" \
	    <<" `" #message "` -> "<<message<<"\n"\
	    <<__FILE__ << " line " << __LINE__ << ": " << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
       } while (false)
#else
#   define ASSERT_FALSE_M(condition,message) do { } while (false)
#endif


#ifndef NDEBUG
#   define ASSERT_EQ(expected, actual) \
    do { \
	if (! (expected==actual)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #expected "==" #actual "` failed.\n" \
	    <<" `" #expected  "`  ="<<expected<<" `" #actual  "`  ="<<actual<<"\n"\
	    <<__FILE__ << " line " << __LINE__  << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
       } while (false)
#else
#   define ASSERT_EQ(expected, actual) do { } while (false)
#endif

#ifndef NDEBUG
#   define ASSERT_EQ_M(expected, actual, message) \
    do { \
	if (! (expected==actual)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #expected "==" #actual "` failed.\n" \
	    <<" `" #expected  "`  ="<<expected<<" `" #actual  "`  ="<<actual<<"\n"\
	    <<" `" #message "` -> "<<message<<"\n"\
	    <<__FILE__ << " line " << __LINE__  << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
       } while (false)
#else
#   define ASSERT_EQ_M(expected, actual,message) do { } while (false)
#endif



#ifndef NDEBUG
#   define ASSERT_NE(expected, actual) \
    do { \
	if ((expected==actual)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #expected "!=" #actual "` failed. \n" \
	    <<" `" #expected  "`  ="<<expected<<" `" #actual  "`  ="<<actual<<"\n"\
	    <<__FILE__ << " line " << __LINE__  << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
       } while (false)
#else
#   define ASSERT_NE(expected, actual) do { } while (false)
#endif

#ifndef NDEBUG
#   define ASSERT_NE_M(expected, actual, message) \
    do { \
	if ((expected==actual)) { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr << "Assertion `" #expected "!=" #actual "` failed.\n" \
	    <<" `" #expected  "`  ="<<expected<<" `" #actual  "`  ="<<actual<<"\n"\
	    <<" `" #message "` -> "<<message<<"\n"\
	    <<__FILE__ << " line " << __LINE__  << std::endl; \
	    catchExit(EXIT_FAILURE); \
	} \
       } while (false)
#else
#   define ASSERT_NE_M(expected, actual,messge) do { } while (false)
#endif



#ifndef NDEBUG
#   define ASSERT_LESS( actual, limit) \
    do { \
        if (! (actual<limit)) { \
            std::cerr.precision(std::numeric_limits<double>::digits10+2);\
            std::cerr << "Assertion `" #actual "<" #limit "` failed.\n" \
            <<" `" #limit  "`  ="<<limit<<" `" #actual  "`  ="<<actual<<"\n"\
            <<__FILE__ << " line " << __LINE__  << std::endl; \
            catchExit(EXIT_FAILURE); \
        } \
       } while (false)
#else
#   define ASSERT_LESS( actual, limit) do { } while (false)
#endif

#ifndef NDEBUG
#   define ASSERT_LESS_M( actual, limit, message) \
    do { \
        if (! (actual<limit)) { \
            std::cerr.precision(std::numeric_limits<double>::digits10+2);\
            std::cerr << "Assertion `" #actual "<" #limit "` failed.\n" \
            <<" `" #limit  "`  ="<<limit<<" `" #actual  "`  ="<<actual<<"\n"\
            <<" `" #message "` -> "<<message<<"\n"\
            <<__FILE__ << " line " << __LINE__  << std::endl; \
            catchExit(EXIT_FAILURE); \
        } \
       } while (false)
#else
#   define ASSERT_LESS_M( actual, limit, message)do { } while (false)
#endif

#ifndef NDEBUG
#   define ASSERT_LEQ( actual, limit) \
    do { \
        if (! (actual<=limit)) { \
            std::cerr.precision(std::numeric_limits<double>::digits10+2);\
            std::cerr << "Assertion `" #actual "<=" #limit "` failed.\n" \
            <<" `" #limit  "`  ="<<limit<<" `" #actual  "`  ="<<actual<<"\n"\
            <<__FILE__ << " line " << __LINE__  << std::endl; \
            catchExit(EXIT_FAILURE); \
        } \
       } while (false)
#else
#   define ASSERT_LEQ( actual, limit) do { } while (false)
#endif

#ifndef NDEBUG
#   define ASSERT_LEQ_M( actual, limit, message) \
    do { \
        if (! (actual<=limit)) { \
            std::cerr.precision(std::numeric_limits<double>::digits10+2);\
            std::cerr << "Assertion `" #actual "<=" #limit "` failed.\n" \
            <<" `" #limit  "`  ="<<limit<<" `" #actual  "`  ="<<actual<<"\n"\
            <<" `" #message "` -> "<<message<<"\n"\
            <<__FILE__ << " line " << __LINE__  << std::endl; \
            catchExit(EXIT_FAILURE); \
        } \
       } while (false)
#else
#   define ASSERT_LEQ_M( actual, limit, message)do { } while (false)
#endif


#ifndef NDEBUG
#   define ASSERT_GEQ( actual, limit) \
    do { \
        if (! (actual>=limit)) { \
            std::cerr.precision(std::numeric_limits<double>::digits10+2);\
            std::cerr << "Assertion `" #actual ">=" #limit "` failed.\n" \
            <<" `" #limit  "`  ="<<limit<<" `" #actual  "`  ="<<actual<<"\n"\
            <<__FILE__ << " line " << __LINE__  << std::endl; \
            catchExit(EXIT_FAILURE); \
        } \
       } while (false)
#else
#   define ASSERT_GEQ( actual, limit) do { } while (false)
#endif

#ifndef NDEBUG
#   define ASSERT_GEQ_M( actual, limit, message) \
    do { \
        if (! (actual>=limit)) { \
            std::cerr.precision(std::numeric_limits<double>::digits10+2);\
            std::cerr << "Assertion `" #actual ">=" #limit "` failed.\n" \
            <<" `" #limit  "`  ="<<limit<<" `" #actual  "`  ="<<actual<<"\n"\
            <<" `" #message "` -> "<<message<<"\n"\
            <<__FILE__ << " line " << __LINE__  << std::endl; \
            catchExit(EXIT_FAILURE); \
        } \
       } while (false)
#else
#   define ASSERT_GEQ_M( actual, limit, message)do { } while (false)
#endif





#endif //ASSERT_VERBOSE

//#undef ASSERT_VERBOSE

#ifndef NDEBUG
#   define SHOW(message) \
    do { \
	    std::cerr.precision(std::numeric_limits<double>::digits10+2);\
	    std::cerr <<message<<"\n"; \
	    std::cerr << "`"#message "` -> " <<message<<"\n"; \
     } while (false)
#else
#   define SHOW(something) do { } while (false)
#endif





#endif // ASSERTPLAIN_H
