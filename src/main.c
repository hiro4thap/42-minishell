/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:45:40 by hiono             #+#    #+#             */
/*   Updated: 2024/05/08 19:00:55 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void) argc;
	(void) argv;
	(void) envp;
	while (1)
	{
		input = readline("> ");
		validate_redirect(input);
		//t_command	cmd = split_cmd(input);
		//(void)cmd;
		commands(input, envp);
		//ft_printf("%s\n", input);	//printing input for test. TODO:to be deleted
	}
	return (0);
}
