NAME = Minishell

FLAGS = gcc -Wall -Wextra -Werror

READLINE = -Wall -Wextra -Werror -g -I /Users/${USER}/.brew/opt/readline/include -L /Users/${USER}/.brew/opt/readline/lib -lreadline

RM = rm -rf

FILES = 	minishell.c\
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

all: $(NAME)

$(NAME): $(FILES)
		$(FLAGS) $(FILES) $(READLINE) -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
