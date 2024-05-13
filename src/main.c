/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:45:40 by hiono             #+#    #+#             */
/*   Updated: 2024/05/20 11:27:03 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*trimmed_input;

	(void) argc;
	(void) argv;
	while (TRUE)
	{
		input = readline("\e[1;34m> \e[0m");
		trimmed_input = ft_strtrim(input, " \t");
		if (!trimmed_input)
		{
			ft_putstr_fd("fail to malloc\n", STDERR_FILENO);
			free(input);
			continue ;
		}
		free(input);
		validate_redirection(trimmed_input);
		if (*trimmed_input)
			commands(trimmed_input, envp);
		free(trimmed_input);
	}
	return (EXIT_SUCCESS);
}
/*
#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_environment *env;

	(void) argc;
	(void) argv;
	ft_printf("\n\n INIT_ENV TEST:\n\n");
	init_environment(&env, envp);
	builtin_env(env);
	ft_printf("\n\n EXPORT TEST:\n\n");
	builtin_export(env, "ARG=TEST");
	builtin_export(env, "ARG1=");
	builtin_export(env, "ARG2");
	builtin_export(env, "ARG3=TEST");
	builtin_export(env, "ARG4=TEST");
	builtin_export(env, "ARG5=TEST");
	builtin_export(env, "ARG6=TEST");
	builtin_export(env, "ARG7=TEST");
	builtin_export(env, "ARG8=TEST");
	builtin_export(env, "ARG9=TEST");
	builtin_export(env, "ARG10=TEST");
	builtin_export(env, "ARG11=TEST");
	builtin_export(env, "ARG12=TEST");
	builtin_export(env, "ARG13=TEST");
	builtin_export(env, "ARG14=TEST");
	builtin_export(env, "ARG15=TEST");
	builtin_export(env, "ARG16=TEST");
	builtin_export(env, "ARG17=TEST");
	// builtin_export(env, "ARG18=TEST");
	builtin_env(env);
	
	ft_printf("\n\n UNSET TEST:\n\n");
	builtin_unset(env, "ARG");
	builtin_env(env);
	builtin_unset(env, "A");
	builtin_env(env);

	ft_printf("\n\n PWD TEST:\n\n");
	builtin_pwd(env);
	ft_printf("\n\n PWD UNSET TEST:\n\n");
	builtin_export(env, "PWD=hello");
	builtin_pwd(env);
	builtin_unset(env, "PWD");
	builtin_pwd(env);
	
	ft_printf("\n\n CD TEST:\n\n");
	builtin_pwd(env);
	builtin_cd(env, "..");
	builtin_pwd(env);
	builtin_cd(env, "03-mini");
	builtin_pwd(env);
	builtin_cd(env, "03-minishell");
	builtin_pwd(env);
	builtin_cd(env, "");
	builtin_pwd(env);
	builtin_unset(env, "HOME");
	builtin_cd(env, "");
	builtin_pwd(env);
	builtin_cd(env, NULL);
	builtin_pwd(env);
	builtin_cd(env, "/");
	builtin_pwd(env);
	builtin_cd(env, "/Users/jhughes/projects");
	builtin_pwd(env);
	builtin_cd(env, "/Users/jhughes/projects/");
	builtin_pwd(env);
}
*/
