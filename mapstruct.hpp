
#ifndef MAPSTRUCT_H_
#define MAPSTRUCT_H_
#include "constant.hpp"

struct puzzle_struct{
	int map[size][size];
	char *route;
};

typedef struct puzzle_struct Puzzle_struct;

void move_up(Puzzle_struct * ptr,int x_row, int x_col);
void move_down(Puzzle_struct * ptr,int x_row, int x_col);
void move_left(Puzzle_struct * ptr,int x_row, int x_col);
void move_right(Puzzle_struct * ptr,int x_row, int x_col);
void copy_map(Puzzle_struct * ptr, int map_out[size][size]);
#endif /* MAPSTRUCT_H_ */
