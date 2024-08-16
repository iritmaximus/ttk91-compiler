CC=gcc
CC_FLAGS=-O2 -Wall -Wextra -g

SRCDIR=src
INCLUDEDIR=include

FILES=$(SRCDIR)/main.c \
	  $(SRCDIR)/scanner.c \
	  $(SRCDIR)/parser.c \
	  $(SRCDIR)/expr.c \
	  $(SRCDIR)/label.c \
	  $(SRCDIR)/ttk_register.c \
	  $(SRCDIR)/comment.c \
	  $(SRCDIR)/oper.c \
	  $(SRCDIR)/value.c

scanner: 
	flex -o $(SRCDIR)/scanner.c $(SRCDIR)/scanner.flex

parser:
	bison --defines=$(INCLUDEDIR)/token.h --output=$(SRCDIR)/parser.c $(SRCDIR)/parser.bison -Wcounterexamples --debug -t

all: scanner parser
	$(CC) $(CC_FLAGS) -I$(INCLUDEDIR) $(FILES) -o compiler
