/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <hiono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:06:48 by hiono             #+#    #+#             */
/*   Updated: 2024/05/10 17:14:58 by hiono            ###   ########.fr       */
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
void	validate_redirection(char *input)
{
	if (!is_redirection_one(input))
	{
		perror("each redirection should not be used more than once \n");
		exit(EXIT_FAILURE);
	}
	else if (!is_inredirection_start(input))
	{
		perror("< or << should be placed before the first pipeline\n");
		exit(EXIT_FAILURE);
	}
	else if (!is_outredirection_end(input))
	{
		perror("> or >> should be placed after the last pipeline\n");
		exit(EXIT_FAILURE);
	}
}
