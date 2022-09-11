/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:15:33 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/12 00:16:29 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
 # include <readline/readline.h>
 # include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>

typedef struct list
{
	char			*cmd;
	char			**allargs;
	char			**args;
	char			*token;
	int				out_fd;
	int				error;
	int				in_fd;
	int				*index_token;
	int				count_token;
	int				words;
	char			*outfile;
	char			*infile;
	char			*heredoc_file;
	struct list		*next;
}	t_list;

typedef struct listenv
{
	char			*key;
	int				status;
	int				allocated;
	char			*value;
	struct listenv	*next;
}	t_list_env;

typedef struct lisinfo
{
	char		**names;
	int			sig;
	int			count_pipes;
	int			heredoc;
	int			heredoc_fd;
	char		*heredoc_file;
	int			cnt_c;
	int			errorstatus;
	t_list_env	*env_lst;
	t_list		*cmds;
}	t_info;

typedef struct execvar
{
	char	*cmd;
	pid_t	pid;
	int		fd[2];
	int		io_fd[2];
	char	**env;
}	t_var;

t_info	g_info;

int			ft_lstsize(t_list_env *lst);
int			is_space(char c);
int			check_syntax(char *s);
int			ft_strlen(char *s);
void		ft_putstr(char *s);
void		check_quotes(char *s);
char		**split_pipes(char *s);
char		*ft_charjoin(char *s1, char s2);
char		*ft_strdup(char *s1);
char		*ft_strdup2(char *s1);
char		*remove_spaces(char *p);
void		init_index(int *i, int *start, int *end);
void		skep_and_full(char *s, char *p, int *d, int *j);
int			split_equal(char **env, int type);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_echo(char **var);
int			ft_export(char **var);
void		ft_env(int x);
void		ft_cd(char *path);
int			ft_pwd(void);
char		*ft_strjoin(char *s1, char *s2);
void		ft_unset(char **str);
int			sort_list(void);
void		ft_exit(char **args);
void		parsing(char	**pips);
int			len_var(char *s);
int			skep_quotes(char *s, int *d, int status);
int			skep_quotes2(char *s, int *d);
int			iftoken(int index, t_list **l);
char		*ft_strdup(char *s1);
char		*ft_charjoin(char *s1, char c);
int			*intjoin(t_list **l, int d);
void		copyto(char *s, char *cmd, int *d, int w);
int			copy_var(char *s, char *dest, int *d);
int			end_of_cmd(char *s);
int			len_of_cmd(char *s, int to);
void		fileopen(t_list	**l, char *outfile, char *token);
int			is_valid_key(char c);
char		*get_env_var(char *key);
char		*get_cmd_from_path(char *cmd);
char		**ft_split(char *s, char c);
void		exec_cmd_sys(char *cmd, char **env, t_list *lst);
char		**prepare_env(void);
char		*ft_itoa(int n);
int			routes(t_list *lst);
int			create_list(char *name, char *value);
void		exec(int intfd, t_list *lst);
void		exc_builtins(t_list *lst);
void		check_key_null(char *str);
char		*generate_name(void);
void		get_var(char *s, int *d, int fd);
void		create_cmd(char *s, char *cmd, int end, int withextra);
void		index_token(char token, int i, t_list **l, int *status);
void		set_token(t_list	**l, t_list	*elm, int i);
void		init_node(t_list	**node, char *pip);
char		**args_filter(t_list	**l);
char		*ignore_directions_and_get_cmd(char *s);
char		**get_args(char *s, t_list **l);
char		*create_var(char *s, int len);
int			redirections_error(char **p, int count);
char		*get_path(char *key);
void		printf_error(char *cmd, char *message, char *status);
int			is_file(const char *path);
char		*get_home(void);
void		closefd(int a, int b, int c, int d);
void		saveio(int fd[], int io_fd[]);
void		restoreio(int io_fd[]);
void		cmd_not_found(int fd[], t_list *lst, char **env);
void		dup_fd(int intfd, int fd[], t_list *lst, t_list *head);
int			ft_atoi(const char *str);
void		prepare_name(char **names);
int			len_key(char *str);
void		ft_envadd_back(t_list_env *new);
t_list_env	*ft_lstenv(char *key, char *value);
int			unexpected(char token, char token2);
int			search_var(char *var, char **env);
int			var_cmp(char *var, char *env);
int			search_var(char *var, char **env);
void		free_env(char *var);
void		free_splited(char **vals, int i);
void		heredoc(t_list **l, char *file);
void		change_status(int	status);
void		free_cmd_line(t_list *head);

#endif