/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:08:02 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/30 14:54:33 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "libft.h"

static int	print_s_null(char *str, t_format *format, t_bool *error)
{
	int	count;
	int	size;
	int	padding;
	int	i;

	padding = 0;
	count = 0;
	size = 6;
	if (ON_LINUX && format->use_precision && format->precision < size)
		size = 0;
	else if (format->use_precision && format->precision < size)
		size = format->precision;
	if (format->use_field_width && format->field_width > size)
		padding = format->field_width - size;
	if (format->use_field_width && !format->f_dash)
		count += putchars_e(' ', padding, STDOUT_FILENO, error);
	i = 0;
	while (i < size)
		count += putchar_e(str[i++], STDOUT_FILENO, error);
	if (format->use_field_width && format->f_dash)
		count += putchars_e(' ', padding, STDOUT_FILENO, error);
	return (count);
}

int	print_s(char *s, t_format *format, t_bool *error)
{
	int	count;
	int	size;
	int	padding;
	int	i;

	if (!s)
		return (print_s_null("(null)", format, error));
	padding = 0;
	count = 0;
	size = ft_strlen(s);
	if (format->use_precision && format->precision < size)
		size = format->precision;
	if (format->use_field_width && format->field_width > size)
		padding = format->field_width - size;
	if (format->use_field_width && !format->f_dash)
		count += putchars_e(' ', padding, STDOUT_FILENO, error);
	i = 0;
	while (i < size)
		count += putchar_e(s[i++], STDOUT_FILENO, error);
	if (format->use_field_width && format->f_dash)
		count += putchars_e(' ', padding, STDOUT_FILENO, error);
	return (count);
}

int	print_c(char c, t_format *format, t_bool *error)
{
	const int	size = 1;
	int			count;
	int			padding;

	if (ON_LINUX && format->conversion == '%')
		return (putchar_e(c, STDOUT_FILENO, error));
	padding = 0;
	count = 0;
	if (format->use_field_width && format->field_width > size)
		padding = format->field_width - size;
	if (format->use_field_width && !format->f_dash)
		count += putchars_e(' ', padding, STDOUT_FILENO, error);
	count += putchar_e(c, STDOUT_FILENO, error);
	if (format->use_field_width && format->f_dash)
		count += putchars_e(' ', padding, STDOUT_FILENO, error);
	return (count);
}

int	print_p(void *p, t_format *format, t_bool *error)
{
	if (ON_LINUX && !p)
	{
		format->use_precision = FALSE;
		return (print_s("(nil)", format, error));
	}
	if (!format->f_hash)
		format->f_hash = TRUE;
	return (print_u((unsigned long) p, format, error));
}
