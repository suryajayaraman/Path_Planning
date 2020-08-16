#include "AStar_concept.h"

/**
 * File containing test functions for AStar_concept.h 
 * 
 * Basic tests for simple grid done
 * 
 * TODO
 * More test case scenarios to be written
 */


int main()
{
  // read input grid file
  std::string filePath {"test_grid1.txt"};
  std::vector<std::vector<GridState>> grid = ReadBoardFile(filePath);

  // define start and goal points
  std::vector<int> startPoint {0,0};
  std::vector<int> goalPoint  {4,5};

  // print Input grid 
  std::cout<< "Input grid is \n";
  PrintBoard(grid);

  // find the optimal path if exists
  std::vector<std::vector<GridState>> OptimalPath = SearchGrid(grid, startPoint, goalPoint);

  // print the Solution to console
  std::cout<< "Solution is \n";
  PrintBoard(OptimalPath);

  return 0;
}