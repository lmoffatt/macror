#include "Markov_Console/Markov_console.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/ExpressionManager.h"
#include "Markov_IO/buildClosureByToken_Templ.h"

#ifdef  __linux__

// for getUnbufChar
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include <vector>



int getUnbufChar(void)
{
  int ch;
  struct termios oldt;
  struct termios newt;
  tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
  newt = oldt; /* copy old settings to new settings */
  newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
  ch = getchar(); /* standard getchar call */
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
  return ch; /*return received char */
}

#endif


#ifndef  __linux__
#include <conio.h>
int getUnbufChar(void)
{
  int ch;
  ch=getch();
  return ch;
}
#endif


std::string incolumns(std::vector<std::string> list,std::size_t colwidth)
{
  std::size_t maxlength=0;
  auto n=list.size();
  for (std::size_t i=0; i< list.size(); ++i)
    if (list.at(i).size()>maxlength)
      maxlength=list.at(i).size();
  maxlength+=2;
  std::size_t ncols=colwidth/maxlength;
  std::size_t nrows=std::ceil(n*1.0/ncols);

  std::string result;
  for (std::size_t i=0; i< nrows; ++i)
    {
      for (std::size_t j=0; j<ncols && i+j*nrows<list.size();j++)
        {

          std::string name=list[i+j*nrows];
          result+=name+std::string(maxlength-name.size(),' ');

        }
      result+="\n";
    }
  return result;


}



namespace Markov_Console_New
{

  //std::string Markov_Console::getline()
  //{
  //    std::string s;
  //    std::getline(std::cin,s);
  //    return s;
  //}

  /// put a string to the output source
  void Markov_Console::put(const std::string& s)
  {
    std::cout<<s;
    currentLine_=currentLine_.substr(0,npos_)+s;
  }

  void Markov_Console::putNewLine()
  {
    std::cout<<"\n";
    currentLine_.clear();
    npos_=0;

  }

  void Markov_Console::freshLine()
  {
    putNewLine();
    put(cm->getProgram().spacer().c_str());
    currentLine_.clear();
    npos_=0;

  }

  void Markov_Console::hideMessage()
  {

  }

  bool Markov_Console::isLineBegin() const
  {
    return npos_==0; // provisional
  }

  bool Markov_Console::isLineEnd() const
  {
    return npos_==currentLine_.size(); // provisional
  }

  std::__cxx11::string Markov_Console::currentLine() const
  {
     return currentLine_;
  }

  char Markov_Console::pop_next_char()
  {
     char out=currentLine_[npos_];
     currentLine_=currentLine_.substr(0,npos_-1);
  }

  void Markov_Console::erase_from_cursor_forward(std::__cxx11::string s)
  {
    erase_from_cursor_forward(s.size());
  }

  void Markov_Console::erase_from_cursor_backward(std::__cxx11::string s)
  {
    erase_from_cursor_forward(-1*(s.size()));
  }

  char Markov_Console::backErase()
  {
    std::cout<<"\b";

  }

  void Markov_Console::move_end()
  {

  }

  void Markov_Console::move_home()
  {

  }

  void Markov_Console::cleanToEndLine()
  {

  }

  void Markov_Console::putTail(const std::__cxx11::string &text)
  {

  }

  std::__cxx11::string Markov_Console::getTail()
  {
     return {};
  }

  void Markov_Console::putError(const std::string &s)
  {
    std::cout<<"\e[31m"<<s<<"\e[31m";
  }

  std::string Markov_Console::getItemFromList(const std::string &title, const std::vector<std::string> &list, bool &ok, std::size_t pos)
  {
    std::cout<<"select an "<<title<<std::endl;
    for (std::string s:list)
      std::cout<<s<<"\t";
    std::cout<<std::endl;
    std::cout<<"current selection [enter to accept; Space to reject]:";

    std::string c=list[pos];
    std::cout<<c;

    while (true)
      {
        Markov_IO_New::Key k=getKey();
        switch (k) {
          case Markov_IO_New::Key_Up:
            if (pos>0)
              {
                auto pos0=pos;
                --pos;
                while ((pos>0)&&((list[pos].front()=='<')||(list[pos].front()=='[')))
                  --pos;
                if ((list[pos].front()=='<')||(list[pos].front()=='['))
                  pos=pos0;
                else
                  {
                    erase_from_cursor_forward(c.size());
                    c=list[pos];
                    std::cout<<c;
                  }
              }
            break;
          case Markov_IO_New::Key_Down:
            if (pos<list.size()-1)
              {
                ++pos;
                auto pos0=pos;
                while (pos<list.size()-1
                       &&((list[pos].front()=='<')||(list[pos].front()=='[')))
                  ++pos;
                if ((list[pos].front()=='<')||(list[pos].front()=='['))
                  pos=pos0;
                else
                  {
                    erase_from_cursor_forward(c.size());
                    c=list[pos];
                    std::cout<<c;
                  }
              }
            break;
          case Markov_IO_New::Key_Return:
          case Markov_IO_New::Key_Enter:
            {
              std::cout<<"\n";
              ok=true;
              return c;
            }
            break;
          case Markov_IO_New::Key_Space:
          case Markov_IO_New::Key_Escape:
            {
              std::cout<<"\n";
              ok=false;
              return {};
            }
            break;

          default:
            break;
          }

      }


  }

