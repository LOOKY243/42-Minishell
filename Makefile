CC = clang
NAME = minishell
INCPATH = includes/
SRCPATH = srcs/
SRCS = cd.c custom_split_utils.c custom_split.c echo.c env.c exit.c export_utils.c export.c handle_file_utils.c handle_file.c handle_print.c libft1.c libft2.c libft3.c libft4.c libft5.c libft6.c main.c parsing1.c parsing2.c parsing3.c parsing4.c parsing5.c parsing6.c pipe_utils.c pipe1.c pipe2.c pipe3.c prompt.c pwd.c random.c readline.c signal.c split.c split_cmd_utils.c split_cmd.c unset.c
HEADER = enum.h minishell.h struct.h
SRCSINC = $(addprefix $(SRCPATH), $(SRCS))
HEADINC = $(addprefix $(INCPATH), $(HEADER))
OBJS = $(SRCSINC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L./$(INCPATH) -lreadline

all:$(NAME)

$(NAME): $(OBJS)
	@printf "\033[1;37m"
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@printf "\033[1;32mCompilation Finished !\n\033[0m"

%.o : %.c $(HEADINC)
	@printf "\033[1;37m"
	$(CC) $(CFLAGS) -I./$(INCPATH)  $< -c -o $@

fclean: clean
	@printf "\033[1;37m"
	rm -f $(NAME)
	@printf "\033[1;31mProgram Deleted !\n\033[0m"

clean:
	@printf "\033[1;37m"
	rm -f $(OBJS) $(OBJSBNS)
	@printf "\033[1;31mObjects Deleted !\n\033[0m"

re: fclean all

.PHONY: all fclean clean re