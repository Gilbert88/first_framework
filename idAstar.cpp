
#include <iostream>
#include <ctime>
#include "idAstar.hpp"
#include "mapstruct.hpp"

using namespace std;

double ttime;

double get_seconds() 
{
	return clock();
}

void start_id_Astar(Puzzle_struct *puzzle_input, 
					float &total_time, 
					int &steps)
{
  Puzzle_struct *puzzle = new Puzzle_struct;
  copy_map(puzzle,puzzle_input->map);
  int cutoff = 0;
  int rt = 2;
  ttime = get_seconds();

  while(1){
  	if(rt!=1){
  	  cutoff++;
  	  cout << "Restart with cutoff " << cutoff << endl;
  	  rt =  search_id_Astar(puzzle, 
  	  						0, 
  	  						-1,
  	  						cutoff, 
  	  						total_time, 
  	  						steps);
  	}
  	else{
  	  break;
  	}
  }
}

int search_id_Astar(Puzzle_struct *puzzle,
					 int cost_reach_node, 
					 int action, 
					 int cutoff, 
					 float &total_time, 
					 int &steps)
{
  int x_position;
  int distance_to_final = heuristic1_Mahattan_Distance(puzzle->map, &x_position);

  if(distance_to_final == 0){
  	cout << "Found with cost_reach_node " << cost_reach_node << endl;
  	steps = cost_reach_node;
  	double t = get_seconds();
  	total_time = ((float)(t-ttime))/CLOCKS_PER_SEC;
  	cout << "time = " << total_time << " seconds." << endl;
  	return 1;
  }

  if(distance_to_final + cost_reach_node > cutoff){
  	return 2;
  }

  int x_row, x_col;
  x_row = x_position / SIZE_; x_col = x_position % SIZE_;
  int result = -1;
  Puzzle_struct * puzzle_next =  new Puzzle_struct;

  if(x_row>0 && action !=2){
  	copy_map(puzzle_next,puzzle->map);
  	move_up(puzzle_next,x_row, x_col);

  	result = search_id_Astar(puzzle_next, 
  					 cost_reach_node + 1, 
  					 				   1,
  					 			  cutoff,
  					 		  total_time, 
  					 		      steps);
  	if(result == 1){
  		return result;
  	}
  }

  if(x_row<SIZE_-1 && action != 1){
  	copy_map(puzzle_next,puzzle->map);
  	move_down(puzzle_next,x_row, x_col);
  	result = search_id_Astar(puzzle_next, 
  						cost_reach_node + 1, 
  						2,
  						cutoff, 
  						total_time, 
  						steps);
  	if(result == 1){
  		return result;
  	}
  }

  if(x_col>0 && action != 4){
  	copy_map(puzzle_next,puzzle->map);
  	move_left(puzzle_next,x_row, x_col);
  	result = search_id_Astar(puzzle_next, 
  						cost_reach_node + 1, 
  						3,
  						cutoff, 
  						total_time, 
  						steps);
  	
  	if(result == 1){
  		return result;
  	}
  }

  if(x_col<SIZE_-1 && action != 3){
  	copy_map(puzzle_next,puzzle->map);
  	move_right(puzzle_next,x_row, x_col);
  	result = search_id_Astar(puzzle_next, 
  						cost_reach_node + 1, 
  						4,
  						cutoff, 
  						total_time, 
  						steps);
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
  return distance;
}
