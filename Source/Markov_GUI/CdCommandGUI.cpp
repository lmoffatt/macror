#include "Markov_GUI/CdCommandGUI.h"

namespace Markov_GUI {

  CdCommandGUI::CdCommandGUI(Markov_Console::Markov_CommandManager *cm, MacrorMainWindow* mw):
    CdCommand(cm),
    mw_(mw)
  {}

  CdCommandGUI::~CdCommandGUI()
  {

  }


  bool CdCommandGUI::run(const std::string &dirName)
  {
      Markov_IO::FileDir d(getCommandManager()->getDir());

        if (dirName.empty())
        {
            output_=d.DirName();
            errorMessage_.clear();
            return true;
        }
        else  if (!d.cd(dirName))
        {
            output_.clear();
            errorMessage_=dirName+" is not a directory";
            return false;
        }
        else
        {
            getCommandManager()->setDir(d.DirName());
            output_=d.DirName();
            errorMessage_.clear();
            mw_->DirHasChanged(QString(d.DirName().c_str()));

            return true;
        }

    }

  }






