#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main (int argc,char* args[]){
	int fd = open("lab3.txt",O_RDONLY);
	int status = system("touch write.txt");
	int fw = open("write.txt", O_RDWR | O_CREAT);

	int ft = ftruncate(fw,4);
	char* data = (char *)mmap(NULL, 10, PROT_READ,MAP_PRIVATE,fd,0);
	
	char *write = (char*)mmap(NULL, 10, PROT_READ|PROT_WRITE,MAP_SHARED,fw,0);

	memcpy(write,data,4);
munmap(data,10);
munmap(write,10);

close(fd);
close(fw);
return 0;
	
}
