#
# A simple Makefile to make the fas2gb program
#

CC?=gcc
CFLAGS?= -Wall -Wextra -O3 -s

all: fas2gb

fas2gb: fas2gb.c
	$(CC) $(CFLAGS) -o fas2gb fas2gb.c 
