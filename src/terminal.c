/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:01:24 by jhughes           #+#    #+#             */
/*   Updated: 2024/06/09 21:44:55 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	sig_echo_get_status(void)
{
	struct termios	state;

	ft_memset(&state, 0, sizeof(state));
	tcgetattr(0, &state);
	if ((state.c_lflag & ECHOCTL) == ECHOCTL)
		return (1);
	return (0);
}

void	sig_echo_disable(void)
{
	struct termios	state;

	ft_memset(&state, 0, sizeof(state));
	tcgetattr(0, &state);
	state.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &state);
}

void	sig_echo_enable(void)
{
	struct termios	state;

	ft_memset(&state, 0, sizeof(state));
	tcgetattr(0, &state);
	state.c_lflag |= ECHOCTL;
	tcsetattr(0, 0, &state);
}
