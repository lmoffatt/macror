#ifndef RANDOMDISTRIBUTION_TEST_H
#define RANDOMDISTRIBUTION_TEST_H

#include "Markov_Bay/G_Test.h"
namespace Markov_Bay
{


class RandomDistribution_Test
{
public:
    double G()const;

    double p()const;

    RandomDistribution_Test(const Markov_LA::M_Matrix<std::size_t>& N,
	   const Markov_LA::M_Matrix<double>& P);



    RandomDistribution_Test(const RandomDistribution_Test& other);
    RandomDistribution_Test();
    RandomDistribution_Test& operator=(const RandomDistribution_Test& other);

    friend void swap(RandomDistribution_Test& one, RandomDistribution_Test& other);


private:

Markov_LA::M_Matrix<std::size_t> N_;
Markov_LA::M_Matrix<double> P_;

};
}


#endif // RANDOMDISTRIBUTION_TEST_H
