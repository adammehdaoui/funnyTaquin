CC := gcc
CFLAGS := -Wall
LDLIBS := -lMLV -lm -Werror

all : main

main :
	$(CC) -o main main.c $(LDLIBS) $(CFLAGS)

run : 
	$(CC) -o main main.c $(LDLIBS) $(CFLAGS)
	./main

clean : 
	rm *.o