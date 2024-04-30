/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:26:58 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/30 14:53:00 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	apply_sign(t_format *format, t_bool *error)
{
	int	count;

	count = 0;
	if (format->f_sign || format->f_space || format->sign == '-')
	{
		count += 1;
		putchar_e(format->sign, STDOUT_FILENO, error);
	}
	return (count);
}

long	ft_power(unsigned int nb, size_t power)
{
	if (power == 0)
		return (1);
	else if (power == 1)
		return (nb);
	else
		return (nb * ft_power(nb, power - 1));
}

int	set_base(char type)
{
	int	base;

	base = 0;
	if (type == 'u')
		base = 10;
	else if (type == 'x' || type == 'X' || type == 'p')
		base = 16;
	else if (type == 'o')
		base = 8;
	return (base);
}

int	int_length(int n)
{
	int	digits;

	digits = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		digits++;
	}
	while (n > 9)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

int	int_length_ul(unsigned long n, unsigned long base)
{
	int	digits;

	if (!base)
		return (0);
	digits = 1;
	while (n >= base)
	{
		n /= base;
		digits++;
	}
	return (digits);
}
