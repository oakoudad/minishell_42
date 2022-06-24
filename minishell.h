#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct list
{
	char		*cmd;
	char		**args;
	int			token;
	int			fd;
	char		*filename;
	struct list	*next;
}	t_list;

void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
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
void	skep_and_full(char *s, char *p, int *d, int *j);