CC = gcc

CFLAGS += -std=gnu11
CFLAGS += -Wall -Werror

wc: wc.c
	${CC} ${CFLAGS} -o wc wc.c
