/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:13:27 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 14:21:39 by hiono            ###   ########.fr       */
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
	if (is_anglebracket(*ptr))
		ptr = ft_strrchr(ptr, *ptr) + 1;
	else
	{
		while (*ptr && !is_spacetab(*ptr) && !is_anglebracket(*ptr))
		{
			if (is_quote(*ptr) && ft_strchr(ptr + 1, *ptr))
				ptr = ft_strchr(ptr + 1, *ptr);
			ptr++;
		}
	}
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
	if (is_anglebracket(*ptr))
		ptr = ft_strrchr(ptr, *ptr) + 1;
	else
	{
		while (*ptr && !is_spacetab(*ptr) && !is_anglebracket(*ptr))
		{
			if (is_quote(*ptr) && ft_strchr(ptr + 1, *ptr))
				ptr = ft_strchr(ptr + 1, *ptr);
			ptr++;
		}
	}
	while (is_spacetab(*ptr))
		ptr++;
	if (!*ptr)
		return (NULL);
	return (ptr);
}

void	init_command(t_command *command, int id)
{
	command->id = id;
	command->command = NULL;
	command->in_redirection = NONE;
	command->out_redirection = NONE;
	command->heredoc_eof = NULL;
	command->in_file = NULL;
	command->out_file = NULL;
}
