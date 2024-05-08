/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <hiono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:33:03 by hiono             #+#    #+#             */
/*   Updated: 2024/05/08 12:52:26 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief check if a character is quote(' or ")
/// @param c character you want to check
/// @return 0: c is NOT a quote, 1: c is a quote
int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

/// @brief check if a character is space or tab
/// @param c character you want to check
/// @return 0: c is NOT space or tab, 1: c is a space or tab
int	is_spacetab(char c)
{
	return (c == ' ' || c == '\t');
}

/// @brief check if a character is angle bracket(< or >)
/// @param c character you want to check
/// @return 0: c is NOT a angle bracket, 1: c is a angle bracket
int	is_anglebracket(char c)
{
	return (c == '<' || c == '>');
}
