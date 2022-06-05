NAME	= minishell
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -I /Users/${USER}/.brew/opt/readline/include -L /Users/${USER}/.brew/opt/readline/lib -lreadline

SRC		=	minishell.c\
			./src/utils.c\
			./src/split_pipes.c\
			./src/check_syntax.c\
			./src/remove_spaces.c

HEADER	=	minishell.h

all: $(NAME)
$(NAME): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:

fclean:
	$(RM) $(NAME)

re : fclean all

.PHONY: fclean clean all minishell