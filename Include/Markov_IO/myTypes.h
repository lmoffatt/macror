#ifndef MYTYPES_H
#define MYTYPES_H
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/GaussianNoise.h"

#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
namespace Markov_IO_New {
  
  using Markov_Mol_New::Q_Markov_Model;
  using Markov_Mol_New::ABC_Markov_Model;
  namespace _private
  {
    namespace _model {

      struct numStates_Field
      {
        typedef std::size_t myC;
        static std::string myId(){return "numStates";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "number of channel states";}
        static std::string myWhatThis() {return "number of different states in the model";}
      };

      inline
      std::size_t getNumStates(const StructureEnv_New* cm)
      {
        std::size_t numstates;
        std::string WhyNot;
        if (!cm->getValueFromId(numStates_Field::myId(),numstates,&WhyNot,""))
          return 0;
        else return numstates;

      }
      inline
      std::size_t oneDim(const StructureEnv_New*)
      {
        return 1;
      }

      struct Q_matrix_Type{

        typedef Q_matrix_Type selfType;
        typedef double elem;

        typedef ::Markov_LA::M_Matrix<elem> myC;
        typedef Implements_Data_Type_New<myC>  vType;

        static std::string myId(){return "Q_matrix_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return " state transition probability rates or  Q matrices";}
        static std::string myWhatThis() {return "";}

        static bool comply(const StructureEnv_New* cm
                           ,const myC& x
                           ,const vType* self
                           ,std::string *WhyNot
                           , const std::string& objective)
        {
          std::size_t numstates;
            if (!cm->getValueFromId(numStates_Field::myId(),numstates,WhyNot,objective))
            return false;
          if (!Matrix::Comply::Size<elem>(x,numstates,numstates,WhyNot,objective))
            return false;
          if (!Matrix::Comply::OffDiagPositive<elem>(x,WhyNot,objective))
            return false;
          //  if (!Matrix::Comply::RowSumIsZero<elem>(x,WhyNot,objective))
          //    return false;
          if (!Matrix::Comply::FiniteEquilibrium<elem>(x,WhyNot,objective))
            return false;
          return true;
        }
        static const Implements_Data_Type_New<elem>* elementType
        (const StructureEnv_New* cm, std::string *whyNot,const std::string& masterObjective)
        {
          return cm->idToTyped<elem>(Cls<elem>::name(),whyNot,masterObjective);
        }



        static Implements_Data_Type_New<elem>* nextElement (
            const StructureEnv_New* cm
            ,const std::vector<elem>& val,
            std::size_t nrow, std::size_t ncol
            ,std::size_t i, std::size_t j
            ,const Implements_Data_Type_New<myC>* self
            , std::string * whyNot, const std::string& masterObjective,
            Implements_Data_Type_New<elem>* source)
        {
          if (i==j)
            {
              return Real::types::Zero::varType(source);
            }
          else if (j>i)
            {
              return Real::types::nonNegative::varType(source);
            }
          else
            {
                if (val[i+j*ncol]==elem(0))
                {
                  return Real::types::Zero::varType(source);
                }
              else {
                  return Real::types::positive::varType(source);
                }
            }
        }



        static std::size_t getColsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return getNumStates(cm);
        }

        static std::size_t getRowsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return getNumStates(cm);
        }

        static constexpr bool areColsFixed=true;
        static constexpr bool areRowsFixed=true;


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm
                ,std::string* whyNot=nullptr,const std::string& masterObjective="")
        {
          auto d=elementType(cm,whyNot,masterObjective);
          if (d==nullptr)
            return nullptr;
          else
            {
              return new Implements_Data_Type_New<myC>
                  (d,&comply,&nextElement,&getColsNumber,&getRowsNumber
                   ,areColsFixed,areRowsFixed);
            }
        }

