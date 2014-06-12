#ifndef BUFFEREDFUNCTION_H
#define BUFFEREDFUNCTION_H

#include <map>

#include "Markov_IO/ABC_Put.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Mol
{
template<typename T1, typename T2>
class buffered_function: public Markov_IO::ABC_Put
{
public:
/// put
    virtual buffered_function<T1,  T2>* clone() const;

    virtual buffered_function* create() const;
    virtual ~buffered_function() ;
    virtual std::ostream& put(std::ostream& s) const;

    const T2& get_Y(const T1&) const;


    bool has_X(const T1& X) const;
    /// it adds a new value of f(X)=Y, removing the last used value if necessary
    /// if f(X) is already defined it returns false


    void put_Y(const T1& X, const T2& Y);
    //  std::size_t flush_at_least(double ratio_removed);


    std::size_t count(const T1& X) const;


   
    std::size_t size()const;

    /// copy constructor

    buffered_function(const buffered_function& other)=default;
    buffered_function(buffered_function&& other)=default;


    ///default constructor
    buffered_function():buff{}{}


    ///asignment
    buffered_function& operator=(const buffered_function& other)=default;

    buffered_function& operator=(buffered_function&& other)=default;


    void reset();

private:

    void remove_non_repeated_elements(std::size_t min_count);


     mutable std::map<T1,std::pair<T2,std::size_t> > buff;
};



}
#endif // BUFFEREDFUNCTION_H
