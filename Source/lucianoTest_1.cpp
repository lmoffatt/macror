#include "runTests.h"
#include "Tests/Markov_LA/Matrix_Test_times.h"
#include "Tests/Markov_LA/Matrix_Test.h"
#include "Tests/Markov_LA/ToleranceComparison_Test.h"
#include "Markov_IO/auxiliarIO.h"
#include "Tests/AssertPlain.h"
#include "Tests/Markov_LA/Markov_LA_Tests.h"

int lucianoTest_1(int argc, char *argv[])
{
    using namespace Markov_Test::Markov_LA_Test;
    Markov_LA_Test<double> latest;
    latest.All_Tests();
    Matrix_Test<double> test;

    test.All_Tests();
    Markov_IO::press_any_key_to_continue();

    Markov_Test::Markov_LA_Test::ToleranceComparison_Test toltest;
    toltest.All_Tests();
    Markov_IO::press_any_key_to_continue();


    return 0;
}


int lucianoTest_2(int argc, char *argv[])
{
    Markov_Test::Markov_LA_Test::Matrix_Test_times<double> test(1);
    SHOW(test.Access());
    SHOW(test.Sum());
    SHOW(test.Product());
    SHOW(test.Copy());
    SHOW(test.Inverse());
    SHOW(test.Expm());

    test=Markov_Test::Markov_LA_Test::Matrix_Test_times<double>(2);

    SHOW(test.Access());
    SHOW(test.Sum());
    SHOW(test.Product());
    SHOW(test.Copy());
    SHOW(test.Inverse());
    SHOW(test.Expm());

    test=Markov_Test::Markov_LA_Test::Matrix_Test_times<double>(5);

    SHOW(test.Access());
    SHOW(test.Sum());
    SHOW(test.Product());
    SHOW(test.Copy());
    SHOW(test.Inverse());
    SHOW(test.Expm());

    test=Markov_Test::Markov_LA_Test::Matrix_Test_times<double>(10);

    SHOW(test.Access());
    SHOW(test.Sum());
    SHOW(test.Product());
    SHOW(test.Copy());
    SHOW(test.Inverse());
    SHOW(test.Expm());

    Markov_IO::press_any_key_to_continue();

    return 0;
}



