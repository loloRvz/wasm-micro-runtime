#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>

#include "wasm_export.h"
#include "bh_read_file.h"
#include "bh_getopt.h"
#include "time.h"


char ctrl_bytes[] = {0x4c,0x6f,0x72,0x65,0x6d,0x20,0x69,0x70,0x73,0x75,0x6d,0x20,0x64,0x6f,0x6c,0x6f,0x72,0x20,0x73,0x69,0x74,0x20,0x61,0x6d,0x65,0x74,0x2c,0x20,0x63,0x6f,0x6e,0x73,0x65,0x63,0x74,0x65,0x74,0x75,0x72,0x20,0x61,0x64,0x69,0x70,0x69,0x73,0x63,0x69,0x6e,0x67,0x20,0x65,0x6c,0x69,0x74,0x2c,0x20,0x73,0x65,0x64,0x20,0x64,0x6f,0x20,0x65,0x69,0x75,0x73,0x6d,0x6f,0x64,0x20,0x74,0x65,0x6d,0x70,0x6f,0x72,0x20,0x69,0x6e,0x63,0x69,0x64,0x69,0x64,0x75,0x6e,0x74,0x20,0x75,0x74,0x20,0x6c,0x61,0x62,0x6f,0x72,0x65,0x20,0x65,0x74,0x20,0x64,0x6f,0x6c,0x6f,0x72,0x65,0x20,0x6d,0x61,0x67,0x6e,0x61,0x20,0x61,0x6c,0x69,0x71,0x75,0x61,0x2e,0x20,0x55,0x74,0x20,0x65,0x6e,0x69,0x6d,0x20,0x61,0x64,0x20,0x6d,0x69,0x6e,0x69,0x6d,0x20,0x76,0x65,0x6e,0x69,0x61,0x6d,0x2c,0x20,0x71,0x75,0x69,0x73,0x20,0x6e,0x6f,0x73,0x74,0x72,0x75,0x64,0x20,0x65,0x78,0x65,0x72,0x63,0x69,0x74,0x61,0x74,0x69,0x6f,0x6e,0x20,0x75,0x6c,0x6c,0x61,0x6d,0x63,0x6f,0x20,0x6c,0x61,0x62,0x6f,0x72,0x69,0x73,0x20,0x6e,0x69,0x73,0x69,0x20,0x75,0x74,0x20,0x61,0x6c,0x69,0x71,0x75,0x69,0x70,0x20,0x65,0x78,0x20,0x65,0x61,0x20,0x63,0x6f,0x6d,0x6d,0x6f,0x64,0x6f,0x20,0x63,0x6f,0x6e,0x73,0x65,0x71,0x75,0x61,0x74,0x2e,0x20,0x44,0x75,0x69,0x73,0x20,0x61,0x75,0x74,0x65,0x20,0x69,0x72,0x75,0x72,0x65,0x20,0x64,0x6f,0x6c,0x6f,0x72,0x20,0x69,0x6e,0x20,0x72,0x65,0x70,0x72,0x65,0x68,0x65,0x6e,0x64,0x65,0x72,0x69,0x74,0x20,0x69,0x6e,0x20,0x76,0x6f,0x6c,0x75,0x70,0x74,0x61,0x74,0x65,0x20,0x76,0x65,0x6c,0x69,0x74,0x20,0x65,0x73,0x73,0x65,0x20,0x63,0x69,0x6c,0x6c,0x75,0x6d,0x20,0x64,0x6f,0x6c,0x6f,0x72,0x65,0x20,0x65,0x75,0x20,0x66,0x75,0x67,0x69,0x61,0x74,0x20,0x6e,0x75,0x6c,0x6c,0x61,0x20,0x70,0x61,0x72,0x69,0x61,0x74,0x75,0x72,0x2e,0x20,0x45,0x78,0x63,0x65,0x70,0x74,0x65,0x75,0x72,0x20,0x73,0x69,0x6e,0x74,0x20,0x6f,0x63,0x63,0x61,0x65,0x63,0x61,0x74,0x20,0x63,0x75,0x70,0x69,0x64,0x61,0x74,0x61,0x74,0x20,0x6e,0x6f,0x6e,0x20,0x70,0x72,0x6f,0x69,0x64,0x65,0x6e,0x74,0x2c,0x20,0x73,0x75,0x6e,0x74,0x20,0x69,0x6e,0x20,0x63,0x75,0x6c,0x70,0x61,0x20,0x71,0x75,0x69,0x20,0x6f,0x66,0x66,0x69,0x63,0x69,0x61,0x20,0x64,0x65,0x73,0x65,0x72,0x75,0x6e,0x74,0x20,0x6d,0x6f,0x6c,0x6c,0x69,0x74,0x20,0x61,0x6e,0x69,0x6d,0x20,0x69,0x64,0x20,0x65,0x73,0x74,0x20,0x6c,0x61,0x62,0x6f,0x72,0x75,0x6d,0x2e};
size_t ctrl_bytes_size = sizeof(ctrl_bytes);

