#include <fstream>
#include "Markov_Console/Markov_consoleTest.h"
#include "Markov_Console/Help_File.h"
#include "Markov_Console/Markov_Script.h"




namespace Markov_Console
{

  /**
  Until user types exit execute the typed commands
  in stdin
  */
  Markov_ConsoleTest::Markov_ConsoleTest(const std::string& fileCommandName)
  {
    std::string commandLine;
    std::string commandWord;
    std::size_t ncols=80;

    std::cout<<"MacroRConsole_Test 0.1."<<cm.ver()<<"\n";
    if (fileCommandName.empty())
      {
        char ch,ch0;
        std::cout <<cm.wellcomeMessage();
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
                      std::vector<std::string> res=cm.complete(commandWord);
                      if ((res.size()==1)&&(res.front()[0]!='<'))
                      {
                        std::string tail=res.at(0).substr(commandWord.size());
                        std::cout<<tail;
                        commandWord=res.at(0);
                      }
                    else if(res.size()>0)
                      {
                        if (ch0=='\t')

                          std::cout<<"\n"<<incolumns(res,ncols)<<">>"<<commandLine+commandWord;
                     }

                  }
                else if ((ch=='\b')||(ch==127))
                  {
                    if (!commandWord.empty())
                      {
                        commandWord.pop_back();
                        std::cout<<'\b';
                      }


                  }
                else if (ch==' ')
                  {
                    std::cout<<ch;
                    std::string err=cm.add_single_token(commandWord);
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
                else
                  {
                    std::cout<<'\n';
                    commandLine+=commandWord;
                    commandWord.clear();
                  }
                ch0=ch;
              }
            ch=0;
            // getline(std::cin,commandLine);
            cm.add_tokens(commandLine);
            commandLine.clear();
            cm.next_instruction();
          }
      }

    else
      {
        Markov_Script ms(cm,fileCommandName);
        commandLine="exit";
        cm.add_tokens(commandLine);
        cm.next_instruction();
      }
  }
}
