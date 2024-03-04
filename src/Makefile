CFLAGS=-Werror -Wextra -Wall 
CC=gcc
FSAN=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector

all: simple_db

rebuild: clean pascal_matrix

simple_db: simple_db.c my_db.c
	$(CC) $(CFLAGS) simple_db.c my_db.c -o ../bin/simple_db	

build_fsanitize:
	$(CC) $(CFLAGS) $(FSAN) pascal_triangle.c pascal.c -o ../bin/pascal_triangle
	$(CC) $(CFLAGS) $(FSAN) pascal_matrix.c pascal.c -o ../bin/pascal_matrix	

clean:
	rm -rf *.o *.out

check:
	clang-format -style='{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 110}' -i *.c
	clang-format -style='{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 110}' -i *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	# valgrind --tool=memcheck --leak-check=yes ../bin/pascal_triangle
	# valgrind --tool=memcheck --leak-check=yes ../bin/pascal_matrix
