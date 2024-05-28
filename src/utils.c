/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:37:50 by hiono             #+#    #+#             */
/*   Updated: 2024/05/28 14:15:49 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief trim a pair of quotes from token.
/// @param token token which can be surrounded by quotes
/// @return [MALLOC] trimmed token.
char	*trim_quote(char *token)
{
	int		len;
	char	*res;

	len = ft_strlen(token);
	res = token;
	if (token[0] == '\'' && token[len - 1] == '\'')
		res = ft_strtrim(token, "\'");
	else if (token[0] == '\"' && token[len - 1] == '\"')
		res = ft_strtrim(token, "\"");
	return (ft_strdup(res));
}

/// @brief display message with a file name or command
/// @param format message including "%s" specifier which is replaced by "fail"
/// @param fail name of file or command you want to display
void	errprint(char *format, char *fail)
{
	while (*format)
	{
		while (*format && *format != '%')
		{
			ft_putchar_fd(*format, STDERR_FILENO);
			format++;
		}
		if (*format && !ft_strncmp(format, "%s", 2))
		{
			ft_putstr_fd(fail, STDERR_FILENO);
			format++;
			format++;
		}
	}
}
