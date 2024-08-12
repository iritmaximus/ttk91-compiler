CC=gcc
CC_FLAGS=-O2 -Wall -Wextra

SRCDIR=src
INCLUDEDIR=include

FILES=$(SRCDIR)/main.c \
	  $(SRCDIR)/scanner.c \
	  $(SRCDIR)/parser.c

scanner: 
	# this is case insensitive!!
	flex -i -o $(SRCDIR)/scanner.c $(SRCDIR)/scanner.flex

parser:
	bison --defines=$(INCLUDEDIR)/token.h --output=$(SRCDIR)/parser.c $(SRCDIR)/parser.bison -Wcounterexamples

all: scanner parser
	$(CC) $(CC_FLAGS) -I$(INCLUDEDIR) $(FILES) -o compiler
