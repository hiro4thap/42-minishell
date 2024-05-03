/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:38:44 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/03 09:41:36 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(int argc, char **argv, char **envp)
{
	const int	size = ft_strarrlen(envp);
	int			index;

	(void) argc;
	(void) argv;
	index = 0;
	while (index < size)
		ft_putendl_fd(envp[index++]);
	return (0);
}