int native_callback(wasm_exec_env_t exec_env, char *buffer, int buffer_len, int t0){
	struct timespec t1,t2;
	clock_gettime(CLOCK_REALTIME, &t1);
	
	printf("Inside native callback!\n");
	/*printf("length: %d\n",buffer_len);
	for(int i=0; i<buffer_len; i++){
		printf("%c",buffer[i]);
	}printf("\n\n");
	*/
	//printf("Native call time: %f ms\n",(float)(t1.tv_nsec-t0)/1000000);
	//printf("%f\n",(float)(t1.tv_nsec-t0)/1000000);
	

	clock_gettime(CLOCK_REALTIME, &t2);
	return t2.tv_nsec;
}


void print_usage(void){
    fprintf(stdout, "Options:\r\n");
    fprintf(stdout, "  -f [path of wasm file] \n");
}

int main(int argc, char *argv[]){
	char *buffer, error_buf[128];
	int opt;
	char * wasm_path;
	int arglen = 0;

	wasm_module_t module = NULL;
	wasm_module_inst_t module_inst = NULL;
	wasm_exec_env_t exec_env = NULL;
	int buf_size, stack_size = 8092, heap_size = 8092;
	int wasm_buffer = 0;

	RuntimeInitArgs init_args;
	memset(&init_args, 0, sizeof(RuntimeInitArgs));

	while ((opt = getopt(argc, argv, "hf:a:")) != -1){
		switch (opt){
			case 'f':
				wasm_path = optarg;
				break;
			case 'a':
				arglen = atoi(optarg);
				break;
			case 'h':
				print_usage();
				return 0;
			case '?':
				print_usage();
				return 0;
			}
		}
		if (optind == 1) {
			print_usage();
			return 0;
	}

	static NativeSymbol native_symbols[] = {
		EXPORT_WASM_API_WITH_SIG(native_callback, "(*~i)i"),
	};

    init_args.mem_alloc_type = Alloc_With_Allocator;
    init_args.mem_alloc_option.allocator.malloc_func = malloc;
    init_args.mem_alloc_option.allocator.realloc_func = realloc;
    init_args.mem_alloc_option.allocator.free_func = free;

	// Native symbols need below registration phase
	init_args.n_native_symbols = sizeof(native_symbols) / sizeof(NativeSymbol);
	init_args.native_module_name = "env";
	init_args.native_symbols = native_symbols;

	if (!wasm_runtime_full_init(&init_args)) {
		printf("Init runtime environment failed.\n");
		return -1;
	}
	
	buffer = bh_read_file_to_buffer(wasm_path, &buf_size);
    if(!buffer) {
        printf("Open wasm app file [%s] failed.\n", wasm_path);
        goto fail;
    }

	//Load wasm module
	module = wasm_runtime_load(buffer, buf_size, error_buf, sizeof(error_buf));
	if(!module) {
		printf("Load wasm module failed. error: %s\n", error_buf);
		goto fail;
	}

	//Instantiate wasm module
	module_inst = wasm_runtime_instantiate(module, stack_size, heap_size, error_buf, sizeof(error_buf));
	if(!module_inst) {
		printf("Instantiate wasm module failed. error: %s\n", error_buf);
		goto fail;
	}

	//Prepare func arguments
	int app_argc = (arglen<0) ? 0 : arglen;
	char **app_argv;
	app_argv = (char**)malloc((app_argc)*sizeof(char*));
	
	printf("Inside native!\n");
	for(int i=0; i<app_argc; i++){
		app_argv[i] = &ctrl_bytes[i];
		//printf("%c",*app_argv[i]);
	}//printf("\n\n");
	
	//Execute
	struct timespec start,stop;
	clock_gettime(CLOCK_REALTIME, &start);
	const char *exception;
	wasm_application_execute_main(module_inst, app_argc, app_argv);
	if ((exception = wasm_runtime_get_exception(module_inst))){
		printf("%s\n", exception);
	}
	clock_gettime(CLOCK_REALTIME, &stop);
	printf("Full program time: %f ms\n",(float)(stop.tv_sec-start.tv_sec)*1000+(float)(stop.tv_nsec-start.tv_nsec)/1000000);
	//printf("%f\n",(float)(stop.tv_sec-start.tv_sec)*1000+(float)(stop.tv_nsec-start.tv_nsec)/1000000);
	
fail:
	if(exec_env) wasm_runtime_destroy_exec_env(exec_env);
	if(module_inst) {
		if(wasm_buffer) wasm_runtime_module_free(module_inst, wasm_buffer);
		wasm_runtime_deinstantiate(module_inst);
	}
	if(module) wasm_runtime_unload(module);
	if(buffer) free(buffer);
	wasm_runtime_destroy();
	return 0;
}





