/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:46:37 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/06 15:53:05 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Changes the current working directory based on ``path``.
/// @param env The minishell environment.
/// @param path The path. Can be absolute (defined from root), or relative
/// (to current directory).
/// @return Exit Code: 0 on success, 1 otherwise.
int	cd(t_environment *env, char *path)
{
	// Check if absolute (starts with /) or relative (should match file, including . or ..)
	// Generate absolute path if ``path`` is relative path.
	// Validate absolute path for existence and accessibility.
	// If valid, updated current directory, else return appropriate error.
	
	// cd with no args should try to access $HOME.
	// ft_putendl_fd("minishell: cd: HOME not set");
}