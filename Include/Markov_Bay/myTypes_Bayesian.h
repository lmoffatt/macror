#ifndef MYTYPES_BAYESIAN_H
#define MYTYPES_BAYESIAN_H


#include "Markov_IO/ABC_Experiment.h"

#include "Markov_Console/Markov_CommandManager.h"


#include "Markov_Bay/LikelihoodEvaluation.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/VarTempl.h"
namespace Markov_IO_New {

  namespace _private
  {
    namespace _bayesian {




      namespace Likelihood
      {

        struct logLikelihood_field
        {
          typedef  double myC;
          typedef Implements_Data_Type_New<myC>  vType;

          static std::string myId(){return "logLikelihood";}
          static std::string myIdType(){return Cls<myC>::name();}
          static std::string myTip(){return "logLikelihood";}
          static std::string myWhatThis() {return "";}
        };
        struct elogLikelihood_field
        {
          typedef  double myC;
          typedef Implements_Data_Type_New<myC>  vType;

          static std::string myId(){return "expected_logLikelihood";}
          static std::string myIdType(){return Cls<myC>::name();}
          static std::string myTip(){return "expected logLikelihood";}
          static std::string myWhatThis() {return "";}
        };

        struct numberOfSamples_field
        {
          typedef  std::size_t myC;
          typedef Implements_Data_Type_New<myC>  vType;

          static std::string myId(){return "number_of_Samples";}
          static std::string myIdType(){return Cls<myC>::name();}
          static std::string myTip(){return "number of Samples used";}
          static std::string myWhatThis() {return "";}
        };

        struct s2logLikelihood_field
        {
          typedef  double myC;
          typedef Implements_Data_Type_New<myC>  vType;

          static std::string myId(){return "stddev_logLikelihood";}
          static std::string myIdType(){return Cls<myC>::name();}
          static std::string myTip(){return "std dev logLikelihood";}
          static std::string myWhatThis() {return "";}
        };


      struct LikelihoodEvalualtion_type {
        typedef Markov_Bay_New::LikelihoodEvaluation myD;
        typedef myD* myC;
        typedef Implements_Data_Type_class<myD*>  vType;

        typedef LikelihoodEvalualtion_type selfType;


        typedef mp_list
        <logLikelihood_field
        ,elogLikelihood_field
        ,numberOfSamples_field,
        s2logLikelihood_field>    buildFieldList;


        typedef mp_append<mp_list<>
        ,buildFieldList>    fieldList;




        typedef mp_list<> dependsOn;


        static std::string myId(){return Cls<myD>::name();}
        static std::string myIdType(){return Cls<myD>::name();}
        static std::string myTip(){return "Likelihood evaluation values";}
        static std::string myWhatThis(){return "";}

        template<typename Field>
        static bool isMandatory() {return true;}


        template<typename Field>
        static typename Field::myC get(const myD* x);




        static myD* map2obj(const StructureEnv_New* cm,
                            const StructureEnv_New* m
                            ,const vType* v
                            ,std::string* WhyNot,
                            const std::string& masterObjective)
        {

          return map2objPtrTempl<selfType>
              (cm,m,v,WhyNot,masterObjective,buildFieldList());

        }


        static  StructureEnv_New* obj2map
        (const StructureEnv_New* cm,
         const myD* x
         ,const vType* v
         , std::string* WhyNot, const std::string& masterObjective)
        {
          return objPtr2mapTempl<selfType>
              (cm,x,v,WhyNot,masterObjective,fieldList());

        }

        static std::vector<std::pair<Implements_Var,bool>> getFields(const StructureEnv_New* cm)
        {
          return getFieldsTempl<selfType>(cm,fieldList());

        }

        static Implements_Data_Type_New<myD*>*
        varType(const StructureEnv_New* cm)
        {

          return new  Implements_Data_Type_class<myD*>
              (myId(),nullptr,getFields(cm),&obj2map,&map2obj);
        }





      };

      template<>
      inline
      typename logLikelihood_field::myC
      LikelihoodEvalualtion_type::get<logLikelihood_field>
      (const typename LikelihoodEvalualtion_type::myD* x)
      {
        return x->logL();
      }

      template<>
      inline
      typename elogLikelihood_field::myC
      LikelihoodEvalualtion_type::get<elogLikelihood_field>
      (const typename LikelihoodEvalualtion_type::myD* x)
      {
        return x->elogL();
      }

      template<>
      inline
      typename numberOfSamples_field::myC
      LikelihoodEvalualtion_type::get<numberOfSamples_field>
      (const typename LikelihoodEvalualtion_type::myD* x)
      {
        return x->nsamples();
      }

      template<>
      inline
      typename s2logLikelihood_field::myC
      LikelihoodEvalualtion_type::get<s2logLikelihood_field>
      (const typename LikelihoodEvalualtion_type::myD* x)
      {
        return x->s2logL();
      }

    }



      inline void push_Types(StructureEnv_New *cm)
      {
        push_MyTypes<Likelihood::LikelihoodEvalualtion_type>(cm);

      }

    }

  };



}



#endif // MYTYPES_BAYESIAN_H
