/*
 *
 */
#include "constant.hpp"
#include "mapstruct.hpp"
#include "stdio.h"
#include "stdlib.h"

void start_id_Astar(Puzzle_struct *puzzle_input);
int search_id_Astar(Puzzle_struct *puzzle, int cost_reach_node , int action , int cutoff );
int heuristic1_Mahattan_Distance(int map[size][size] ,int *x_position);
