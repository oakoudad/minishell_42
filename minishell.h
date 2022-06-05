#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int		is_space(char c);
int		check_syntax(char *s);
int		ft_strlen(char *s);
void	ft_putstr(char *s);
void	check_quotes(char *s);
char	**split_pipes(char *s);
int		skep_quotes(char *s, int *d);
char	*ft_charjoin(char *s1, char s2);
char	*ft_strdup(char *s1);
char	*remove_spaces(char *p);
void	init_index(int *i, int *start, int *end);