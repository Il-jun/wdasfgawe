myfs : main.o scan_comm.o make_fs.o a.o data_b.o prompt.o mycpfrom.o sblock.o mydatablock.o
	gcc -o myfs main.o scan_comm.o make_fs.o a.o data_b.o prompt.o mycpfrom.o sblock.o mydatablock.o
main.o : func.h make_fs.c prompt.c scan_comm.c 
	gcc -c main.c
scan_comm.o : func.h struct.h make_fs.c a.c data_b.c mycpfrom.c prompt.c 
	gcc -c scan_comm.c
make_fs.o : func.h a.c 
	gcc -c make_fs.c
a.o : header.h func.h 
	gcc -c a.c
data_b.o : func.h struct.h sblock.c 
	gcc -c data_b.c
prompt.o : func.h struct.h
	gcc -c prompt.c
mycpfrom.o : func.h struct.h sblock.c a.c data_b.c
	gcc -c mycpfrom.c
mydatablock.o : func.h struct.h 
	gcc -c mydatablock.c
sblock.o : sblock.c
	gcc -c sblock.c

