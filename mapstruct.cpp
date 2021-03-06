
#include <iostream>
#include "mapstruct.hpp"
#include "constant.hpp"

using namespace std;

void copy_map(Puzzle_struct * ptr, int map_out[SIZE_][SIZE_])
{
	int i,j;
	for( i = 0 ; i < SIZE_ ; i++){
		for(j = 0 ; j < SIZE_ ; j++){
			ptr->map[i][j] = map_out[i][j];
		}
	}
}

void move_up(Puzzle_struct * ptr,int x_row, int x_col)
{
	ptr->map[x_row][x_col] = ptr->map[x_row-1][x_col] ;
	ptr->map[x_row-1][x_col] = -1;
}

void move_down(Puzzle_struct * ptr,int x_row, int x_col)
{
	ptr->map[x_row][x_col] = ptr->map[x_row+1][x_col] ;
	ptr->map[x_row+1][x_col] = -1;
}

void move_left(Puzzle_struct * ptr,int x_row, int x_col)
{
	ptr->map[x_row][x_col] = ptr->map[x_row][x_col-1] ;
	ptr->map[x_row][x_col-1] = -1;
}

void move_right(Puzzle_struct * ptr,int x_row, int x_col)
{
	ptr->map[x_row][x_col] = ptr->map[x_row][x_col+1] ;
	ptr->map[x_row][x_col+1] = -1;
}
