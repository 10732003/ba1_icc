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
enum {DOT = -4, WALL = -3, EMPTY = -2, PT_B = -1, PT_A = 0};
enum {UP = 'U', DOWN = 'D', RIGHT = 'R', LEFT = 'L'};
struct element 
{
	size_t row;
	size_t col;
};

struct path
{
	element last_cel;
	string movements;
};
typedef vector<element> list_cell;

//-------------------------prototypes----------------------------------
table maze_creation();
void maze_display(table &maze);
element add_element(table& maze, int x, bool ask_position = true, size_t row = 0, size_t col = 0);
list_cell find_neighbours(table &maze, element point, int value, bool all_cell_around = false);
void print_error(string message, bool with_cell = false, unsigned i=0, unsigned j=0);
void add_walls(table &maze, element A, element B);
void make_crown(table &maze, int crown_rank, list_cell last_crown);

// ------------------------test----------------------------------------
void path_exist(table &maze, element B);

vector<path> find_path(table &maze, element B, list_cell &crossed_cell);
int smallest_val(table &maze, list_cell list);
char relative_position(element cel_now, element next_cel);
void resolve_path(table &maze, vector<path> &all_path, int val, list_cell &crossed_cell);
void add_path(table &maze, list_cell &crossed_cell, element A);
void clean_maze(table &maze);
void display_path(vector<path> &all_path);

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
	
	path_exist(maze, B);
	
	cout << endl;
	
	list_cell crossed_cell;
	vector<path> all_path = find_path(maze, B, crossed_cell);
	
	add_path(maze, crossed_cell, A);
	clean_maze(maze);
	
	maze_display(maze);
	
	cout << endl;
	
	display_path(all_path);
	
	return 0;
}


//-------------------------functions-----------------------------------
void display_path(vector<path> &all_path)
{
	size_t path_size = all_path[0].movements.size();
	
	for (size_t i(0); i < all_path.size(); ++i)
	{
		//down left right up
		cout << all_path[i].movements << endl;
	}
}

void clean_maze(table &maze)
{
	for(size_t i(0); i < maze.size(); ++i)
		{
			for (size_t j(0); j < maze[i].size(); ++j)
				
				if (maze[i][j] > 0)
					{maze[i][j] = EMPTY;}
		}
}

void add_path(table &maze, list_cell &crossed_cell, element A)
{
	for (size_t i(0); i < crossed_cell.size(); i++)
	{
		if (A.row != crossed_cell[i].row or A.col != crossed_cell[i].col)
		{ 
			add_element(maze, DOT, false, crossed_cell[i].row, crossed_cell[i].col);
		}
	}
	return;
}

vector<path> find_path(table &maze, element B, list_cell &crossed_cell)
{
	path initial_path = {B, ""};
	vector<path> all_path{initial_path};
	
	list_cell around_b = find_neighbours(maze, B, 0, true);
	int val = smallest_val(maze, around_b);
	
	while (val >= 0)
	{
		resolve_path(maze, all_path, val, crossed_cell);
		val -= 1;
	}
		
	return all_path;
}

void resolve_path(table &maze, vector<path> &all_path, int val, list_cell &crossed_cell)
{
	for (size_t i(0); i < all_path.size(); ++i)
	{
		path base_path = all_path[i];
		element base_cel = base_path.last_cel;
		string base_movements = base_path.movements;
	
		list_cell around_cel = find_neighbours(maze, base_cel, val);
		
		for (size_t j(0); j < around_cel.size(); j++)
		{
			element next_cel = around_cel[j];
			crossed_cell.push_back(next_cel);
			
			char next_mvt = relative_position(base_cel, next_cel);
			string movements = next_mvt + base_movements;
			
			if (j == around_cel.size()-1)
			{
				all_path[i] = {next_cel, movements};
			} 
			else {
				path new_path = {next_cel, movements};
				all_path.push_back(new_path);
			}
		}
	}
	return;
}

char relative_position(element cel_now, element next_cel)
{
	char letter;
	
	if (cel_now.row > next_cel.row)
	{ letter = DOWN; }

	else if (cel_now.row < next_cel.row)
	{ letter = UP; }
	
	else if (cel_now.col > next_cel.col)
	{ letter = RIGHT; }
	
	else if (cel_now.col < next_cel.col)
	{ letter = LEFT; }
	
	return letter;
}

int smallest_val(table &maze, list_cell list)
{
	size_t size = list.size();
	
	int min_val(EMPTY);
	
	for (size_t i(0); i < size; ++i)
	{
		element cel(list[i]);
		int val = maze[cel.row][cel.col];
		
		if (min_val < 0)
		{ min_val = val; }
		
		if (val < min_val and val >= 0)
		{ min_val = val; }
	}
	
	return min_val;
}

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


void maze_display(table &maze)
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
					
				else if (maze[i][j] == DOT)
					{cout << '.';}
				
				else {cout << maze[i][j];}
				
			cout << endl;
		}
}


element add_element(table &maze, int x, bool ask_position, size_t row, size_t col)
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
	
	if ( 	(row == A.row and col == A.col) 
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


list_cell find_neighbours(table &maze, element point, int value, bool all_cell_around)
{
	list_cell neighbours;
	
	size_t row = point.row;
	size_t col = point.col;
	
	if (maze[row-1][col] == value or all_cell_around) // top
	{
		neighbours.push_back({row-1, col});
	}
	
	if (maze[row+1][col] == value or all_cell_around) // down
	{
		neighbours.push_back({row+1, col});
	}
	
	if (maze[row][col-1] == value or all_cell_around) // left
	{
		neighbours.push_back({row, col-1});
	}
	
	if (maze[row][col+1] == value or all_cell_around) // right
	{
		neighbours.push_back({row, col+1});
	}
	
	return neighbours;
}


void make_crown(table &maze, int crown_rank, list_cell last_crown)
{	
	++crown_rank;
	bool finish(true);
	list_cell new_crown;
	
	for (size_t i(0); i < last_crown.size(); ++i)
	{
		list_cell neighbours = find_neighbours(maze, last_crown[i], EMPTY);
		
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


void path_exist(table &maze, element B)
{
	list_cell cell_around_b = find_neighbours(maze, B, 0, true);
	
	for (size_t i(0); i < cell_around_b.size(); ++i)
	{
		size_t row = cell_around_b[i].row;
		size_t col = cell_around_b[i].col;
		
		if (maze[row][col] >= 0)
		{
			return;
		}
	}
	print_error(NO_SOLUTION);
	return;
}


//--------------------------------display path-------------------------



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
