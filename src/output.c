#include "../minishell.h"

void    putstr_fd(int fd, char *str)
{
    write(fd, str, ft_strlen(str));
}