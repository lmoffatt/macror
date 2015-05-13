/*!
 * @file matrixIO.cpp @brief Implementation of I/O operations on Matrix

 */


#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixIO.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_LA
{
    /**
      @brief Matrix Insert Operator. It inserts the formatted contents of the
      Matrix into an ostream.
      @remarks It uses the operator<<(std::ostream&,T) for formatting the elements
    of the Matrix
      @post all the elements of the same row are separated by spaces in the same
      line
      @post each row is presented on a different line separated by end of line
      character "\\n"
       */
    template<typename T>
    std::ostream& operator<< (std::ostream& s,const M_Matrix<T>& A)
    {
	//s<<"\n pointer value ="<<A._data<<"\n";
        s.precision(std::numeric_limits<T>::digits10+2);
	for (size_t i=0; i<nrows(A); i++)
	{
	    for (size_t j=0; j<ncols(A); j++)
		s<<A(i,j)<<"  ";
	    s<<"\n";
	}
	return s;
    }

    /**
      @brief Matrix Extract Operator. It extract the formatted contents of an
istream into a Matrix
      @pre the input has to follow the conventions of the operator<<()
      @returns an empty Matrix if the format is invalid
      @post if the format is invalid it sends to the std::cerr the values
       */

    template<typename T>
    std::istream& operator>> (std::istream& s, M_Matrix<T>& A)
    {
	if (size(A)!=0)
	{
	    std::string line;
	    for (std::size_t i=0; i<nrows(A); i++)
	    {
		getline(s,line);
		std::istringstream ss(line);

		for (std::size_t j=0; j<ncols(A); j++)
		{
		    T value;
		    if (ss>>value)
		    {
			A(i,j)=value;
		    }
		    else
		    {
			std::string expStr=
				"M_Matrix; Invalid input at the "+
				Markov_IO::ToString<std::size_t>(j+1)+ "th column";
			if (i>0)
			    expStr+=", "+Markov_IO::ToString(i)+"th row";
			expStr+="; the original line is"+line;
			//throw (input_error(expStr));
			std::cout<<expStr<<"\n";
			s.setstate(s.rdstate() | std::ios_base::failbit);
			return s;


		    }
		}
		T value;
		if (ss>>value)
		{
		    std::string expStr=
			    "M_Matrix; Invalid input at the"+
			    Markov_IO::ToString(i+1)+ "th row";
		    expStr+="; too many values (expected, "+
			    Markov_IO::ToString(ncols(A))+")";
		    expStr+="; the original line is"+line;
		    //throw (input_error(expStr));
		    std::cout<<expStr;
		    s.setstate(s.rdstate() | std::ios_base::failbit);
		    return s;

		};

	    };

	    getline(s,line);
	    std::istringstream ss(line);
	    T value;
	    if (ss>>value)
	    {
		std::string expStr=
			"M_Matrix; Invalid input";
		expStr+="; Too many rows (expected, "+
			Markov_IO::ToString(nrows(A))+")";
		expStr+="; the original line is"+line;
		//throw (input_error(expStr));
		std::cout<<expStr;
		s.setstate(s.rdstate() | std::ios_base::failbit);
		return s;

	    };
	    s.clear();


	}
	else
	{
	    std::size_t ncol=0;
	    std::size_t nrow=0;
	    std::string line;
	    getline(s,line);
	    std::istringstream ss(line);
	    std::vector<T> v;
	    T value;
	    while (ss>>value)  v.push_back(value);
	    ncol=v.size();
	    if (ncol>0)
	    {
		++nrow;
		while (true)
		{
		    if (!s.good())
			    break;
		    getline(s,line);
		    //     std::cout<<"line"<<line<<"\n";
		    std::istringstream  ss2(line);

		    if (ss2>>value)
		    {
			v.push_back(value);
			//       std::cout<<"pling caja \n";
		    }
		    else
			break;
		    nrow++;
		    for (size_t k=1; k<ncol; k++)
		    {
			if (ss2>>value) v.push_back(value);
			else
			{
			    std::string expStr=
				    "M_Matrix; Invalid input at the"+
				    Markov_IO::ToString(k+1)+ "th column";
			    if (nrow>1)
				expStr+=", "+
					Markov_IO::ToString(nrow)+"th row";
			    expStr+="; the original line is"+line;
			    //throw (input_error(expStr));
			    std::cout<<expStr;
			    s.setstate(s.rdstate() | std::ios_base::failbit);
			    return s;

			};
		    };
		    if (ss2>>value)
		    {
			std::string expStr=
				"M_Matrix; Invalid input at the"+
				Markov_IO::ToString(nrow)+ "th row";
			expStr+="; too many values (expected, "+
				Markov_IO::ToString(ncol)+")";
			expStr+="; the original line is"+line;
			//       throw (input_error(expStr));
			std::cout<<expStr;
			s.setstate(s.rdstate() | std::ios_base::failbit);
			return s;


		    };
		};
		A=M_Matrix<T>(nrow,ncol,v);
		s.clear();


	    }
	};
	return s;
    }



    template<>
    std::istream& operator>> (std::istream& s, M_Matrix<double>& A)
    {
	if (size(A)!=0)
	{
	    std::string line;
	    for (std::size_t i=0; i<nrows(A); i++)
	    {
		getline(s,line);
		std::istringstream ss(line);

		for (std::size_t j=0; j<ncols(A); j++)
		{
		    double value;
		    if (Markov_IO::extract_NaN_safe(ss,value))
		    {
			A(i,j)=value;
		    }
		    else
		    {
			std::string expStr=
				"M_Matrix; Invalid input at the "+
				Markov_IO::ToString<std::size_t>(j+1)+ "th column";
			if (i>0)
			    expStr+=", "+Markov_IO::ToString(i)+"th row";
			expStr+="; the original line is"+line;
			//throw (input_error(expStr));
			std::cout<<expStr<<"\n";
			s.setstate(s.rdstate() | std::ios_base::failbit);
			return s;


		    }
		}
		double value;
		if (Markov_IO::extract_NaN_safe(ss,value))
		{
		    std::string expStr=
			    "M_Matrix; Invalid input at the"+
			    Markov_IO::ToString(i+1)+ "th row";
		    expStr+="; too many values (expected, "+
			    Markov_IO::ToString(ncols(A))+")";
		    expStr+="; the original line is"+line;
		    //throw (input_error(expStr));
		    std::cout<<expStr;
		    s.setstate(s.rdstate() | std::ios_base::failbit);
		    return s;

		};

	    };

	    getline(s,line);
	    std::istringstream ss(line);
	    double value;
	    if (Markov_IO::extract_NaN_safe(ss,value))
	    {
		std::string expStr=
			"M_Matrix; Invalid input";
		expStr+="; Too many rows (expected, "+
			Markov_IO::ToString(nrows(A))+")";
		expStr+="; the original line is"+line;
		//throw (input_error(expStr));
		std::cout<<expStr;
		s.setstate(s.rdstate() | std::ios_base::failbit);
		return s;

	    };
	    s.clear();


	}
	else
	{
	    std::size_t ncol=0;
	    std::size_t nrow=0;
	    std::string line;
	    getline(s,line);
	    std::istringstream ss(line);
	    std::vector<double> v;
	    double value;
	    while (Markov_IO::extract_NaN_safe(ss,value))  v.push_back(value);
	    ncol=v.size();
	    if (ncol>0)
	    {
		++nrow;
		while (true)
		{
		    if (!s.good())
			    break;
		    getline(s,line);
		    //     std::cout<<"line"<<line<<"\n";
		    std::istringstream  ss2(line);

		    if (Markov_IO::extract_NaN_safe(ss2,value))
		    {
			v.push_back(value);
			//       std::cout<<"pling caja \n";
		    }
		    else
			break;
		    nrow++;
		    for (size_t k=1; k<ncol; k++)
		    {
			if (Markov_IO::extract_NaN_safe(ss2,value)) v.push_back(value);
			else
			{
			    std::string expStr=
				    "M_Matrix; Invalid input at the"+
				    Markov_IO::ToString(k+1)+ "th column";
			    if (nrow>1)
				expStr+=", "+
					Markov_IO::ToString(nrow)+"th row";
			    expStr+="; the original line is"+line;
			    //throw (input_error(expStr));
			    std::cout<<expStr;
			    s.setstate(s.rdstate() | std::ios_base::failbit);
			    return s;

			};
		    };
		    if (Markov_IO::extract_NaN_safe(ss2,value))
		    {
			std::string expStr=
				"M_Matrix; Invalid input at the"+
				Markov_IO::ToString(nrow)+ "th row";
			expStr+="; too many values (expected, "+
				Markov_IO::ToString(ncol)+")";
			expStr+="; the original line is"+line;
			//       throw (input_error(expStr));
			std::cout<<expStr;
			s.setstate(s.rdstate() | std::ios_base::failbit);
			return s;


		    };
		};
		A=M_Matrix<double>(nrow,ncol,v);
		s.clear();


	    }
	};
	return s;
    }




template
std::istream& operator>> (std::istream& s, M_Matrix<double>& A);

template
std::ostream& operator<< (std::ostream& s,const M_Matrix<double>& A);


    template
    std::istream& operator>> (std::istream& s, M_Matrix<int>& A);

    template
    std::ostream& operator<< (std::ostream& s,const M_Matrix<int>& A);

template
std::istream& operator>> (std::istream& s, M_Matrix<std::size_t>& A);

template
std::ostream& operator<< (std::ostream& s,const M_Matrix<std::size_t>& A);

} //end of namespace Markov_LA
