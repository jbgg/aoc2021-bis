#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern char _input[];

#define N (100)
#define NN (5*N)

typedef struct {
	/* position */
	int i;
	int j;
	/* v is the cost of this node */
	int v;
	/* min is the minimal distance from [0][0] when the node belongs to A set
	otherwise it's value is -1 */
	int min;
	/* cur is the current minimal distance from [0][0] when the node belongs to B set
	otherwise it's value is -1 */
	int cur;
	/* B_t* pointer to corresponding B_t */
	struct _B_t *B_p;
} node_t;

node_t nodes[NN][NN];

typedef struct _B_t {
	node_t *node_p;
	struct _B_t *next_p;
} B_t;

/* B_head is the first element of the linked list
of nodes that belongs to B set.
This list is sorted by cur value of the nodes.
*/
B_t *B_head;

/* B_insert function adds the node [i][j]
the new value of cur will be
node[i][j].v + minc
if the new value is smaller than the actual value
or if the node does not belong to B set
*/
void B_insert(int i, int j, int minc);
void B_print(); /* this function is for testing purpose */

void B_insert_raw(B_t *B_p);
void B_delete_raw(B_t *B_p);

void create_nodes(){
	int i;
	int j;

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
		nodes[i][j].i = i;
		nodes[i][j].j = j;
		nodes[i][j].B_p = NULL;
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
		nodes[i][j].i = i;
		nodes[i][j].j = j;
		nodes[i][j].B_p = NULL;
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
		nodes[i][j].i = i;
		nodes[i][j].j = j;
		nodes[i][j].B_p = NULL;
	} }
}

int main(int argc, char *argv[]){

	B_head = NULL;

	create_nodes();

	B_insert(0,0,5);
	B_insert(1,0,2);
	B_insert(2,1,3);
	B_insert(0,0,3);

	B_delete_raw(B_head);

	B_print();

	return 0;
}

void B_insert_raw(B_t *B_p){
	B_t **pp;

	pp=&B_head;
	while(pp[0] != NULL &&
		pp[0]->node_p->cur < B_p->node_p->cur){
		pp = &pp[0]->next_p;
	}
	B_p->next_p = pp[0];
	pp[0] = B_p;
}

void B_delete_raw(B_t *B_p){
	B_t **pp;

	pp=&B_head;
	while(pp[0] != B_p){
		pp = &pp[0]->next_p;
	}
	pp[0] = B_p->next_p;
}

void B_insert(int i, int j, int minc){
	node_t *node_p;
	int newcur;

	if(i<0 || i>=NN || j<0 || j>=NN){
		return;
	}

	node_p = &nodes[i][j];

	/* this node is in A set */
	if(node_p->min != -1){
		return;
	}

	newcur = minc + node_p->v;

	if(node_p->cur == -1){
		printf("[%d][%d] cur=-1, newcur=%d\n", node_p->i, node_p->j, newcur);
		node_p->cur = newcur;
		B_t *B_p = malloc(sizeof(B_p));
		node_p->B_p = B_p;
		B_p->node_p = node_p;
		B_p->next_p = NULL;
		B_insert_raw(B_p);
	}else if(newcur < node_p->cur){
		printf("[%d][%d] cur=%d, newcur=%d\n", node_p->i, node_p->j, node_p->cur, newcur);
		B_delete_raw(node_p->B_p);
		node_p->cur = newcur;
		B_insert_raw(node_p->B_p);
	}
}

void B_print(){
	B_t *p;

	p = B_head;
	while(p!=NULL){
		printf("%p %d\n", p->node_p, p->node_p->cur);
		p=p->next_p;
	}
}
