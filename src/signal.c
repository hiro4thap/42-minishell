/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:47:40 by hiono             #+#    #+#             */
/*   Updated: 2024/05/27 00:58:37 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	signal_other(int signal)
{
	if (signal == SIGQUIT)
		printf("Quit");
	printf("\n");
	rl_on_new_line();
}

static void	signal_interactive(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
	}
	rl_on_new_line();
	rl_redisplay();
}

void	set_interactive(int is_interative)
{
	struct sigaction	interupt;
	struct sigaction	quit;

	if (is_interative)
	{
		interupt.sa_handler = &signal_interactive;
		quit.sa_handler = SIG_IGN;
	}
	else
	{
		interupt.sa_handler = &signal_other;
		quit.sa_handler = &signal_other;
	}
	sigaction(SIGINT, &interupt, NULL);
	sigaction(SIGQUIT, &quit, NULL);
}
