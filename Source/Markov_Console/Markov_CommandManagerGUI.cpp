#include "Markov_Console/Markov_CommandManagerGui.h"
#include <QApplication>


namespace Markov_Console
{

Markov_CommandManagerGui::Markov_CommandManagerGui()
{
}


void Markov_CommandManagerGui::plot(const std::string& plottable_in)
{
    // TODO: switch by variable type
    //Markov_Plot::Plot(getExperiments()[plottable_in]->Get_PlotData(),screen);
}

void Markov_CommandManagerGui::plot_save(const std::string& plottable_in, std::string file)
{
    // TODO: switch by variable type
  //  Markov_Plot::Plot(getExperiments()[plottable_in]->Get_PlotData(),file);
}

void Markov_CommandManagerGui::show_help()
{
    // Call super method
    Markov_CommandManager::show_help();
    std::cout << "   - plot VAR: Plots VAR in screen" << std::endl<< std::endl;
    std::cout << "   - PlotSave VAR FILE_NAME: Plots VAR in FILE_NAME" << std::endl<< std::endl;
}


bool Markov_CommandManagerGui::next_instruction()
{
    if (tokens.size()==0) return false;

    switch (tokens[0].get_token())
    {
    case Token::NAME:
	if (tokens[0].Name()=="plot")
	{
	    if (tokens.size()<2)
		missing_parameter();
	    else
		plot(tokens[1].Name());
	}
        else if (tokens[0].Name()=="plotSave")
            if (tokens.size()<3) missing_parameter();
            else plot_save( tokens[1].Name(), tokens[2].Name() );
    }


    // Else try with all other commands
    Markov_CommandManager::next_instruction();
}

}

