/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:34:57 by jhughes           #+#    #+#             */
/*   Updated: 2024/06/12 14:21:20 by hiono            ###   ########.fr       */
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

static int	check_vars(t_environment *env)
{
	int		value;
	char	*str;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	if (get_key_index(env, "SHLVL") > -1)
	{
		value = ft_atoi(get_value(env, "SHLVL"));
		if (value > 0)
		{
			str = ft_itoa(value + 1);
			if (!str)
				return (EXIT_NO_MEMORY);
			exit_code = set_var(env, "SHLVL", str);
			free(str);
		}
	}
	else
		exit_code = set_var(env, "SHLVL", "1");
	if (get_key_index(env, "PATH") == -1)
		exit_code = set_var(env, "PATH",
				"/usr/local/bin:/usr/local/sbin:/usr/bin:/bin");
	return (exit_code);
}

static void	init_terminal(t_environment *env, char *shell)
{
	env->shell = get_file_from_path(shell);
	env->exit_code = EXIT_SUCCESS;
	env->echoctl_was_enabled = sig_echo_get_status();
	env->home = getenv("HOME");
	tcgetattr(0, &env->init_state);
}

/// @brief Initialises environment from the calling shells environment.
/// @param[out] env Environment pointer to be initialised.
/// @param[in] shell Name of shell from main arguments.
/// @param[in] shell_env Environment from calling process.
/// @return Exit code: 0 on success, 1 otherwise, 3 on malloc failure.
int	init_environment(t_environment **env, char *shell, char **shell_env)
{
	const int	total_user_variables = 15;
	int			index;

	init_terminal(*env, shell);
	(*env)->size = ft_strarr_len(shell_env);
	(*env)->max_size = (*env)->size + total_user_variables;
	if (allocate((void **) &((*env)->envp),
			ft_calloc((*env)->max_size + 1, sizeof(char *))) == EXIT_FAILURE)
		return (EXIT_NO_MEMORY);
	index = 0;
	while (index < (*env)->size)
	{
		if (allocate((void **) &(*env)->envp[index],
				ft_strdup(shell_env[index])) == EXIT_FAILURE)
		{
			ft_strarr_clear((*env)->envp);
			return (EXIT_NO_MEMORY);
		}
		index++;
	}
	(*env)->envp[index] = NULL;
	return (check_vars(*env));
}
