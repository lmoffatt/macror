#include "Markov_IO/Object.h"
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixIO.h"
namespace Markov_IO
{

/// copy constructors


template<typename T> Object<T>*
Object<T>::clone() const
{
    return new Object<T>(*this);
}
///  default constructors
template<typename T> Object<T>*
Object<T>::create() const
{return new Object<T>();}

template<typename T>
Object<T>::~Object(){}



template<typename T>
std::string Object<T>::ClassName()
{
    return "composite";
}


template<>
std::string Object<std::string>::ClassName()
{
    return "string";
}



template<>
std::string Object<double>::ClassName()
{
    return "double";
}

template<>
std::string Object<std::size_t>::ClassName()
{
    return "size_t";
}

template<>
std::string Object<bool>::ClassName()
{
    return "bool";
}



template<>
std::string Object<Markov_LA::M_Matrix<double> >::ClassName()
{
    return "doublesMatrix";
}

template<>
std::string Object<Markov_LA::M_Matrix<std::size_t> >::ClassName()
{
    return "size_tsMatrix";
}






template<typename T>
std::string Object<T>::myClass()const
{
    return ClassName();
}





template<typename T>
T& Object<T>::Value(){
    return value_;
}

template<typename T>
const T& Object<T>::Value()const{
    return value_;
}

template<typename T>
Object<T>::Object(T value):
    value_(value){}

template<typename T>
Object<T>::Object(const Object<T>& other):value_(other.value_){}

template<typename T>
Object<T>::Object():value_(){}

template<typename T>
Object<T>& Object<T>::operator=(const Object<T>& other)
{
    if (this!=&other)
    {
	Object<T> tmp(other);
	swap(*this, tmp);
    }
    return *this;
}

template<typename T>
void swap(Object<T>& one, Object<T>& two)
{
    using std::swap;
    swap(one.value_,two.value_);
}

template<typename T>
std::ostream& Object<T>::put(std::ostream &s) const
{
    s<<this->value_;
    return s;
};

template class Object<double>;
template class Object<std::string>;
template class Object<std::size_t>;
template class Object<bool>;
template class Object<Markov_LA::M_Matrix<double> >;
template class Object<Markov_LA::M_Matrix<std::size_t> >;

}

