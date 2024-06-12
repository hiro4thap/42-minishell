/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:45:40 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 10:56:05 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief split the whole command into chanks by pipelines before execution
/// @param input the string input through prompt
/// @param env	the Minishell environment.
static int	commands(char *input, t_environment *env)
{
	char	**commands;
	int		arrlen;
	int		*pipes;
	int		exit_code;

	commands = split_command(input);
	if (!commands)
		return (EXIT_NO_MEMORY);
	arrlen = ft_strarr_len(commands);
	pipes = malloc(sizeof(int) * (2 * arrlen));
	exit_code = EXIT_SUCCESS;
	if (!pipes)
	{
		ft_strarr_clear(commands);
		return (EXIT_NO_MEMORY);
	}
	if (arrlen == 1)
		exit_code = process_builtins(commands, env);
	if (exit_code)
	{
		ft_strarr_clear(commands);
		free(pipes);
		return (exit_code);
	}
	if (!exit_code || arrlen > 1)
		exit_code = handle_pipeline(commands, arrlen, pipes, env);
	ft_strarr_clear(commands);
	free(pipes);
	return (exit_code);
}

static int	handle_input(char *input, t_environment *env)
{
	char	*trimmed_input;
	int		exit_code;

	if (!input)
		return (0);
	trimmed_input = ft_strtrim(input, " \t");
	if (!trimmed_input)
	{
		free(input);
		return (EXIT_NO_MEMORY);
	}
	if (*trimmed_input)
		add_history(input);
	if (!is_valid_redirection(trimmed_input, env))
		return (0);
	if (*trimmed_input)
	{
		exit_code = commands(trimmed_input, env);
		if (exit_code)
			return (exit_code);
		rl_on_new_line();
	}
	free(trimmed_input);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_environment	tenv;
	t_environment	*env;
	int				result;

	(void) argc;
	env = &tenv;
	if (init_environment(&env, argv[0], envp))
		exit(EXIT_FAILURE);
	using_history();
	input = NULL;
	while (TRUE)
	{
		set_interactive(TRUE, env);
		if (get_prompt(env, &input))
		{
			ft_strarr_clear(env->envp);
			exit(EXIT_FAILURE);
		}
		set_interactive(FALSE, env);
		if (!input)
			builtin_exit(NULL, env);
		result = handle_input(input, env);
		free(input);
		if (result == EXIT_NO_MEMORY
			|| result == EXIT_PIPE_FAILURE
			|| result == EXIT_FORK_FAILURE)
		{
			perror(env->shell);
			ft_strarr_clear(env->envp);
			exit(EXIT_FAILURE);
		}
		else if (result)
			continue ;
	}
	return (EXIT_SUCCESS);
}
