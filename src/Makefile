#CFLAGS=-Wall -Werror -Wextra
CFLAGS = -Wall -Werror -Wextra -std=c11


all: clean s21_string.a test gcov_report

ubuntu: clean s21_string.a test_ubuntu gcov_report

test: main.c s21_sprintf.c s21_string.c s21_sscanf.c
	gcc -o test $(CFLAGS) --coverage main.c s21_sprintf.c s21_string.c s21_sscanf.c -lcheck -lpthread -lm  -I /usr/local/include -L/usr/local/lib
	
test_ubuntu: main.c s21_sprintf.c s21_string.c s21_sscanf.c
	gcc -o test $(CFLAGS) --coverage main.c s21_sprintf.c s21_string.c s21_sscanf.c -lcheck -lm -lpthread -lsubunit
	
s21_string.a: s21_sprintf.o s21_string.o s21_sscanf.o
	ar rc s21_string.a s21_string.o s21_sprintf.o s21_sscanf.o
	ranlib s21_string.a
	
s21_sprintf.o: s21_sprintf.c
	gcc $(CFLAGS) -c s21_sprintf.c

s21_string.o: s21_string.c
	gcc $(CFLAGS) -c s21_string.c

s21_sscanf.o: s21_sscanf.c
	gcc $(CFLAGS) -c s21_sscanf.c
	
gcov_report: test
	./test
	gcovr --html-details rep.html
	

check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i *.c
	clang-format -i *.h
	

clean:
	rm -rf *.o *.gcda *.a *.html *.gcno *.css
	rm -f test
	rm -f test_ubuntu
	
git:
	git add *.c
	git add *.h
	git add Makefile
	git commit -m "add from make"
	git push
