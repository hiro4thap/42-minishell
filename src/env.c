/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:38:44 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/06 11:16:17 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Builtin: Displays all environment variables in the terminal.
/// @param env The minishell environment.
/// @return Exit code: 0 on success.
int	env(t_environment *env)
{
	int	index;

	index = 0;
	while (index < env->size)
		ft_putendl_fd(env->envp[index++], STDOUT_FILENO);
	return (0);
}
