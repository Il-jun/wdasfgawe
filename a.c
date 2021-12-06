#include "header.h"
#include "func.h"

char * set_time(void) //시간설정함수
{
	char * time_ = malloc(sizeof(char) * 20);

	struct tm * date;
	const time_t t = time(NULL);
	date = localtime(&t);

	sprintf(time_, "%d/%d/%d %d:%d:%d", date -> tm_year + 1900, date -> tm_mon + 1, date -> tm_mday, date -> tm_hour, date -> tm_min, date -> tm_sec);
	return (time_);
}

int get_size(int i_num) //인자로 inode 번호, 파일 총 크기 리턴
{
	int size = 0;
	char * temp;
	char ch;
	inode tmp;
	int num = 1;

	FILE * fp = fopen("inode.bin","rb");
	rewind(fp);

	while(1) {
		fread(&tmp, sizeof(inode), 1, fp);
		if(tmp.inode_num == i_num)
			break;
	}
	fclose(fp);
	fp = fopen("datablock.bin","rb");

	if(tmp.data1 != 0) {
		rewind (fp);
		while (num < tmp.data1) {
			fread (&ch, 1, 1, fp);
			if (ch == 0x0A) {
				num++;
				break;
			}
		}
		do {
			fread (&ch, 1, 1, fp);
			size++;
		} while (ch != 0x0A);
	}

	num = 1;
	if(tmp.data2 != 0) {
		rewind (fp);
		while (num < tmp.data2) {
			fread (&ch, 1, 1, fp);
			if (ch == 0x0A) {
				num++;
				break;
			}
		}
		do {
			fread (&ch, 1, 1, fp);
			size++;
		} while (ch != 0x0A);
	}

	num = 1;
	if(tmp.data3 != 0) {
		rewind (fp);
		while (num < tmp.data3) {
			fread (&ch, 1, 1, fp);
			if (ch == 0x0A) {
				num++;
				break;
			}
		}
		do {
			fread (&ch, 1, 1, fp);
			size++;
		} while (ch != 0x0A);
	}

	num = 1;
	if(tmp.data4 != 0) {
		rewind (fp);
		while (num < tmp.data4) {
			fread (&ch, 1, 1, fp);
			if (ch == 0x0A) {
				num++;
				break;
			}
		}
		do {
			fread (&ch, 1, 1, fp);
			size++;
		} while (ch != 0x0A);
	}

	num = 1;
	if(tmp.data5 != 0) {
		rewind (fp);
		while (num < tmp.data5) {
			fread (&ch, 1, 1, fp);
			if (ch == 0x0A) {
				num++;
				break;
			}
		}
		do {
			fread (&ch, 1, 1, fp);
			size++;
		} while (ch != 0x0A);
	}

	num = 1;
	if(tmp.data6 != 0) {
		rewind (fp);
		while (num < tmp.data6) {
			fread (&ch, 1, 1, fp);
			if (ch == 0x0A) {
				num++;
				break;
			}
		}
		do {
			fread (&ch, 1, 1, fp);
			size++;
		} while (ch != 0x0A);
	}

	num = 1;
	if(tmp.data7 != 0) {
		rewind (fp);
		while (num < tmp.data7) {
			fread (&ch, 1, 1, fp);
			if (ch == 0x0A) {
				num++;
				break;
			}
		}
		do {
			fread (&ch, 1, 1, fp);
			size++;
		} while (ch != 0x0A);
	}

	num = 1;
	if(tmp.data8 != 0) {
		rewind (fp);
		while (num < tmp.data8) {
			fread (&ch, 1, 1, fp);
			if (ch == 0x0A) {
				num++;
				break;
			}
		}
		do {
			fread (&ch, 1, 1, fp);
			size++;
		} while (ch != 0x0A);
	}
	fclose (fp);
	return size;
}

void clear_inode_data(int i_num)
{
	FILE * fp;
	inode tmp;

	fp = fopen("inode.bin","rb+");
	rewind(fp);

	while(1)
	{
		fread(&tmp,sizeof(inode), 1, fp);
		if(tmp.inode_num == i_num)
			break;
	}

	tmp.data1 = 0;
	tmp.data2 = 0;
	tmp.data3 = 0;
	tmp.data4 = 0;
	tmp.data5 = 0;
	tmp.data6 = 0;
	tmp.data7 = 0;
	tmp.data8 = 0;


	fseek(fp, -sizeof(inode), SEEK_CUR);
	fwrite(&tmp, sizeof(inode), 1, fp);

	fclose(fp);
}




