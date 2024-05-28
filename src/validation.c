/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <hiono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:06:48 by hiono             #+#    #+#             */
/*   Updated: 2024/05/28 18:43:28 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief validate if the input contains no more than one 
/// inward or outward redirection
/// @param input the string input into terminal
/// @return 1: true / 0:false
int	is_redirection_one(char *input)
{
	if (1 < ft_strrchr(input, '<') - ft_strchr(input, '<')
		|| 1 < ft_strrchr(input, '>') - ft_strchr(input, '>'))
		return (0);
	return (1);
}

/// @brief validate if the inward redirection exists at the first simple command
/// @param input the string input into terminal
/// @return 1: true / 0:false
int	is_inredirection_start(char *input)
{
	if (!ft_strchr(input, '<')
		|| !ft_strchr(input, '|')
		|| ft_strchr(input, '<') < ft_strchr(input, '|'))
		return (1);
	return (0);
}

/// @brief validate if the outward redirection exists at the last simple command
/// @param input the string input into terminal
/// @return 1: true / 0:false
int	is_outredirection_end(char *input)
{
	if (!ft_strchr(input, '>')
		|| !ft_strchr(input, '|')
		|| ft_strchr(input, '|') < ft_strchr(input, '>'))
		return (1);
	return (0);
}

/// @brief validate if the redirections are used in a allowed format
/// @param input the string input into terminal
bool	is_valid_redirection(char *input)
{
	if (!is_redirection_one(input))
	{
		ft_putstr_fd("each redirection should not be used more than once \n",
			STDERR_FILENO);
		return (FALSE);
	}
	else if (!is_inredirection_start(input))
	{
		ft_putstr_fd("< or << should be placed before the first pipeline\n",
			STDERR_FILENO);
		return (FALSE);
	}
	else if (!is_outredirection_end(input))
	{
		ft_putstr_fd("> or >> should be placed after the last pipeline\n",
			STDERR_FILENO);
		return (FALSE);
	}
	return (TRUE);
}
