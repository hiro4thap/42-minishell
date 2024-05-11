/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <hiono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:45:40 by hiono             #+#    #+#             */
/*   Updated: 2024/05/11 15:41:51 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*trimmed_input;

	(void) argc;
	(void) argv;
	while (1)
	{
		input = readline("\e[1;34m> \e[0m");
		validate_redirection(input);
		trimmed_input = ft_strtrim(input, " \t");
		if (*trimmed_input)
			commands(trimmed_input, envp);
		free(input);
		free(trimmed_input);
	}
	return (0);
}
