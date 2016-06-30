#ifndef BUILDBYTOKENTEMPL_H
#define BUILDBYTOKENTEMPL_H


#include "Markov_IO/buildByToken.h"
#include "Markov_IO/Implements_ComplexVar_New.h"



namespace Markov_IO_New {

  template<typename T>
    bool buildByToken<T,false>::pushToken(Token_New t, std::string *whyNot, const std::string &masterObjective)
  {
    const std::string objective=masterObjective+": "+"Token "+t.str()+" was not accepted by ";
    T d;
    if (!t.toValue(d, whyNot,objective))
      {
        return false;
      }
    else if (varType_->isValueInDomain(parent(),d,whyNot,objective))
      {
        x_=d;
        isComplete_=true;
        return true;
      }
    else
      return false;
  }
     template<typename T>
     buildByToken<Markov_LA::M_Matrix<T> ,true>::buildByToken
     (const StructureEnv_New *parent,
      const _private::Implements_Data_Type_New_M_Matrix<T > *typeVar)
        :ABC_BuildByToken(parent)
        ,mystate(S_Init)
        ,dataType_(typeVar)
       ,eleTypeInit_(typeVar->getElementDataType(parent))
        ,eleType_(eleTypeInit_->clone())
        ,eleB_(new buildByToken<T>(parent,eleType_))
        ,x_()
        ,hasFixedCols_(dataType_->hasFixedCols())
      ,  hasFixedRows_(dataType_->hasFixedRows())
      ,runCols_(0),nCols_(dataType_->getNumberOfCols(parent))
      ,nCols_Init_(nCols_)
      ,runRows_(0),nRows_(dataType_->getNumberOfRows(parent))
      ,nRows_Init_(nRows_)
      ,v_{},buffer_(nCols_*nRows_),isComplete_(false)
      {

      }








}
#endif // BUILDBYTOKENTEMPL_H
