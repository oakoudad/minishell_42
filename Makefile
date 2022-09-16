NAME = minishell

INC = minishell.h

READLINE = $(shell brew --prefix readline)

INCLUDE_READLINE = $(addprefix $(READLINE),/include)

LIB_READLINE = $(addprefix $(READLINE),/lib)

CC = cc -Wall -Wextra -Werror

SRC = 		minishell.c\
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
		./src/ft_calloc.c\
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
		./execve/exec.c\
		./execve/exec_pips_utils.c

OBJ = $(SRC:.c=.o)

COLOUR_GREEN=\033[0;32m
COLOUR_YELLOW=\033[0;33m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

%.o : %.c
	@echo "Create $(COLOUR_BLUE)$@$(COLOUR_END) from $(COLOUR_YELLOW)$<$(COLOUR_END)"
	@$(CC) -I $(INCLUDE_READLINE) -c $< -o $@

all : $(NAME)

$(NAME) : $(INC)  $(OBJ)
	@$(CC)  -I $(INCLUDE_READLINE) -L $(LIB_READLINE) -lreadline $(OBJ) -o $(NAME)
	@echo "$(COLOUR_GREEN)Executable created (./${NAME})$(COLOUR_END)"

clean:
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

re: fclean all
.PHONY : clean fclean re all