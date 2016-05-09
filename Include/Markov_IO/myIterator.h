#ifndef MYITERATOR_H
#define MYITERATOR_H
#include <string>
#include <iterator>
namespace Markov_IO_New {

  namespace iter
  {

    template<class T, class Container>
    class my_random_iterator {
       public:
            typedef typename std::ptrdiff_t difference_type;
            typedef  T value_type;
            typedef  T& reference;
            typedef  T* pointer;
            typedef std::random_access_iterator_tag iterator_category; //or another tag
            my_random_iterator();
            my_random_iterator(const my_random_iterator&);
            ~my_random_iterator();

            my_random_iterator& operator=(const my_random_iterator&);
            bool operator==(const my_random_iterator&) const;
            bool operator!=(const my_random_iterator&) const;
            bool operator<(const my_random_iterator&) const; //optional
            bool operator>(const my_random_iterator&) const; //optional
            bool operator<=(const my_random_iterator&) const; //optional
            bool operator>=(const my_random_iterator&) const; //optional

            my_random_iterator& operator++();
            my_random_iterator operator++(int); //optional
            my_random_iterator& operator--(); //optional
            my_random_iterator operator--(int); //optional
            my_random_iterator& operator+=(std::size_t ); //optional
            my_random_iterator operator+(std::size_t ) const; //optional
            friend my_random_iterator operator+(std::size_t, const my_random_iterator&); //optional
            my_random_iterator& operator-=(std::size_t); //optional
            my_random_iterator operator-(std::size_t) const; //optional
            difference_type operator-(my_random_iterator) const; //optional

            reference operator*() const;
            pointer operator->() const;
            reference operator[](std::size_t) const; //optional
        };


    template<class T, class Container>
    class my_random_const_iterator {
        public:
          typedef typename std::ptrdiff_t difference_type;
          typedef  T value_type;
          typedef const T& const_reference;
          typedef const  T* const_pointer;
          typedef std::random_access_iterator_tag iterator_category; //or another tag

            my_random_const_iterator ();
            my_random_const_iterator (const my_random_const_iterator&);
            my_random_const_iterator (const my_random_iterator<T,Container>&);
            ~my_random_const_iterator();

            my_random_const_iterator& operator=(const my_random_const_iterator&);
            bool operator==(const my_random_const_iterator&) const;
            bool operator!=(const my_random_const_iterator&) const;
            bool operator<(const my_random_const_iterator&) const; //optional
            bool operator>(const my_random_const_iterator&) const; //optional
            bool operator<=(const my_random_const_iterator&) const; //optional
            bool operator>=(const my_random_const_iterator&) const; //optional

            my_random_const_iterator& operator++();
            my_random_const_iterator operator++(int); //optional
            my_random_const_iterator& operator--(); //optional
            my_random_const_iterator operator--(int); //optional
            my_random_const_iterator& operator+=(std::size_t); //optional
            my_random_const_iterator operator+(std::size_t) const; //optional
            friend my_random_const_iterator<T,Container> operator+(std::size_t, const my_random_const_iterator<T,Container>&); //optional
            my_random_const_iterator& operator-=(std::size_t); //optional
            my_random_const_iterator operator-(std::size_t) const; //optional
            difference_type operator-(my_random_const_iterator) const; //optional

            const_reference operator*() const;
            const_pointer operator->() const;
            const_reference operator[](std::size_t) const; //optional
        };


    template<class T, class Container>
    class my_input_iterator {
       public:
            typedef typename std::ptrdiff_t difference_type;
            typedef  T value_type;
            typedef  const T& reference;
            typedef  const T* pointer;
            typedef std::input_iterator_tag iterator_category; //or another tag
            my_input_iterator();
            my_input_iterator(const my_input_iterator&);
            ~my_input_iterator();

            my_input_iterator& operator=(const my_input_iterator&);
            bool operator==(const my_input_iterator&) const;
            bool operator!=(const my_input_iterator&) const;

