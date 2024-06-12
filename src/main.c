/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:45:40 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 13:36:54 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	commands_cleanup(char **commands, int *pipes, int exit_code)
{
	if (commands)
		ft_strarr_clear(commands);
	if (pipes)
		free(pipes);
	return (exit_code);
}

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
		commands_cleanup(commands, NULL, EXIT_NO_MEMORY);
	if (arrlen == 1)
		exit_code = process_builtins(commands, env);
	if (exit_code != EXIT_SUCCESS)
		return (commands_cleanup(commands, pipes, exit_code));
	if (!exit_code || arrlen > 1)
		exit_code = handle_pipeline(commands, arrlen, pipes, env);
	return (commands_cleanup(commands, pipes, exit_code));
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

static void	setup(t_environment *env, char *shell, char **envp, char **input)
{
	if (init_environment(&env, shell, envp))
		exit(EXIT_FAILURE);
	using_history();
	*input = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_environment	env;
	int				result;

	(void) argc;
	setup(&env, argv[0], envp, &input);
	while (TRUE)
	{
		set_interactive(TRUE, &env);
		if (get_prompt(&env, &input))
			exit(commands_cleanup(env.envp, NULL, EXIT_FAILURE));
		set_interactive(FALSE, &env);
		if (!input)
			builtin_exit(NULL, &env);
		result = handle_input(input, &env);
		free(input);
		if (result == EXIT_NO_MEMORY || result == EXIT_PIPE_FAILURE
			|| result == EXIT_FORK_FAILURE)
		{
			perror(env.shell);
			exit(commands_cleanup(env.envp, NULL, EXIT_FAILURE));
		}
	}
	return (EXIT_SUCCESS);
}
