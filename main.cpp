/*
Recursive maze algorithm solve:
This code takes in a maze from a file and then solves it using a recursive algorithm.
The correct path of the computer is recorded in a linked list
*/

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

//linked list structure to store the correct path through the maze in both
//X and Y coordinates
struct NODE{
  int pathX;
  int pathY;
  NODE *next;
};

//class containing variables that would otherwise be global as well as the methods for modularity
class mazeSolve{
  private:

    //private stack variables
    NODE *topX;
    NODE *headX;
    NODE *topY;
    NODE *headY;

  public:

    //since I have to access x and y in the main of the code, I've made them public
    //so that they may be accessed easily in the main
    int x;
    int y;

    //methods for the program
    mazeSolve();
    bool FindPath(char **maze, int posX, int posY);
    void PrintMaze(char **maze, int x, int y);

    //Must have a push and pop for both axis because the code must be able to store
    //the X and Y coordinates of the correct path
    void PushX(int posX);
    void PushY(int posY);
    int popX();
    int popY();
};

int main() {
  //create the universal variable for the pathing
  mazeSolve mazePath;
  
  //open file
  fstream mazeF("maze.txt");

  //limit in the x direction and position of start in the x axis
  int startX;

  //limit in the y direction and position of start in the y axis
  int startY;

  //maze array
  char **maze;

  //reading in the limits of the maze
  mazeF >> mazePath.y;
  mazeF >> mazePath.x;

  cout << mazePath.x << " " << mazePath.y << endl;

  //creating the limits of the maze with pointers
  //create a y char line for each x char character
  maze = new char *[mazePath.x];
  for (int i = 0; i <mazePath.x; i++) maze[i] = new char [mazePath.y];

  //reading in the maze
  for (int i = 0; i <mazePath.y; i++){
    for (int j = 0; j <mazePath.x; j++){
      mazeF >> maze[j][i];

      //finding the starting coordinates of the maze
      if (maze[j][i] == 'S'){
        startX = j;
        startY = i;
      }
    }
  }
  
  //printing out the maze before the algorithm so that the user may see what the
  //maze looks like for a brief second
  mazePath.PrintMaze(maze,mazePath.x,mazePath.y);
  this_thread::sleep_for(chrono::milliseconds(1000));

  //run the algorithm
  mazePath.FindPath(maze, startX, startY);

  return 0;
}

//printing function, can be used anywhere
void mazeSolve::PrintMaze(char **maze, int x, int y){

  //sleep_for method and clear for the maze solving to look animated
  this_thread::sleep_for(chrono::milliseconds(50));
  system("clear");

  //printing out the maze
  cout << endl;
  for (int i = 0; i < y; i++){
    for (int j = 0; j < x; j++){
      
      //replacing the blocked path squares with a period so that the console output
      //looks more clean
      if (maze[j][i] == '*') cout << ".";

      //printing the maze out if it doesn't encounter a dead end tile
      else cout << maze[j][i];
    }
    cout << endl;
  }
}

//algorithm to solve the maze
bool mazeSolve::FindPath(char **maze, int posX, int posY){
  
  //checking to see if our current position is within the maze and popping the
  //bad coordinates out of their stacks
  if (posX < 0 || posX + 1 > x || posY < 0 || posY + 1 > y){
    posX = popX();
    posY = popY();
    return false;
  }
  //return if we reach the goal
  if (maze[posX][posY] == 'G' || maze[posX][posY] == 'F') return true;

  //checking to see if the square is available (not #)
  if (maze[posX][posY] != '.' && maze[posX][posY] != 'S') return false;

  //"drawing" the path of the computer, pushing it's x and y
  //coordinates into their stacks
  maze[posX][posY] = 'o';
  PushX(posX);
  PushY(posY);

  //print out the maze as it is before every recursion
  PrintMaze(maze, x, y);

  //calls movements for pathing recursively in the order down, right, up, left
  if (FindPath(maze, posX, posY + 1)) return true;
  if (FindPath(maze, posX + 1, posY)) return true;
  if (FindPath(maze, posX, posY - 1)) return true;
  if (FindPath(maze, posX - 1, posY)) return true;

  //if none of the directions are possible to move to, it's a dead end.
  //replace the char at the dead end position with the dead end character: *
  maze[posX][posY] = '*';
  
  //pops the the X and Y of the current position out of the list
  //and make the current position the one that came before it
  popX();
  posX = popX();
  popY();
  posY = popY();

  //print the maze after each dead end recursion
  PrintMaze(maze, x, y);

  //will return after each dead end and if all the cases fail
  return false;
}

//constructor (just for the linked list variables)
mazeSolve::mazeSolve(){
  topX = NULL;
  headX = NULL;
  topY = NULL;
  headY = NULL;
}

//pushing X coordinates to the top of X position stack
void mazeSolve::PushX(int posX){
	NODE *newNode = new NODE;
	newNode -> pathX = posX;
	newNode -> next = NULL;
	if (headX == NULL){
		headX = newNode;
		topX = newNode;
	} else {
    topX -> next = newNode;
    topX = topX -> next;
	}
}

//pushing Y coordinate to the top of Y position stack
void mazeSolve::PushY(int posY){
	NODE *newNode = new NODE;
	newNode -> pathY = posY;
	newNode -> next = NULL;
	if (headY == NULL){
		headY = newNode;
		topY = newNode;
	} else {
    topY -> next = newNode;
    topY = topY -> next;
	}
}

//popping the top X value
int mazeSolve::popX(){
	NODE *endNode = new NODE;
	NODE *prevNode = new NODE;
	endNode = headX;
	while (endNode -> next){
		prevNode = endNode;
		endNode = endNode -> next;
	}
  float buff = topX -> pathX;
	topX = prevNode;
	prevNode -> next = NULL;
	delete endNode;
	return buff;
}

//popping the top Y value
int mazeSolve::popY(){
	NODE *endNode = new NODE;
	NODE *prevNode = new NODE;
	endNode = headY;
	while (endNode -> next){
		prevNode = endNode;
		endNode = endNode -> next;
	}
  float buff = topY -> pathY;
	topY = prevNode;
	prevNode -> next = NULL;
	delete endNode;
	return buff;
}
