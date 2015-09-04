/*
 * Sequential Version of N Puzzle Solver
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include "mapstruct.hpp"
#include "idAstar.hpp"

 using namespace std;

int main(int argv, char **argc){
	int i;
	FILE *file;
	file = fopen("testPuzzle.txt", "r");

	char buffer[100];

	int map[size][size];
	int count = 0,j = 0,pre = 0;

	int myid,numprocs;
	int  namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	while( fgets (buffer, 60, file)!=NULL ) {
	      int map_i = 0;
	      while(buffer[j]!='\n'){
	    	  if(buffer[j] == ' '){
	    		  buffer[j] = '\0';
	    		  map[count][map_i] = atoi(&buffer[pre]);
	    		  pre = j+1;
	    		  map_i ++;
	    	  }
	    	  j++;
	      }
	      buffer[j] = '\0';
	      map[count][map_i] = atoi(&buffer[pre]);
	      pre = 0;j=0;count++;
	}

	for(i = 0 ; i < size ; i ++){
		for(j = 0 ; j < size ; j ++){
			cout << map[i][j];
		}
		cout << endl;
	}
	Puzzle_struct *puzzle = new Puzzle_struct;
	copy_map(puzzle,map);
	start_id_Astar(puzzle);
	return 0;
}
