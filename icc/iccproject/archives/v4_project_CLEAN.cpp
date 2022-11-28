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
typedef vector<vector<int>> table;
enum {WALL = -3, EMPTY = -2, PT_B = -1, PT_A = 0};
struct element 
{
	size_t row;
	size_t col;
};
typedef vector<element> list_cell;

//-------------------------prototypes----------------------------------
table maze_creation();
void maze_display(table maze);
element add_element(table& maze, int x, bool ask_position = true, size_t row = 0, size_t col = 0);
list_cell find_empty_neighbours(table maze, element point);
void print_error(string message, bool with_cell = false, unsigned i=0, unsigned j=0);
void add_walls(table &maze, element A, element B);
void make_crown(table& maze, int crown_rank, list_cell last_crown);

// ------------------------test----------------------------------------


//-------------------------main----------------------------------------
int main()
{
	// maze setup
	table maze = maze_creation();
	const element A = add_element(maze, PT_A);
	const element B = add_element(maze, PT_B);
	
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
	
	// find path
	list_cell crown0 {A};
	make_crown(maze, 0, crown0);
	
	return 0;
}


//-------------------------functions-----------------------------------

//-------------------------maze setup----------------------------------

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
	table maze(rows, vector<int>(cols, EMPTY));
	
	for(int i(0); i < cols; ++i)
	{
		maze[0][i] = WALL;
		maze[rows-1][i] = WALL;
	}
	
	for(int i(1); i < rows-1; ++i)
	{
		maze[i][0] = WALL;
		maze[i][cols-1] = WALL;
	}

	return maze;
}


void maze_display(table maze)
{
	for(size_t i(0); i < maze.size(); ++i)
		{
			for (size_t j(0); j < maze[i].size(); ++j)
				
				if (maze[i][j] == WALL)
					{cout << '#';}
				
				else if (maze[i][j] == EMPTY)
					{cout << ' ';}
				
				else if (maze[i][j] == PT_A)
					{cout << 'A';}
				
				else if (maze[i][j] == PT_B)
					{cout << 'B';}
				
				else {cout << maze[i][j];}
				
			cout << endl;
		}
}


element add_element(table& maze, int x, bool ask_position, size_t row, size_t col)
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
	
	element position({row, col});
	maze[row][col] = x;
	
	return position;
}


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
	
	if (maze[row][col] != EMPTY)
	{
		print_error(OVERLAP_FULL, true, row , col);
	}
	
	add_element(maze, WALL, false, row, col);
}


//-------------------------path finding algo---------------------------


list_cell find_empty_neighbours(table maze, element point)
{
	list_cell neighbours;
	
	size_t row = point.row;
	size_t col = point.col;
	
	if (maze[row-1][col] == EMPTY) // top
	{
		neighbours.push_back({row-1, col});
	}
	
	if (maze[row+1][col] == EMPTY) // down
	{
		neighbours.push_back({row+1, col});
	}
	
	if (maze[row][col-1] == EMPTY) // left
	{
		neighbours.push_back({row, col-1});
	}
	
	if (maze[row][col+1] == EMPTY) // right
	{
		neighbours.push_back({row, col+1});
	}
	
	return neighbours;
}


void make_crown(table& maze, int crown_rank, list_cell last_crown)
{	
	++crown_rank;
	bool finish(true);
	list_cell new_crown;
	
	for (size_t i(0); i < last_crown.size(); ++i)
	{
		list_cell neighbours = find_empty_neighbours(maze, last_crown[i]);
		
		for (size_t j(0); j < neighbours.size(); ++j)
		{
			size_t row = neighbours[j].row;
			size_t col = neighbours[j].col;
			maze[row][col] = crown_rank;
			element x = {row, col};
			new_crown.push_back(x);
		}
		if (neighbours.size() != 0)
		{	finish = false;		}
	}
	
	if (finish)
	{ return; }
	
	make_crown(maze, crown_rank, new_crown);
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
