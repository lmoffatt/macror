#include "Markov_Console/Markov_console.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_Script.h"
#include "Markov_Console/ExpressionManager.h"

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



namespace Markov_Console
{

  //std::string Markov_Console::getline()
  //{
  //    std::string s;
  //    std::getline(std::cin,s);
  //    return s;
  //}

  /// put a string to the output source
  void Markov_Console::put(const std::string& s) const
  {
    std::cout<<s;
  }

  void Markov_Console::putError(const std::string &s)const
  {
    std::cerr<<s;
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
        Markov_IO::Key k=getKey();
        switch (k) {
          case Markov_IO::Key_Up:
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
          case Markov_IO::Key_Down:
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
          case Markov_IO::Key_Return:
          case Markov_IO::Key_Enter:
            {
              std::cout<<"\n";
              ok=true;
              return c;
            }
            break;
          case Markov_IO::Key_Space:
          case Markov_IO::Key_Escape:
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


  Markov_IO::Key Markov_Console::getKey()
  {
    int ch=getUnbufChar();

    if (ch=='\t')
      {
        return Markov_IO::Key_Tab;
      }
    else if ((ch=='\b')||(ch==127))
      {
        return Markov_IO::Key_Backspace;
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
          return Markov_IO::Key_Up;

        else if (((ch2=='[')&&(ch3=='B'))||(ch2=='P')) //downkey
          return Markov_IO::Key_Down;

        else  if (((ch2=='[')&&(ch3=='C'))||(ch2=='M')) // rightkey
          {
            return Markov_IO::Key_Right;
          }
        else  if (((ch2=='[')&&(ch3=='D'))||(ch2=='K')) // leftkey
          {
            return Markov_IO::Key_Left;
          }
        else return Markov_IO::Key_Unknown;
      }
    else if (ch==' ')
      {
        return Markov_IO::Key_Space;
      }
    else if ((ch!='\n')&&(ch!='\r'))
      {
        return Markov_IO::Key_Return;
      }
    else
      return static_cast<Markov_IO::Key>(ch);
  }

#ifdef  __linux__

  void Markov_Console::move_cursor(int n)
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


  Markov_Console::Markov_Console(Markov_CommandManager *c, const std::string& fileCommandName):
    cm(c)
  {
    cm->setIO(this);
    std::string commandLine;
    std::string commandWord;
    std::size_t ncols=80;
    std::string tail;

    if (fileCommandName.empty())
      {
        char ch,ch0=' ';
        std::cout <<cm->wellcomeMessage();
        while(true)
          {
            std::cout<<">>";
            commandWord.clear();
            commandLine.clear();
            ch=0;
            while ((ch!='\n')&&(ch!='\r'))
              {
                ch=getUnbufChar();
                if (ch=='\t')
                  {
                    std::vector<std::string> res=cm->complete(commandWord);
                    if ((res.size()==1)&&(res.front()[0]!='<')&&(res.front()[0]!='['))
                      {
                        std::string tail=Autocomplete::suggestedCharacters(res,commandWord);
                        std::cout<<tail;
                        std::cout.flush();
                        commandWord+=tail;
                      }
                    else if(res.size()>0)
                      {
                        if (ch0=='\t')
                          {

                            std::string tail=Autocomplete::suggestedCharacters(res,commandWord);
                            commandWord+=tail;
                            std::cout<<"\n"<<incolumns(res,ncols)<<">>"<<commandLine+commandWord;
                          }
                      }

                  }
                else if ((ch=='\b')||(ch==127))
                  {
                    if (!commandWord.empty())
                      {
                        commandWord.pop_back();
                        std::cout<<'\b';
                        std::cout<<' ';
                        std::cout<<'\b';
                      }


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
                    if ((((ch2=='[')&&(ch3=='A'))||(ch2=='H'))||  //upkey
                        (((ch2=='[')&&(ch3=='B'))||(ch2=='P'))) //downkey
                      {
                        std::string tail0=tail;
                        if ((ch3=='A')||(ch2=='H'))
                          tail=cm->getH().up(commandWord);
                        else
                          tail=cm->getH().down(commandWord);

                        if (tail0.size()>tail.size())
                          {
                            std::cout<<tail<<std::string(tail0.size()-tail.size(),' ');
                            std::cout.flush();
                            if (ch=='\033')
                              for (std::size_t i=0; i<tail0.size(); ++i)
                                std::cout<<'\033'<<'['<<'D';
                            else
                              for (std::size_t i=0; i<tail0.size(); ++i)
                                std::cout<<'\b';
                            std::cout.flush();
                          }
                        else
                          {
                            std::cout<<tail;
                            std::cout.flush();
                            if (ch=='\033')
                              for (std::size_t i=0; i<tail.size(); ++i)
                                std::cout<<'\033'<<'['<<'D';
                            else
                              for (std::size_t i=0; i<tail.size(); ++i)
                                std::cout<<'\b';

                            std::cout.flush();
                          }
                      }
                    else  if (((ch2=='[')&&(ch3=='C'))||(ch2=='M')) // rightkey
                      {
                        if (!tail.empty())
                          {
                            if (ch=='\033')
                              std::cout<<'\033'<<'['<<'C';
                            else
                              std::cout<<tail.front();
                            std::cout.flush();
                            commandWord+=tail.front();
                            tail=tail.substr(1);
                          }

                      }
                    else  if (((ch2=='[')&&(ch3=='D'))||(ch2=='K')) // leftkey
                      {
                        if (!commandWord.empty())
                          {
                            if (ch=='\033')
                              std::cout<<'\033'<<'['<<'D';
                            else
                              std::cout<<'\b';
                            std::cout.flush();
                            tail=commandWord.back()+tail;
                            commandWord.pop_back();
                          }
                      }
                  }
                else if (ch==' ')
                  {
                    std::cout<<ch;
                    std::string err=cm->add_single_token(commandWord);
                    if (!err.empty())
                      {
                        std::cout<<"\n"<<err<<">>"<<commandLine;
                      }
                    else
                      commandLine+=commandWord+ch;
                    commandWord.clear();

                  }
                else if ((ch!='\n')&&(ch!='\r'))
                  {
                    std::cout<<ch;
                    commandWord+=ch;
                  }
                else  // new line
                  {
                    std::cout<<'\n';
                    commandLine+=commandWord+tail;
                    tail.clear();
                    commandWord.clear();
                    cm->getH().reset();
                  }
                ch0=ch;
              }
            ch=0;
            // getline(std::cin,commandLine);
            cm->add_tokens(commandLine);
            if (cm->next_instruction())
              cm->getH().push_back(commandLine);
            cm->clear_tokens();
            commandLine.clear();
          }
      }

    else
      {
        Markov_Script ms(cm,fileCommandName);
        commandLine="exit";
        cm->add_tokens(commandLine);
        cm->next_instruction();
      }
  }


  Markov_Console::Markov_Console(Markov_CommandManagerVar *c, const std::string& fileCommandName):
    cmV(c)
  {
    cmV->setIO(this);
    std::string commandLine;
    std::string commandWord;
    std::size_t ncols=80;
    std::string tail;

    if (fileCommandName.empty())
      {
        char ch,ch0=' ';
        std::cout <<cm->wellcomeMessage();
        while(true)
          {
            std::cout<<">>";
            commandWord.clear();
            commandLine.clear();
            ch=0;
            while ((ch!='\n')&&(ch!='\r'))
              {
                ch=getUnbufChar();
                if (ch=='\t')
                  {
                    std::vector<std::string> res=cm->complete(commandWord);
                    if ((res.size()==1)&&(res.front()[0]!='<')&&(res.front()[0]!='['))
                      {
                        std::string tail=Autocomplete::suggestedCharacters(res,commandWord);
                        std::cout<<tail;
                        std::cout.flush();
                        commandWord+=tail;
                      }
                    else if(res.size()>0)
                      {
                        if (ch0=='\t')
                          {

                            std::string tail=Autocomplete::suggestedCharacters(res,commandWord);
                            commandWord+=tail;
                            std::cout<<"\n"<<incolumns(res,ncols)<<">>"<<commandLine+commandWord;
                          }
                      }

                  }
                else if ((ch=='\b')||(ch==127))
                  {
                    if (!commandWord.empty())
                      {
                        commandWord.pop_back();
                        std::cout<<'\b';
                        std::cout<<' ';
                        std::cout<<'\b';
                      }


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
                    if ((((ch2=='[')&&(ch3=='A'))||(ch2=='H'))||  //upkey
                        (((ch2=='[')&&(ch3=='B'))||(ch2=='P'))) //downkey
                      {
                        std::string tail0=tail;
                        if ((ch3=='A')||(ch2=='H'))
                          tail=cm->getH().up(commandWord);
                        else
                          tail=cm->getH().down(commandWord);

                        if (tail0.size()>tail.size())
                          {
                            std::cout<<tail<<std::string(tail0.size()-tail.size(),' ');
                            std::cout.flush();
                            if (ch=='\033')
                              for (std::size_t i=0; i<tail0.size(); ++i)
                                std::cout<<'\033'<<'['<<'D';
                            else
                              for (std::size_t i=0; i<tail0.size(); ++i)
                                std::cout<<'\b';
                            std::cout.flush();
                          }
                        else
                          {
                            std::cout<<tail;
                            std::cout.flush();
                            if (ch=='\033')
                              for (std::size_t i=0; i<tail.size(); ++i)
                                std::cout<<'\033'<<'['<<'D';
                            else
                              for (std::size_t i=0; i<tail.size(); ++i)
                                std::cout<<'\b';

                            std::cout.flush();
                          }
                      }
                    else  if (((ch2=='[')&&(ch3=='C'))||(ch2=='M')) // rightkey
                      {
                        if (!tail.empty())
                          {
                            if (ch=='\033')
                              std::cout<<'\033'<<'['<<'C';
                            else
                              std::cout<<tail.front();
                            std::cout.flush();
                            commandWord+=tail.front();
                            tail=tail.substr(1);
                          }

                      }
                    else  if (((ch2=='[')&&(ch3=='D'))||(ch2=='K')) // leftkey
                      {
                        if (!commandWord.empty())
                          {
                            if (ch=='\033')
                              std::cout<<'\033'<<'['<<'D';
                            else
                              std::cout<<'\b';
                            std::cout.flush();
                            tail=commandWord.back()+tail;
                            commandWord.pop_back();
                          }
                      }
                  }
                else if (ch==' ')
                  {
                    std::cout<<ch;
                    std::string err=cm->add_single_token(commandWord);
                    if (!err.empty())
                      {
                        std::cout<<"\n"<<err<<">>"<<commandLine;
                      }
                    else
                      commandLine+=commandWord+ch;
                    commandWord.clear();

                  }
                else if ((ch!='\n')&&(ch!='\r'))
                  {
                    std::cout<<ch;
                    commandWord+=ch;
                  }
                else  // new line
                  {
                    std::cout<<'\n';
                    commandLine+=commandWord+tail;
                    tail.clear();
                    commandWord.clear();
                    cm->getH().reset();
                  }
                ch0=ch;
              }
            ch=0;
            // getline(std::cin,commandLine);
            cm->add_tokens(commandLine);
            if (cm->next_instruction())
              cm->getH().push_back(commandLine);
            cm->clear_tokens();
            commandLine.clear();
          }
      }

    else
      {
        Markov_Script ms(cm,fileCommandName);
        commandLine="exit";
        cm->add_tokens(commandLine);
        cm->next_instruction();
      }
  }




  int  Markov_Console::exec()
  {
    put(cm->wellcomeMessage());
    while(true)
      {
        cm->KeyEvent(getKey());
      }
    return 0;
  }




  int Markov_Console::exec(const std::string fileCommandName)
  {
    Markov_Script ms(cm,fileCommandName);
    std::string commandLine="exit";
    cm->add_tokens(commandLine);
    cm->next_instruction();
    return 0;

  }

  std::__cxx11::string Markov_Console::spacer() const
  {
    return cmV->getProgram().spacer();
  }


}
