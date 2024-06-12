/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:24:43 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 14:25:57 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static int	free_vars(void *ptr1, void *ptr2, void *ptr3, int exit_code)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	return (exit_code);
}

/// @brief Calls readline, formatting the prompt with the current directory, and
///  sets the result into 'input'.
/// @param env The minishell environment.
/// @param[out] input The output of readline. 
int	get_prompt(t_environment *env, char **input)
{
	char	*path;
	char	*dir;
	char	*arrow;
	char	*prompt;

	path = getcwd(NULL, 0);
	if (!path)
		return (EXIT_NO_MEMORY);
	if (env->home
		&& (ft_strncmp(path, env->home, ft_strlen(env->home) + 1)) == 0)
		dir = ft_strdup("~");
	else
		dir = get_directory(path);
	if (!dir)
		return (free_vars(path, NULL, NULL, EXIT_NO_MEMORY));
	if (env->exit_code)
		arrow = "\001\e[1;31m\002 > \001\e[0m\002";
	else
		arrow = "\001\e[1;34m\002 > \001\e[0m\002";
	prompt = ft_strconcat("\001\e[1;32m\002", dir, "\001\e[0m\002",
			arrow, NULL);
	if (!prompt)
		return (free_vars(dir, path, NULL, EXIT_NO_MEMORY));
	(*input) = readline(prompt);
	return (free_vars(prompt, path, dir, EXIT_SUCCESS));
}
