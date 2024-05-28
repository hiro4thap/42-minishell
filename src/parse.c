/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <hiono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:11:50 by hiono             #+#    #+#             */
/*   Updated: 2024/05/28 14:24:38 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief duplicate the token which is pointed by the param 'ptr'
/// @param ptr current pointer
/// @return [MALLOC] a token which can be surrounded by quotes
char	*get_current_token(char *ptr)
{
	char	*ptr_start;
	char	*token;

	while (is_spacetab(*ptr))
		ptr++;
	ptr_start = ptr;
	if (is_quote(*ptr))
		ptr = ft_strchr(ptr + 1, *ptr) + 1;
	else if (is_anglebracket(*ptr))
		ptr = ft_strrchr(ptr, *ptr) + 1;
	else
		while (*ptr && !is_anglebracket(*ptr) && !is_spacetab(*ptr))
			ptr++;
	token = ft_substr(ptr_start, 0, ptr - ptr_start);
	return (token);
}

/// @brief search the next token within a simple command
/// @param ptr current pointer
/// @return pointer which points to the first character of next token
char	*point_next_token(char *ptr)
{
	while (is_spacetab(*ptr))
		ptr++;
	if (is_quote(*ptr))
		ptr = ft_strchr(ptr + 1, *ptr) + 1;
	else if (is_anglebracket(*ptr))
		ptr = ft_strrchr(ptr, *ptr) + 1;
	else
		while (*ptr && !is_anglebracket(*ptr) && !is_spacetab(*ptr))
			ptr++;
	while (is_spacetab(*ptr))
		ptr++;
	if (!*ptr)
		return (NULL);
	return (ptr);
}

/// @brief count the numebr of command strings
/// @param simple_command a command split by pipeline
/// @return the number of command strings (command + arguments + options)
int	count_command(char *simple_command)
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
t_command	handle_redirections(
		char *token, char *simple_command, t_command command)
{
	char	*redirection_argument;

	redirection_argument = get_current_token(point_next_token(simple_command));
	if (!ft_strncmp(token, "<", 2))
	{
		command.in_redirection = SINGLE_IN;
		command.in_file = redirection_argument;
	}
	else if (!ft_strncmp(token, "<<", 3))
	{
		command.in_redirection = DOUBLE_IN;
		command.heredoc_eof = redirection_argument;
	}
	else if (!ft_strncmp(token, ">", 2))
	{
		command.out_redirection = SINGLE_OUT;
		command.out_file = redirection_argument;
	}
	else if (!ft_strncmp(token, ">>", 3))
	{
		command.out_redirection = DOUBLE_OUT;
		command.out_file = redirection_argument;
	}
	return (command);
}

/// @brief parse a simple command by splitting it into tokens
/// @param simple_command a command split by pipeline
/// @return [MALLOC] t_command instance with parameters filled
t_command	parse_command(char *simple_command, t_environment *env)
{
	int			i;
	int			len;
	char		*token;
	t_command	command;

	len = count_command(simple_command);
	command.command = malloc((len + 1) * sizeof(char *));
	i = 0;
	command.in_redirection = NONE;
	command.out_redirection = NONE;
	while (simple_command)
	{
		token = get_current_token(simple_command);
		if (is_anglebracket(*token))
		{
			command = handle_redirections(token, simple_command, command);
			simple_command = point_next_token(simple_command);
		}
		else
			command.command[i++] = expand_variables(token, env);
		free(token);
		simple_command = point_next_token(simple_command);
	}
	command.command[i] = NULL;
	return (command);
}
