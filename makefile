# COMPILATION SETTINGS
CC=gcc
CFLAGS=-Wall -std=c17
LDLIBS=-lMLV -lm -Werror

# DIRECTORIES
OBJDIR=obj
SRCDIR=src
INCDIR=include

# FILES
EXEC=taquin
OBJ=obj/display.o obj/taquin.o obj/utils.o obj/main.o

.PHONY: all run force clean

all: $(EXEC)

$(OBJDIR)/display.o: include/display.h src/display.c
	$(CC) -c src/display.c -o obj/display.o $(CFLAGS) $(LDLIBS) 

$(OBJDIR)/taquin.o: include/taquin.h src/taquin.c
	$(CC) -c src/taquin.c -o obj/taquin.o $(CFLAGS) $(LDLIBS)

$(OBJDIR)/utils.o: include/utils.h src/utils.c
	$(CC) -c src/utils.c -o obj/utils.o $(CFLAGS) $(LDLIBS)  

$(OBJDIR)/main.o: src/main.c
	$(CC) -c src/main.c -o obj/main.o $(CFLAGS) $(LDLIBS)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(CFLAGS) $(LDLIBS)

run: $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(CFLAGS) $(LDLIBS)
	./$(EXEC)

force:
	make --always-make

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(EXEC)