        static void push_Types(StructureEnv_New *cm)
        {
          cm->pushRegularType<elem>();
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());
        }


      };


      struct Q_matrix_Field  {
        typedef ::Markov_LA::M_Matrix<double> myC;
        typedef Implements_Data_Type_New<myC> vType;


        static std::string myId(){return "Q_matrix";}
        static std::string myIdType(){return Q_matrix_Type::myId();}
        static std::string myTip(){return "a transition probability rate matrix";}
        static std::string myWhatThis() {return "";}
      };



      struct conductance_vector_Type
      {
        typedef conductance_vector_Type selfType;
        typedef double elem;

        typedef typename ::Markov_LA::M_Matrix<elem> myC;

        typedef Implements_Data_Type_New<myC> vType;
        static std::string myId(){return "conductance_vector_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "the class of relative conductance by state";}
        static std::string myWhatThis() {return "";}

        static bool comply
        (const StructureEnv_New* cm
         ,const myC & x
         ,const vType* self,
         std::string *WhyNot
         , const std::string& objective)
        {
          std::size_t numstates;
          if (!cm->getValueFromId(numStates_Field::myId(),numstates,WhyNot,objective))
            return false;
          if (!Matrix::Comply::Size<elem>(x,numstates,1,WhyNot,objective))
            return false;
          if (!Matrix::Comply::notAllZero<elem>(x,WhyNot,objective))
            return false;

          return true;
        }

        static const Implements_Data_Type_New<elem>* elementType
        (const StructureEnv_New* cm, std::string *whyNot,const std::string& masterObjective)
        {
          return cm->idToTyped<elem>(Cls<elem>::name(),whyNot,masterObjective);
        }

        static Implements_Data_Type_New<elem>* nextElement (
            const StructureEnv_New* cm
            ,const std::vector<elem>& val,
            std::size_t ncol, std::size_t nrow
            ,std::size_t i, std::size_t j
            ,const vType* self, std::string * whyNot, const std::string& masterObjective,
            Implements_Data_Type_New<elem>* source)
        {
          return source;
        }

        static std::size_t getColsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return oneDim(cm);
        }

        static std::size_t getRowsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return getNumStates(cm);
        }

        static constexpr bool areColsFixed=true;
        static constexpr bool areRowsFixed=true;


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm
                ,std::string* whyNot=nullptr,const std::string& masterObjective="")
        {
          auto d=elementType(cm,whyNot,masterObjective);
          if (d==nullptr)
            return nullptr;
          else
            {
              return new Implements_Data_Type_New<myC>
                  (d,&comply,&nextElement,&getColsNumber,&getRowsNumber
                   ,areColsFixed,areRowsFixed);
            }
        }
        static void push_Types(StructureEnv_New *cm)
        {
          cm->pushRegularType<elem>();
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());
        }

      };


      struct conductance_vector_Field
      {

        typedef  ::Markov_LA::M_Matrix<double> myC;
        typedef Implements_Data_Type_New<myC> vType;
        static std::string myId(){return "conductance_vector";}
        static std::string myIdType(){return conductance_vector_Type::myId();}
        static std::string myTip(){return "relative conductance by state";}
        static std::string myWhatThis() {return "";}
      };



      struct agonist_vector_type

      {
        typedef agonist_vector_type selfType;

        typedef std::size_t elem;
        typedef  ::Markov_LA::M_Matrix<elem> myC;
        typedef Implements_Data_Type_New<myC> vType;

        static std::string myId(){return "agonist_vector_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "number of bound agonist at each states";}
        static std::string myWhatThis() {return "";}


        static bool comply
        (const StructureEnv_New* cm
         ,const myC & x
         ,const vType* self,
         std::string *WhyNot
         , const std::string& objective)
        {
            std::size_t numstates;
            if (!cm->getValueFromId(numStates_Field::myId(),numstates,WhyNot,objective))
              return false;
            if (!Matrix::Comply::Size<elem>(x,numstates,1,WhyNot,objective))
              return false;

            return true;
          }

        static const Implements_Data_Type_New<elem>* elementType
        (const StructureEnv_New* cm, std::string *whyNot,const std::string& masterObjective)
        {
          return cm->idToTyped<elem>(Cls<elem>::name(),whyNot,masterObjective);
        }

        static std::size_t getColsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return oneDim(cm);
        }

        static std::size_t getRowsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return getNumStates(cm);
        }

        static constexpr bool areColsFixed=true;
        static constexpr bool areRowsFixed=true;


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm
                ,std::string* whyNot=nullptr,const std::string& masterObjective="")
        {
          auto d=elementType(cm,whyNot,masterObjective);
          if (d==nullptr)
            return nullptr;
          else
            {
              return new Implements_Data_Type_New<myC>
                  (d,&comply,nullptr,&getColsNumber,&getRowsNumber
                   ,areColsFixed,areRowsFixed);
            }
        }


        static void push_Types(StructureEnv_New *cm)
        {
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());
          cm->pushRegularType<elem>();
        }

      };

      struct agonist_vector_field
      {
        typedef  ::Markov_LA::M_Matrix<std::size_t> myC;
        typedef Implements_Data_Type_New<myC> vType;
        typedef agonist_vector_type myType;

        static std::string myId(){return "agonist_vector";}
        static std::string myIdType(){return myType::myId();}
        static std::string myTip(){return "number of bound agonist at each states";}
        static std::string myWhatThis() {return "";}
      };

      struct unitary_conductance_field
      {
        typedef  double myC;
        typedef Implements_Data_Type_New<myC> vType;

        static std::string myId(){return "unitary_conductance";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "number of bound agonist at each states";}
        static std::string myWhatThis() {return "";}
      };



      struct ABC_Markov_Model_type {
        typedef Markov_Mol_New::ABC_Markov_Model myB;
        typedef mp_list<> dependsOn;
        typedef mp_list<>  fieldList;



        static std::string myId(){return Cls<myB*>::name();}
        static std::string myIdType(){return Cls<myB*>::name();}
        static std::string myTip(){return "any model of channel kinetics";}
        static std::string myWhatThis(){return "";}

      public:
        typedef Implements_Data_Type_class<myB*> vType;








        static Implements_Data_Type_New<myB*>*
        varType(const StructureEnv_New* cm)
        {
          return new  Implements_Data_Type_class<myB*>
              ();
        }



      };



      struct Q_Markov_Model_type {
        typedef Markov_Mol_New::ABC_Markov_Model myB;
        typedef Markov_Mol_New::Q_Markov_Model myC;

        static std::string myId(){return Cls<myC*>::name();}
        static std::string myIdType(){return Cls<myC*>::name();}
        static std::string myTip(){return "model of channel kinetics";}
        static std::string myWhatThis(){return "";}

      public:
        typedef Implements_Data_Type_derived_class<myC,myB> vType;
        typedef Implements_Data_Type_class<myB*> baseType;

        static myC* map2obj(const StructureEnv_New* cm,
                            const StructureEnv_New* m
                            ,const vType* v
                            ,std::string* WhyNot,
                            const std::string& masterObjective)
        {
          numStates_Field::myC numSt;
          Q_matrix_Field::myC Q;
          conductance_vector_Field::myC g;
          agonist_vector_field::myC a;
          unitary_conductance_field::myC gamma;

          if (!m->getDataValue<numStates_Field>(numSt,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<Q_matrix_Field>(Q,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<conductance_vector_Field>(g,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<agonist_vector_field>(a,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<unitary_conductance_field>(gamma,WhyNot,masterObjective))
            return nullptr;
          else return new Markov_Mol_New::Q_Markov_Model(Q,g,a,gamma);

        }



        static  StructureEnv_New* objB2map
        (const StructureEnv_New* cm,
         const myB* Q
         ,const baseType* v
         , std::string* WhyNot, const std::string& masterObjective)
        {
          auto f=new StructureEnv_New(cm,Cls<myB*>::name());
          f->pushVar<numStates_Field>(Q->k());
          f->pushVar<Q_matrix_Field>(Q->Q());

          ::Markov_LA::M_Matrix<double> g=Q->g();
          double gamma=::Markov_LA::maxAbs(g);
          g=g/gamma;

          f->pushVar<conductance_vector_Field>(g);
          f->pushVar<agonist_vector_field>(Q->n_bound_agonists());
          f->pushVar<unitary_conductance_field>(gamma);

          return f;
        }


        static  StructureEnv_New* obj2map
        (const StructureEnv_New* cm,
         const myC* Q
         ,const vType* v
         , std::string* WhyNot, const std::string& masterObjective)
        {
          auto f=new StructureEnv_New(cm,Cls<myC*>::name());
          f->pushVar<numStates_Field>(Q->k());
          f->pushVar<Q_matrix_Field>(Q->Q());

          ::Markov_LA::M_Matrix<double> g=Q->g();
          double gamma=Q->gamma();
          g=g/gamma;

          f->pushVar<conductance_vector_Field>(g);
          f->pushVar<agonist_vector_field>(Q->n_bound_agonists());
          f->pushVar<unitary_conductance_field>(gamma);
          return f;
        }
      public:

        static std::vector<std::pair<Implements_Var,bool>> getFields()
        {
          std::vector<std::pair<Implements_Var,bool>> f;
          f.push_back({getMyVar<numStates_Field>(),true});
          f.push_back({getMyVar<Q_matrix_Field>(),true});
          f.push_back({getMyVar<conductance_vector_Field>(),true});
          f.push_back({getMyVar<agonist_vector_field>(),true});
          f.push_back({getMyVar<unitary_conductance_field>(),true});
          return f;
        }


        static Implements_Data_Type_New<myC*>*
        varType(const StructureEnv_New* cm)
        {
          return new  Implements_Data_Type_derived_class<myC,myB>
              (getFields(),&obj2map,&map2obj,nullptr,&objB2map);
        }

        static void push_Types(StructureEnv_New *cm)
        {
          cm->pushRegularType<std::size_t>();
          agonist_vector_type::push_Types(cm);
          conductance_vector_Type::push_Types(cm);
          Q_matrix_Type::push_Types(cm);
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());


        }

      };



      namespace noise

      {


     struct frequency_of_sampling_field
     {
       typedef  Real::types::positive vType;
       typedef  typename vType::myC  myC;

       static std::string myId(){return "frequency_of_sampling";}
       static std::string myIdType(){return vType::myId();}
       static std::string myTip(){return "frequency of sampling referred by the standar deviation";}
       static std::string myWhatThis() {return "";}
     };



      struct standard_deviation_fs_field
          {
            typedef  Real::types::nonNegative vType;
            typedef  typename vType::myC  myC;

            static std::string myId(){return "standard_deviation_at_fs";}
            static std::string myIdType(){return vType::myId();}
            static std::string myTip(){return "standard deviation for "
                  +frequency_of_sampling_field::myId();}
            static std::string myWhatThis() {return "";}
          };


      struct Gaussian_type {
        typedef Markov_Mol_New::ABC_noise myB;
        typedef Markov_Mol_New::gaussian_noise myD;
        typedef Implements_Data_Type_derived_class<myD,myB>  vType;

        typedef Gaussian_type selfType;


        typedef mp_list
        <standard_deviation_fs_field,
         frequency_of_sampling_field
        >    buildFieldList;




        typedef mp_append<mp_list<>,buildFieldList>    fieldList;




        typedef mp_list<> dependsOn;


        static std::string myId(){return Cls<myD*>::name();}
        static std::string myIdType(){return Cls<myD*>::name();}
        static std::string myTip(){return "gaussian noise that depends on the frequency of sampling";}
        static std::string myWhatThis(){return "";}

        template<typename Field>
        static bool isMandatory() {return true;}


        template<typename Field>
        static typename Field::myC get(const myD* x);




        static myD* map2objPtr(const StructureEnv_New* cm,
                            const StructureEnv_New* m
                            ,const vType* v
                            ,std::string* WhyNot,
                            const std::string& masterObjective)
        {

          return map2objPtrTempl<selfType>
              (cm,m,v,WhyNot,masterObjective,buildFieldList());

        }

        static  StructureEnv_New* objPtr2map
        (const StructureEnv_New* cm,
         const myD* x
         ,const vType* v
         , std::string* WhyNot, const std::string& masterObjective)
        {
          return objPtr2mapTempl<selfType>
              (cm,x,v,WhyNot,masterObjective,fieldList());

        }

        static std::vector<std::pair<Implements_Var,bool>> getFields()
        {
          return getFieldsTempl<selfType>(buildFieldList());

        }

        static Implements_Data_Type_New<myD*>*
        varType(const StructureEnv_New* cm)
        {
          return new  Implements_Data_Type_derived_class<myD,myB>
              (getFields(),&objPtr2map,&map2objPtr,nullptr,nullptr);
        }

        struct valueType
        {
          typedef   Gaussian_type      uType;
          typedef Implements_Data_Type_class<myD>  vType;

          typedef  typename uType::fieldList    fieldList;




          typedef uType::dependsOn dependsOn;




          static std::string myId(){return Cls<myD>::name();}
          static std::string myIdType(){return Cls<myD>::name();}

          static std::string myTip(){return uType::myTip();}
          static std::string myWhatThis(){return uType::myWhatThis();}

          static myD map2obj(const StructureEnv_New* cm,
                              const StructureEnv_New* m
                             ,bool & success
                             ,const vType* v
                              ,std::string* WhyNot,
                              const std::string& masterObjective)
          {

            return map2objTempl<selfType>
                (cm,m,success,v,WhyNot,masterObjective,buildFieldList());

          }


          static  StructureEnv_New* obj2map
          (const StructureEnv_New* cm,
           const myD& x
           ,const vType* v
           , std::string* WhyNot, const std::string& masterObjective)
          {
            return obj2mapTempl<selfType>
                (cm,x,v,WhyNot,masterObjective,fieldList());

          }

          static std::vector<std::pair<Implements_Var,bool>> getFields()
          {
            return getFieldsTempl<selfType>(fieldList());

          }

          static Implements_Data_Type_New<myD>*
          varType(const StructureEnv_New* cm)
          {
            return new  Implements_Data_Type_class<myD>
                (getFields(),&obj2map,&map2obj);
          }




        };

      };

      template<>
      inline
      typename frequency_of_sampling_field::myC
      Gaussian_type::get<frequency_of_sampling_field>
      (const typename Gaussian_type::myD* x)
      {
        return x->frequency_of_sampling();
      }

      template<>
      inline
      typename standard_deviation_fs_field::myC
      Gaussian_type::get<standard_deviation_fs_field>
      (const typename Gaussian_type::myD* x)
      {
        return x->standard_deviation();
      }




    }



      struct ABC_Noise_type {
        typedef Markov_Mol_New::ABC_noise myB;
        typedef myB myC;
        typedef mp_list<_model::noise::Gaussian_type> dependsOn;
        typedef mp_list<>  fieldList;



        static std::string myId(){return Cls<myB*>::name();}
        static std::string myIdType(){return Cls<myB*>::name();}
        static std::string myTip(){return "any noise of channel kinetics";}
        static std::string myWhatThis(){return "";}

      public:
        typedef Implements_Data_Type_class<myB*> vType;


        static Implements_Data_Type_New<myB*>*
        varType(const StructureEnv_New* cm)
        {
          return new  Implements_Data_Type_class<myB*>
              ();
        }



      };


      namespace patch

      {

        struct Noise_field
        {
          typedef  ABC_Noise_type vType;
          typedef  typename vType::myB*   myC;

          static std::string myId(){return "Noise_model";}
          static std::string myIdType(){return vType::myId();}
          static std::string myTip(){return "mathematical model of the noise present in the patch";}
          static std::string myWhatThis() {return "";}

        };




      struct Number_of_Channels_field
      {
        typedef  std::size_t   myC;
        typedef  Implements_Data_Type_New<myC> vType;

        static std::string myId(){return "Number_of_Channels";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "list of times when the agonist concentration changed and the concentration reached";}
        static std::string myWhatThis() {return "";}

      };



      struct Channel_Model_field
      {
        typedef  ABC_Markov_Model_type vType;
        typedef  typename vType::myB*   myC;


        static std::string myId(){return "Channel_Model";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "mathematical model of the channel present in the patch";}
        static std::string myWhatThis() {return "";}

      };


      struct PatchModel_type {
        typedef Markov_Mol_New::ABC_PatchModel myB;
        typedef Markov_Mol_New::PatchModel myD;
        typedef Implements_Data_Type_derived_class<myD,myB>  vType;

        typedef PatchModel_type selfType;


        typedef mp_list
        <Channel_Model_field
        ,Number_of_Channels_field
        ,Noise_field>
        buildFieldList;


        typedef mp_append<mp_list<>
        ,buildFieldList>    fieldList;




        typedef mp_list<> dependsOn;


        static std::string myId(){return Cls<myD*>::name();}
        static std::string myIdType(){return Cls<myD*>::name();}
        static std::string myTip(){return "Evolution of the changes in concentrationa and of measured current descibed at low level for a single trace";}
        static std::string myWhatThis(){return "";}

        template<typename Field>
        static bool isMandatory() {return true;}


        template<typename Field>
        static typename Field::myC get(const myD* x);




        static myD* map2objPtr(const StructureEnv_New* cm,
                            const StructureEnv_New* m
                            ,const vType* v
                            ,std::string* WhyNot,
                            const std::string& masterObjective)
        {

          return map2objPtrTempl<selfType>
              (cm,m,v,WhyNot,masterObjective,buildFieldList());

        }








        static  StructureEnv_New* objPtr2map
        (const StructureEnv_New* cm,
         const myD* x
         ,const vType* v
         , std::string* WhyNot, const std::string& masterObjective)
        {
          return objPtr2mapTempl<selfType>
              (cm,x,v,WhyNot,masterObjective,fieldList());

        }

        static std::vector<std::pair<Implements_Var,bool>> getFields()
        {
          return getFieldsTempl<selfType>(fieldList());

        }

        static Implements_Data_Type_New<myD*>*
        varType(const StructureEnv_New* cm)
        {
          return new  Implements_Data_Type_derived_class<myD,myB>
              (getFields(),&objPtr2map,&map2objPtr,nullptr,nullptr);
        }

        struct valueType
        {
          typedef   PatchModel_type      uType;
          typedef Implements_Data_Type_class<myD>  vType;

          typedef  typename uType::fieldList    fieldList;




          typedef uType::dependsOn dependsOn;




          static std::string myId(){return Cls<myD>::name();}
          static std::string myIdType(){return Cls<myD>::name();}

          static std::string myTip(){return uType::myTip();}
          static std::string myWhatThis(){return uType::myWhatThis();}

          static myD map2obj(const StructureEnv_New* cm,
                              const StructureEnv_New* m
                             ,bool & success
                             ,const vType* v
                              ,std::string* WhyNot,
                              const std::string& masterObjective)
          {

            return map2objTempl<selfType>
                (cm,m,success,v,WhyNot,masterObjective,buildFieldList());

          }


          static  StructureEnv_New* obj2map
          (const StructureEnv_New* cm,
           const myD& x
           ,const vType* v
           , std::string* WhyNot, const std::string& masterObjective)
          {
            return obj2mapTempl<selfType>
                (cm,x,v,WhyNot,masterObjective,fieldList());

          }

          static std::vector<std::pair<Implements_Var,bool>> getFields()
          {
            return getFieldsTempl<selfType>(fieldList());

          }

          static Implements_Data_Type_New<myD>*
          varType(const StructureEnv_New* cm)
          {
            return new  Implements_Data_Type_class<myD>
                (getFields(),&obj2map,&map2obj);
          }




        };

      };

      template<>
      inline
       typename Channel_Model_field::myC
      PatchModel_type::get<Channel_Model_field>
      (const typename PatchModel_type::myD* x)
      {
        return x->Model().clone();
      }

      template<>
      inline
       typename Noise_field::myC
      PatchModel_type::get<Noise_field>
      (const typename PatchModel_type::myD* x)
      {
        return x->Noise().clone();
      }

      template<>
      inline
       typename Number_of_Channels_field::myC
      PatchModel_type::get<Number_of_Channels_field>
      (const typename PatchModel_type::myD* x)
      {
        return x->ChannelsCount();
      }




    }


inline
      void push_Types(StructureEnv_New *cm)
      {
       Q_Markov_Model_type::push_Types(cm);
        push_MyTypes<patch::PatchModel_type>(cm);

      }

    }



  };



}



#endif // MYTYPES_H
