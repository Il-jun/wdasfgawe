#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define INODE 1
#define DBLOCK 0

typedef struct sblock{
	unsigned inode1 : 32, inode2 : 32, inode3 : 32, inode4 : 32;
	unsigned data1 : 32, data2 : 32, data3 : 32, data4 : 32, data5 : 32, data6 : 32, data7 : 32, data8 : 32;
}sblock;

void add_sblock_data(int data_num) // 인자로 추가할 data 번호
{
   sblock tmp;
   int data_a = 0;
   int data_b = 0;
   unsigned mask;

   data_a = (data_num / 32) + 1;
   data_b = data_num % 32;   

   mask = 1 << (32 - data_b);

   FILE * fp;

   fp = fopen("superblock.bin","rb");
   rewind(fp);

   fread(&tmp, sizeof(sblock), 1, fp);

   fclose(fp);

   switch(data_a){
      case 1 :
         tmp.data1 = (tmp.data1 | mask);
         break;
      case 2 :
         tmp.data2 = (tmp.data2 | mask);
         break;
      case 3 :
         tmp.data3 = (tmp.data3 | mask);
         break;
      case 4 :
         tmp.data4 = (tmp.data4 | mask);
         break;
      case 5 :
         tmp.data5 = (tmp.data5 | mask);
         break;
      case 6 :
         tmp.data6 = (tmp.data6 | mask);
         break;
      case 7 :
         tmp.data7 = (tmp.data7 | mask);
         break;
      case 8 :
         tmp.data8 = (tmp.data8 | mask);
         break;
   }

   fp = fopen("superblock.bin", "wb");
   rewind(fp);

   fwrite(&tmp, sizeof(sblock), 1, fp);

   fclose(fp);

}

void mkfirst_sblock(void){ //mkfs 와 함께 호출
        sblock tmp = {0x80000000,0};

        FILE * fp;
        fp = fopen("superblock.bin","wb");

        fwrite((void*)&tmp, sizeof(sblock), 1, fp);

        fclose(fp);
}

void add_sblock_inode(int inode_num) // 인자로 추가할 inode 번호
{
	sblock tmp;
	int inode_a = 0;
	int inode_b = 0;
	unsigned mask;

	inode_a = (inode_num / 32) + 1;
	inode_b = inode_num % 32;	

	mask = 1 << (32 - inode_b);

	FILE * fp;

	fp = fopen("superblock.bin","rb");
	rewind(fp);

	fread(&tmp, sizeof(sblock), 1, fp);

	fclose(fp);

	switch(inode_a){
		case 1 :
			tmp.inode1 = (tmp.inode1 | mask);
			break;
		case 2 :
			tmp.inode2 = (tmp.inode2 | mask);
			break;
		case 3 :
			tmp.inode3 = (tmp.inode3 | mask);
			break;
		case 4 :
			tmp.inode4 = (tmp.inode4 | mask);
			break;
	}

	fp = fopen("superblock.bin", "wb");
	rewind(fp);

	fwrite(&tmp, sizeof(sblock), 1, fp);

	fclose(fp);

}

void rm_sblock_inode(int inode_num) // 인자로 삭제할 inode 번호
{
	sblock tmp;
	int inode_a = 0;
	int inode_b = 0;
	unsigned mask;

	inode_a = (inode_num / 32) + 1;
	inode_b = inode_num % 32;

	mask = 1 << (32 - inode_b);

	FILE * fp;

	fp = fopen("superblock.bin","rb");
	rewind(fp);

	fread(&tmp, sizeof(sblock), 1, fp);

	fclose(fp);

	switch(inode_a){
		case 1 :
			tmp.inode1 = (tmp.inode1 ^ mask);
			break;
		case 2 :
			tmp.inode2 = (tmp.inode2 ^ mask);
			break;
		case 3 :
			tmp.inode3 = (tmp.inode3 ^ mask);
			break;
		case 4 :
			tmp.inode4 = (tmp.inode4 ^ mask);
			break;
	}

	fp = fopen("superblock.bin", "wb");
	rewind(fp);

	fwrite(&tmp, sizeof(sblock), 1, fp);

	fclose(fp);

}



int count_used_inode(void)
{
	sblock tmp;
	unsigned mask = 1 << 31;
	int used_inode = 0;
	int i;

	FILE * fp;
	fp = fopen("superblock.bin", "rb");
	rewind(fp);

	fread(&tmp, sizeof(sblock), 1, fp);

	fclose(fp);

	for(i = 1; i <= 32; ++i){
		if((tmp.inode1 & mask) != 0)
			++used_inode;
		mask >>= 1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if((tmp.inode2 & mask) != 0)
			++used_inode;
		mask >>= 1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if((tmp.inode3 & mask) != 0)
			++used_inode;
		mask >>= 1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if((tmp.inode4 & mask) != 0)
			++used_inode;
		mask >>= 1;
	}
	mask = 1 << 31;

	return used_inode;
}

