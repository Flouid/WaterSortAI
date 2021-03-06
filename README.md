# WaterSortAI
This is a C++ AI that plays the puzzle game Water Sort / Ball Sort automagically.

It has two modes, fast solve mode and perfect solve mode.
Fast solve will take any level and solve it almost instaneously, but doensn't necessarily generate shortest possible solutions, it is very close though.
Perfect solve will always return a shortest possible path to the solution, but is very performance limited. Using it is not recommended.

The program works by taking the name of a text file containing the game state and ingesting it into a game state before running the analysis. Below is an example file l110.txt:

![image](https://user-images.githubusercontent.com/17460504/110222671-e6af1380-7ea1-11eb-9127-c215f04ac32d.png)

The representations used for the colors don't matter so long as they are consistent, they could even be numbers. Empty slots must be signified by "empty" or "e".
The program outputs a path to the solution as a sequence of moves. Below is an example for the provided text file:

![image](https://user-images.githubusercontent.com/17460504/110222706-2fff6300-7ea2-11eb-9810-177904fcede1.png)

To read this, pour the tube to the left of the arrow into the tube to the right of the arrow, the 0th move is always the initialization of the game state. 
For example, since level 110 has 11 tubes, begin by pouring the 8th tube into the 11th. The second move is pour the 6th tube into the 11th tube and so forth, the 21rst is pour the first tube into the 9th. 

At the end of the sequence of moves, the game is guaranteed to be solved. 
