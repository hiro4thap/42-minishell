/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <hiono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:37:50 by hiono             #+#    #+#             */
/*   Updated: 2024/05/10 15:28:43 by hiono            ###   ########.fr       */
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
	{
		res = ft_strtrim(token, "\'");
		free(token);
	}
	else if (token[0] == '\"' && token[len - 1] == '\"')
	{
		res = ft_strtrim(token, "\"");
		free(token);
	}
	return (res);
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
			ft_putchar_fd(*format, 2);
			format++;
		}
		if (*format && !ft_strncmp(format, "%s", 2))
		{
			ft_putstr_fd(fail, 2);
			format++;
			format++;
		}
	}
}

/// @brief count the lenght of a string array (NULL is not included)
/// @param str_array the array you want to know the length of
/// @return the length of a string array
size_t	ft_arrlen(char **str_array)
{
	size_t	len;

	len = 0;
	while (*str_array)
	{
		len += 1;
		str_array++;
	}
	return (len);
}