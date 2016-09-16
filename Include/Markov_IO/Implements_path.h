#ifndef IMPLEMENTS_PATH_H
#define IMPLEMENTS_PATH_H
#include "Markov_IO/Implements_ComplexVar_New.h"

namespace Markov_IO_New {
  namespace pathName
  {

    namespace fields
    {
      struct extension_field
      {
        typedef std::string myC;
        typedef Implements_Data_Type_New<myC>  vType;

        static std::string myId(){return "extension_field";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "file extension";}
        static std::string myWhatThis() {return "different types of variables";}

      };
    }

    struct types
    {
      struct filenameUsed
      {
        typedef  std::string myC;
        typedef filenameUsed selfType;

        static std::string myId(){return "fileNameUsed";}
        static std::string myId(const std::string& extension){return myId()+"_ext_"+extension;}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "an existant filename identifier";}
        static std::string myWhatThis(){return "an identifier to a type";}

        static bool comply
        (const StructureEnv_New*
         , const myC& x
         , const Implements_Data_Type_New<myC>* self,
         std::string *WhyNot
         , const std::string& objective);

        static std::set<std::string>
        alternativeNext(const StructureEnv_New*,
                        const Implements_Data_Type_New<myC> *self);

        static  std::string
        defaultVal(const StructureEnv_New*cm, const StructureEnv_New* self);

        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm)
        {
          return new Implements_Data_Type_New<myC>
              (myId(),nullptr,false,&comply
               ,&alternativeNext);
        }
        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm, const std::string& ext)
        {
         auto out= new Implements_Data_Type_New<myC>
              (myId(),nullptr,false,&comply
               ,&alternativeNext);
         out->getEnv()->pushVar<fields::extension_field>(ext);
         return out;
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

      };

    void push_Types(StructureEnv_New *cm);



  };

}

}
#endif // IMPLEMENTS_PATH_H
