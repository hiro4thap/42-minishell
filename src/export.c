/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:45:07 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/03 12:45:49 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(int argc, char **argv, char **envp)
{
	const int	size = ft_strarrlen(envp);
	int			index;

	(void) argc;
	(void) argv;
	index = 0;
	while (index < size)
		ft_putendl_fd(envp[index++], STDOUT_FILENO);
	return (0);
}