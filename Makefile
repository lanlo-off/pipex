SRCS = src/main.c\
	src/pipex.c\
	src/utils.c

OBJS := $(SRCS:.c=.o)

NAME = pipex

SRCS_BONUS = src_bonus/main_bonus.c\
	src_bonus/pipex_bonus.c\
	src_bonus/utils_bonus.c

HEADER = includes/pipex.h

OBJS_BONUS := $(SRCS_BONUS:.c=.o)

NAME_BONUS = pipex_bonus

HEADER_BONUS = includes/pipex_bonus.h

CC = cc

AR = ar rcs

CFLAGS = -Wall -Wextra -Werror -g3

TEST_FILES = test.c\
	src/pipex.c\
	src/utils.c

TEST_NAME = pipex_test

ARGS = infile.txt "grep Hello" "wc -l" outfile.txt

all: $(NAME)

$(NAME): libs $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -I./libft $(CFLAGS) -c $< -o $@

libs:
	make -C libft

bonus : libs $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -L./libft -lft -o $(NAME_BONUS)

clean:
	@make clean -C libft
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@make fclean -C libft
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

test: all
	$(CC) $(CFLAGS) $(TEST_FILES) -I./includes -I./libft -L./libft -lft -o $(TEST_NAME) && ./$(TEST_NAME)

leakcheck: all
	valgrind --trace-children=yes ./pipex $(ARGS)