#include "Markov_IO/FileLoadSave.h"
#include <stdlib.h>
#include <cstdio>
#include <string>
#include <climits>

#include <unistd.h>


#ifdef __WIN32__

#include <windows.h>
#endif

namespace Markov_IO_New {

  namespace fd {


    char File::slash()
    {
    #ifdef __linux__
        return '/';
    #endif
    #ifdef __WIN32__
        return '\\';
    #endif


    }

    bool isMacrorFile(const std::__cxx11::string &path,std::string* whyNot,const std::string& objective)
    {
      if(path.find("macror.txt")==path.npos)
        {
          *whyNot=objective+": "+path+" has not macror.txt termination";
          return false;
        }
      else
        return true;
    }

    bool isMacrorFile(const std::__cxx11::string &path)
    {
      if(path.find("macror.txt")==path.npos)
        {
          return false;
        }
      else
        return true;
    }



    std::string getWorkingPath()
    {
      char temp[FILENAME_MAX];
      if (getcwd(temp, FILENAME_MAX))
        {
          std::string res=temp;
          return res;
        }
      else
        return "";
    }


    std::string getExecutablePath()
    {
#ifdef __linux__

      char result[ PATH_MAX ];
      ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
      return std::string( result, (count > 0) ? count : 0 );
#endif
#ifdef __WIN32__
      char result[ MAX_PATH ];
      ::GetModuleFileNameA( NULL, result, MAX_PATH ) ;

      return std::string( result);
#endif
    }



    std::string getDirectory(std::string path)
    {
      std::size_t pos=path.find_last_of("/ \\",path.size()-2);
      return path.substr(0,pos);
    }

    std::string getExecutableDir()
    {
      std::string path=getExecutablePath();
      return getDirectory(path);
    }





    bool isDir(const std::string& path)
    {
      struct stat buf;
      if (stat( path.c_str(), &buf)==0)
        return S_ISDIR( buf.st_mode);
      else
        return false;
    }

    bool isFile(const std::string& path)
    {
      struct stat buf;
      if (stat( path.c_str(), &buf)==0)
        return S_ISREG( buf.st_mode);
      else
        return false;
    }


    std::string& removeLastSlash(std::string& dirname)
    {
      if (!dirname.empty())
        {
          if ((dirname.back()== '\\' )||(dirname.back()== '/' ))
            dirname.pop_back();
        }
      return dirname;
    }




    std::vector<std::string> getDirsInDir(const std::string& dir)
    {
      Directory d(dir);
      std::vector<std::string> subdirs;
      for (auto it=d.begin(); it!=d.end(); ++it)
        {
          if (it->isDir())
            subdirs.push_back(it->name());
        }
      return subdirs;

    }

    std::vector<std::string> getFilesInDir(const std::string& dir)
    {
      Directory d(dir);
      std::vector<std::string> files;
      for (auto it=d.begin(); it!=d.end(); ++it)
        {
          if (it->isFile())
            files.push_back(it->name());
        }
      return files;
    }



    std::vector<std::__cxx11::string> getFilesInDir(const std::__cxx11::string &dir, filePredicate test)
    {
      Directory d(dir);
      std::vector<std::string> files;
      for (auto it=d.begin(); it!=d.end(); ++it)
        {
          if ((it->isFile()&&(*test)(*it)))
            files.push_back(it->name());
        }
      return files;

    }



    std::string getFirstFileInDir(const std::string &dir,filePredicate test)

    {
      Directory d(dir);
      for (auto it=d.begin(); it!=d.end(); ++it)
        {
          if ((it->isFile()&&(*test)(*it)))
            return it->name();
        }
      return "";

    }



    std::vector<std::__cxx11::string> getFilesInDir(const std::__cxx11::string &dir, namePredicate test)
    {
      Directory d(dir);
      std::vector<std::string> files;
      for (auto it=d.begin(); it!=d.end(); ++it)
        {
          if ((it->isFile()&&(*test)(it->name())))
            files.push_back(it->name());
        }
      return files;

    }



    std::string getFirstFileInDir(const std::string &dir,namePredicate test)

    {
      Directory d(dir);
      for (auto it=d.begin(); it!=d.end(); ++it)
        {
          if ((it->isFile()&&(*test)(it->name())))
            return it->name();
        }
      return "";

    }








  }





}

