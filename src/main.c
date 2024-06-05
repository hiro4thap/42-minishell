/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:45:40 by hiono             #+#    #+#             */
/*   Updated: 2024/06/04 17:25:51 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_input(char *input, t_environment *env)
{
	char	*trimmed_input;

	trimmed_input = ft_strtrim(input, " \t");
	if (!trimmed_input)
	{
		ft_putstr_fd("fail to malloc\n", STDERR_FILENO);
		free(input);
		return (0);
	}
	if (*trimmed_input)
		add_history(input);
	if (!is_valid_redirection(trimmed_input, env))
	{
		free(input);
		return (0);
	}
	if (*trimmed_input)
	{
		commands(trimmed_input, env);
		rl_on_new_line();
	}
	free(trimmed_input);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_environment	*env;

	(void) argc;
	(void) argv;
	init_environment(&env, argv[0], envp);
	using_history();
	sig_echo_disable();
	while (TRUE)
	{
		set_interactive(TRUE, env);
		if (env->exit_code)
			input = readline("\001\e[1;31m\002> \001\e[0m\002");
		else
			input = readline("\001\e[1;34m\002> \001\e[0m\002");
		set_interactive(FALSE, env);
		if (!input)
			builtin_exit(NULL, env);
		if (!handle_input(input, env))
			continue ;
		free(input);
	}
	return (EXIT_SUCCESS);
}
