/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:06:48 by hiono             #+#    #+#             */
/*   Updated: 2024/05/04 16:33:47 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_redirect_one(char *str)
{
	if (1 < ft_strrchr(str, '<') - ft_strchr(str, '<')
		|| 1 < ft_strrchr(str, '>') - ft_strchr(str, '>'))
		return (0);
	return (1);
}

int	is_inredirect_start(char *str)
{
	if (!ft_strchr(str, '<')
		|| !ft_strchr(str, '|')
		|| ft_strchr(str, '<') < ft_strchr(str, '|'))
		return (1);
	return (0);
}

int	is_outredirect_end(char *str)
{
	if (!ft_strchr(str, '>')
		|| !ft_strchr(str, '|')
		|| ft_strchr(str, '|') < ft_strchr(str, '>'))
		return (1);
	return (0);
}

void	validate_redirect(char *str)
{
	if (!is_redirect_one(str))
	{
		perror("each redirection should not be used more than once \n");
		exit(EXIT_FAILURE);
	}
	else if (!is_inredirect_start(str))
	{
		perror("< or << should be placed before the first pipeline\n");
		exit(EXIT_FAILURE);
	}
	else if (!is_outredirect_end(str))
	{
		perror("> or >> should be placed after the last pipeline\n");
		exit(EXIT_FAILURE);
	}
}
