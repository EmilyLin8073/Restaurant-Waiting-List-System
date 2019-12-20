proj4base: proj4base1.o proj4base2.o proj4base3.o
	gcc -o proj4base proj4base1.o proj4base2.o proj4base3.o

proj4base1.o: proj4base1.c proj4base.h
	gcc -std=c99 -c proj4base1.c

proj4base2.o: proj4base2.c proj4base.h
	gcc -std=c99 -c proj4base2.c

proj4base3.o: proj4base3.c proj4base.h
	gcc -std=c99 -c proj4base3.c
