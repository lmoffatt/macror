#include "Markov_Console/Markov_Script.h"

namespace Markov_Console
{

    /**
      Run all commands in a script file

      @todo �Parse the file looking for errors?

      */

    Markov_Script::Markov_Script(Markov_CommandManager *cm,
                                 const std::string& file)
    {
        std::ifstream fin;
        fin.open(file.c_str());
        std::string line;
        if (!(!fin))
          while (getline(fin,line))
            {
              std::cout<<line<<std::endl;
              cm->add_tokens(line);
              cm->next_instruction();
            }
        else
          {
            std::cerr<<"file "<<file<<" not found\n";
          }

     }
}
