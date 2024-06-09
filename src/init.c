/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:39:45 by jhughes           #+#    #+#             */
/*   Updated: 2024/06/09 22:07:33 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	allocate(void **pointer, void *malloc_return)
{
	*pointer = malloc_return;
	if (*pointer)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

static char	*get_file_from_path(char *path)
{
	char	*str;

	if (!path)
		return (NULL);
	str = ft_strrchr(path, '/');
	if (str && *(str + 1))
		return (str + 1);
	return (path);
}

static void	init_terminal(t_environment *env, char *shell)
{
	env->shell = get_file_from_path(shell);
	env->exit_code = EXIT_SUCCESS;
	env->echoctl_was_enabled = sig_echo_get_status();
}

/// @brief Initialises environment from the calling shells environment.
/// @param[out] env Environment pointer to be initialised. 
/// @param[in] shell Name of shell from main arguments.
/// @param[in] shell_env Environment from calling process.
/// @return Exit code: 0 on success, 1 otherwise.
int	init_environment(t_environment **env, char *shell, char **shell_env)
{
	const int	total_user_variables = 15;
	int			index;

	if (allocate((void **) env, malloc(sizeof(t_environment))) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_terminal(*env, shell);
	(*env)->size = ft_strarr_len(shell_env);
	(*env)->max_size = (*env)->size + total_user_variables;
	if (allocate((void **) &((*env)->envp),
			ft_calloc((*env)->max_size + 1, sizeof(char *))) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	index = 0;
	while (index < (*env)->size)
	{
		if (allocate((void **) &(*env)->envp[index],
				ft_strdup(shell_env[index])) == EXIT_FAILURE)
		{
			ft_strarr_clear((*env)->envp);
			return (EXIT_FAILURE);
		}
		index++;
	}
	(*env)->envp[index] = NULL;
	return (EXIT_SUCCESS);
}

void	init_command(t_command *command, int id)
{
	command->id = id;
	command->command = NULL;
	command->in_redirection = NONE;
	command->out_redirection = NONE;
	command->heredoc_eof = NULL;
	command->in_file = NULL;
	command->out_file = NULL;
}
