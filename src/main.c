/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <hiono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:45:40 by hiono             #+#    #+#             */
/*   Updated: 2024/05/13 14:56:00 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*trimmed_input;

	(void) argc;
	(void) argv;
	while (TRUE)
	{
		input = readline("\e[1;34m> \e[0m");
		trimmed_input = ft_strtrim(input, " \t");
		if (!trimmed_input)
		{
			ft_putstr_fd("fail to malloc\n", STDERR_FILENO);
			free(input);
			continue ;
		}
		free(input);
		validate_redirection(trimmed_input);
		if (*trimmed_input)
			commands(trimmed_input, envp);
		free(trimmed_input);
	}
	return (EXIT_SUCCESS);
}
