#include<stdio.h>
int main(){
	int fd = open('t.txt' ,0);
	write(fd, "test", 4);
	return 1;
}
