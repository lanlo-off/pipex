SRCS = src/main.c\
	src/pipex.c\
	src/utils.c\
	src/files.c\
	src/free.c\
	src/here_doc.c

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

CFLAGS = -Wall -Wextra -Werror -g3

ARGS = infile.txt "cat -e" "wc -l" outfile.txt
ARGS2 = infile.txt "cat -e" "cat -e" outfile.txt
ARGS_ERROR = infile.txt "cat -e" "greknvjk" outfile.txt

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

leakcheck: all
	valgrind --leak-check=full --trace-children=yes --track-fds=yes ./pipex $(ARGS)