#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "struct.h"

void mydatablock (int d_num) {
	FILE * data_b;
	int num;
	char ch;

	data_b = fopen("datablock.bin", "rb");
	rewind (data_b);

	if ( d_num ) {
		while (num < d_num) {
			fread(&ch, 1, 1, data_b);
			if (ch == 0x0A) 
				num++;
		}
		do {		
			fread(&ch, 1, 1, data_b);
			printf("%c", ch);
		} while (ch != 0x0A);
	}
}