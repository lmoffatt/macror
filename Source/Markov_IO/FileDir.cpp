#include "Markov_IO/FileDir.h"
#include <stdlib.h>
#include <cstdio>
#include <string>
#include <climits>

#include <unistd.h>


#ifdef __WIN32__

#include <windows.h>
#endif

namespace Markov_IO_New
{
  namespace fdfd {



    /**
  Constructor
  @param dirName Absolute or relative address  to the directory
  @warning if using windows convention use double"\" , ie. "C:\\temp\\"
*/
    FileDir::FileDir(const std::string& dirName):
      dirName_(dirName),DIR_(0),dirent_(0),error_(0)
    {
      init();
    }

    /**
  Default Constructor
  @post It uses getWorkingPath()
  */

    FileDir::FileDir():
      dirName_(getWorkingPath()),
      DIR_(0),dirent_(0),error_(0){
      init();
    }

    /**
  Copy constructor
  */
    FileDir::FileDir(const FileDir& other):
      dirName_(other.dirName_),DIR_(0),dirent_(0),error_(0)
    {
      init();
    }


    /**
  Destructor
  @post It closes the directory
  */
    FileDir::~FileDir()
    {
      closedir(DIR_);
    }

    FileDir& FileDir::operator=(const FileDir& other)
    {
      if (this!=&other)
        {
          FileDir tmp(other);
          swap(*this,tmp);
        }
      return *this;
    }

    void swap( FileDir& one, FileDir& other){

      std::swap(one.dirName_,other.dirName_);
      std::swap(one.DIR_,other.DIR_);
      std::swap(one.dirent_,other.dirent_);
      std::swap(one.buf_,other.buf_);
      std::swap(one.error_,other.error_);


    }



    void FileDir::init()
    {
      // remove possible "\" or "/" last character

      removeLastSlash(dirName_);

      DIR_=opendir(dirName_.c_str());
      error_=errno;
      if(DIR_)
        {
          dirent_=readdir(DIR_);
          error_=errno;
        }
    }

    bool FileDir::cd(const std::string &dirname)
    {
      std::string tmp;
      if (dirname=="..")
        tmp=getDirectory(DirName());
      else tmp=DirName()+slash()+dirname;
      if (::Markov_IO::IsDir(tmp))
        {
          FileDir d(tmp);
          swap(*this,d);
          return true;
        }
      else
        if (::Markov_IO::IsDir(dirname))
          {
            FileDir tmp(dirname);
            swap(*this,tmp);
            return true;
          }
        else
          {
            return false;
          }
    }

    char FileDir::slash()
    {
#ifdef __linux__
      return '/';
#endif
#ifdef __WIN32__
      return '\\';
#endif

    }



    std::vector<std::string> getDirsInDir(const std::string& dir)
    {
      FileDir d(dir);
      std::vector<std::string> subdirs;
      d.begin();
      while(d.next())
        {
          if (d.IsDir())
            subdirs.push_back(d.FileName());
        }
      return subdirs;

    }



    std::vector<std::string> getFilesInDir(const std::string& dir)
    {
      FileDir d(dir);
      std::vector<std::string> files;
      d.begin();
      while(d.next())
        {
          if (d.IsFile())
            files.push_back(d.FileName());
        }
      return files;
    }



    std::vector<std::__cxx11::string> getFilesInDir(const std::__cxx11::string &dir, filePredicate test)
    {
      FileDir d(dir);
      std::vector<std::string> files;
      d.begin();
      while(d.next())
        {
          if (d.IsFile()&&(*test)(d.FileName()))
            files.push_back(d.FileName());
        }
      return files;

    }



    std::string getFirstFilesInDir(const std::string &dir,filePredicate test)

    {
      FileDir d(dir);
      d.begin();
      while(d.next())
        {
          if (d.IsFile()&&(*test)(d.FileName()))
            return d.FileName();
        }
      return "";

    }




    std::string FileDir::DirName()const
    {
      return this->dirName_;
    }

    bool FileDir::NotError()const
    {
      return bool(DIR_);
    }
    bool FileDir::NotEnd()const
    {
      return bool(dirent_);
    }
    FileDir::operator bool()const
    {
      return NotError()&& NotEnd();
    }

    bool FileDir::operator==(const FileDir& other)const
    {
      return dirName_==other.dirName_;
    }

    ;
    bool FileDir::operator<(const FileDir& other )const
    {
      return dirName_<other.dirName_;
    }

    FileDir& FileDir::begin()
    {
      rewinddir(DIR_);
      dirent_=readdir(DIR_);
      error_=errno;
      return *this;
    }

    FileDir& FileDir::next()
    {
      dirent_=readdir(DIR_);
      error_=errno;
      return *this;
    }

    std::string FileDir::FileName()const
    {
      return dirent_->d_name;
    }

    bool FileDir::IsDir()
    {

      const std::string& fname=DirName()+slash()+FileName();
      stat( fname.c_str(), buf_);
      return S_ISDIR( buf_->st_mode);
    }


    bool FileDir::IsFile()
    {

      const std::string& fname=DirName()+slash()+FileName();
      stat( fname.c_str(), buf_);
      return S_ISREG( buf_->st_mode);
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

    std::string getExecutableDir()
    {
      std::string path=getExecutablePath();
      return getDirectory(path);
    }


    std::string getDirectory(std::string path)
    {
      std::size_t pos=path.find_last_of("/ \\",path.size()-2);
      return path.substr(0,pos);
    }





    bool IsDir(const std::string& path)
    {
      struct stat buf;
      if (stat( path.c_str(), &buf)==0)
        return S_ISDIR( buf.st_mode);
      else
        return false;
    }

    bool IsFile(const std::string& path)
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



  }


};

