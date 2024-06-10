/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:37:50 by hiono             #+#    #+#             */
/*   Updated: 2024/06/10 13:17:28 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief trim a pair of quotes from token.
/// @param token token which can be surrounded by quotes
/// @return [MALLOC] trimmed token.
char	*trim_quote(char *token)
{
	int		len;

	len = ft_strlen(token);
	if (len == 1)
		return (ft_strdup(token));
	if (token[0] == '\'' && token[len - 1] == '\'')
		return (ft_strtrim(token, "\'"));
	else if (token[0] == '\"' && token[len - 1] == '\"')
		return (ft_strtrim(token, "\""));
	return (ft_strdup(token));
}

/// @brief display message with a file name or command
/// @param format message including "%s" specifier which is replaced by "fail"
/// @param fail name of file or command you want to display
void	errprint(char *format, char *fail, t_environment *env)
{
	ft_putstr_fd((char *) env->shell, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	while (*format)
	{
		while (*format && *format != '%')
		{
			ft_putchar_fd(*format, STDERR_FILENO);
			format++;
		}
		if (*format && !ft_strncmp(format, "%s", 2))
		{
			ft_putstr_fd(fail, STDERR_FILENO);
			format++;
			format++;
		}
	}
}

void	errprint_exit(char *format, char *fail, t_environment *env,
		int exit_code)
{
	errprint(format, fail, env);
	(void)exit_code;
	exit(1);
}

char	*replace_substr(char *str, const char *toreplace,
			const char *replacement)
{
	char	*pos;
	size_t	len;
	char	*newstr;

	pos = ft_strnstr(str, toreplace, ft_strlen(str));
	if (!pos)
	{
		return (ft_strdup(str));
	}
	while (pos)
	{
		len = ft_strlen(str) - ft_strlen(toreplace) + ft_strlen(replacement);
		newstr = malloc(len + 1);
		memcpy(newstr, str, pos - str);
		memcpy(newstr + (pos - str), replacement, ft_strlen(replacement));
		memcpy(newstr + (pos - str) + ft_strlen(replacement),
			pos + ft_strlen(toreplace), ft_strlen(str) - (pos - str));
		newstr[len] = '\0';
		str = newstr;
		pos = ft_strnstr(str, toreplace, ft_strlen(toreplace));
	}
	return (str);
}

/// @brief Gets the file/directory at the end of path
/// @param path The path to extract from
/// @return Dynamically allocated copy of the directory, or NULL if error.
static char	*get_directory(char *path)
{
	char	*str;

	if (!path)
		return (NULL);
	if (ft_strncmp(path, "/", 2) == 0)
		return (ft_strdup("/"));
	str = ft_strrchr(path, '/');
	if (!str)
		return (NULL);
	str++;
	return (ft_strdup(str));
}

/// @brief Calls readline, formatting the prompt with the current directory, and
///  sets the result into 'input'.
/// @param env The minishell environment.
/// @param[out] input The output of readline. 
void	get_prompt(t_environment *env, char **input)
{
	char	*path;
	char	*dir;
	char	*arrow;
	char	*prompt;

	path = getcwd(NULL, 0);
	if (env->home
		&& (ft_strncmp(path, env->home, ft_strlen(env->home) + 1)) == 0)
		dir = ft_strdup("~");
	else
		dir = get_directory(path);
	if (env->exit_code)
		arrow = "\001\e[1;31m\002 > \001\e[0m\002";
	else
		arrow = "\001\e[1;34m\002 > \001\e[0m\002";
	prompt = ft_strconcat("\001\e[1;32m\002", dir, "\001\e[0m\002",
			arrow, NULL);
	(*input) = readline(prompt);
	free(prompt);
	free(path);
	free(dir);
}
