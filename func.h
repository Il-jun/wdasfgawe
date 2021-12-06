#include <stdbool.h>
#ifndef STRUCT_H
#include "struct.h"
#define STRUCT_H
#endif

void make_fs ();
void print_shell();
void op_comm(char *);
void mkinode (int, _Bool, char *);
void set_sblock (_Bool, int);
void mkfirst_sblock();

void clear_inode_data (int i_num);
void mkfirstinode(void);

void mycpfrom (char *, char *);
inode find_file (char *);
void load_file_to_com (int);
void load_file (int);
void mycpto (char *, char *);
inode load_inode (int);
void mytouch(char *);
void add_sblock_data(int);

void print_prompt ();
void print_pwd ();
void set_root_path ();
void set_next_path (char *);
void cd_path (char *);

void mystate ();
void myinode (int);
void add_sblock_inode(int);

void cmp_comm (char *, char *, char *);
void scan_comm (char **, char **, char **);

void show_ls ();
void myls_1(char *);

void save_file_data (int , char *);
int get_size (int);
void load_file (int);
void mkfirst_sblock();

int find_empty_datab ();
int find_empty_inode ();
void add_sblock_inode(int);

void mycpto (char *, char *);
void mydatablock (int);

// stack 구현 함수
void s_reset();
void s_push(char c);
char s_pop();
char s_top();
bool s_empty();
bool s_full();
//queue 구현 함수