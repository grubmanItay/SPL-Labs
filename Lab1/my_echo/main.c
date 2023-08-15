#include <stdio.h>
int main() {
	int c;
	printf("\n my echo: ");
	while (c!=EOF)
	{
	c= getchar();
	putchar(c);
	}
return 0;
}	
