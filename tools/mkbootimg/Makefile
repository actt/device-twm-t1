CC=gcc
OBJS=  mkbootimg.o  rsa.o  sha.o
EXEC=mkbootimg

CFLAGS=-Iinclude

.c.o:
	$(CC) -c ${CFLAGS} $^

${EXEC}:${OBJS}
	$(CC) -o ${EXEC} ${LDFLAGS} ${OBJS}
clean:
	rm -rf ${EXEC} ${OBJS}
