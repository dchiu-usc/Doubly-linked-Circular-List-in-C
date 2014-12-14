warmup1: warmup1.o my402list.o print.o sort.o
	gcc -o warmup1 -g warmup1.o my402list.o print.o sort.o

warmup1.o: warmup1.c my402list.h
	gcc -g -c -Wall warmup1.c

my402list.o: my402list.c my402list.h
	gcc -g -c -Wall my402list.c
print.o: print.c 
	gcc -g -c -Wall print.c
sort.o: sort.c
	gcc -g -c -Wall sort.c

clean:
	rm -f *.o warmup1
