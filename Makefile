NAME = unit_test
FLAGS = -std=c++11 -Iinclude -Wall -Wextra -Werror -Wunreachable-code -Wpedantic
ALL = prep ex00 ex01 ex02 ex03 ex04 ex05 ex06 ex07 ex08 ex09 ex10 ex11 ex12 ex13
#MEMCHECK = valgrind

$(NAME) all a: $(ALL)

$(ALL):
	clang++ test/$@.cpp -o $(NAME) $(FLAGS)
	-$(MEMCHECK) ./$(NAME)
	@$(RM) $(NAME)

.PHONY: all $(ALL) debug
