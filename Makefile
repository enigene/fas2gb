#
# A simple Makefile to make the fas2gb program
#

CC?=gcc
CFLAGS?= -Wall -Wextra -O3 -s

all: fas2gb

fas2gb: fas2gb.c
<<<<<<< HEAD
	$(CC) $(CFLAGS) -o fas2gb fas2gb.c
=======
	$(CC) $(CFLAGS) -o fas2gb fas2gb.c 
>>>>>>> 2eefc6db619a3df363eebbf54031e915c0d7bd55
