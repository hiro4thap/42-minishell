/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:45:18 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/06 11:17:04 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Removes ``key`` from the minishell environment if it exists.
/// @param env The minishell environment.
/// @param key The key to remove from the minishell environment.
/// @return Exit code: 0 on sucesss, 1 otherwise.
int	unset(t_environment *env, char *key)
{
	return (remove_var(env, key));
}
