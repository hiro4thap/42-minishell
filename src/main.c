/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:45:40 by hiono             #+#    #+#             */
/*   Updated: 2024/05/09 17:31:17 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*trimmed_input;

	(void) argc;
	(void) argv;
	(void) envp;
	while (1)
	{
		input = readline("\e[1;34m> \e[0m");
		trimmed_input = ft_strtrim(input, " \t");
		if (!*trimmed_input)
			continue ;
		validate_redirect(input);
		commands(input, envp);
		free(trimmed_input);
	}
	return (0);
}
