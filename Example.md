# Introduction #

How to install and use MacroRConsole 0.01


# Details #

Download and unzip the file MacroRConsole001.zip in any directory.
Run the executable MacroRConsole.exe.

You should see a DOS type console.

This console works with commands. The commands are listed by entering help.
By entering help and the name of the command, there is a brief description of the usage of the command.

The more important commands are:
> `load`
> > (it will load an already there example).


> `save`
> > (it save all the variables in the file macror.txt)


> `model patch `
> > (that allow you to build from scratch a model of a channel with the number of channels and instrumental noise)


> `experiment `
> > (allow you to configure the sequence of application of the agonist).


> `simulate `
> > (it simulates the outcome of an experiment)


> `optimize `
> > (it fits the parameters of a kinetic model to a given experiment).

for example try


> `load`
> `optimize mypatch mySimulation`