int count_used_data(void)
{
	sblock tmp;
	unsigned mask = 1 << 31;
	int used_data = 0;
	int i;

	FILE * fp;
	fp = fopen("superblock.bin", "rb");
	rewind(fp);

	fread(&tmp, sizeof(sblock), 1, fp);

	fclose(fp);

	for(i = 1; i <= 32; ++i){
		if((tmp.data1 & mask) != 0)
			++used_data;
		mask >>= 1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if((tmp.data2 & mask) != 0)
			++used_data;
		mask >>= 1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if((tmp.data3 & mask) != 0)
			++used_data;
		mask >>= 1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if((tmp.data4 & mask) != 0)
			++used_data;
		mask >>= 1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if((tmp.data5 & mask) != 0)
			++used_data;
		mask >>= 1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if((tmp.data6 & mask) != 0)
			++used_data;
		mask >>= 1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if((tmp.data7 & mask) != 0)
			++used_data;
		mask >>= 1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if((tmp.data8 & mask) != 0)
			++used_data;
		mask >>= 1;
	}
	mask = 1 << 31;

	return used_data;
}

int find_empty_inode (void) {
	sblock temp;
	unsigned mask = 1 << 31;
	int i = 0;
	FILE * fp;
	fp = fopen("superblock.bin","rb");
	rewind(fp);

	fread(&temp, sizeof(sblock), 1, fp);

	fclose(fp);
	
	for(i = 1; i <= 32; ++i){
		if ((temp.inode1 & mask) == 0)
			return i;
		mask >>=1;
	}

	mask = 1 << 31;
	for(i = 1; i <= 32; ++i){
		if ((temp.inode2 & mask) == 0)
			return i + 32;
		mask >>=1;
	}

	mask = 1 << 31;
	for(i = 1; i <= 32; ++i){
		if ((temp.inode3 & mask) == 0)
			return i + 64;
		mask >>=1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if ((temp.inode4 & mask) == 0)
			return i + 96;
		mask >>=1;
	}
}


int find_empty_datab (void) {
	sblock temp;
	unsigned mask = 1 << 31;
	int i = 0;
	FILE * fp;
	fp = fopen("superblock.bin","rb");
	rewind(fp);

	fread(&temp, sizeof(sblock), 1, fp);

	fclose(fp);
	
	for(i = 1; i <= 32; ++i){
		if ((temp.data1 & mask) == 0)
			return i;
		mask >>=1;
	}

	mask = 1 << 31;
	for(i = 1; i <= 32; ++i){
		if ((temp.data2 & mask) == 0)
			return i + 32;
		mask >>=1;
	}

	mask = 1 << 31;
	for(i = 1; i <= 32; ++i){
		if ((temp.data3 & mask) == 0)
			return i + 64;
		mask >>=1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if ((temp.data4 & mask) == 0)
			return i + 96;
		mask >>=1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if ((temp.data5 & mask) == 0)
			return i + 128;
		mask >>=1;
	}

	mask = 1 << 31;
	for(i = 1; i <= 32; ++i){
		if ((temp.data6 & mask) == 0)
			return i + 160;
		mask >>=1;
	}

	mask = 1 << 31;
	for(i = 1; i <= 32; ++i){
		if ((temp.data7 & mask) == 0)
			return i + 192;
		mask >>=1;
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		if ((temp.data8 & mask) == 0)
			return i + 224;
		mask >>=1;
	}
	mask = 1 << 31;
}


void mystate(void)
{
	sblock tmp;
	unsigned mask = 1 << 31;
	int used_inode = count_used_inode();
	int used_data = count_used_data();
	int i;


	FILE * fp;
	fp = fopen("superblock.bin","rb");
	rewind(fp);

	fread(&tmp, sizeof(sblock), 1, fp);

	fclose(fp);

	printf("Inode state :\n");
	printf("    Total : 128\n");
	printf("    Used : %d\n", used_inode);
	printf("    Available : %d\n", 128 - used_inode);

	printf("    Inode Map :\n     ");
	for(i = 1; i <= 32; ++i){
		putchar(((tmp.inode1 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		putchar(((tmp.inode2 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');

	}
	printf("\n     ");
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		putchar(((tmp.inode3 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		putchar(((tmp.inode4 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');

	}
	printf("\n");
	mask = 1 << 31;

	printf("Data Block state :\n");
	printf("    Total : 256 blocks / %d byte\n", 256 * 256);
	printf("    Used : %d blocks / %d byte\n", used_data, used_data * 256);
	printf("    Available : %d blocks / %d byte\n", 128 - used_data, (256 - used_data) * 256);

	printf("    Inode Map :\n     ");
	for(i = 1; i <= 32; ++i){
		putchar(((tmp.data1 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		putchar(((tmp.data2 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');
	}
	printf("\n     ");
	mask = 1 << 31;


	for(i = 1; i <= 32; ++i){
		putchar(((tmp.data3 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		putchar(((tmp.data4 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');
	}
	printf("\n     ");
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		putchar(((tmp.data5 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		putchar(((tmp.data6 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');
	}
	printf("\n     ");
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		putchar(((tmp.data7 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');
	}
	mask = 1 << 31;

	for(i = 1; i <= 32; ++i){
		putchar(((tmp.data8 & mask) == 0) ? '0' : '1');
		mask >>=1;
		if(i % 4 == 0)
			putchar(' ');
	}
	printf("\n");
	mask = 1 << 31;

}

