#ifndef SIMULATECOMMAND_H
#define SIMULATECOMMAND_H
#include <Markov_Console/ABC_Command.h>


namespace Markov_Console
{
class SimulateCommand:public ABC_Command
{
public:
    /// virtual destructor
    virtual ~SimulateCommand();

    SimulateCommand(Markov_CommandManager* cm);


    virtual std::string commandName()const;


    virtual bool run(const std::vector<std::string>& InputValue,
                     const std::vector<std::string>& OutputValue);


    virtual bool run(const std::string& patch_in,
                     const std::string& experiment_in,
                     const std::string& experiment_out,
                     std::size_t num_replicates,
                     const std::string& options_in);

};


}

#endif // SIMULATECOMMAND_H
