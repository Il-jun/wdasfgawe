#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "func.h"

inode find_file (char * file_name) {
	FILE *fp;
	fp = fopen("inode.bin", "rb");
	rewind(fp);
	inode tmp;
	while (1) {
		fread(&tmp, sizeof(inode), 1, fp);
		if(!strcmp(file_name, tmp.filename)) 
			break;
	}
	fclose (fp);
	return tmp;
}

void mycpfrom (char * host_file, char * saved_file_name) {
	FILE * host_f;
	FILE * sfile;
	
	if ((host_f = fopen(host_file, "r")) == NULL)
		printf("can't find file\nfile name : %s\n", host_file);
	else {
		int e_inode = find_empty_inode();
		add_sblock_inode(e_inode);
		mkinode(e_inode, 1, saved_file_name);
		save_file_data (e_inode, host_file);
	}
}

void load_file_to_com (int i_num) {
	FILE * data_b;
	inode tmp = load_inode(i_num);
	int num = 0;
	char ch;
	_Bool b = 0;

	data_b = fopen("datablock.bin", "rb");
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
}

void mycpto (char * source, char * host_file) {
	
	FILE * host_f;
	FILE * source_f;
	char ch;
	int count = 1;
	inode tmp;
	int num = 1;

	tmp = find_file (source);
	host_f = fopen(host_file, "w");
	source_f = fopen("datablock.bin", "rb");

	if ( tmp.data1 ) {
		while (num < tmp.data1) {
			fread(&ch, 1, 1, source_f);
			if (ch == 0x0A) 
				num++;
		}
		do {
			fread(&ch, 1, 1, source_f);
			putc (ch, host_f);
		} while (ch != 0x0A);
	}
	if ( tmp.data2 ) {
		while (num < tmp.data2) {
			fread(&ch, 1, 1, source_f);
			if (ch == 0x0A) 
				num++;
		}
		do {
			fread(&ch, 1, 1, source_f);
			putc (ch, host_f);
		} while (ch != 0x0A);
	}
	if ( tmp.data3 ) {
		while (num < tmp.data3) {
			fread(&ch, 1, 1, source_f);
			if (ch == 0x0A) 
				num++;
		}
		do {
			fread(&ch, 1, 1, source_f);
			putc (ch, host_f);
		} while (ch != 0x0A);
	}
	if ( tmp.data4 ) {
		while (num < tmp.data4) {
			fread(&ch, 1, 1, source_f);
			if (ch == 0x0A) 
				num++;
		}
		do {
			fread(&ch, 1, 1, source_f);
			putc (ch, host_f);
		} while (ch != 0x0A);
	}
	if ( tmp.data5 ) {
		while (num < tmp.data5) {
			fread(&ch, 1, 1, source_f);
			if (ch == 0x0A) 
				num++;
		}
		do {
			fread(&ch, 1, 1, source_f);
			putc (ch, host_f);
		} while (ch != 0x0A);
	}
	if ( tmp.data6 ) {
		while (num < tmp.data6) {
			fread(&ch, 1, 1, source_f);
			if (ch == 0x0A) 
				num++;
		}
		do {
			fread(&ch, 1, 1, source_f);
			putc (ch, host_f);
		} while (ch != 0x0A);
	}
	if ( tmp.data7 ) {
		while (num < tmp.data7) {
			fread(&ch, 1, 1, source_f);
			if (ch == 0x0A) 
				num++;
		}
		do {
			fread(&ch, 1, 1, source_f);
			putc (ch, host_f);
		} while (ch != 0x0A);
	}
	if ( tmp.data8 ) {
		while (num < tmp.data8) {
			fread(&ch, 1, 1, source_f);
			if (ch == 0x0A) 
				num++;
		}
		do {
			fread(&ch, 1, 1, source_f);
			putc (ch, host_f);
		} while (ch != 0x0A);
	}
	fclose (host_f);
	fclose (source_f);
}