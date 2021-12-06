#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

char * comm1 = NULL, * comm2 = NULL, * comm3 = NULL;

pwd_list * path_list;
pwd_list * b_path;

int main (){
	make_fs();
	set_root_path();
	do {
		print_prompt();
		scan_comm(&comm1, &comm2, &comm3);
		cmp_comm(comm1, comm2, comm3);
	} while(1);
}

// make_fs.c, prompt.c scan_comm.c