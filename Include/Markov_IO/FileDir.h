#ifndef FILEDIR_H
#define FILEDIR_H

#include <dirent.h>
#include <string>
#include <algorithm>
#include <sys/stat.h>
#include <errno.h>


namespace Markov_IO
{

class FileDir
{
public:
    FileDir(const std::string& dirName);
    FileDir();
    FileDir(const FileDir& fileDir);

    FileDir& operator=(const FileDir& other);

    friend void swap( FileDir& one, FileDir& other);

    ~FileDir();

    std::string DirName()const;

    bool NotError()const;
    bool NotEnd()const;

    operator bool()const;
    bool operator==(const FileDir& other)const;
    bool operator<(const FileDir& other )const;

    const FileDir& begin()const;
    const FileDir& next()const;

    bool cd(const std::string& dirname);



    std::string FileName()const;

    bool IsDir()const;

private:
    void init();
    std::string dirName_;

    mutable DIR *DIR_;
    mutable dirent*  dirent_;

    mutable struct stat* buf_;

    mutable int error_;
};

std::string getWorkingPath();



bool IsDir(const std::string& path);

bool IsFile(const std::string& path);


/* some day we might implement them
std::string absolutePath(const std::string& relativePath,
			 const std::string& workingPath=getWorkingPath());

std::string relativePath(const std::string& absolutePath,
			 const std::string& workingPath=getWorkingPath());

*/
}

#endif // FILEDIR_H
