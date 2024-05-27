/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <hiono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:37:50 by hiono             #+#    #+#             */
/*   Updated: 2024/05/24 15:42:28 by hiono            ###   ########.fr       */
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

/// @brief handle token by expanding variable and trimming quotes
/// @param token a token that needs to be expanded
/// @param env environment variable
/// @return expnaded and quotes-trimmed string
char	*expand_variable(char *token, t_environment *env)
{
	bool		is_to_be_expanded;
	char		*trimmed_token;
	const char	*expanded_token;

	is_to_be_expanded = 1;
	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
		is_to_be_expanded = 0;
	trimmed_token = trim_quote(token);
	if (!is_to_be_expanded || trimmed_token[0] != '$')
		return (trimmed_token);
	if (!ft_strncmp(trimmed_token, "$?", 3))
		return (ft_itoa(123)); //TODO: the int value should be retreaved from env structure
	expanded_token = get_value(env, trimmed_token + 1);
	free(trimmed_token);
	if (!expanded_token)
		return (ft_strdup(" "));
	return (ft_strdup(expanded_token));
}

