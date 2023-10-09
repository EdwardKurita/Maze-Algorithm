# Maze-Algorithm

Grade 12 Project, Fall 2021

Notes:
Written in C++
Uses linked lists
Uses recursion

Description:

Reads in the infromation from a txt file "maze.txt". The first two lines define the bounds of the maze (x, y dimensions). 
The rest of the file contains the maze itself:
  Start is denoted with 'S'
  Goal is denoted with 'G'
  Walls are denoted with '#'
  Open space are denoted with '.'

The linked lists contains the information of the solution path. Each move is recorded in order.
Recursion is used to check every direction that the leading position can 'look at'.
This allows the path to move out of dead ends if it ends up by popping and blocking paths that lead to dead ends. Effectively 'backing up' until there's a space that is accessible.
Once the path reaches 'G' the solver stops.
