#include <stdio.h>
#include <stdlib.h>
#include "time.h"


int native_callback(char *buffer, int buffer_len, int t0);

int main(int argc, char **argv){
	char *buffer = (char*)malloc((argc)*sizeof(char));
	int buffer_len = argc;
	
	printf("Inside wasm!\n");
	/*printf("argc: %d\n",argc);
	for(int i=0; i<argc; i++){
		printf("%c",*argv[i]);
		buffer[i] = *argv[i];
	}printf("\n\n");
	*/
	struct timespec t0,t3;
	clock_gettime(CLOCK_REALTIME, &t0);
	int t2 = native_callback(buffer, buffer_len, t0.tv_nsec);
	clock_gettime(CLOCK_REALTIME, &t3);
	//printf("Native return time: %f ms\n",(float) (t3.tv_nsec-t2)/1000000);
	//printf("%f\n",(float) (t3.tv_nsec-t2)*0.000001);
	
	return 0;
}
