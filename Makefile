CC = cc
NAME = minishell
HEADER = minishell.h
SRCS = main.c \
		ft_split.c \
		ft_calloc.c \
		parsing.c \
		echo.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Werror -Wextra -Wall -g

all:$(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME)
	@printf "\033[1;32mCompilation Finished!\n\033[0m"

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) $< -c -o $@

fclean: clean
	@rm -f $(NAME)
	@printf "\033[1;35mFiles Deleted!\n\033[0m"

clean:
	@rm -f $(OBJS)
	@printf "\033[1;35mObjects Deleted!\n\033[0m"

.PHONY: all fclean clean re