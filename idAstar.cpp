/*
 *
 */
#include <iostream>
#include <ctime>
#include "idAstar.hpp"
#include "mapstruct.hpp"

using namespace std;

double ttime;

double get_seconds() {
  // struct timeval tp;
  // gettimeofday(&tp, NULL);
  // return (double) (tp.tv_sec + ((1e-6)*tp.tv_usec));
	return clock();
}


void start_id_Astar(Puzzle_struct *puzzle_input, float &total_time, int &steps){

	Puzzle_struct *puzzle = new Puzzle_struct;
	copy_map(puzzle,puzzle_input->map);
	int cutoff = 0;
	int rt = 2;
	ttime = get_seconds();
//	long tStart = System.currentTimeMillis();
	while(1){

		if(rt!=1){
			cutoff++;
			cout << "Restart with cutoff " << cutoff << endl;
			rt =  search_id_Astar(puzzle, 0, -1,cutoff, total_time, steps);
		}
		else{
			break;

		}
	}
//	//long tEnd = System.currentTimeMillis();
//	long tDelta = tEnd - tStart;
//	double elapsedSeconds = tDelta / 1000.0;

	//System.exit(0);
}


int search_id_Astar(Puzzle_struct *puzzle, int cost_reach_node , int action , int cutoff, float &total_time, int &steps){
	int x_position;
	int distance_to_final = heuristic1_Mahattan_Distance(puzzle->map, &x_position);
	//System.out.cout << "distance_to_final is " << distance_to_final << endl;
	if(distance_to_final == 0){
		//puzzle.print_map();
		cout << "Found with cost_reach_node " << cost_reach_node << endl;
		//System.out.cout << "The rout is %s.\n",puzzle.route);
		steps = cost_reach_node;
		//id_Astar.final_route +=puzzle.route;
		double t = get_seconds();
		total_time = ((float)(t-ttime))/CLOCKS_PER_SEC;
		cout << "time = " << total_time << " seconds." << endl;
		return 1;
		//exit(0);
	}
	if(distance_to_final + cost_reach_node > cutoff){
		//System.out.cout << "Reach cutoff with cost_reach_node " << cost_reach_node << endl;
		return 2;
	}

	int x_row, x_col;
	x_row = x_position / SIZE_; x_col = x_position % SIZE_;
	//System.out.cout << "xrow = %d, xcol = %d\n", x_row,x_col);
	int result = -1;
	Puzzle_struct * puzzle_next =  new Puzzle_struct;

	if(x_row>0 && action !=2){
		//move up
		//System.out.print("Move up\n");
		//puzzle_next.copy_map(puzzle.map);
		copy_map(puzzle_next,puzzle->map);
		move_up(puzzle_next,x_row, x_col);
		//puzzle_next->route = puzzle->route+"u";
		//puzzle_next.print_map();
		result = search_id_Astar(puzzle_next, cost_reach_node + 1, 1,cutoff, total_time, steps);
		if(result == 1){
			return result;
		}
	}
	if(x_row<SIZE_-1 && action != 1){
		//move down
		//System.out.print("Move down\n");
		copy_map(puzzle_next,puzzle->map);
		move_down(puzzle_next,x_row, x_col);
		//puzzle_next.route = puzzle.route+"d";
		//puzzle_next.print_map();
		result = search_id_Astar(puzzle_next, cost_reach_node + 1, 2,cutoff, total_time, steps);
		if(result == 1){
			return result;
		}
	}
	if(x_col>0 && action != 4){
		//move left
		//System.out.print("Move left\n");
		copy_map(puzzle_next,puzzle->map);
		move_left(puzzle_next,x_row, x_col);
		//puzzle_next.route = puzzle.route+"l";
		//puzzle_next.print_map();
		result = search_id_Astar(puzzle_next, cost_reach_node + 1, 3,cutoff, total_time, steps);
		if(result == 1){
			return result;
		}
	}
	if(x_col<SIZE_-1 && action != 3){
		//move right
		//System.out.print("Move right\n");
		copy_map(puzzle_next,puzzle->map);
		move_right(puzzle_next,x_row, x_col);
		//puzzle_next.route = puzzle.route+"r";
		//puzzle_next.print_map();
		result = search_id_Astar(puzzle_next, cost_reach_node + 1, 4,cutoff, total_time, steps);
		if(result == 1){
			return result;
		}
	}
	delete puzzle_next;
	return 2;
}

int heuristic1_Mahattan_Distance(int map[SIZE_][SIZE_] ,int *x_position){
		int i,j,distance = 0;
		int row,col;
		for(i = 0; i<SIZE_ ; i++){
			for(j = 0 ; j < SIZE_ ; j++){
				if(map[i][j] == -1){
					*x_position = i * SIZE_ + j ;
				}
				else{
					row = (map[i][j]-1)/SIZE_;
					col = (map[i][j]-1)%SIZE_;
					distance+=abs(row-i)+abs(col-j);
				}
			}
		}
		//cout << "distance = %d", distance);
		return distance;
}
