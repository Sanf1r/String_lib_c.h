CFLAGS=-c -Wall -Wextra -Werror -std=c11 -pedantic
LDFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic
ASAN=#-fsanitize=address -fanalyzer


all: s21_string.a

s21_string.a:
	gcc $(CFLAGS) -o s21_string.o -c s21_string.c
	gcc $(CFLAGS) -o s21_sprintf.o -c s21_sprintf.c
	ar rc s21_string.a s21_string.o s21_sprintf.o
	ranlib s21_string.a

s21_string.a_for_tests:
	rm -f s21_string.a
	gcc $(CFLAGS) $(ASAN) -fprofile-arcs -ftest-coverage -o s21_string.o -c s21_string.c
	gcc $(CFLAGS) $(ASAN) -fprofile-arcs -ftest-coverage -o s21_sprintf.o -c s21_sprintf.c
	ar rc s21_string.a s21_string.o s21_sprintf.o
	ranlib s21_string.a

clean:
	rm -f *.a *.o
	rm -f *_tests
	rm -f *.info *.gcda *.gcno *.gcov
	rm -rf coverage
	rm -f megatests

test: s21_string.a_for_tests
	gcc $(LDFLAGS) $(ASAN) -fprofile-arcs -ftest-coverage ./checktests/s21_string_test.c -o megatests -lcheck -L. s21_string.a
	./megatests
	geninfo . -b . -o ./coverage.info
	genhtml coverage.info -o ./coverage

open_gcov:
	open coverage/index.html
