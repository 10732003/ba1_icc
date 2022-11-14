#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> maze_creation();
void maze_display(vector<vector<char>>maze);
vector<int> add_element(vector<vector<char>>&maze, char element);

int main()
{
	vector<vector<char>> maze = maze_creation();
	vector<int>pos_A = add_element(maze, 'A');
	vector<int>pos_B = add_element(maze, 'B');
	
	int nbr_walls;
	cin >> nbr_walls;
	while (nbr_walls > 0)
	{
		add_element(maze, '#');
		--nbr_walls;
	}
	
	maze_display(maze);

	return 0;
}


// ask for two number and initialize a maze
vector<vector<char>> maze_creation()
{
	int rows;
	cin >> rows;
		
	int cols;
	cin >> cols;
		
	vector<vector<char>>maze(rows, vector<char>(cols, ' '));
	
	for(int i(0); i < cols; ++i)
	{
		maze[0][i] = '#';
		maze[rows-1][i] = '#';
	}
	
	for(int i(1); i < rows-1; ++i)
	{
		maze[i][0] = '#';
		maze[i][cols-1] = '#';
	}

	return maze;
}


// display the maze, take a 2 dimensional vector as a parameter
void maze_display(vector<vector<char>>maze)
{
	for(size_t i(0); i < maze.size(); ++i)
		{
			for (size_t j(0); j < maze[i].size(); ++j)
				{cout << maze[i][j];}
			cout <<endl;
		}
}


// parameters: vector 2X2 (maze) and char to add
// return position vector of the element (int row, int column)
vector<int> add_element(vector<vector<char>>&maze, char element)
{
	int r;
	cin >> r;
	int c;
	cin >> c;
	
	vector<int>position({r, c});
	
	maze[r][c] = element;
	
	return position;
}





























