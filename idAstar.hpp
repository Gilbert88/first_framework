#include "constant.hpp"
#include "mapstruct.hpp"
#include "stdio.h"
#include "stdlib.h"

void start_id_Astar(Puzzle_struct *puzzle_input, int &total_time, int &steps);
int search_id_Astar(Puzzle_struct *puzzle, int cost_reach_node , int action , int cutoff, int &total_time, int &steps);
int heuristic1_Mahattan_Distance(int map[SIZE_][SIZE_] ,int *x_position);