            my_input_iterator& operator++();
            my_input_iterator operator++(int); //optional

            reference operator*() const;
            pointer operator->() const;
        };


    template<class T, class Container>
    class my_forward_iterator {
       public:
            typedef typename std::ptrdiff_t difference_type;
            typedef  T value_type;
            typedef  T& reference;
            typedef  T* pointer;
            typedef std::forward_iterator_tag iterator_category; //or another tag
            my_forward_iterator();
            my_forward_iterator(const my_forward_iterator&);
            ~my_forward_iterator();

            my_forward_iterator& operator=(const my_forward_iterator&);
            bool operator==(const my_forward_iterator&) const;
            bool operator!=(const my_forward_iterator&) const;

            my_forward_iterator& operator++();
            my_forward_iterator operator++(int); //optional

            reference operator*() const;
            pointer operator->() const;
        };


    template<class T, class Container>
    class my_forward_const_iterator {
        public:
          typedef typename std::ptrdiff_t difference_type;
          typedef  T value_type;
          typedef  const T& const_reference;
          typedef  const T* const_pointer;
          typedef std::forward_iterator_tag iterator_category; //or another tag

            my_forward_const_iterator ();
            my_forward_const_iterator (const my_forward_const_iterator&);
            my_forward_const_iterator (const my_forward_iterator<T,Container>&);
            ~my_forward_const_iterator();

            my_forward_const_iterator& operator=(const my_forward_const_iterator&);
            bool operator==(const my_forward_const_iterator&) const;
            bool operator!=(const my_forward_const_iterator&) const;

            my_forward_const_iterator& operator++();
            my_forward_const_iterator operator++(int); //optional

            const_reference operator*() const;
            const_pointer operator->() const;
            const_reference operator[](std::size_t) const; //optional
        };


    template<class T, class Container>
    class my_bidirectional_iterator {
       public:
            typedef typename std::ptrdiff_t difference_type;
            typedef  T value_type;
            typedef  T& reference;
            typedef  T* pointer;
            typedef std::bidirectional_iterator_tag iterator_category; //or another tag
            my_bidirectional_iterator();
            my_bidirectional_iterator(const my_bidirectional_iterator&);
            ~my_bidirectional_iterator();

            my_bidirectional_iterator& operator=(const my_bidirectional_iterator&);
            bool operator==(const my_bidirectional_iterator&) const;
            bool operator!=(const my_bidirectional_iterator&) const;

            my_bidirectional_iterator& operator++();
            my_bidirectional_iterator operator++(int); //optional
            my_bidirectional_iterator& operator--(); //optional
            my_bidirectional_iterator operator--(int); //optional

            reference operator*() const;
            pointer operator->() const;
        };


    template<class T, class Container>
    class my_bidirectional_const_iterator {
        public:
          typedef typename std::ptrdiff_t difference_type;
          typedef  T value_type;
          typedef  const T& const_reference;
          typedef  const T* const_pointer;
          typedef std::bidirectional_iterator_tag iterator_category; //or another tag

            my_bidirectional_const_iterator ();
            my_bidirectional_const_iterator (const my_bidirectional_const_iterator&);
            my_bidirectional_const_iterator (const my_bidirectional_iterator<T,Container>&);
            ~my_bidirectional_const_iterator();

            my_bidirectional_const_iterator& operator=(const my_bidirectional_const_iterator&);
            bool operator==(const my_bidirectional_const_iterator&) const;
            bool operator!=(const my_bidirectional_const_iterator&) const;

            my_bidirectional_const_iterator& operator++();
            my_bidirectional_const_iterator operator++(int); //optional
            my_bidirectional_const_iterator& operator--(); //optional
            my_bidirectional_const_iterator operator--(int); //optional

            const_reference operator*() const;
            const_pointer operator->() const;
         };




  }


}


#endif // MYITERATOR_H
