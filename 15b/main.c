#include <stdio.h>
#include <stdint.h>

extern char _input[];

#define N (100)
#define NN (5*N)

typedef struct {
	int v; /* the cost of this node */
	int min; /* minimal distance from [0][0] */
	int cur; /* current minimal distance from [0][0] */
} node_t;

node_t nodes[NN][NN];

void create_nodes(){
	int i;
	int j;
	int k;

	/* Reding from _input the first block
	     0 1 2 3 4
	   0 X
	   1
	   2
	   3
	   4
	*/
	for(i=0;i<N;i++){ for(j=0;j<N;j++){
		/* assuming '\n' has size 1 in _input */
		/* getting the i-th row and j-th column from _input */
		nodes[i][j].v = _input[i*(N+1) + j] - '0';
		nodes[i][j].min = -1;
		nodes[i][j].cur = -1;
	} }

	/* fill in the following blocks
	  0 1 2 3 4
	0 Y X X X X
	1
	2
	3
	4
	*/
	for(i=0;i<N;i++){ for(j=N;j<NN;j++){
		int t = nodes[i][j - N].v;
		nodes[i][j].v = (t == 9) ? 1 : t+1;
		nodes[i][j].min = -1;
		nodes[i][j].cur = -1;
	} }


	/* fill in the following blocks
	     0 1 2 3 4
	   0 Y Y Y Y Y
	   1 X X X X X
	   2 X X X X X
	   3 X X X X X
	   4 X X X X X
	*/
	for(i=N;i<NN;i++){ for(j=0;j<NN;j++){
		int t = nodes[i-N][j].v;
		nodes[i][j].v = (t == 9) ? 1 : t+1;
		nodes[i][j].min = -1;
		nodes[i][j].cur = -1;
	} }
}

int main(int argc, char *argv[]){
	create_nodes();
	return 0;
}
