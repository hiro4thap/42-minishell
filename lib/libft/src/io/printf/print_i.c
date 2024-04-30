/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:28:34 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/30 14:48:18 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "limits.h"

static void	set_sign(int n, t_format *format)
{
	if (format->f_space && !format->f_sign)
		format->sign = ' ';
	if (format->f_sign && n >= 0)
		format->sign = '+';
	if (n < 0)
		format->sign = '-';
}

static void	init_padding(int *precison_padding, int *padding, int size,
							t_format *format)
{
	*precison_padding = 0;
	*padding = 0;
	if (format->use_precision && format->precision > size)
		*precison_padding = format->precision - size;
	if (format->use_field_width)
	{
		*padding = format->field_width - (size + *precison_padding);
		if (format->sign != '\0')
			*padding -= 1;
	}
}

static int	pad_front(int precison_padding, int padding, t_format *format,
						t_bool *error)
{
	int	count;

	count = 0;
	if (format->use_field_width && !format->f_dash
		&& !(format->f_zero && !format->use_precision))
		count += putchars_e(' ', padding, STDOUT_FILENO, error);
	if (format->sign)
		count += putchars_e(format->sign, 1, STDOUT_FILENO, error);
	if (format->use_field_width && !format->f_dash
		&& (format->f_zero && !format->use_precision))
		count += putchars_e('0', padding, STDOUT_FILENO, error);
	count += putchars_e('0', precison_padding, STDOUT_FILENO, error);
	return (count);
}

static int	print_d_min(t_format *format, t_bool *error)
{
	int		count;
	int		size;
	int		padding;
	int		precison_padding;

	format->sign = '-';
	size = 10;
	init_padding(&precison_padding, &padding, size, format);
	count = pad_front(precison_padding, padding, format, error);
	count += putnbr_e(2, STDOUT_FILENO, error);
	count += putnbr_e(147483648, STDOUT_FILENO, error);
	if (format->use_field_width && format->f_dash)
		count += putchars_e(' ', padding, STDOUT_FILENO, error);
	return (count);
}

int	print_i(int n, t_format *format, t_bool *error)
{
	int		count;
	int		size;
	int		padding;
	int		precison_padding;

	if (n == INT_MIN)
		return (print_d_min(format, error));
	size = 0;
	set_sign(n, format);
	if (n < 0)
		n = -n;
	size += int_length(n);
	init_padding(&precison_padding, &padding, size, format);
	if (format->use_precision && !(format->precision) && !n)
		padding += 1;
	count = pad_front(precison_padding, padding, format, error);
	if (!(format->use_precision && !(format->precision) && !n))
		count += putnbr_e(n, STDOUT_FILENO, error);
	if (format->use_field_width && format->f_dash)
		count += putchars_e(' ', padding, STDOUT_FILENO, error);
	return (count);
}
