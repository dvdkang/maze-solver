# Generic Makefile for compiling a single C program and linking with relevant
# math, MyroC, bluetooth, and jpeg libraries for CSC 161

# To build a program "foo" from "foo.c", simply type "make foo". 
# To build an object file "foo.o" from "foo.c", simply type "make foo.o"
# We rely on make's implicit rules foo.c -> foo.o for compiling and
# foo.o --> foo for linking

# Set compiler to clang, rather than the system default
CC = clang

# Set preprocessor flags
CPPFLAGS+=-I/home/walker/MyroC/include

# Set appropriate compiler flags
CFLAGS+=-Wall -Werror -std=c11 -g 

# Set linker flags to include the relevant libraries
LDFLAGS+=

all: solve

# List program components

solve: path.o maze.o queue.o solve.o
	$(CC) $(LDFLAGS) -o $@ $^

solve.o: solve.c path.h maze.h queue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

path.o: path.c path.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

maze.o: maze.c maze.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

queue.o: queue.c queue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

#----------------------------------------------------------------------------
# cleanup rules: To invoke this command, type "make clean".
# Use this target to clean up your directory, deleting (without warning) 
#   object files, old emacs source versions, and core dumps.

clean: 
	rm -f solve *.o *~ core*