  std::string Markov_Console::getItemFromSeveralLists(const std::string &title, const std::map<std::string, std::vector<std::string> > &list, bool &ok, std::size_t current)
  {
   std::vector<std::string> commonList;
   for (std::pair <std::string, std::vector<std::string>> p:list)
     {
       std::string field="<";
       field.append(p.first);
       field.append(">");
       commonList.push_back(field);
       commonList.insert(commonList.end(),p.second.begin(),p.second.end());
     }
   return getItemFromList(title,commonList,ok,current);

  }


  Markov_IO_New::Key Markov_Console::getKey()
  {
    int ch=getUnbufChar();

    if (ch=='\t')
      {
        return Markov_IO_New::Key_Tab;
      }
    else if ((ch=='\b')||(ch==127))
      {
        return Markov_IO_New::Key_Backspace;
      }
    else if ((ch=='\033')||(ch==-32))  //indicates an arrow  key
      {
        char ch2,ch3;
        if (ch=='\033')   // linux

          {
            ch2=getUnbufChar();

            ch3=getUnbufChar();
          }
        else
          {
            ch2=getUnbufChar();
            ch3=' ';
          }
        if (((ch2=='[')&&(ch3=='A'))||(ch2=='H'))
          return Markov_IO_New::Key_Up;

        else if (((ch2=='[')&&(ch3=='B'))||(ch2=='P')) //downkey
          return Markov_IO_New::Key_Down;

        else  if (((ch2=='[')&&(ch3=='C'))||(ch2=='M')) // rightkey
          {
            return Markov_IO_New::Key_Right;
          }
        else  if (((ch2=='[')&&(ch3=='D'))||(ch2=='K')) // leftkey
          {
            return Markov_IO_New::Key_Left;
          }
        else return Markov_IO_New::Key_Unknown;
      }
    else if (ch==' ')
      {
        return Markov_IO_New::Key_Space;
      }
    else if ((ch=='\n')||(ch=='\r'))
      {
        return Markov_IO_New::Key_Return;
      }
    else
      return static_cast<Markov_IO_New::Key>(ch);
  }

#ifdef  __linux__

  std::__cxx11::string Markov_Console::move_cursor(int n)
  {
    if (n>0)
      {
        for (auto i=0;i<n;++i)
          std::cout<<"\033"<<'['<<'C';
      }
    else
      {
        for (auto i=0;i<n;++i)
          std::cout<<"\033"<<'['<<'D';
      }
  }
#endif



#ifndef  __linux__
  void Markov_Console::move_cursor(int n)
  {
    int ch=-32;
    if (n>0)
      {
        for (auto i=0;i<n;++i)
          std::cout<<char(ch)<<'C';
      }
    else
      {
        for (auto i=0;i<n;++i)
          std::cout<<char(ch)<<'D';
      }
  }


#endif


  void Markov_Console::erase_from_cursor_forward(int n)
  {
    if (n<0)
      {
        for (auto i=0;i<-n;++i)
          std::cout<<"\b \b";
      }
    else
      {
        for (auto i=0; i<n; ++i)
          {
            move_cursor(1);
            std::cout<<"\b \b";
          }
      }
  }

  void Markov_Console::showMessage(const std::string &m)
  {
    std::cout<<m<<std::endl;
  }




  /**
  Until user types exit execute the typed commands
  in stdin
  */




  Markov_Console::Markov_Console(Markov_IO_New::Markov_CommandManagerVar *c):
    cm(c),currentLine_(),npos_(0)
  {
    cm->setIO(this);
  }




  int  Markov_Console::exec()
  {
   // put(cm->wellcomeMessage());
    while(true)
      {
        cm->KeyEvent(getKey());
      }
    return 0;
  }




  int Markov_Console::exec(const std::string line)
  {
   Markov_IO_New::StringInput s(line);
   Markov_IO_New::StdOStream o(std::cout);

   cm->run(&s,&o,true);
    return 0;

  }

  std::string Markov_Console::spacer() const
  {
    return cm->getProgram().spacer();
  }


}
