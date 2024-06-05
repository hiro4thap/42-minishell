/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:06:48 by hiono             #+#    #+#             */
/*   Updated: 2024/06/05 13:49:49 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief validate if the redirections are used in a allowed format
/// @param input the string input into terminal
/// @return TRUE / FALSE
int	is_valid_redirection(char *input, t_environment *env)
{
	if (!is_redirection_one(input))
		errprint("each redirection should not be used more than once \n",
			NULL, env);
	else if (!is_inredirection_start(input))
		errprint("< or << should be placed before the first pipeline\n",
			NULL, env);
	else if (!is_outredirection_end(input))
		errprint("> or >> should be placed after the last pipeline\n",
			NULL, env);
	else if (!has_redirection_filename(input))
		errprint("syntax error near unexpected token\n", NULL, env);
	else if (!has_command_characters(input))
		errprint("syntax error near unexpected token\n", NULL, env);
	if (!is_redirection_one(input)
		|| !is_inredirection_start(input)
		|| !is_outredirection_end(input)
		|| !has_redirection_filename(input)
		|| !has_command_characters(input))
		return (FALSE);
	return (TRUE);
}
