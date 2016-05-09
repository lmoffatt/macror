#ifndef IMPLEMENTS_PATH_H
#define IMPLEMENTS_PATH_H
#include "Markov_IO/Implements_ComplexVar_New.h"

namespace Markov_IO_New {
  namespace pathName
  {
    struct types
    {
      struct filenameUsed
      {
        typedef  std::string myC;
        typedef filenameUsed selfType;

        static std::string myId(){return "filenameUsed";}
        static std::string myId(const std::string& extension){return myId()+"_ext_"+extension;}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "a filename identifier";}
        static std::string myWhatThis(){return "an identifier to a type";}

        static bool comply
        (const Implements_ComplexVar_New*
         ,const myC& x
         ,const Implements_ComplexVar_New* ,
         std::string *WhyNot
         , const std::string& objective);

        static std::set<std::string>
        alternativeNext(const Implements_ComplexVar_New*,
                        const Implements_ComplexVar_New*);

        static  std::string
        defaultVal(const Implements_ComplexVar_New*cm, const Implements_ComplexVar_New* self);

        static Implements_Data_Type_New<myC>*
        varType(const Implements_ComplexVar_New* cm)
        {
          return new Implements_Data_Type_New<myC>
              (cm,myId(),myIdType(),myTip(),myWhatThis(),""
               ,&comply
               ,nullptr
               ,&defaultVal
               ,&alternativeNext,nullptr,nullptr);
        }
      };




    };


    struct vars {
      struct workingPath
      {
        typedef  std::string myC;
        typedef workingPath selfType;

        static std::string myId(){return "workingPath";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "current working path";}
        static std::string myWhatThis(){return "an identifier to a type";}

        static std::string getWorkingPath();

        static Implements_Var_New<myC>*
        varValue(const Implements_ComplexVar_New* cm)
        {
          return new Implements_Var_New<myC>
              (cm,myId(),myIdType(),getWorkingPath(),myTip(),myWhatThis());
        }
      };


      struct executablePath
      {
        typedef  std::string myC;
        typedef executablePath selfType;

        static std::string myId(){return "executablePath";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "current executable path";}
        static std::string myWhatThis(){return "an identifier to a type";}

        static std::string getExecutablePath();

        static Implements_Var_New<myC>*
        varValue(const Implements_ComplexVar_New* cm)
        {
          return new Implements_Var_New<myC>
              (cm,myId(),myIdType(),getExecutablePath(),myTip(),myWhatThis());
        }
      };

    };

    void push_Types(Markov_CommandManagerVar* cm);



  };

}


#endif // IMPLEMENTS_PATH_H
