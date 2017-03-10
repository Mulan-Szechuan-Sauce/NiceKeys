FLAGS = -Wall -lssl -lcrypto
DEPENDENCIES = nicekeys.h

all: nicekeys

nicekeys: nicekeys.o
	gcc ${FLAGS} -o $@ $^

%.o: %.c ${DEPENDENCIES}
	gcc ${FLAGS} -c $<

clean: 
	rm *.o nicekeys
