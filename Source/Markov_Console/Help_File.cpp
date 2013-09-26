#include <fstream>
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"



namespace Markov_Console
{

std::string HelpFile(const std::string& filename)
{
    std::string helppath="help_files/"+filename;
    std::fstream f(helppath.c_str());
    std::string hlptxt;
    std::string line;
    while (Markov_IO::safeGetline(f,line))
	if (line[0]!='>')
	   hlptxt+=line+"\n";
    return hlptxt;


}

}
