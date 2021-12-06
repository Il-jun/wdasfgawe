#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void make_fs(){
	FILE * myfs;
	myfs = fopen("myfs.bin", "rb");
	if (myfs == NULL) { //myfs가 존재하지 않음
		printf("파일시스템이 없습니다. 파일시스템을 만듭니다.\n");
		myfs = fopen("myfs.bin", "wb");
		fclose(myfs);
		mkfirstinode();
	}
	else {
		char *  ch;
		ch = malloc (sizeof(char));
		printf("파일시스템이 있습니다. 다시 만들겠습니까? (y/n) : ");
		do {
			scanf("%s", ch);
			getchar();
			if (!strcmp(ch, "y") || !strcmp(ch, "n"))
				break;
		} while (1);
		if (!strcmp(ch, "y")){
			fclose(myfs);
			myfs = fopen("myfs.bin", "wb");		
			fclose(myfs);
			mkfirstinode();
		}
		else {
			fclose(myfs);
	}
}
}
