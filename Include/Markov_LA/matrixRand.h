/*!
 * @file matrixRand.h @brief Custom size Matrices of Random numbers
 */
#ifndef MATRIXRAND_H
#define MATRIXRAND_H

#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixInit.h"

#include <random>
namespace Markov_LA
{

  template<template <typename> class _Vector
           ,typename _IntType = std::size_t>
  class multinomial_distribution;

  template<typename T>
  using My_vec = std::vector<T>;


  template<typename _IntType>
  class multinomial_distribution<My_vec,_IntType>

  {
    static_assert(std::is_integral<_IntType>::value,
                  "template argument not an integral type");

  public:
    /** The type of the range of the distribution. */
    typedef std::vector<_IntType> result_type;
    /** Parameter type. */

    struct param_type
    {
      typedef multinomial_distribution<My_vec,_IntType> distribution_type;
      friend class multinomial_distribution<My_vec,_IntType>;

      explicit
      param_type(_IntType _N, std::vector<double> P )
        : N_(_N), P_(P)
      {
        _M_initialize();
      }

      _IntType
      N() const
      { return N_; }

      const std::vector<double>&
      P() const
      { return P_; }

      friend bool
      operator==(const param_type& __p1, const param_type& __p2)
      { return __p1.N_ == __p2.N_ && __p1.P_ == __p2.P_; }

    private:
      void
      _M_initialize()
      {
        std::size_t n=P_.size();
        rP_=std::vector<double>(n);
        auto s=std::vector<double>(n);
        s[n-1]=P_[n-1];
        for (std::size_t i=1; i<P_.size(); ++i)
          {
            s[n-1-i]=P_[n-1-i]+s[n-i];
          }
        for (std::size_t i=0; i<P_.size(); ++i)
          {
            rP_[i]=P_[i]/s[i];
            P_[i]=P_[i]/s[0];
          }
      }

      _IntType N_;
      std::vector<double> P_;
      std::vector<double> rP_;
      std::binomial_distribution<_IntType> Bi_;

    };



    // constructors and member function
    explicit
    multinomial_distribution(_IntType __t,
                             std::vector<double> __p )
      : _M_param(__t, __p)
    { }



    /**
       * @brief Returns the distribution @p t parameter.
       */
    _IntType
    N() const
    { return _M_param.N(); }

    /**
       * @brief Returns the distribution @p p parameter.
       */
    const std::vector<double>&
    P() const
    { return _M_param.P(); }

    /**
       * @brief Returns the parameter set of the distribution.
       */
    param_type
    param() const
    { return _M_param; }

    /**
       * @brief Sets the parameter set of the distribution.
       * @param __param The new parameter set of the distribution.
       */
    void
    param(const param_type& __param)
    { _M_param = __param; }

    /**
       * @brief Returns the greatest lower bound value of the distribution.
       */
    _IntType
    min() const
    { return 0; }

    /**
       * @brief Returns the least upper bound value of the distribution.
       */
    _IntType
    max() const
    { return _M_param.N(); }

    /**
       * @brief Generating functions.
       */
    template<typename _UniformRandomNumberGenerator>
    result_type
    operator()(_UniformRandomNumberGenerator& __urng)
    { return this->operator()(__urng, _M_param); }

    template<typename _UniformRandomNumberGenerator>
    result_type
    operator()(_UniformRandomNumberGenerator& __urng,
               const param_type& __p)
    {
      result_type out(__p.P().size());
      _IntType Nr=__p.N_;
      for (std::size_t i=0; i< out.size()-1; ++i)
        {
          _IntType ni=__p.Bi_(__urng,{Nr,__p.rP_[i]});
          Nr-=ni;
          out[i]=ni;
        }
      out[out.size()-1]=Nr;
    }


  private:

    param_type _M_param;

  };






  template<typename _IntType>
  class multinomial_distribution<M_Matrix,_IntType>

  {
    static_assert(std::is_integral<_IntType>::value,
                  "template argument not an integral type");

  public:
    /** The type of the range of the distribution. */
    typedef M_Matrix<_IntType> result_type;
    /** Parameter type. */

    struct param_type
    {
      typedef multinomial_distribution<M_Matrix,_IntType> distribution_type;
      friend class multinomial_distribution<M_Matrix,_IntType>;

      explicit
      param_type(const M_Matrix<_IntType>& _N, const M_Matrix<double>& P , bool sumcols=true)
        : N_(_N), P_(P),rP_(M_Matrix<double>(nrows(P),ncols(P)))
        ,sumcols_(sumcols)

      {
        _M_initialize();
      }

      const M_Matrix<_IntType>&
      N() const
      { return N_; }

      void set_P(const M_Matrix<double>&
      _P)
      { P_=_P;
      _M_initialize();
      }

      void set_N(M_Matrix<_IntType>&
      _N)
      {  N_=_N; }

