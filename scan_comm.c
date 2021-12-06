#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void scan_comm (char ** comm1, char ** comm2, char ** comm3) {
	char *temp;
	char *p_str = NULL;
	int total_size = 0, size = 0, comm_num = 1; 
	
	temp = malloc(sizeof(char));
	while (1) {  
		fgets(temp, 2, stdin);
		size = strlen(temp);
		total_size += size;
		if (!strcmp(temp, " ")){
			switch (comm_num) {
				case 1 :
					*comm1 = p_str;
					break;
				case 2 :
					*comm2 = p_str;
					break;
			}
			p_str = NULL;
			comm_num++;
			continue;
		}
		if (!strcmp("\n", temp)) {
			if (comm_num == 1)
				*comm1 = p_str;
			if (comm_num == 2)
				*comm2 = p_str;
			if (comm_num == 3)
				*comm3 = p_str;
			break;
		}
			
		if (p_str == NULL) {  
			p_str = (char *)malloc(total_size + 1);
			strcpy(p_str, temp);
		}
		else {
			p_str = (char *)realloc(p_str, total_size + 1);
			strcat(p_str, temp);
		}
	}
}

void cmp_comm (char * comm1, char * comm2, char * comm3) {
	if (strcmp(comm1, "mymkfs") == 0) {
		make_fs();
	}
	if (!strcmp(comm1, "myls")) {
		if (comm2 == NULL)
			;
		else 
			myls_1(comm2);
	}
	if (strcmp(comm1, "mycat") == 0) {
		if (comm2 == NULL)
			printf ("need file name\n");
		else {
			inode i;
			i = find_file (comm2);
			load_file(i.inode_num);
		}
	}
		
	if (strcmp(comm1, "myshowfile"))
		;
		
	if (strcmp(comm1, "mypwd") == 0)
		print_pwd();

	if (strcmp(comm1, "mycd") == 0)
		//cd_path(comm2);
		;
		
	if (strcmp(comm1, "mycp") == 0)
		;
		
	if (strcmp(comm1, "mycpto") == 0) {
		if (comm2 == NULL || comm3 == NULL)
			printf ("need file name\n");
		else
			mycpto(comm2, comm3);
	}
		
	if (strcmp(comm1, "mycpfrom") == 0) {
		if (comm2 == NULL || comm3 == NULL)
			printf ("need file name\n");
		else
			mycpfrom(comm2, comm3);
	}
		
	if (strcmp(comm1, "mymkdir") == 0)
		;
		
	if (strcmp(comm1, "myrmdir") == 0)
		;
		
	if (strcmp(comm1, "myrm") == 0)
		;
		
	if (strcmp(comm1, "mymv") == 0)
		;
		
	if (strcmp(comm1, "mytouch") == 0) {
		if (comm2 == NULL) 
			printf ("need file name\n");
		else
			mytouch(comm2);
	}
		
	if (strcmp(comm1, "myinode") == 0) {
		if (comm2 == NULL)
			printf ("need inode number\n");
		else if (atoi(comm2) > 0 && atoi(comm2) < 128)
			myinode(atoi(comm2));
		else
			printf("need inode number\n");
	}
		
	if (strcmp(comm1, "mydatablock") == 0)
		mydatablock(atoi(comm2));
		
	if (strcmp(comm1, "mystate") == 0)
		mystate();
		
	if (strcmp(comm1, "mytree") == 0)
		;
	if (!strcmp(comm1, "exit"))
		exit(0);
}
