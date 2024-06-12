/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:11:50 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 14:14:14 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief count the numebr of command strings
/// @param simple_command a command split by pipeline
/// @return the number of command strings (command + arguments + options)
static int	count_command(char *simple_command)
{
	int	i;

	i = 0;
	while (is_spacetab(*simple_command))
		simple_command++;
	while (simple_command)
	{
		if (is_anglebracket(*simple_command))
		{
			simple_command = point_next_token(point_next_token(simple_command));
			continue ;
		}
		i++;
		simple_command = point_next_token(simple_command);
	}
	return (i);
}

/// @brief parse redirection containded in a simple command and store it
/// @param token token, which should be single or double angle bracket(s)
/// @param simple_command a command split by pipeline
/// @param command t_struct instance to store data on redirection
/// @return command which is updated on redirection
static t_command	*handle_redirections(
		char *token, char *simple_command, t_command *command)
{
	char	*redirection_argument;

	redirection_argument = get_current_token(point_next_token(simple_command));
	if (!ft_strncmp(token, "<", 2))
	{
		command->in_redirection = SINGLE_IN;
		command->in_file = redirection_argument;
	}
	else if (!ft_strncmp(token, "<<", 3))
	{
		command->in_redirection = DOUBLE_IN;
		command->heredoc_eof = redirection_argument;
	}
	else if (!ft_strncmp(token, ">", 2))
	{
		command->out_redirection = SINGLE_OUT;
		command->out_file = redirection_argument;
	}
	else if (!ft_strncmp(token, ">>", 3))
	{
		command->out_redirection = DOUBLE_OUT;
		command->out_file = redirection_argument;
	}
	return (command);
}

static int	free_vars(char **command, char *token, int exit_code)
{
	ft_strarr_clear(command);
	free(token);
	return (exit_code);
}

static int	handle_anglebracket(char *token, char **simple_command,
				t_command **command)
{
	if (is_anglebracket(*token))
	{
		*command = handle_redirections(token, *simple_command, *command);
		*simple_command = point_next_token(*simple_command);
		return (TRUE);
	}
	return (FALSE);
}

/// @brief parse a simple command by splitting it into tokens
/// @param simple_command a command split by pipeline
/// @return [MALLOC] t_command instance with parameters filled
int	parse_command(int id, char *simple_command, t_environment *env,
			t_command *command)
{
	int			i;
	const int	len = count_command(simple_command);
	char		*token;

	init_command(command, id);
	command->command = malloc((len + 1) * sizeof(char *));
	if (!command->command)
		return (EXIT_NO_MEMORY);
	i = 0;
	while (simple_command)
	{
		token = get_current_token(simple_command);
		if (!handle_anglebracket(token, &simple_command, &command))
		{
			command->command[i++] = expand_token(token, env);
			if (!command->command[i - 1])
				return (free_vars(command->command, token, EXIT_NO_MEMORY));
		}
		free(token);
		simple_command = point_next_token(simple_command);
	}
	command->command[i] = NULL;
	return (EXIT_SUCCESS);
}
