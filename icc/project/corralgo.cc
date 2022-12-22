/* 
*	File name	:	355726.cc
*	Author		:	Dutruy Eloi
* 	SCIPER		:	355726
* 	Version		:	6.2
*/ 

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


//-------------------------struct, typedef and enum-----------------------------
enum {DOT = -4, WALL = -3, EMPTY = -2, PT_B = -1, PT_A = 0};
enum {UP = 'U', DOWN = 'D', RIGHT = 'R', LEFT = 'L'};

struct Element 
{
	size_t row;
	size_t col;
};

struct Path
{
	Element last_cel;
	string movements;
};

typedef vector<vector<int>> table;
typedef vector<Element> list_cell;
typedef vector<string> list_str;

//-------------------------prototypes----------------------------------

// maze setup
table maze_creation();
void maze_display(table &maze);
Element add_element(table &maze,int elem,bool ask_pos=true,size_t row=0,size_t col=0);
void add_obstacles(table &maze, Element A, Element B);
void add_walls(table &maze, Element A, Element B);

// path finding algo
list_cell find_neighbours(table &maze, Element el, int val, bool cell_around = false);
void make_crown(table &maze, int crown_rank, list_cell last_crown);
void path_exist(table &maze, Element B);
vector<Path> find_path(table &maze, Element B, list_cell &crossed_cell);
void resolve_path(table &maze, vector<Path> &paths, int val, list_cell &crossed_cell);
char relative_position(Element cel_now, Element next_cel);
int smallest_val(table &maze, list_cell list);

// display path
void add_path(table &maze, list_cell &crossed_cell, Element A);
void clean_maze(table &maze);
void display_path(vector<Path> &all_path);
list_str merge_list(list_str left, size_t size_l, list_str right, size_t size_r);
list_str sort_list(list_str list_path, size_t size_list);
bool one_before_two(string string1, string string2);

// print error function, given source code
void print_error(string message, bool with_cell = false, unsigned i=0, unsigned j=0);

//-------------------------main----------------------------------------

int main()
{
	// maze setup
	table maze = maze_creation();
	const Element A = add_element(maze, PT_A);
	const Element B = add_element(maze, PT_B);
	
	add_obstacles(maze, A, B);
	
	maze_display(maze);
	cout << endl;
	
	// find path
	make_crown(maze, 0, {A});
	path_exist(maze, B);
	
	list_cell crossed_cell;
	vector<Path> all_path = find_path(maze, B, crossed_cell);
	
	add_path(maze, crossed_cell, A);
	clean_maze(maze);
	
	maze_display(maze);
	cout << endl;
	
	display_path(all_path);
	
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

Element add_element(table &maze, int elem, bool ask_position, size_t row, size_t col)
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
	
	Element position({row, col});
	
	if (maze[row][col] == PT_A and elem == PT_B)
	{
		print_error(OVERLAP_AB);
	}
	
	maze[row][col] = elem;
	
	return position;
}

void add_obstacles(table &maze, Element A, Element B)
{
	int nbr_walls;
		cin >> nbr_walls;
		while (nbr_walls > 0)
		{
			add_walls(maze, A, B);	
			--nbr_walls;
		}
}

void add_walls(table &maze, Element A, Element B)
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
	
	bool overlap(false);
	if (maze[row][col] != EMPTY)
	{
		overlap = true;
	}
	
	add_element(maze, WALL, false, row, col);
	
	if (overlap)
	{
		print_error(OVERLAP_FULL, true, row , col);
	}
}


//-------------------------path finding algo---------------------------

list_cell find_neighbours(table &maze, Element point, int val, bool all_cell_around)
{
	list_cell neighbours;
	
	size_t row = point.row;
	size_t col = point.col;
	
	if (maze[row-1][col] == val or all_cell_around) // top
	{
		neighbours.push_back({row-1, col});
	}
	
	if (maze[row+1][col] == val or all_cell_around) // down
	{
		neighbours.push_back({row+1, col});
	}
	
	if (maze[row][col-1] == val or all_cell_around) // left
	{
		neighbours.push_back({row, col-1});
	}
	
	if (maze[row][col+1] == val or all_cell_around) // right
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
			Element x = {row, col};
			new_crown.push_back(x);
		}
		if (neighbours.size() != 0)
		{	finish = false;		}
	}
	
	if (finish)
	{ return; }
	
	make_crown(maze, crown_rank, new_crown);
}

void path_exist(table &maze, Element B)
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

