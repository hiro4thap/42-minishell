/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:44:59 by hiono             #+#    #+#             */
/*   Updated: 2024/05/04 16:23:21 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "../lib/libft/includes/libft.h"
# include "../lib/libft/includes/ft_printf_utils.h"

void	validate_redirect(char *str);

#endif
