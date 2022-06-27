#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct list
{
	char			*cmd;
	char			**args;
	char			*token;
	int				fd;
	int				*index_token;
	int				count_token;
	int				words;
	char			*filename;
	struct listenv	*env;
	struct list	*next;
}	t_list;

typedef struct listenv
{
	char			*key;
	char			*value;
	struct listenv	*next;
}	t_list_env;


void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
int		is_space(char c);
int		check_syntax(char *s, t_list_env **lst);
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
void	split_equal(t_list_env **lst, char **env);
int	ft_strncmp(const char *s1, const char *s2);