#include <iostream>
#include <vector>

using namespace std;

// const
const string NO_SOLUTION("No path from start to end cells");
// Error messages
const string TOO_SMALL("Error: the number of lines/columns must be greater than 2");
const string BAD_LOCATION("Error: the cell is not in the inner space of the grid");
const string OVERLAP_AB("Error: self overlap of start and end cells is not allowed");
const string OVERLAP_FULL("Error: this cell is already full");
const string OVERLAP_AB_FULL("Error: overlap of start or end cells is not allowed");


//-------------------------struct and type-----------------------------
typedef vector<vector<char>> table;

struct element 
{
	char direction;
	size_t row;
	size_t col;
};

//-------------------------prototypes--TEST--------------------------------
void find_path(table& maze, element A, element B, vector<element>path);
//-------------------------prototypes----------------------------------
table maze_creation();
void maze_display(table maze);
element add_element(table& maze, char element, bool ask_position = true,
					size_t row = 0, size_t col = 0);
vector<element> find_neighbours(table maze, element point);
void print_error(	string message, bool with_cell = false, 
					unsigned i=0, unsigned j=0);
void add_walls(table &maze, element A, element B);


//-------------------------main----------------------------------------
int main()
{
	table maze = maze_creation();
	const element A = add_element(maze, 'A');
	const element B = add_element(maze, 'B');
	
	if (A.row == B.row and A.col == B.col)
	{
		print_error(OVERLAP_AB);
	}
	
	int nbr_walls;
	cin >> nbr_walls;
	while (nbr_walls > 0)
	{
		add_walls(maze, A, B);	
		--nbr_walls;
	}
	
	maze_display(maze);

	
	return 0;
}


//-------------------------functions-----------------------------------

//-------------------------maze setup----------------------------------

// ask for two number and initialize a maze
table maze_creation()
{
	int rows;
	cin >> rows;
		
	int cols;
	cin >> cols;
		
	if (cols < 3 or rows < 3)
	{
		print_error(TOO_SMALL);
	}
	table maze(rows, vector<char>(cols, ' '));
	
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
void maze_display(table maze)
{
	for(size_t i(0); i < maze.size(); ++i)
		{
			for (size_t j(0); j < maze[i].size(); ++j)
				{cout << maze[i][j];}
			cout << endl;
		}
}


// parameters: vector 2X2 (maze) and char to add
// return position vector of the element: element, row, column
element add_element(table& maze, char x, 
					bool ask_position, size_t row, size_t col)
{
	if (ask_position)
	{
		cin >> row;
		cin >> col;
	}
	
	bool inside(true);
	
	if (row > maze.size() - 2 or row < 1)
	{
		inside = false;
	}
	
	if (col > maze[0].size() - 2 or col < 1)
	{
		inside = false;
	}
	
	if (not inside)
	{
		print_error(BAD_LOCATION, true, row, col);
	}
	
	element position({x, row, col});
	maze[row][col] = x;
	
	return position;
}


// 
void add_walls(table &maze, element A, element B)
{
	size_t row;
	cin >> row;
	size_t col;
	cin >> col;
	
	if ( 	(col == A.row and col == A.col) 
		or	(row == B.row and col == B.col)
		)
	{
		print_error(OVERLAP_AB_FULL, true, row, col);
	}
	
	if (maze[row][col] != ' ')
	{
		print_error(OVERLAP_FULL, true, row , col);
	}
	
	add_element(maze, '#', false, row, col);
}


//-------------------------path finding algo---------------------------

// parameters: 2X2 vector (maze), row and column
vector<element> find_neighbours(table maze, element point)
{
	vector<element>neighbours;
	
	size_t& row = point.row;
	size_t& col = point.col;
	
	if (maze[row-1][col] != '#') // top
	{
		neighbours.push_back({'T', row-1, col});
	}
	
	if (maze[row+1][col] != '#') // down
	{
		neighbours.push_back({'D', row-1, col});
	}
	
	if (maze[row][col-1] != '#') // left
	{
		neighbours.push_back({'L', row, col-1});
	}
	
	if (maze[row][col+1] != '#') // right
	{
		neighbours.push_back({'R', row, col+1});
	}
	
	return neighbours;
}

//-------------------------//--------TEST START HERE-------//-------------------------

//-------------------------//---------END TEST----------------//-------------------------

//------------- print error function, given source code ---------------

void print_error(string message, bool with_cell, unsigned i, unsigned j)
{
    cout << message ;
    
    if(with_cell) 
    {
        cout << " : ligne = " << i << " colonne = " << j ;
    }

    cout << endl;

    exit(0);
}