void mkfirstinode(void) // 루트디렉터리 생성;
{
	FILE * fp;

	fp = fopen("inode.bin", "wb");

	inode root;
	root.inode_num = 1;
	root.type = 0;
	root.filename = malloc (sizeof(char) * 4); // root 이름 저장을 위한 메모리 할당
	strcat(root.filename, "root"); // root 이름 저장
	root.time_ = malloc(sizeof(char) * 20);
	root.time_ = set_time();

	rewind(fp);
	fwrite(&root, sizeof(inode), 1, fp);
	fclose(fp);

	clear_inode_data(1);
	mkfirst_sblock();
}

void mkinode(int inode_num, _Bool type, char * filename)
{
	FILE * fp;

	fp = fopen("inode.bin", "ab+");

	inode mkinode;
	mkinode.inode_num = inode_num;
	mkinode.type = type;
	mkinode.filename = malloc(sizeof(char) * 8);
	strcpy(mkinode.filename, filename);
	mkinode.time_ = malloc(sizeof(char) * 20);
	mkinode.time_ = set_time();

	fseek(fp, -1, SEEK_END);
	fwrite(&mkinode, sizeof(inode), 1, fp);
	fclose(fp);



	clear_inode_data(inode_num);
}
/*
   void mydatablock(int num) // 인자로 데이터 블록 번호
   {
   char *tmp = malloc(sizeof(char) * 256);

   FILE * fp;
   fp = fopen("datablock.bin", "rb");
   fseek(fp, sizeof(char) * 256 * num - 1, SEEK_SET);

   fread((void *)&tmp, sizeof(char) * 256, 1,fp);

   fclose(fp);

   printf("\n%s", tmp);

   }
   */

   void mytouch(char * filename)
   {
   FILE * fp;
   fp = fopen("inode.bin","rb+");

   inode tmp;

   rewind(fp);

   while(1)
   {
   fread(&tmp, sizeof(inode), 1, fp);
   if(!strcmp(tmp.filename, filename))
   break;
   }

   tmp.time_ = set_time();

   fseek(fp, -sizeof(inode), SEEK_CUR);

   fwrite(&tmp, sizeof(inode), 1, fp);

   fclose(fp);


   }






void tmp_inode_2(void) //임시 inode 2개 생성;
{

	char * b_fname = "hi_b";
	char * c_fname = "hi_c";
	//	sleep(1);
	mkinode(2, 1, b_fname);
	{
		FILE * fp;
		inode tmp;

		fp = fopen("inode.bin","rb+");
		rewind(fp);

		while(1)
		{
			fread(&tmp,sizeof(inode), 1, fp);
			if(tmp.inode_num == 2)
				break;
		}

		tmp.data1 = 2;
		tmp.data2 = 3;
		tmp.data3 = 4;
		tmp.data4 = 5;
		tmp.data5 = 6;
		tmp.data6 = 0;
		tmp.data7 = 0;
		tmp.data8 = 0;



		fseek(fp, -sizeof(inode), SEEK_CUR);
		fwrite((void *)&tmp, sizeof(inode), 1, fp);

		fclose(fp);
	}

	//	sleep(1);
	mkinode(3, 0, c_fname);


}

void myinode(int inum) 	//인자 출력할 inode 번호 

{
	FILE *fp;
	fp = fopen("inode.bin", "rb");

	rewind(fp);

	inode tmp;

	while(1)
	{
		fread(&tmp, sizeof(inode), 1, fp);
		if(tmp.inode_num == inum) 
			break;
	}

	if(tmp.type == 0)
		printf("파일종류 : 디렉터리\n");
	else if(tmp.type == 1)
		printf("파일종류 : 파일\n");

	printf("생성일자 : %s\n", tmp.time_);
	printf("직업 블록 목록 : \n");


	if(tmp.data1)
		printf("    #0 직접 데이터 블록 : %d\n", tmp.data1);
	if(tmp.data2)
		printf("    #1 직접 데이터 블록 : %d\n", tmp.data2);
	if(tmp.data3)
		printf("    #2 직접 데이터 블록 : %d\n", tmp.data3);
	if(tmp.data4)
		printf("    #3 직접 데이터 블록 : %d\n", tmp.data4);
	if(tmp.data5)
		printf("    #4 직접 데이터 블록 : %d\n", tmp.data5);
	if(tmp.data6)
		printf("    #5 직접 데이터 블록 : %d\n", tmp.data6);
	if(tmp.data7)
		printf("    #6 직접 데이터 블록 : %d\n", tmp.data7);
	if(tmp.data8)
		printf("    #7 직접 데이터 블록 : %d\n", tmp.data8);
	printf("간접 블록 번호 : 0\n");






}


