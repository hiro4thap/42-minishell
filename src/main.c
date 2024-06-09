/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:45:40 by hiono             #+#    #+#             */
/*   Updated: 2024/06/09 22:46:22 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief split the whole command into chanks by pipelines before execution
/// @param input the string input through prompt
/// @param env	the Minishell environment.
static void	commands(char *input, t_environment *env)
{
	char	**commands;
	int		arrlen;
	int		*pipes;

	commands = split_command(input);
	arrlen = ft_strarr_len(commands);
	pipes = malloc(sizeof(int) * (2 * arrlen));
	if (!pipes)
	{
		ft_strarr_clear(commands);
		env->exit_code = EXIT_NO_MEMORY;
		return ;
	}
	else if ((arrlen == 1 && !process_builtins(commands, env)) || arrlen > 1)
	{
		handle_pipeline(commands, arrlen, pipes, env);
	}
	ft_strarr_clear(commands);
	free(pipes);
}

static int	handle_input(char *input, t_environment *env)
{
	char	*trimmed_input;

	if (!input)
		return (0);
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
	input = NULL;
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
