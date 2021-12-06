#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "struct.h"

/*
int main () {
	mkfirst_sblock();
	mkfirstinode();
	mkinode(1, 1, "test");
	save_file_data (1, "test.txt");
	load_file(1);
}
*/

inode load_inode (int inum) {
	FILE *fp;
	fp = fopen("inode.bin", "rb");
	rewind(fp);
	inode tmp;
	while (1) {
		fread(&tmp, sizeof(inode), 1, fp);
		if(tmp.inode_num == inum) 
			break;
	}
	fclose (fp);
	return tmp;
}

void save_file_data (int i_num, char * filename){
	char ch;
	char * temp;
	inode tmp = load_inode(i_num);
	int num = 1;
	FILE * data_b;
	FILE * file = fopen(filename, "r");
	data_b = fopen("datablock.bin", "ab");
	
	while (num < 9) {
		int e_num = find_empty_datab();
		fseek(data_b, 256*e_num, 0);
		while ((ch = getc(file)) != EOF && ftell(file) != 256*num) {
			fwrite (&ch, sizeof(char), 1, data_b);
			if (ftell(file) == 256*num)
				fwrite ("\0", sizeof(char), 1, data_b);
		}
		if (ch == EOF) 
			fwrite ("\0", sizeof(char), 1, data_b);
		add_sblock_data(e_num);
		switch (num) {
			case 1 :
				tmp.data1 = e_num;
				break;
			case 2 :
				tmp.data2 = e_num;
				break;
			case 3 :
				tmp.data3 = e_num;
				break;
			case 4 :
				tmp.data4 = e_num;
				break;
			case 5 :
				tmp.data5 = e_num;
				break;
			case 6 :
				tmp.data6 = e_num;
				break;
			case 7 :
				tmp.data7 = e_num;
				break;
			case 8 :
				tmp.data8 = e_num;
				break;
		}
		num++;
		if (ch == EOF)
			break;
	}
	FILE * fp;
	fp = fopen("inode.bin", "rb+");
	fseek(fp, sizeof(inode) * (i_num-1), 0);
	fwrite(&tmp, sizeof(inode), 1, fp);
	fclose(fp);
}

void make_dir_data (inode * i) {
	char * temp;
	FILE * data_b;
	temp = malloc(256);
	data_b = fopen("datablock.bin", "ab");
	char num;
	char * list = malloc (7);
	
	

}

void load_file (int i_num) {
	FILE * data_b;
	inode tmp = load_inode(i_num);
	int num = 1;
	char ch;
	_Bool b = 0;

	data_b = fopen("datablock.bin", "rb");

	rewind (data_b);
	if ( tmp.data1 ) {
		while (num < tmp.data1) {
			fread(&ch, 1, 1, data_b);
			if (ch == 0x0A) 
				num++;
		}
		do {
			fread(&ch, 1, 1, data_b);
			printf("%c", ch);
		} while (ch != 0x0A);
	}

	if ( tmp.data2 ) {
		while (num < tmp.data2) {
			fread(&ch, 1, 1, data_b);
			if (ch == 0x0A)
				num++;
		}
		do {
			fread(&ch, 1, 1, data_b);
			printf("%c", ch);
		} while (ch != 0x0A);
	}

	if ( tmp.data3 ) {
		while (num < tmp.data3) {
			fread(&ch, 1, 1, data_b);
			if (ch == 0x0A)
				num++;
		}
		do {
			fread(&ch, 1, 1, data_b);
			printf("%c", ch);
		} while (ch != 0x0A);
	}

	if ( tmp.data4 ) {
		while (num < tmp.data4) {
			fread(&ch, 1, 1, data_b);
			if (ch == 0x0A)
				num++;
		}
		do {
			fread(&ch, 1, 1, data_b);
			printf("%c", ch);
		} while (ch != 0x0A);
	}

	if ( tmp.data5 ) {
		while (num < tmp.data5) {
			fread(&ch, 1, 1, data_b);
			if (ch == 0x0A)
				num++;
		}
		do {
			fread(&ch, 1, 1, data_b);
			printf("%c", ch);
		} while (ch != 0x0A);
	}

	if ( tmp.data6 ) {
		while (num < tmp.data6) {
			fread(&ch, 1, 1, data_b);
			if (ch == 0x0A)
				num++;
		}
		do {
			fread(&ch, 1, 1, data_b);
			printf("%c", ch);
		} while (ch != 0x0A);
	}

	if ( tmp.data7 ) {
		while (num < tmp.data7) {
			fread(&ch, 1, 1, data_b);
			if (ch == 0x0A)
				num++;
		}
		do {
			fread(&ch, 1, 1, data_b);
			printf("%c", ch);
		} while (ch != 0x0A);
	}

	if ( tmp.data8 ) {
		while (num < tmp.data8) {
			fread(&ch, 1, 1, data_b);
			if (ch == 0x0A)
				num++;
		}
		do {
			fread(&ch, 1, 1, data_b);
			printf("%c", ch);
		} while (ch != 0x0A);
	}
	
	/*
	if (b==0) {
		fseek(data_b, (256 * tmp.data1)-1, 0);
		do {
			fread (&ch, 1, 1, data_b);
			printf("%c", ch);
			if (ch == '\0') {
				b = 1;
				break;
			}
			num++;
		} while (num<256);
	}
	if (b==0 && tmp.data2 != 0) {
		fseek(data_b, (256 * tmp.data2)-1, 0);
		do {
			fread (&ch, 1, 1, data_b);
			if (ch == '\0') {
				b = 1;
				break;
			}
			printf("%c", ch);
			num++;
		} while (num<256);
	}
	if (b==0 && tmp.data3 != 0) {
		fseek(data_b, (256 * tmp.data3)-1, 0);
		do {
			fread (&ch, 1, 1, data_b);
			if (ch == '\0') {
				b = 1;
				break;
			}
			printf("%c", ch);
			num++;
		} while (num<256);
	}
	if (b==0 && tmp.data4 != 0) {
		fseek(data_b, (256 * tmp.data4)-1, 0);
		do {
			fread (&ch, 1, 1, data_b);
			if (ch == '\0') {
				b = 1;
				break;
			}
			printf("%c", ch);
			num++;
		} while (num<256);
	}
	if (b==0 && tmp.data5 != 0) {
		fseek(data_b, (256 * tmp.data5)-1, 0);
		do {
			fread (&ch, 1, 1, data_b);
			if (ch == '\0') {
				b = 1;
				break;
			}
			printf("%c", ch);
			num++;
		} while (num<256);
	}
	if (b==0 && tmp.data6 != 0) {
		fseek(data_b, (256 * tmp.data6)-1, 0);
		do {
			fread (&ch, 1, 1, data_b);
			if (ch == '\0') {
				b = 1;
				break;
			}
			printf("%c", ch);
			num++;
		} while (num<256);
	}
	if (b==0 && tmp.data7 != 0) {
		fseek(data_b, (256 * tmp.data7)-1, 0);
		do {
			fread (&ch, 1, 1, data_b);
			if (ch == '\0') {
				b = 1;
				break;
			}
			printf("%c", ch);
			num++;
		} while (num<256);
	}
	if (b==0 && tmp.data8 != 0) {
		fseek(data_b, (256 * tmp.data8)-1, 0);
		do {
			fread (&ch, 1, 1, data_b);
			if (ch == '\0') {
				b = 1;
				break;
			}
			printf("%c", ch);
			num++;
		} while (num<256);
	}
	*/
}