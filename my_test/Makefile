CC=gcc
OBJECT=handler.c
INCLUDE= -I /usr/local/libmemcached/include/ -I /usr/local/libmemached/include/libmemcached/
LIBS_PATH= -L /usr/local/libmemcached/lib/
LIBS= -lmemcached
FLAGS= -g #-std=gnu++0x


all:
	$(CC)  $(FLAGS) $(OBJECT) $(INCLUDE) $(LIBS_PATH) $(LIBS)
	#$(CC)  $(OBJECT) $(INCLUDE) $(LIBS_PATH) $(LIBS)

clean:
	rm -rf a.out *.o