      const M_Matrix<double>&
      P() const
      { return P_; }

      friend bool
      operator==(const param_type& __p1, const param_type& __p2)
      { return __p1.N_ == __p2.N_ && __p1.P_ == __p2.P_; }

    private:
      void
      _M_initialize()
      {
        std::size_t n=ncols(P_);

        auto s=M_Matrix<double>(nrows(P_),ncols(P_));

        for (std::size_t i=0; i<nrows(P_); ++i)
          {
            s(i,n-1)=P_(i,n-1);
            for (std::size_t j=1; j<ncols(P_); ++j)
              {
                s(i,n-1-j)=P_(i,n-1-j)+s(i,n-j);
              }
            for (std::size_t j=0; j<ncols(P_); ++j)
              {
                rP_(i,j)=P_(i,j)/s(i,j);
                P_(i,j)=P_(i,j)/s(i,0);
              }
          }
      }

      M_Matrix<_IntType> N_;
      M_Matrix<double> P_;
      M_Matrix<double> rP_;
      bool sumcols_;
    };


    // constructors and member function
    explicit
    multinomial_distribution(const M_Matrix<_IntType>& __t,
                             const M_Matrix<double>& __p, bool sumrows=true )
      : _M_param(__t, __p,sumrows)
    { }



    /**
         * @brief Returns the distribution @p t parameter.
         */
    const M_Matrix<_IntType>&
    N() const
    { return _M_param.N(); }




    /**
         * @brief Returns the distribution @p p parameter.
         */
    const M_Matrix<double>&
    P() const
    { return _M_param.P(); }


    void set_P(const M_Matrix<double>&
    _P)
    { _M_param.set_P(_P);
    }

    void set_N(M_Matrix<_IntType>&
    _N)
    {
      _M_param.set_N(_N);
    }


    /**
         * @brief Returns the parameter set of the distribution.
         */
    param_type
    param() const
    { return _M_param; }

    /**
         * @brief Sets the parameter set of the distribution.
         * @param __param The new parameter set of the distribution.
         */
    void
    param(const param_type& __param)
    { _M_param = __param; }

    /**
         * @brief Returns the greatest lower bound value of the distribution.
         */
    _IntType
    min() const
    { return 0; }

    /**
         * @brief Returns the least upper bound value of the distribution.
         */
    _IntType
    max() const
    { return totalsum(_M_param.N()); }

    /**
         * @brief Generating functions.
         */
    template<typename _UniformRandomNumberGenerator>
    result_type
    operator()(_UniformRandomNumberGenerator& __urng)
    { return this->operator()(__urng, _M_param); }

    template<typename _UniformRandomNumberGenerator>
    result_type
    operator()(_UniformRandomNumberGenerator& __urng,
               const param_type& _p)
    {
      if (_p.sumcols_)
        {
          std::size_t nc=ncols(_p.P_);
          M_Matrix<_IntType> out(1,nc,0);
          for (std::size_t i=0; i< nrows(_p.P_); ++i)
            {
              _IntType Nr=_p.N_[i];

              for (std::size_t j=1; j< nc-1; ++j)
                {
                  double p=_p.rP_(i,j);
                  auto bi=std::binomial_distribution<_IntType>(Nr,p);
                  _IntType n=bi(__urng);
                  Nr-=n;
                  out(0,j)+=n;
                }
              out(0,nc-1)+=Nr;
            }
          return out;
        }
      else
        {
          std::size_t nc=ncols(_p.P_);
          std::size_t nr=nrows(_p.P_);
          M_Matrix<_IntType> out(nr,nc);
          for (std::size_t i=0; i< nrows(_p.P_); ++i)
            {
              _IntType Nr=_p.N_[i];

              for (std::size_t j=1; j< nc-1; ++j)
                {
                  double p=_p.rP_(i,j);
                  auto bi=std::binomial_distribution<_IntType>(Nr,p);
                  _IntType n=bi(__urng);
                  Nr-=n;
                  out(i,j)=n;
                }
              out(i,nc-1)+=Nr;
            }
          return out;
        }

    }


  private:

    param_type _M_param;

  };




  template<typename T>
  M_Matrix<T>  Rand(std::size_t nrows_,
                    std::size_t ncols_,
                    std::mt19937_64& TR);

  template<typename T>
  M_Matrix<T>  Rand(std::size_t nrows_,std::size_t ncols_, long seed=0);

  template<typename T>
  M_Matrix<T>  Rand(M_Matrix<T> x)
  {
    std::normal_distribution<> normal;
    std::random_device rd;
    std::mt19937_64 sto(rd());





    auto out=zeros<T>(x);
    for (std::size_t i=0; i<size(out); ++i)
      x[i]=normal(sto);
  }

}

#endif // MATRIXRAND_H
