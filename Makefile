CC = gcc
FLAGS = -Wall -lssl -lcrypto -O3 -g
DEPENDENCIES = nicekeys.h
OUTFILES = *.o nicekeys
TAGFILES = TAGS ETAGS tags

RM := rm -f

all: tags nicekeys

nicekeys: nicekeys.o
	gcc $(FLAGS) -o $@ $^

%.o: %.c $(DEPENDENCIES)
	$(CC) $(FLAGS) -c $<

tags:
	-ctags -R --exclude LICENSE *
	-etags -R -o ETAGS *

clean:
	$(RM) $(TAGFILES) $(OUTFILES)
