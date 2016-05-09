#ifndef FILEDIR_H
#define FILEDIR_H

#include <dirent.h>
#include <string>
#include <algorithm>
#include <sys/stat.h>
#include <errno.h>


namespace Markov_IO_New
{

  namespace fdfd {


    using filePredicate=bool(*)(const std::string& fname);

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

      FileDir& begin();
      FileDir& next();

      bool cd(const std::string& dirname);


      std::string FileName()const;

      bool IsDir();
      bool IsFile();

      static char slash();

    private:
      void init();
      std::string dirName_;

      DIR *DIR_;
      dirent*  dirent_;

      struct stat buf_[1];

      int error_;
    };

    std::string getWorkingPath();

    std::string getExecutablePath();

    std::string getExecutableDir();

    std::string getDirectory(std::string path);
    std::string getUpperDirectory(std::string path);


    std::vector<std::string> getDirsInDir(const std::string &dir);


    std::vector<std::string> getFilesInDir(const std::string &dir);


    std::vector<std::string> getFilesInDir(const std::string &dir,filePredicate test);

    std::string getFirstFilesInDir(const std::string &dir,filePredicate test);



    std::string& removeLastSlash(std::string& dirname);


    bool IsDir(const std::string& path);

    bool IsFile(const std::string& path);


    /* some day we might implement them
std::string absolutePath(const std::string& relativePath,
                         const std::string& workingPath=getWorkingPath());

std::string relativePath(const std::string& absolutePath,
                         const std::string& workingPath=getWorkingPath());

*/
  }
}


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

    FileDir& begin();
    FileDir& next();

    bool cd(const std::string& dirname);


    std::string FileName()const;

    bool IsDir();

    static char slash();

  private:
    void init();
    std::string dirName_;

    DIR *DIR_;
    dirent*  dirent_;

    struct stat buf_[1];

    int error_;
  };

  std::string getWorkingPath();

  std::string getExecutablePath();

  std::string getExecutableDir();

  std::string getDirectory(std::string path);
  std::string getUpperDirectory(std::string path);


  std::vector<std::string> getSubDirs(const std::string &dir);

  std::string& removeLastSlash(std::string& dirname);


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
