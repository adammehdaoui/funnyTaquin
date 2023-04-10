# COMPILATION SETTINGS
CC=gcc
CFLAGS=-Wall -ansi -pedantic
LDLIBS=-lMLV -lm -Werror

# DIRECTORIES
OBJDIR=obj
SRCDIR=src
INCDIR=include

# FILES
EXEC=taquin
OBJ=display.o taquin.o main.o

all: taquin

display.o: include/display.h src/display.c
	$(CC) -c src/display.c $(CFLAGS) $(LDLIBS)

taquin.o: include/taquin.h src/taquin.c
	$(CC) -c src/taquin.c $(CFLAGS) $(LDLIBS)

main.o: src/main.c
	$(CC) -c src/main.c $(CFLAGS) $(LDLIBS)

taquin: $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(CFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f taquin

# $(CC) $(CFLAGS) -c $< -o $@ $(LDLIBS)

# in_out.o: include/in_out.h src/in_out.c
# 	$(CC) -c src/in_out.c $(CFLAGS)

# display.o : include/sudoku.h include/display.h src/display.c 
# 	$(CC) -c src/display.c $(CFLAGS) $(LDLIBS)

# sudoku.o: include/sudoku.h src/sudoku.c include/display.h
# 	$(CC) -c src/sudoku.c $(CFLAGS)

# main.o: src/main.c
# 	$(CC) -c src/main.c $(CFLAGS)

# sudoku: $(OBJ)
# 	$(CC) -o $(MAIN) $(OBJ) $(LDLIBS)

# run: $(OBJ)
# 	$(CC) -o $(MAIN) $(OBJ) $(LDLIBS)
# 	./$(MAIN) grid1.txt