void myls_1(char * file_name) // myls로 파일이름 인자로 있을떄
{
	FILE * fp;
	fp = fopen("inode.bin", "rb+");

	inode tmp;
	
	rewind(fp);
	while(1)
	{
		fread(&tmp, sizeof(inode), 1, fp);
		if(!strcmp(tmp.filename, file_name))
			break;
	}

	if(tmp.type == 0)
		printf("%s directory %5d %dbyte\n", tmp.time_, tmp.inode_num, get_size(tmp.inode_num));

	else if(tmp.type = 1)
		printf("%s file      %5d %dbyte\n", tmp.time_, tmp.inode_num, get_size(tmp.inode_num));

	fclose(fp);	
}
/*
int main(void)
{
	char * check_fname = "hi";  //생성할 파일 이름
	mkfirstinode();
	tmp_inode_2();		//2번, 3번 inode생성
	mkinode(4, 1, check_fname); //4번 inode생성

	FILE * fp;
	if ((fp = fopen("inode.bin","rb"))==NULL){
		fprintf(stderr, "파일 열 수 없음");
	}

	inode tmp;

	rewind(fp);


	fread(&tmp, sizeof(inode), 1, fp);
	printf(" root inode 정보 / inode번호 : %d inode type : %d 파일 이름 : %s 생성 시간 : %s\n", tmp.inode_num, tmp.type, tmp.filename, tmp.time_);

	fread(&tmp, sizeof(inode), 1, fp);
	printf(" 2번  inode 정보 / inode번호 : %d inode type : %d 파일 이름 : %s 생성 시간 : %s\n", tmp.inode_num, tmp.type, tmp.filename, tmp.time_);

	fread(&tmp, sizeof(inode), 1, fp);
	printf(" 3번  inode 정보 / inode번호 : %d inode type : %d 파일 이름 : %s 생성 시간 : %s\n", tmp.inode_num, tmp.type, tmp.filename, tmp.time_);

	fread(&tmp, sizeof(inode), 1, fp);
	printf(" 4번  inode 정보 / inode번호 : %d inode type : %d 파일 이름 : %s 생성 시간 : %s\n", tmp.inode_num, tmp.type, tmp.filename, tmp.time_);
	fclose(fp);

	printf("\n");

	int a;
	printf("myinode로 확인할 inode 번호 : **2번으로 테스트 가능 ** : ");
	scanf("%d", &a);
	myinode(a);

	printf("\n");

	char *b = malloc(sizeof(char)*8);
	printf("myls로 확인할 파일 이름 : ");
	scanf("%s", b);
	myls_1(b);


	printf("\n\n\n mystate:\n");
	mystate();


	printf("\n\n\n\n mystouch로 2번 시간 초기화\n\n");

	mytouch("hi_b");







	printf("\n\n\n최종확인 \n");

	if ((fp = fopen("inode.bin","rb"))==NULL){
		fprintf(stderr, "파일 열 수 없음");
	}

	rewind(fp);


	fread(&tmp, sizeof(inode), 1, fp);
	printf(" root inode 정보 / inode번호 : %d inode type : %d 파일 이름 : %s 생성 시간 : %s\n", tmp.inode_num, tmp.type, tmp.filename, tmp.time_);

	fread(&tmp, sizeof(inode), 1, fp);
	printf(" 2번  inode 정보 / inode번호 : %d inode type : %d 파일 이름 : %s 생성 시간 : %s\n", tmp.inode_num, tmp.type, tmp.filename, tmp.time_);

	fread(&tmp, sizeof(inode), 1, fp);
	printf(" 3번  inode 정보 / inode번호 : %d inode type : %d 파일 이름 : %s 생성 시간 : %s\n", tmp.inode_num, tmp.type, tmp.filename, tmp.time_);

	fread(&tmp, sizeof(inode), 1, fp);
	printf(" 4번  inode 정보 / inode번호 : %d inode type : %d 파일 이름 : %s 생성 시간 : %s\n", tmp.inode_num, tmp.type, tmp.filename, tmp.time_);
	fclose(fp);//	printf("myls인자 없을떄\n");
	//	myls_0(3);

}
*/
