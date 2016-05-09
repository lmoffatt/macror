#ifndef FILELOADSAVE_H
#define FILELOADSAVE_H

#include "Markov_IO/myIterator.h"



#include <string>
#include <cstddef>
#include <dirent.h>
#include <string>
#include <algorithm>
#include <sys/stat.h>
#include <errno.h>



namespace Markov_IO_New {
  namespace fd {


    class File
    {
    public:
      static char slash();


      std::string name()const{return name_;}
      std::string path()const{return dir()+slash()+name();};
      std::string dir()const {return dir_;}
      File()=default;

      File(const std::string& dir, const std::string& name):
        dir_(dir),name_(name) {}

      void setName(const std::string& name){name_=name;}

      bool isFile()const
      {
        struct stat buf[1];
        stat( path().c_str(), buf);
        return S_ISDIR( buf->st_mode);

      }
      bool isDir()const
      {
        struct stat buf[1];
        stat( path().c_str(), buf);
        return S_ISDIR( buf->st_mode);

      }

      friend void swap(File& one,File& two)
      {
        std::swap(one.dir_,two.dir_);
        std::swap(one.name_,two.name_);
      }

    private:
      std::string dir_;
      std::string name_;
    };

    using filePredicate=bool(*)(const File& fname);
    using namePredicate=bool(*)(const std::string& name);


    class my_File_iterator {
    public:
      typedef File T;
      typedef typename std::ptrdiff_t difference_type;
      typedef  T value_type;
      typedef  const T& reference;
      typedef  const T* pointer;
      typedef std::input_iterator_tag iterator_category; //or another tag
      my_File_iterator(const std::string& dirName):
        dirName_(dirName),DIR_(0),dirent_(0),error_(0),curr_(dirName,"")
      {
        DIR_=opendir(dirName_.c_str());
        error_=errno;
        ++*this;
      }
      my_File_iterator():
        dirName_(),DIR_(nullptr),dirent_(nullptr),error_(0),curr_(){}

      my_File_iterator(const my_File_iterator& other):
        my_File_iterator(other.dirName_){}

      ~my_File_iterator()
      {
        closedir(DIR_);
      }

      friend void swap(my_File_iterator& one, my_File_iterator& two)
      {
        std::swap(one.DIR_,two.DIR_);
        std::swap(one.dirName_,two.dirName_);
        std::swap(one.dirent_,two.dirent_);
        std::swap(one.error_,two.error_);
        swap(one.curr_,two.curr_);
      }


      my_File_iterator& operator=(const my_File_iterator& other)
      {
        my_File_iterator tmp(other);
        swap(*this,tmp);
        return *this;
      }
      my_File_iterator& operator=(my_File_iterator&& other)
      {

        swap(*this,other);
        return *this;
      }



      bool operator==(const my_File_iterator& other) const
      {
        return dirent_==other.dirent_;
      }
      bool operator!=(const my_File_iterator& other) const
      {
        return !(*this==other);
      }

      my_File_iterator& operator++()
      {
        if(DIR_)
          {
            dirent_=readdir(DIR_);
            error_=errno;
          }
        if (dirent_!=nullptr)
          {
            curr_.setName(dirent_->d_name);
          }
        else
          curr_.setName("");
        return *this;
      }


      reference operator*() const
      {
        return curr_;
      }
      pointer operator->() const
      {
        return &curr_;
      }
    private:

      std::string dirName_;
      DIR *DIR_;
      dirent*  dirent_;
      int error_;
      File curr_;

    };


    class Directory:public File
    {
    public:
      typedef my_File_iterator const_iterator;
      const_iterator begin()const
      {
        if (isDir())
          return my_File_iterator(path());
        else
          return my_File_iterator();
      }
      const_iterator end()const
      {
        return my_File_iterator();
      }

      Directory(const std::string& dir):
        File(dir,""){}

      Directory(File f):
        File(f.dir(),f.isDir()? f.name():""){}

      ~Directory()
      {

      }

    };


    std::string getWorkingPath();

    std::string getExecutablePath();

    std::string getExecutableDir();

    std::string getDirectory(std::string path);
    std::string getUpperDirectory(std::string path);


    std::vector<std::string> getDirsInDir(const std::string &dir);


    std::vector<std::string> getFilesInDir(const std::string &dir);


    std::vector<std::string> getFilesInDir(const std::string &dir,filePredicate test);

    std::string getFirstFileInDir(const std::string &dir,filePredicate test);

    std::vector<std::string> getFilesInDir(const std::string &dir,namePredicate test);

    std::string getFirstFileInDir(const std::string &dir,namePredicate test);


    std::string& removeLastSlash(std::string& dirname);

    bool isDir(const std::string& path);

    bool isFile(const std::string& path);



    bool isMacrorFile(const std::string& path, std::string* whyNot,const std::string& object);
    bool isMacrorFile(const std::string& path);

  }

}

#endif // FILELOADSAVE_H
