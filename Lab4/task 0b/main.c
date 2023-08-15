#include "util.h"
#define SYS_OPEN 5
#define SYS_LSEEK 19
#define SYS_WRITE 4
#define SYS_CLOSE 6
int main (int argc , char* argv[], char* envp[])
{
	char* fileName = argv[1];
	char* X_NAME = argv[2];
	int fd = system_call(SYS_OPEN, fileName, 0x002, 0x700);
	system_call(SYS_LSEEK, fd, 0X291, 1);
	system_call(SYS_WRITE, fd, X_NAME, strlen(X_NAME));
	system_call(SYS_CLOSE, fd);
  return 0;
}
