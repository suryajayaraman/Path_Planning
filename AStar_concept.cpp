#include "AStar_concept.h"


std::vector<GridState> Parseline(const std::string &line)
{
    std::istringstream lineString(line);
    std::vector<GridState> rowData;
    int n;
    char c;
    while (lineString >> n >> c && c == ',') 
    {
        if (n == 0)
        {
            rowData.push_back(GridState::kEmpty);
        } 
      
        else 
        {
            rowData.push_back(GridState::kObstacle);
        }
    }
    return rowData;
}



std::vector<std::vector<GridState>> ReadBoardFile(std::string path)
{
    std::ifstream gridFile{path};
    std::vector<std::vector<GridState>> Grid{};
    if(gridFile)
    {
        std::cout << "File read success \n";
        
        std::string line;
        while(getline(gridFile, line))
        {
            std::vector<GridState> rowData = Parseline(line);
            Grid.push_back(rowData);
        }
    }
    return Grid;
}



std::string CellString(const GridState &cell)
{
  switch(cell) 
  {
    case GridState::kObstacle: 
      return "⛰   ";

    case GridState::kPath: 
      return "🚗   ";

    case GridState::kStart:
      return "🚦   ";

    case GridState::kFinish:
      return "🏁   ";

    default: 
      return "0   "; 
  }
}


void PrintBoard(const std::vector<std::vector<GridState>> &board) 
{
  for (unsigned int i = 0; i < board.size(); i++)
  {
    for(unsigned int j = 0; j < board[0].size(); j++) 
    {
      std::cout<< CellString(board[i][j]);
    }
    std::cout << "\n";
  }
}


int Heuristic(const int &x1, const int &y1, const int &x2, const int &y2)
{
  return (std::abs(x2-x1) + std::abs(y2-y1));
}


void AddToOpen(const std::vector<int> &node, std::vector<std::vector<int>> &openList, std::vector<std::vector<GridState>> &grid)
{
  openList.push_back(node);
  grid[node[0]][node[1]] = GridState::kClosed;
}


bool CompareNodes(const std::vector<int> &Node1, const std::vector<int> &Node2)
{
  return ( (Node1[2]+ Node1[3]) > Node2[2]+ Node2[3] ) ? true : false;
}



void CellSort(std::vector<std::vector<int>> *v)
{
  std::sort(v->begin(), v->end(), CompareNodes);
}



bool CheckCell_Validity(const std::vector<int> &Node, std::vector<std::vector<GridState>> &grid)
{
  bool within_xlim = (Node[0]>=0) && (Node[0] <grid.size());
  bool within_ylim = (Node[1]>=0) && (Node[1] <grid[0].size());
  
  if(within_xlim && within_ylim)
  {
    if(grid[Node[0]][Node[1]] == GridState::kEmpty)
    {
      return true;
    }
  }
  return false;
}


// ExpandNeighbors {
void ExpandNeighbours(const std::vector<int> &currentNode, std::vector<std::vector<int>> &openList, std::vector<std::vector<GridState>> &grid, const std::vector<int> &goal)
{
  std::vector<int> tempNode {};
  int tempHeuristic = 0;

  // TODO: Loop through current node's potential neighbors.
  for (unsigned int i = 0; i < action.size(); i++)
  {
    // TODO: Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
    tempNode = {currentNode[0] + action[i][0], currentNode[1] + action[i][1]};
    // std::cout << "  Temp node[" << i << "] = (" << tempNode[0] << "," <<  tempNode[1] <<")\n";
    // TODO: Increment g value, compute h value, and add neighbor to open list.
    // Add tempNode to openList
    if(CheckCell_Validity(tempNode, grid) == true)
    {
      tempHeuristic = Heuristic(tempNode[0], tempNode[1], goal[0], goal[1]);
      AddToOpen(std::vector<int> {tempNode[0], tempNode[1], currentNode[2] + 1, tempHeuristic}, openList, grid);
      // std::cout << "  Node (" << tempNode[0] << "," << tempNode[1] << ") added to openlist\n";
    }
  }
}



// The Search function stub
std::vector<std::vector<GridState>> SearchGrid(std::vector<std::vector<GridState>> &grid, const std::vector<int> &start, const std::vector<int> &goal)
{

  // creating an openlist and adding start point to it
  std::vector<std::vector<int>> openList {};
  AddToOpen(std::vector<int> {start[0], start[1], 0, Heuristic(start[0], start[1], goal[0], goal[1])}, openList, grid);

  // while open list is non empty {
  while (openList.size() > 0)
  {
    // Sort the open list using `CellSort`, and get the current node.
    CellSort(&openList);  

    // Get the x and y values from the current node, and set grid[x][y] to kPath.
    std::vector<int> currentNode = openList.back();
    openList.pop_back();
    grid[currentNode[0]][currentNode[1]] = GridState::kPath;

    // Check if you've reached the goal. If so, return grid.
    if((currentNode[0] == goal[0]) && (currentNode[1] == goal[1]))
    {
        // marking the start and goal points
        grid[start[0]][start[1]] = GridState::kStart;
        grid[goal[0]][goal[1]] = GridState::kFinish;

      //std::cout << "Goal node reached \n";
      return grid;
    }
    //std::cout << "current node : " <<currentNode[0] << " " << currentNode[1] << "\n";
    ExpandNeighbours(currentNode, openList, grid, goal);

    /*std::cout << "\n";
    for(auto cell :openList)
    {
      std::cout << " (";
      for(auto pos:cell)
        std::cout << pos << " ";
      std::cout << ")";
    }*/

  }  
  std::cout << "No path found! \n";
  std::vector<std::vector<GridState>> AStarPath {};
  return AStarPath;
}