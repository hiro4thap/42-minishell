/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:43:12 by hiono             #+#    #+#             */
/*   Updated: 2024/06/05 13:43:39 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief validate if the input contains no more than one 
/// inward or outward redirection
/// @param input the string input into terminal
/// @return TRUE / FALSE
int	is_redirection_one(char *input)
{
	char	*ptr_in;
	char	*ptr_out;

	ptr_in = ft_strchrout(input, "\"\'", '<');
	if (ptr_in && ft_strchrout(ptr_in + 2, "\"\'", '<'))
		return (FALSE);
	ptr_out = ft_strchrout(input, "\"\'", '>');
	if (ptr_out && ft_strchrout(ptr_out + 2, "\"\'", '>'))
		return (FALSE);
	return (TRUE);
}

/// @brief validate if the inward redirection exists at the first simple command
/// @param input the string input into terminal
/// @return TRUE / FALSE
int	is_inredirection_start(char *input)
{
	if (!ft_strchrout(input, "\"\'", '<')
		|| !ft_strchrout(input, "\"\'", '|')
		|| ft_strchrout(input, "\"\'", '<') < ft_strchrout(input, "\"\'", '|'))
		return (TRUE);
	return (FALSE);
}

/// @brief validate if the outward redirection exists at the last simple command
/// @param input the string input into terminal
/// @return TRUE / FALSE
int	is_outredirection_end(char *input)
{
	if (!ft_strchrout(input, "\"\'", '>')
		|| !ft_strchrout(input, "\"\'", '|')
		|| ft_strchrout(input, "\"\'", '|') < ft_strchrout(input, "\"\'", '>'))
		return (TRUE);
	return (FALSE);
}

int	has_redirection_filename(char *input)
{
	char	*ptr_file;

	if (ft_strchrout(input, "\"\'", '<'))
	{
		ptr_file = ft_strchrout(input, "\"\'", '<') + 1;
		if (*ptr_file == '<')
			ptr_file++;
		while (*ptr_file && is_spacetab(*ptr_file))
			ptr_file++;
		if (!ft_isalnum(*ptr_file) && *ptr_file != '[' && *ptr_file != ']'
			&& *ptr_file != '!' && *ptr_file != '?' && *ptr_file != '$')
			return (FALSE);
	}
	if (ft_strchrout(input, "\"\'", '>'))
	{
		ptr_file = ft_strchrout(input, "\"\'", '>') + 1;
		if (*ptr_file == '>')
			ptr_file++;
		while (*ptr_file && is_spacetab(*ptr_file))
			ptr_file++;
		if (!ft_isalnum(*ptr_file) && *ptr_file != '[' && *ptr_file != ']'
			&& *ptr_file != '!' && *ptr_file != '?' && *ptr_file != '$')
			return (FALSE);
	}
	return (TRUE);
}

int	has_command_characters(char *input)
{
	while (is_spacetab(*input))
		input++;
	if (*input == '|')
		return (FALSE);
	input = ft_strchrout(input, "\"\'", '|');
	while (input)
	{
		input++;
		while (is_spacetab(*input))
			input++;
		if (!*input || *input == '|')
			return (FALSE);
		input = ft_strchrout(input, "\"\'", '|');
	}
	return (TRUE);
}
