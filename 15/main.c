#include <stdio.h>

extern char _input[];

int main(int argc, char *argv[]){
	int i;
	char c;
	for(i=0;(c=_input[i])!=0;i++){
		printf("%c", c);
	}
	return 0;
}
