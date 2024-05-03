/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:11:20 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/03 09:37:32 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int argc, char **argv, char **envp)
{
	char	*path;

	(void) argc;
	(void) argv;
	(void) envp;
	path = getcwd(NULL, 0);
	if (!path)
		error();
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (0);
}