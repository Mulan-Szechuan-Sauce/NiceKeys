FLAGS = -Wall -lssl -lcrypto -O3 -g
DEPENDENCIES = nicekeys.h

all: nicekeys

nicekeys: nicekeys.o
	gcc ${FLAGS} -o $@ $^

%.o: %.c ${DEPENDENCIES}
	gcc ${FLAGS} -c $<

clean: 
	rm *.o nicekeys
