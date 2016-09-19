#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <signal.h>
#include <string.h>

void sighandler(int);

char *p;

int main(int args , char* argc[]){
	size_t boundary = 4096;
	size_t size = 1000;
	p = (char *) memalign(boundary,size);
	printf("%p\n",p);
	int m = mprotect(p,100,PROT_READ|PROT_EXEC);

	signal(SIGSEGV,sighandler);
	memcpy((char*)p,"try to write",20);


	printf("Content: %s\nwrtie successfully\n",(char *)p);


	return 0;
}

void sighandler(int signum){
	printf("Caught signal %d, program continuing\n",signum);
	mprotect(p,100,PROT_READ| PROT_WRITE|PROT_EXEC);
}
