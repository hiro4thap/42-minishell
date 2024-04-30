/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:33:10 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/30 15:07:16 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf_utils.h"

static void	initialise_format(t_format *format)
{
	format->conversion = '\0';
	format->use_field_width = FALSE;
	format->use_precision = FALSE;
	format->f_zero = FALSE;
	format->f_dash = FALSE;
	format->f_sign = FALSE;
	format->f_space = FALSE;
	format->f_hash = FALSE;
	format->field_width = 0;
	format->precision = 0;
	format->sign = '\0';
}

static int	apply_conversion(t_format *format, va_list lst, t_bool *error)
{
	int	written_bytes;

	if (!format)
		return (0);
	if (format->conversion == 'd' || format->conversion == 'i')
		written_bytes = (print_i(va_arg(lst, int), format, error));
	else if (format->conversion == 's')
		written_bytes = (print_s(va_arg(lst, char *), format, error));
	else if (format->conversion == 'c')
		written_bytes = (print_c(va_arg(lst, int), format, error));
	else if (format->conversion == 'p')
		written_bytes = (print_p(va_arg(lst, void *), format, error));
	else if (format->conversion == 'u' || format->conversion == 'o'
		|| format->conversion == 'x' || format->conversion == 'X')
		written_bytes = (print_u(va_arg(lst, unsigned int), format, error));
	else
		written_bytes = (print_c(format->conversion, format, error));
	return (written_bytes);
}

static int	is_flag(char c, t_format *format)
{
	if (c == '#' && !format->f_hash)
		format->f_hash = TRUE;
	else if (c == '0' && !format->f_zero)
		format->f_zero = TRUE;
	else if (c == '-' && !format->f_zero)
		format->f_dash = TRUE;
	else if (c == ' ' && !format->f_space)
		format->f_space = TRUE;
	else if (c == '+' && !format->f_sign)
		format->f_sign = TRUE;
	else
		return (0);
	return (1);
}

static void	set_format(t_format *format, const char *s, int *index)
{
	initialise_format(format);
	while (is_flag(s[*index], format))
		(*index)++;
	if (ft_isdigit(s[*index]))
	{
		format->use_field_width = TRUE;
		format->field_width = ft_atoi(s + *index);
		while (ft_isdigit(s[*index]))
			(*index)++;
	}
	if (s[*index] == '.')
	{
		(*index)++;
		format->use_precision = TRUE;
		format->precision = ft_atoi(s + (*index));
		while (ft_isdigit(s[*index]))
			(*index)++;
		if (format->precision < 0)
			format->precision = 0;
	}
	format->conversion = s[*index];
}

// Prints a format string s, replacing any conversions (indicated with %) with
// the string conversion. Returns the number of bytes written to STDOUT
int	ft_printf(const char *s, ...)
{
	va_list		args;
	int			index;
	int			written_bytes;
	t_bool		error;
	t_format	format;

	va_start(args, s);
	index = 0;
	written_bytes = 0;
	error = FALSE;
	while (s[index] && !error)
	{
		while (s[index] && s[index] != '%')
			written_bytes += write_e(STDOUT_FILENO, &s[index++], 1, &error);
		if (!s[index] || error)
			break ;
		index++;
		set_format(&format, s, &index);
		written_bytes += apply_conversion(&format, args, &error);
		index++;
	}
	if (error)
		return (-1);
	return (written_bytes);
}
