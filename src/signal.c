/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:47:40 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 10:08:24 by jhughes          ###   ########.fr       */
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

static void	set_signals(void (*sa_interupt)(int), void (*sa_quit)(int))
{
	struct sigaction	interupt;
	struct sigaction	quit;

	ft_memset(&interupt, 0, sizeof(interupt));
	ft_memset(&quit, 0, sizeof(quit));
	interupt.sa_handler = sa_interupt;
	quit.sa_handler = sa_quit;
	sigaction(SIGINT, &interupt, NULL);
	sigaction(SIGQUIT, &quit, NULL);
}

void	set_child(void)
{
	set_signals(SIG_DFL, SIG_DFL);
}

void	set_interactive(int is_interative, t_environment *env)
{
	void	(*sa_interupt)(int);
	void	(*sa_quit)(int);

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
		tcsetattr(0, 0, &env->init_state);
		sig_echo_disable();
		sa_interupt = &signal_interactive;
		sa_quit = SIG_IGN;
	}
	else
	{
		sig_echo_enable();
		sa_interupt = &signal_other;
		sa_quit = &signal_other;
	}
	set_signals(sa_interupt, sa_quit);
}
