CC=gcc
CFLAGS=-g
TARGET:test.exe

OBJS=gluelist/gllist.o	\
	 graph.o	\
	 topology.o

test.exe:testapp.o ${OBJS}
	${CC} ${CFLAGS} testapp.o ${OBJS} -o test.exe

testapp.o:testapp.c
	${CC} ${CFLAGS} -c testapp.c -o testapp.o

gluelist/gllist.o:gluelist/gllist.c
	${CC} ${CFLAGS} -c -I gllist gluelist/gllist.c -o gluelist/gllist.o
graph.o:graph.c
	${CC} ${CFLAGS} -c -I . graph.c -o graph.o
topologies.o:topology.c
	${CC} ${CFLAGS} -c -I . topology.c -o topology.o

clean:
	rm *.o
	rm gluelist/gllist.o
	rm *exe
