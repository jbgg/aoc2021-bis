#include <stdio.h>
#include <stdint.h>

extern char _input[];

#define N (100)

int64_t _input2[N][N];

int64_t s[N][N];

void fill(int i, int j, int prev){
	int snew;
	if(i<0 || i>=N || j<0 || j>=N){
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
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			s[i][j] = -1;
			_input2[i][j] = _input[i*(N+1) + j] - '0';
			printf("%d", _input2[i][j]);
		}
		printf("\n");
	}
	s[0][0] = 0;

	fill(1, 0, 0);
	fill(0, 1, 0);

	printf("%d\n", s[N-1][N-1]);

	return 0;
}
