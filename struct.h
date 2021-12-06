#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifndef STRUCT_H
#define STRUCT_H

typedef struct sblock{
	unsigned inode1 : 32, inode2 : 32, inode3 : 32, inode4 : 32;
	unsigned data1 : 32, data2 : 32, data3 : 32, data4 : 32, data5 : 32, data6 : 32, data7 : 32, data8 : 32;
}sblock;

typedef struct inode{
	int inode_num;
	_Bool type;//디럭터리인지 파일인지 구분(디렉터리 = 0, 파일 = 1)
	char * filename;   // 파일 이름 최대 7글자
	char * time_;//만들어진 시간을 확인
	int data1;
	int data2;
	int data3;
	int data4;
	int data5;
	int data6;
	int data7 ;
	int data8;
	int indata;
	struct inode *iptr;

}inode; // inode를 위한 구조체 선언

typedef struct pwd_list {
	char * name;
	struct pwd_list * next;
} pwd_list;

typedef struct stack {
	char s;
	int top;
} stack;

#endif
