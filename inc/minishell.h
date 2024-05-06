/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:44:59 by hiono             #+#    #+#             */
/*   Updated: 2024/05/20 11:24:47 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// opendir, readdir, closedir
# include <dirent.h>
// open
# include <fcntl.h>
// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,
// add_history
# include <readline/readline.h>
# include <readline/history.h>
// signal, sigaction, sigemptyset, sigaddset, kill
# include <signal.h>
// printf, perror
# include <stdio.h>
// malloc, free, exit, getenv
# include <stdlib.h>
// strerror
# include <string.h>
// ioctl
# include <sys/ioctl.h>
// stat, lstat, fstat
# include <sys/stat.h>
// wait, waitpid, wait3, wait4
# include <sys/wait.h>
// write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2,
// pipe, ttyname, isatty
# include <unistd.h>
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>
# include <term.h>
// tcsetattr, tcgetattr
# include <termios.h>
// boolean type
# include <stdbool.h>
/*
termios structure
struct termios
{
	tcflag_t	c_iflag;    // input modes
	tcflag_t	c_oflag;    // output modes
	tcflag_t	c_cflag;    // control modes
	tcflag_t	c_lflag;    // local modes
	cc_t		c_cc[NCCS]; // control chars
}
*/
# include "../lib/libft/includes/libft.h"

# define EXIT_COMMAND_NOT_EXIST 127

/// @brief The minishell environment
typedef struct s_environment
{
	char	**envp;
	int		size;
	int		max_size;
}	t_environment;

typedef struct s_command
{
	int		in_redirection;		//0:none 1:< 2:<<
	char	*in_file;
	int		out_redirection;	//0:none 1:> 2:>>
	char	*out_file;	
	char	*heredoc_eof;
	char	**command;
}	t_command;

typedef enum e_redirection
{
	NONE,
	SINGLE_IN,
	DOUBLE_IN,
	SINGLE_OUT,
	DOUBLE_OUT
}	t_redirection;

int			init_environment(t_environment **env, char **shell_env);
const char	*get_key(t_environment *env, char *key);
int			get_key_index(t_environment *env, char *key);
int			add_var(t_environment *env, char *key, char *value);
int			set_var(t_environment *env, char *key, char *value);
int			remove_var(t_environment *env, char *key);
const char	*get_value(t_environment *env, char *key);
t_command	parse_command(char *cmd);
void		validate_redirection(char *str);
void		commands(char *input, char **envp);
void		dup_out_fds(int pipefd_p[2], t_command command);
void		dup_in_fds(int pipefd_c[2], t_command command, int index);

int			env(t_environment *env);
int			export(t_environment *env, char *key_value);

void		errprint(char *msg, char *fail);
char		*trim_quote(char *token);
size_t		ft_arrlen(char **str_array);
int			is_quote(char c);
int			is_spacetab(char c);
int			is_anglebracket(char c);

# define EXIT_COMMAND_NOT_EXIST 127

/// @brief The minishell environment
typedef struct s_environment
{
	char	**envp;
	int		size;
	int		max_size;
}	t_environment;

typedef struct s_command
{
	int		in_redirection;		//0:none 1:< 2:<<
	char	*in_file;
	int		out_redirection;	//0:none 1:> 2:>>
	char	*out_file;	
	char	*heredoc_eof;
	char	**command;
}	t_command;

typedef enum e_redirection
{
	NONE,
	SINGLE_IN,
	DOUBLE_IN,
	SINGLE_OUT,
	DOUBLE_OUT
}	t_redirection;

int			init_environment(t_environment **env, char **shell_env);
const char	*get_key(t_environment *env, char *key);
int			get_key_index(t_environment *env, char *key);
int			add_var(t_environment *env, char *key, char *value);
int			set_var(t_environment *env, char *key, char *value);
int			remove_var(t_environment *env, char *key);
const char	*get_value(t_environment *env, char *key);
t_command	parse_command(char *cmd);
void		validate_redirection(char *str);
void		commands(char *input, char **envp);
void		dup_out_fds(int pipefd_p[2], t_command command);
void		dup_in_fds(int pipefd_c[2], t_command command, int index);

int			env(t_environment *env);
int			export(t_environment *env, char *key_value);

void		errprint(char *msg, char *fail);
char		*trim_quote(char *token);
size_t		ft_arrlen(char **str_array);
int			is_quote(char c);
int			is_spacetab(char c);
int			is_anglebracket(char c);

/// @brief The minishell environment
typedef struct s_environment
{
	char	**envp;
	int		size;
	int		max_size;
}	t_environment;

int			init_environment(t_environment **env, char **shell_env);
const char	*get_key(t_environment *env, char *key);
int			get_key_index(t_environment *env, char *key);
int			add_var(t_environment *env, char *key, char *value);
int			set_var(t_environment *env, char *key, char *value);
int			remove_var(t_environment *env, char *key);
const char	*get_value(t_environment *env, char *key);

int			env(t_environment *env);
int			export(t_environment *env, char *key_value);

#endif
