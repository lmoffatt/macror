#include "Markov_IO/Implements_path.h"


#include "Markov_IO/FileDir.h"
#include "Markov_IO/FileLoadSave.h"
#include <unistd.h>
#include <limits.h>

#ifdef __WIN32__

#include <windows.h>
#endif

namespace Markov_IO_New {
  namespace pathName {

    std::__cxx11::string vars::workingPath::getWorkingPath()
    {
      return fd::getWorkingPath();
    }

    std::__cxx11::string vars::executablePath::getExecutablePath()
    {
      return fd::getExecutablePath();
    }

    bool types::filenameUsed::comply
    (const StructureEnv_New *cm
     , const types::filenameUsed::myC &x
     , const Implements_Data_Type_New<myC>* self
     , std::__cxx11::string *WhyNot
     , const std::__cxx11::string &objective)
    {
      std::string wPath=cm->getDataValueS<vars::workingPath>();
      std::string ext=self->getEnv()->getDataValueS<fields::extension_field>();
      std::string path=wPath+fd::File::slash()+x;
      if (!fd::isFile(path))
        {
          *WhyNot=objective+": file"+path+" not found";
          return false;
        }
      else if (ext.empty())
        return true;
      else
        return fd::hasExtension(x,ext,WhyNot,objective);
    }

    std::set<std::__cxx11::string> types::filenameUsed::alternativeNext(const StructureEnv_New *cm, const Implements_Data_Type_New<myC> *self)
    {
      std::string wd=cm->getDataValueS<vars::workingPath>();
      std::string ext=self->getEnv()->getDataValueS<fields::extension_field>();


      std::vector<std::string> list=fd::getFilesInDir
          (wd,[&ext](const fd::File& f)->bool
      { return fd::hasExtension(f.path(),ext);});

      return {list.begin(),list.end()};
    }

    std::__cxx11::string types::filenameUsed::defaultVal(const StructureEnv_New * cm, const StructureEnv_New *self)
    {
      std::string wd=cm->getDataValueS<vars::workingPath>();
      std::string ext=self->getDataValueS<fields::extension_field>();
      return fd::getFirstFileInDir(
            wd
            ,[&ext](const fd::File& f)->bool
      { return fd::hasExtension(f.path(),ext);}
      );
    }





  }

}
