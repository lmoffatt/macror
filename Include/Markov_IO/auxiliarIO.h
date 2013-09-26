/*!
 */
#ifndef AUXILIARIO_H
#define AUXILIARIO_H

#include <iostream>
#include <sstream>

#include <map>
#include <vector>

#include "Markov_IO/ABC_Object.h"




namespace Markov_IO
{

    /*!
  it waits for an input from io
  */

    char press_any_key_to_continue();


    // temporarily removed
//    /**
//  @brief Vector Insert Operator. It inserts the formatted contents of the vector
//  into an ostream.
//   */
//    template<typename T>
    //    std::ostream& operator<< (std::ostream& s,const std::vector<T>& v);


//    /**
//  @brief Map Insert Operator. It inserts the formatted contents of the map
//  into an ostream.
//   */
//    template<typename K, typename D>
//    std::ostream& operator<< (std::ostream& s,const std::map<K,D>& v);


    /**
@brief Displays in a String the contents of the class T.
*/
    template <class T>
    std::string ToString(const T& x);

    /**



  @brief Extract an object of class T from a string.
  */
    template<class T>
    bool ToValue(const std::string& str,T& value);


    template<class T>
    bool ToValue(const ABC_Object* o,T& value);

    bool ToObject(const std::string& s,ABC_Object*& o);

    std::istream& extract_NaN_safe(std::istream&, double& value);



    std::vector < std::string > LineToWords (const std::string& input_line,
					       const std::string delimiters=
					       " \t\n\v\f\r"
					      );


    void removeEndOfLine(std::string& name);

    std::istream& safeGetline(std::istream& is, std::string& t);


}

#endif // AUXILIARIO_H
