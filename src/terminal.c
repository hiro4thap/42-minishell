/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:01:24 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/27 01:02:02 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_file_from_path(char *path)
{
	char	*str;

	if (!path)
		return (NULL);
	str = ft_strrchr(path, '/');
	if (str && *(str + 1))
		return (str + 1);
	return (path);
}

static int	sig_echo_get_status(void)
{
	struct termios	state;

	tcgetattr(0, &state);
	if ((state.c_lflag & ECHOCTL) == ECHOCTL)
		return (1);
	return (0);
}

void	init_terminal(t_environment *env, char *shell)
{
	env->shell = get_file_from_path(shell);
	env->exit_code = EXIT_SUCCESS;
	env->echoctl_was_enabled = sig_echo_get_status();
}

void	sig_echo_disable(void)
{
	struct termios	state;

	tcgetattr(0, &state);
	state.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &state);
}

void	sig_echo_enable(void)
{
	struct termios	state;

	tcgetattr(0, &state);
	state.c_lflag |= ECHOCTL;
	tcsetattr(0, 0, &state);
}