vector<Path> find_path(table &maze, Element B, list_cell &crossed_cell)
{
	Path initial_path = {B, ""};
	vector<Path> all_path{initial_path};
	
	list_cell around_b = find_neighbours(maze, B, 0, true);
	int val = smallest_val(maze, around_b);
	
	while (val >= 0)
	{
		resolve_path(maze, all_path, val, crossed_cell);
		val -= 1;
	}
	
	return all_path;
}

void resolve_path(table &maze, vector<Path> &paths, int val, list_cell &crossed_cell)
{
	for (size_t i(0); i < paths.size(); ++i)
	{
		Path base_path = paths[i];
		Element base_cel = base_path.last_cel;
		string base_movements = base_path.movements;
	
		list_cell around_cel = find_neighbours(maze, base_cel, val);
		
		for (size_t j(0); j < around_cel.size(); j++)
		{
			Element next_cel = around_cel[j];
			crossed_cell.push_back(next_cel);
			
			char next_mvt = relative_position(base_cel, next_cel);
			string movements = next_mvt + base_movements;
			
			if (j == around_cel.size()-1)
			{
				paths[i] = {next_cel, movements};
			} 
			else {
				Path new_path = {next_cel, movements};
				paths.push_back(new_path);
			}
		}
	}
	return;
}

char relative_position(Element cel_now, Element next_cel)
{
	char letter(0);
	
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
		Element cell(list[i]);
		int val = maze[cell.row][cell.col];
		
		if (min_val < 0)
		{ min_val = val; }
		
		if (val < min_val and val >= 0)
		{ min_val = val; }
	}
	
	return min_val;
}


//--------------------------------display path-------------------------

void add_path(table &maze, list_cell &crossed_cell, Element A)
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

void clean_maze(table &maze)
{
	for(size_t i(0); i < maze.size(); ++i)
		{
			for (size_t j(0); j < maze[i].size(); ++j)
				
				if (maze[i][j] > 0)
					{maze[i][j] = EMPTY;}
		}
}

void display_path(vector<Path> &list)
{	
	size_t size_list = list.size();
	
	list_str list_path;
	for (size_t i(0); i < size_list; ++i)
	{
		list_path.push_back(list[i].movements);
	}
	
	list_path = sort_list(list_path, list_path.size());
	
	for (size_t i(0); i < size_list; ++i)
	{
		cout << list_path[i] << endl;
	}
}

list_str sort_list(list_str list, size_t size_list)
{	
	if (size_list == 1)
	{
		return list;
	}
	
	if (size_list == 2)
	{
		if (one_before_two(list[0], list[1]))
		{
			return list;
		}
		else
		{
			list_str new_list(list);
			string temp(new_list[0]);
			new_list[0] = new_list[1];
			new_list[1] = temp;
			return new_list;
		}
	}
	
	size_t mid(size_list/2);
	list_str left{};
	
	size_t i(0);
	while (i < mid)
	{	
		left.push_back(list[i]);
		++i;
	}

	list_str right{};
	
	size_t j(mid);
	while (j < size_list)
	{	
		right.push_back(list[j]);
		++j;
	}
	j = j-i;
	
	left = sort_list(left, i);
	right = sort_list(right, j);
	
	list_str new_list = merge_list(left, i, right, j);
	
	return new_list;
}

list_str merge_list(list_str left, size_t size_l, list_str right, size_t size_r)
{
	size_t i(0), j(0);
	list_str sorted_list{};
	
	while (i < size_l and j < size_r)
	{
		if (one_before_two(left[i], right[j]))
		{
			sorted_list.push_back(left[i]);
			++i;
		}
		else
		{
			sorted_list.push_back(right[j]);
			++j;
		}
	}
	
	while (i < size_l)
	{	
		sorted_list.push_back(left[i]);	
		++i;
	}
	
	while (j < size_r)
	{	
		sorted_list.push_back(right[j]);
		++j;
	}
	
	return sorted_list;
}

bool one_before_two(string string1, string string2)
{
	bool one_smaller(false);
	
	// D < L < R < U
	for (size_t i(0); i < string1.size(); ++i)
	{
		if (string1[i] == string2[i])
		{
			continue;
		}
		
		// check string 1 before 2
		if (string1[i] == 'D' and string2[i] != 'D')
		{
			one_smaller = true;
			break;
		}
		if (string1[i] == 'L' and (string2[i] == 'R' or string2[i] == 'U'))
		{
			one_smaller = true;
			break;
		}
		if (string1[i] == 'R' and string2[i] == 'U')
		{
			one_smaller = true;
			break;
		}
		
		break;
	}
	
	return one_smaller;
}


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
