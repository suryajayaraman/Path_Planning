#ifndef __ASTAR_STARTER__
#define __ASTAR_STARTER__


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * enum class to represent possible states of grid cell as obstacle, empty etc.
 */
enum class GridState {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};


// directional deltas
const std::vector<std::vector<int>> action { {1,0}, {-1,0}, {0,1}, {0,-1} };


/**
 * Function to parse single line of gridData
 */ 
std::vector<GridState> Parseline(const std::string &line);

/**
 * Function to Read grid from file 
 */ 
std::vector<std::vector<GridState>> ReadBoardFile(std::string path);


/**
 * Function to print the grid to console
 */
void PrintBoard(const std::vector<std::vector<GridState>> &board);

/**
 * Function to return correponding cell reprsentation symbol for printing to console
 */
std::string CellString(const GridState &cell);

/**
 * Function to find the optimal path in given grid using A star algorithm
 */
std::vector<std::vector<GridState>> SearchGrid(std::vector<std::vector<GridState>> &grid, const std::vector<int> &start, const std::vector<int> &goal);


/**
 * Function to calculate the heuristic function of a node
 */
int Heuristic(const int &x1, const int &x2, const int &y1, const int &y2);

/**
 * Function to add a node to the openlist
 */
void AddToOpen(const std::vector<int> &node, std::vector<std::vector<int>> &openList, const std::vector<std::vector<GridState>> &grid);


/**
 * Function to compare nodes based on f-value and return if first node is smaller than second one
 */
bool CompareNodes(const std::vector<int> &Node1, const std::vector<int> &Node2);


/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(std::vector<std::vector<int>> *v);


/**
 * Check if cell is freespace or obstacle
 */
bool CheckCell_Validity(const std::vector<int> &Node, std::vector<std::vector<GridState>> &grid);


/**
 * Expands current node using 'action' and adds to openlist
 */
void ExpandNeighbours(const std::vector<int> &currentNode, std::vector<std::vector<int>> &openList, std::vector<std::vector<GridState>> &grid, const std::vector<int> &goal);


#endif  /* __ASTAR_STARTER__ */