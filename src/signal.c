/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:47:40 by hiono             #+#    #+#             */
/*   Updated: 2024/06/10 13:09:26 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_num = 0;

static void	signal_other(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", STDOUT_FILENO);
		ft_putnbr_fd(SIGQUIT, STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_sig_num = signal;
}

static void	signal_interactive(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig_num = -SIGINT;
	}
}

void	set_interactive(int is_interative, t_environment *env)
{
	struct sigaction	interupt;
	struct sigaction	quit;

	ft_memset(&interupt, 0, sizeof(interupt));
	ft_memset(&quit, 0, sizeof(quit));
	if (g_sig_num)
	{
		if (g_sig_num > 0)
			env->exit_code = 128 + g_sig_num;
		else if (g_sig_num == -SIGINT)
			env->exit_code = EXIT_FAILURE;
		g_sig_num = 0;
	}
	if (is_interative)
	{
		sig_echo_disable();
		interupt.sa_handler = &signal_interactive;
		quit.sa_handler = SIG_IGN;
	}
	else
	{
		sig_echo_enable();
		interupt.sa_handler = &signal_other;
		quit.sa_handler = &signal_other;
	}
	sigaction(SIGINT, &interupt, NULL);
	sigaction(SIGQUIT, &quit, NULL);
}
