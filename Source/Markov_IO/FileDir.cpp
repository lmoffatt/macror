#include "Markov_IO/FileDir.h"
#include <stdlib.h>
#include <cstdio>
#include <string>
#include <climits>

#include <unistd.h>


#ifdef __WIN32__

#include <windows.h>
#endif





namespace Markov_IO
{
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

    one.init();
    other.init();
}


void FileDir::init()
{
    // remove possible "\" or "/" last character

    if (dirName_[dirName_.size()]== '\\' )
        dirName_.erase(dirName_.end()--);
    if (dirName_[dirName_.size()]== '/' )
        dirName_.erase(dirName_.end()--);


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

    std::string tmp=this->DirName()+"/"+dirname;
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
;
bool FileDir::operator==(const FileDir& other)const
{
    return dirName_==other.dirName_;
}

;
bool FileDir::operator<(const FileDir& other )const
{
    return dirName_<other.dirName_;
};

const FileDir& FileDir::begin()const
{
    rewinddir(DIR_);
    dirent_=readdir(DIR_);
    error_=errno;
    return *this;
};
const FileDir& FileDir::next()const
{
    dirent_=readdir(DIR_);
    error_=errno;
    return *this;
};
std::string FileDir::FileName()const
{
    return dirent_->d_name;
}

bool FileDir::IsDir()const
{

    const std::string& fname=DirName()+"/"+FileName();
    stat( fname.c_str(), buf_);
    return S_ISDIR( buf_->st_mode);
}


std::string getWorkingPath()
{
    char temp[FILENAME_MAX];
    return ( getcwd(temp, FILENAME_MAX) ? std::string( temp ) : std::string("") );
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
    return path.substr(0,pos+1);
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




}
