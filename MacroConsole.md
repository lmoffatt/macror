# Specification #
  * Console command interface.

## Command list ##

help subject
> Displays help on subject

dir
> List the contents of current directory

cd
> Display current directory

cd dirname
> Changes current directory to dirname

who
> List the variables

clear  [all/object-alias]
> Delete all or the specified variables from memory

edit object-alias
> Edit the object

save filename
> Save all the variables in filename, default macror.txt

export dirname object-alias...
> Save each variable in its own file

load filename
> Loads the content of filename

simulate patch-alias experiment-alias ...
> Simulates a patch on an experiment

likelihood patch-alias simulationdata-alias ...
> Calculates the likelihood that a patch would produce the

optimize patch-alias experimentdata-alias ...
> Optimize the parameters of the patch model for the experiment

model channel new-alias
> Opens an interactive dialog to create a model of a channel

model patch new-alias
> Opens an interactive dialog to create a model of a patch

experiment new-alias
> Opens an interactive dialog to create an experiment

option command new-alias
> Opens an interactive dialog to create a

object-alias
> Displays the contents of the specified object (i.e, a model, experiment
> etc..

script-filename
> Looks for a the file "script-filename.macror.txt" in current directory
> and executes all the commands found on it.