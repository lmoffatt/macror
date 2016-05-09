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
    (const Implements_ComplexVar_New *cm
     , const types::filenameUsed::myC &x
     , const Implements_ComplexVar_New *
     , std::__cxx11::string *WhyNot
     , const std::__cxx11::string &objective)
    {
        std::string wPath=cm->get_Value<vars::workingPath>();
        std::string path=wPath+fd::File::slash()+x;
        if (!fd::IsFile(path))
          {
            *WhyNot=objective+": file"+path+" not found";
            return false;
          }
        else return fd::isMacrorFile(path,WhyNot,objective);
    }

    std::set<std::__cxx11::string> types::filenameUsed::alternativeNext(const Implements_ComplexVar_New *cm, const Implements_ComplexVar_New *)
    {
        std::string wd=cm->get_Value<vars::workingPath>();
        std::vector<std::string> list=fd::getFilesInDir(wd,&fd::isMacrorFile);
        return {list.begin(),list.end()};
    }

    std::__cxx11::string types::filenameUsed::defaultVal(const Implements_ComplexVar_New * cm, const Implements_ComplexVar_New *)
    {
       std::string wd=cm->get_Value<vars::workingPath>();
       fd::FileDir d(wd);
       d.begin();
       return d.FileName();
    }





  }

}
