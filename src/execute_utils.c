/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:13:40 by hiono             #+#    #+#             */
/*   Updated: 2024/05/28 16:32:33 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*point_next_simple_command(char *command)
{
	while(*command)
	{
		if (*command == '|')
		{
			command++;
			break ;
		}
		if (is_quote(*command))
			command = ft_strchr(command + 1, *command);
		command++;
	}
	if (!*command)
		command = NULL;
	return (command);
}

int	count_simple_commands(char *command)
{
	int	len;

	len = 0;
	while (command && *command)
	{
		len++;
		command = point_next_simple_command(command);
	}
	return (len);
}

// [MALLOC]
char	*get_current_simple_command(char *command)
{
	char	*start;
	char	*end;
	char	*simple_command;

	start = command;
	if (!point_next_simple_command(command))
		end = ft_strchr(command, '\n');
	else
		end = point_next_simple_command(command);
	simple_command = ft_substr(start, 0, end - start - 1);
	return (simple_command);
}

char	**split_command(char *command)
{
	int		len;
	char	**simple_commands;
	int		i;

	len = count_simple_commands(command);
	simple_commands = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		simple_commands[i] = get_current_simple_command(command);
		command = point_next_simple_command(command);
		i++;
	}
	simple_commands[i] = NULL;
	return (simple_commands);
}

