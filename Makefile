NAME = unit_test
FLAGS = -std=c++11 -Iinclude -Wall -Wextra -Werror -Wunreachable-code -Wpedantic -g3 -fsanitize=address
#ALL = $(foreach f,$(wildcard test/*.cpp),$(basename $(notdir $(f))))
ALL = prep ex00 ex01 ex02 ex03 ex04 ex05 ex06 ex07 ex08 ex09

all a: $(ALL)

$(ALL):
	clang++ test/$@.cpp -o $(NAME) $(FLAGS)
	-./$(NAME)
	@$(RM) $(NAME)

.PHONY: all $(ALL) debug