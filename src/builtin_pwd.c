/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:11:20 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/25 11:50:18 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief Prints the working directory to the terminal.
/// @param env The minishell environment.
/// @return Exit status: 0 on sucesses, 1 otherwise.
int	builtin_pwd(t_environment *env)
{
	char	*path;

	(void) env;
	path = getcwd(NULL, 0);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (EXIT_SUCCESS);
}
