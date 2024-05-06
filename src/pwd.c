/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:11:20 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/06 11:16:47 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Prints the value of the ``PWD`` key in the minishell environment.
/// @param env The minishell environment.
/// @return Exit status: 0 on sucesses, 1 otherwise.
int	pwd(t_environment *env)
{
	const char	*path;

	path = get_value(env, "PWD");
	if (!path)
		return (1);
	ft_putendl_fd(path, STDOUT_FILENO);
	return (0);
}
