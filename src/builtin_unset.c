/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:45:18 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/29 13:39:00 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief Removes ``key`` from the minishell environment if it exists.
/// @param env The minishell environment.
/// @param key The key to remove from the minishell environment.
/// @return Exit code: 0 on sucesss, 1 otherwise.
int	builtin_unset(t_command command, t_environment *env)
{
	unsigned int	index;
	int				exit_code;

	index = 1;
	exit_code = EXIT_SUCCESS;
	while (index < ft_strarr_len(command.command))
	{
		exit_code = remove_var(env, command.command[index]);
		index++;
	}
	return (exit_code);
}
