/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:28:34 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/30 14:55:28 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	apply_alt_form(char type, t_bool *error)
{
	if (type == 'x' || type == 'X' || type == 'p')
	{
		if (type == 'X')
			return (write_e(STDOUT_FILENO, "0X", 2, error));
		else
			return (write_e(STDOUT_FILENO, "0x", 2, error));
	}
	if (type == 'o')
		return (putchar_e('0', STDOUT_FILENO, error));
	return (0);
}

static int	init_size(unsigned long n, t_format *format)
{
	int	size;

	size = 0;
	if (format->conversion == 'x' || format->conversion == 'X'
		|| format->conversion == 'p')
		size = int_length_ul(n, 16);
	if (format->conversion == 'o')
		size = int_length_ul(n, 8);
	if (format->conversion == 'u')
		size = int_length_ul(n, 10);
	return (size);
}

static int	init_precision_padding(t_format *format, int size)
{
	int	precison_padding;

	precison_padding = 0;
	if (format->use_precision && format->precision > size)
		precison_padding = format->precision - size;
	return (precison_padding);
}

static int	init_padding(t_format *format, int size, int precison_padding,
							unsigned long n)
{
	int	padding;

	padding = 0;
	if (format->use_field_width
		&& format->field_width > size + precison_padding)
	{
		padding = format->field_width - (size + precison_padding);
		if (format->f_hash && (n || format->conversion == 'p'))
		{
			if (format->conversion == 'o')
				padding -= 1;
			else
				padding -= 2;
		}
	}
	return (padding);
}

int	print_u(unsigned long n, t_format *format, t_bool *error)
{
	const int	size = init_size(n, format);
	int			precison_padding;
	int			padding;
	int			count;

	count = 0;
	precison_padding = init_precision_padding(format, size);
	padding = init_padding(format, size, precison_padding, n);
	if (format->use_precision && !(format->precision) && !n)
		padding += 1;
	if (format->use_field_width && !format->f_dash
		&& !(format->f_zero && !format->use_precision))
		count += putchars_e(' ', padding, STDOUT_FILENO, error);
	if (format->f_hash && (n || format->conversion == 'p'))
		count += apply_alt_form(format->conversion, error);
	if (format->use_field_width && !format->f_dash
		&& (format->f_zero && !format->use_precision))
		count += putchars_e('0', padding, STDOUT_FILENO, error);
	count += putchars_e('0', precison_padding, STDOUT_FILENO, error);
	if (!(format->use_precision && !(format->precision) && !n))
		count += putnbr_u_e(n, format->conversion, STDOUT_FILENO, error);
	if (format->use_field_width && format->f_dash)
		count += putchars_e(' ', padding, STDOUT_FILENO, error);
	return (count);
}
