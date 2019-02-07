Here is a simple program that runs a 'Game of Life' in C

In order to get a better visual impression of the program it is possible to 'animate' the output.
When the program is run the successive iterations of the grid are printed in the file output.txt.
If this file is opened in Windows Notepad (or some similar program), one may animate the output by
setting the window to an appropriate size and holding down the Page Down key, so that each time
the page jumps down the visible grid is replaced by the next one, giving the illusion of animation.
On my system I found it consistently works for any grid size if the Notepad window shows the entirety
of the initial grid, and the space below, and the first row of the next grid. Obviously this is a 
very basic method, but I tried to keep it simple in this way to maintain platform-independency.
For the preset seeds giving more complicated behaviour (pentomino, random seed) a bigger grid can 
be set and the font size reduced in Notepad to give a more 'zoomed out' animation.


Some notes on the code:
-in one iteration, the program scans each element of the play grid, checks whether it is alive
or dead, then counts the number of live neighbouring cells and applies the rules to decide whether 
that cell should be dead or alive. This choice is stored in a temporary grid to avoid messing up
the count for other cells in this iteration, then at the end the new grid values are put back into
the play grid, and the next iteration begins
- I have set the grid with finite dimension, which can be altered by changing the global variable 
D defined outside the main function. An infinite grid would be impractical, it couldn't be displayed
on screen
-to deal with the behaviour of cells near the edge of the grid, I set up a 'phantom' border of dead
cells, which is not visible to the player and does not follow the rules of life and death but remains
permanently dead. The alternative to this would have been to put in periodic boundary conditions 
where cells at one edge of the grid would interact with cells on the opposite edge as if they were
next to each other. I decided against doing this because it would be harder to observe the change
from a chaotic grid to a settled one.
-I tried to make the program more robust against bad user input, through the use of do while
loops. In the loop the input is checked to see if it is appropriate, and if it is 
not the loop restarts and asks for input again. The loop only exits when appropriate 
input has been detected. This seems quite foolproof, the only instance I can see where 
bad input would not be rejected is when the user types correct input followed by
bad input, for example "12abc" as a cell reference number or "Y123" as an option choice
at the start. In these cases scanf only takes the data of the correct type and discards
the rest, and the program continues without error.

