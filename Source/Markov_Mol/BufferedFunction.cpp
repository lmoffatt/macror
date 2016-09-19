#include "Markov_Mol/BufferedFunction.h"
#include "Markov_IO/x_dt.h"
#include "Markov_Mol/MarkovTransitionRate.h"
#include "Markov_Mol/MarkovTransitionStep.h"
#include "Markov_IO/auxiliarIO.h"




namespace Markov_Mol_New
{
    using Markov_IO_New::operator <<;

template<typename T1, typename T2>
buffered_function<T1,  T2>* buffered_function<T1,T2>::clone() const
{
    return new buffered_function< T1,  T2>(*this);
}

///template<typename T1, typename T2> default constructors
template<typename T1, typename T2>
buffered_function<T1,T2>* buffered_function<T1,T2>::create() const
{
    return new buffered_function<T1,T2>();
}

template<typename T1, typename T2>
buffered_function<T1,T2>::~buffered_function() {}


template<typename T1, typename T2>
std::ostream& buffered_function<T1,T2>::put(std::ostream& s) const
{
    s<<"buffered function";

   // s<<"\nBuffer\n"<<buff;

    return s;

}



template<typename T1, typename T2>
void buffered_function<T1,T2>::reset()
{
    buff.clear();
    }



template<typename T1, typename T2>
const T2& buffered_function<T1,T2>::get_Y(const T1& X) const
{
    ++(buff[X]).second;
    return (buff[X]).first;
}


template<typename T1, typename T2>
bool buffered_function<T1,T2>::has_X(const T1& X) const
{
    return  this->buff.find(X)!=buff.end();
}

/// it adds a new value of f(X)=Y, removing the last used value if necessary
/// if f(X) is already defined it returns false

template<typename T1, typename T2>
void buffered_function<T1,T2>::put_Y(const T1& X, const T2& Y)
{
    buff[X]=std::pair<T2,std::size_t>(Y,1);
 }

template<typename T1, typename T2>
std::size_t buffered_function<T1,T2>::count(const T1& X) const
{
    return (buff[X]).second;
}
template<typename T1, typename T2>
std::size_t buffered_function<T1,T2>::size()const
{
    return buff.size();
}

template<typename T1, typename T2>
void buffered_function<T1,T2>::remove_non_repeated_elements(
	std::size_t min_count
	)
{
    typename std::map<T1,std::pair<T2,std::size_t> >::iterator it=buff.begin();
    while ( it!=buff.end())
    {
        if (it->second.second>min_count)
        {
            ++it;
        }
        else
        {
            buff.erase(it++);
        };
    };
}


template class buffered_function<Markov_IO_New::x_dt,Markov_Transition_step>;
template class buffered_function<double,Markov_Transition_rate>;


}







