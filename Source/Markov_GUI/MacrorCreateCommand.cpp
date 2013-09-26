
#include <string>
#include  <QInputDialog>
#include <QDir>
#include <QString>

#include "Markov_GUI/MacrorCreateCommand.h"
#include "Markov_GUI/CreateQModelWizard.h"
#include "Markov_GUI/CreateWizard.h"
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/PatchModel.h"

///  destructor
MacrorCreateCommand::~MacrorCreateCommand(){}



MacrorCreateCommand::MacrorCreateCommand(Markov_Console::Markov_CommandManager* cm):
    CreateCommand(cm)
{}



bool MacrorCreateCommand::run(const std::string &typeName,
                              const std::string &varname)
{
    if (cm_->has_type(typeName))
    {
        QString className(typeName.c_str());
        Markov_IO::ABC_Saveable *s;
        Markov_IO::ABC_Saveable **sptr=&s;
        Markov_IO::ClassDescription cd;
        CreateWizard* c=new CreateWizard(&className,&cd,sptr);
        if (c->exec()==1)
        {    cm_->add_var(varname,*sptr);


        return true;
        }
        return false;
    }
    if (cm_->has_superType(typeName))
    {
        QStringList classNames;
        QString className;
        std::vector<std::string> cNs=cm_->getChilds(typeName);
        for (int i=0; i<cNs.size(); ++i)
            classNames<<cNs[i].c_str();
        Markov_IO::ClassDescription cd;
        Markov_IO::ABC_Saveable *s;
        Markov_IO::ABC_Saveable **sptr=&s;
        CreateWizard* c=new CreateWizard(classNames,&className,&cd,sptr);
        if (c->exec()==1)
        {
            cm_->add_var(varname,*sptr);
        return true;
        }
        return false;
    }
    if (typeName=="Model")
    {
        QStringList classNames(Markov_Mol::Q_Markov_Model::ClassName().c_str());
        classNames<<Markov_Mol::PatchModel::ClassName().c_str();
        QString className;
        Markov_IO::ClassDescription cd;
        Markov_IO::ABC_Saveable *s;
        Markov_IO::ABC_Saveable **sptr=&s;
        CreateWizard* c=new CreateWizard(classNames,&className,&cd,sptr);
        if (c->exec()==1)
        {
            cm_->add_var(varname,*sptr);
        return true;
        }
        return false;
    }


    return false;
}




