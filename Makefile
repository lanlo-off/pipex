SRCS = src/main.c\
	src/pipex.c\
	src/utils.c

OBJS := $(SRCS:.c=.o)

NAME = pipex

HEADER = includes/pipex.h

CC = cc

AR = ar rcs

CFLAGS = -Wall -Wextra -Werror -g

TEST_FILES = test.c\
	src/pipex.c\
	src/utils.c

TEST_NAME = pipex

ARGS = infile.txt "grep Hello" "wc -l" outfile.txt

all: $(NAME)

$(NAME): libs $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -I./libft $(CFLAGS) -c $< -o $@

libs:
	make -C libft

clean:
	@make clean -C libft
	rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean all

test: all
	$(CC) $(CFLAGS) $(TEST_FILES) -I./includes -I./libft -L./libft -lft -o $(TEST_NAME) && ./$(TEST_NAME)

leakcheck: all
	valgrind --trace-children=yes ./pipex $(ARGS)