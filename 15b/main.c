#include <stdio.h>
#include <stdint.h>

extern char _input[];

#define N (10)
#define NN (5*N)

int64_t _input2[NN][NN];

int64_t s[NN][NN];

void fill(int i, int j, int prev){
	int snew;
	if(i<0 || i>=NN || j<0 || j>=NN){
		return;
	}
	snew = prev + _input2[i][j];
	if(s[i][j] == -1
		|| snew < s[i][j]){
		s[i][j] = snew;
		fill(i-1,j, snew);
		fill(i,j-1, snew);
		fill(i+1,j, snew);
		fill(i,j+1, snew);
	}
}

int main(int argc, char *argv[]){
	int i;
	int j;
	int k;

	/* i
		j 0 1 2 3 4 ...
	   0      X
	   1
	   2
	   3
	   4
	*/
	for(i=0;i<N;i++){ for(j=0;j<N;j++){
			s[i][j] = -1;
			_input2[i][j] = _input[i*(N+1) + j] - '0';
	} }
	s[0][0] = 0;

	/* i
		j 0 1 2 3 4 ...
	   0      Y X X X X
	   1
	   2
	   3
	   4
	*/
	for(i=0;i<N;i++){ for(j=N;j<NN;j++){
		s[i][j] = -1;
		int64_t t = _input2[i][j - N];
		_input2[i][j] = (t == 9) ? 1 : t+1;
	} }


	/* i
		j 0 1 2 3 4 ...
	   0      Y Y Y Y Y
	   1      X X X X X
	   2      X X X X X
	   3      X X X X X
	   4      X X X X X
	*/
	for(i=N;i<NN;i++){ for(j=0;j<NN;j++){
		s[i][j] = -1;
		int64_t t = _input2[i-N][j];
		_input2[i][j] = (t == 9) ? 1 : t+1;
	} }

	fill(1, 0, 0);
	fill(0, 1, 0);

	printf("%d\n", s[NN-1][NN-1]);

	return 0;
}
