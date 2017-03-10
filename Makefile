FLAGS = -Wall -lssl -lcrypto
DEPENDENCIES = keygen.h

all: nicekeys

nicekeys: keygen.o
	gcc ${FLAGS} -o $@ $^

%.o: %.c ${DEPENDENCIES}
	gcc ${FLAGS} -c $<

clean: 
	rm *.o nicekeys
