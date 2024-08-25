OS := $(shell uname)

GCC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = --std=c++17
LINKFLAGS = -lstdc++ -lm
GCOV_FLAGS = -fprofile-arcs -ftest-coverage --coverage
LCOV_FLAG = --ignore-errors inconsistent

SRC = s21_matrix_oop.cpp 
TEST_SRC = test.cpp

TEST_OUTPUT = test
GCOV_OUTPUT = ./gcov/gcov_test

ifeq ($(OS), Darwin)
	GTEST_FLAGS = -I/opt/homebrew/opt/googletest/include -L/opt/homebrew/opt/googletest/lib -lgtest -lgtest_main -pthread
	OPEN_CMD = open
	LCOV_FLAG = --ignore-errors inconsistent
else
	GTEST_FLAGS = -I/usr/include/gtest -L/usr/lib -lgtest -lgtest_main -pthread
	OPEN_CMD = xdg-open
	LCOV_FLAG = 
endif


all: s21_matrix_oop.a test gcov_report


s21_matrix_oop.a:
	$(GCC) $(CFLAGS) $(CPPFLAGS) -c $(SRC) -o s21_matrix_oop.o
	ar rcs libs21_matrix_oop.a s21_matrix_oop.o
	ranlib libs21_matrix_oop.a


test: s21_matrix_oop.a
	$(GCC) $(CFLAGS) $(CPPFLAGS) $(TEST_SRC) -o $(TEST_OUTPUT) $(GTEST_FLAGS) $(LINKFLAGS) -L. -ls21_matrix_oop
	./$(TEST_OUTPUT)


gcov_report:
	mkdir -p gcov
	$(GCC) $(CFLAGS) $(CPPFLAGS) $(TEST_SRC) $(SRC) -o $(GCOV_OUTPUT) $(GTEST_FLAGS) $(GCOV_FLAGS) $(LINKFLAGS)
	./gcov/gcov_test
ifeq ($(OS), Darwin)
	mv *.gcno *.gcda ./gcov
endif
	lcov --capture --directory ./gcov --output-file ./gcov/coverage.info $(LCOV_FLAG)
	lcov --remove ./gcov/coverage.info '/opt/homebrew/opt/googletest/*' '/usr/*' --output-file ./gcov/coverage.info $(LCOV_FLAG)
	genhtml -o ./gcov/report ./gcov/coverage.info $(LCOV_FLAG)
	$(OPEN_CMD) ./gcov/report/index.html


leaks: test
ifeq ($(OS), Darwin)
	leaks --atExit -- ./test
else
	valgrind --leak-check=full --show-leak-kinds=all ./test
endif


clang_format:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i s21_matrix_oop.cpp s21_matrix_oop.h test.cpp
	rm -f .clang-format


clang_check:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n s21_matrix_oop.cpp s21_matrix_oop.h test.cpp
	rm -f .clang-format


clean:
	rm -rf $(TEST_OUTPUT) *.o *.a gcov
