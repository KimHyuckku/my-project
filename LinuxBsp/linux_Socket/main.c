#include <stdio.h>
#define BUFFSIZE 100

int main(int argc, char * argv[])
{
	int i=0;
	char buf[BUFFSIZE];
	while(1)
	{
		printf("Hello World i=%d\n", i++);
	}
	return 0;
} 

