#ifndef OBJECT_H
#define OBJECT_H

#include "Markov_IO/ABC_Object.h"

namespace Markov_IO
{
template<typename T>
class Object: public ABC_Object
{
public:
    ///virtual copy constructors
    virtual Object<T>* clone() const;
    ///virtual default constructors
    virtual Object<T>* create() const;

    virtual ~Object();

    static std::string ClassName();
    virtual std::string myClass()const;

    virtual T& Value();
    virtual const T& Value()const;

    Object(T value);
    Object(const Object<T>& other);
    Object();

    Object<T>& operator=(const Object<T>& other);

    template<typename T2>
    friend void swap(Object<T2>& one, Object<T2>& two);


    virtual std::ostream& put(std::ostream& s)const;


private:
    T value_;
};

}



#endif // OBJECT_H
