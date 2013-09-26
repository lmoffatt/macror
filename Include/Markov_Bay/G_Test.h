#ifndef G_TEST_H
#define G_TEST_H
#include "Markov_LA/Matrix.h"

namespace Markov_Bay
{


class G_Test
{
public:
    double G()const;

    double p()const;

    std::size_t df()const;

    const std::map<double,std::size_t>& count()const;

    const std::map<double,double>& pdf()const;


    G_Test(const Markov_LA::M_Matrix<std::size_t>& N,
           const Markov_LA::M_Matrix<double>& P);

    G_Test(const Markov_LA::M_Matrix<double>& sample,
           const std::map<double,double>& pdf);

    G_Test(const G_Test& other);
    G_Test();
    G_Test& operator=(const G_Test& other);

    friend void swap(G_Test& one, G_Test& other);

    ~G_Test();


private:
    void Compute();


    std::size_t Nt_;
    std::map<double,std::size_t> count_;
    std::map<double,double> pdf_;
    double G_;
    std::size_t df_;
    double p_;

};
}

#endif // G_TEST_H
