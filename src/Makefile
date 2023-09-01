CC=g++
CFLAGS= -c  
FILES = s21_matrix_oop.cc
TEST_FLAGS=-lgtest -lgmock -pthread
TEST_FUNC= mytest.cc

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	TEST_FLAGS += -lsubunit -lrt -lm
	DOX = echo 'you must install doxygen'
	VAL = echo 'you must install doxygen'
else
	DOX =brew install doxygen
endif

all: test

installDox:
	$(DOX)

installVal:
	sudo apt-get install libgtest-dev libgmock-dev -y
	sudo apt install g++ -y

dvi: clean
	doxygen Doxyfile
	open html/index.html

clean:
	rm -rf *.a *.o report gcov test *.gcno *.gcda html s21_matrix_oop.a

s21_matrix_oop.a:
	$(CC) $(CFLAGS) $(FILES)
	ar rcs s21_matrix_oop.a $(FILES:.cc=.o)
	rm *.o

clang:
	clang-format -style="{BasedOnStyle: Google}" -n *.h *.cc

goclang:
	clang-format -style="{BasedOnStyle: Google}" -i *.h *.cc

test: clean s21_matrix_oop.a
	$(CC) $(TEST_FUNC) s21_matrix_oop.a -o test $(TEST_FLAGS)
	./test

valgrind: clean test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s ./test

check_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(FILES) *.h

leaks: clean s21_matrix_oop.a
	$(CC) $(TEST_FUNC) s21_matrix_oop.a -o test $(TEST_FLAGS)
	leaks -atExit -- ./test
.PHONY: installDox dvi clean s21_matrix_oop.a clang goclang test valgrind check_cppcheck