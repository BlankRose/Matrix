NAME = unit_test
FLAGS = -std=c++14 -Iinclude -Wall -Wextra -Werror -Wunreachable-code -Wpedantic
ALL = $(foreach f,$(wildcard test/*.cpp),$(basename $(notdir $(f))))

all a: $(ALL)

$(ALL):
	clang++ test/$@.cpp -o $(NAME) $(FLAGS)
	-./$(NAME)
	@$(RM) $(NAME)

.PHONY: all $(ALL) debug