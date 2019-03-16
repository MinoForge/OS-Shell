# 
# Makefile
# 
# Written by Dr. William Kreahling
#            Department of Mathematics and Computer Science
#            Western Carolina University
#
# A GNU Makefile for building the WCU UNIX shell.
# TODO Put all files in the same folder or will not compile
CC=gcc
CFLAGS=-O -Wall -Wextra -ggdb
LIBS=-lfl
LEX=flex
RM=rm -f

OBJECTS=shellParser.o history.o builtin.o redirect.o shell.o LinkedQueue.o Malloc.o
PROG=shell

all:	$(PROG)

shellParser.c:	shellParser.l shellParser.h
	$(LEX) -t shellParser.l > shellParser.c


shellParser.o:	shellParser.c
shell.o:		shell.c shell.h shellParser.h
history.o:		history.c history.h
builtin.o:		builtin.c builtin.h shell.h
redirect.o:		redirect.c shell.h redirect.h
LinkedQueue.o:  LinkedQueue.c LinkedQueue.h Queue.h
Malloc.o:       Malloc.c Malloc.h

shell:	history.o redirect.o builtin.o shell.o shellParser.o LinkedQueue.o Malloc.o
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROG) $(LIBS)

clean:
	$(RM) shellParser.c $(OBJECTS) $(PROG)
