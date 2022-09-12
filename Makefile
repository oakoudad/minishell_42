NAME	= minishell
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g -I /Users/${USER}/.brew/opt/readline/include -L /Users/${USER}/.brew/opt/readline/lib -lreadline
SRC		=	minishell.c\
			./src/utils.c\
			./src/list.c\
			./src/utils2.c\
			./src/split_pipes.c\
			./src/check_syntax.c\
			./src/remove_spaces.c\
			./src/lst_env.c\
			./src/lst_env_utils.c\
			./src/numbers.c\
			./src/if_file.c\
			./src/ft_split.c\
			./src/generate_name.c\
			./src/get_var.c\
			./src/get_home.c\
			./src/free_env.c\
			./src/redirection_error.c\
			./builting/echo.c\
			./builting/export.c\
			./builting/env.c\
			./builting/cd.c\
			./builting/unset.c\
			./builting/exit.c\
			./builting/pwd.c\
			./parsing/parsing.c\
			./parsing/copy_var.c\
			./parsing/fileopen.c\
			./parsing/parsing_utils.c\
			./parsing/utils.c\
			./parsing/utils2.c\
			./parsing/heredoc.c\
			./parsing/free.c\
			./execve/check_cmd.c\
			./execve/builtin.c\
			./execve/utils.c\
			./execve/exec.c

HEADER	=	minishell.h

all: $(NAME)
$(NAME): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:

fclean:
	$(RM) $(NAME)

re : fclean all

.PHONY: fclean clean all minishell