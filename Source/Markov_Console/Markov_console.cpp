#include "Markov_Console/Markov_console.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_Script.h"

#ifdef  __linux__

// for getUnbufChar
#include <stdio.h>
#include <unistd.h>
#include <termios.h>


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

int newInputArise()
{

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

std::string Markov_Console::getline()
{
    std::string s;
    std::getline(std::cin,s);
    return s;
}

char Markov_Console::getchar()
{
    return getUnbufChar();
}

/// put a string to the output source
void Markov_Console::put(const std::string& s)
{
    std::cout<<s;
}

void Markov_Console::putError(const std::string &s)
{
    std::cerr<<s;
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




}
