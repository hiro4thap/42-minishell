/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_e.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:38:02 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/30 14:48:28 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	write_e(int fd, const char *buffer, size_t bytes, t_bool *error)
{
	int	output;

	if (*error)
		return (0);
	output = write(fd, buffer, bytes);
	if (output == -1)
	{
		*error = TRUE;
		return (0);
	}
	return (output);
}

int	putchar_e(char c, int fd, t_bool *error)
{
	int	output;

	output = write_e(fd, &c, 1, error);
	return (output);
}

int	putchars_e(char c, int count, int fd, t_bool *error)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (putchar_e(c, fd, error) == -1)
			break ;
		i++;
	}
	return (i);
}

// Writes the integer 'm' to file descriptor 'fd'.
// fd = 1 corresponds to STDOUT, fd = 2 corresponds to STDERR.
int	putnbr_e(int n, int fd, t_bool *error)
{
	int		written_bytes;
	char	c;

	written_bytes = 0;
	if (n == -2147483648)
		return (write_e(fd, "-2147483648", 11, error));
	if (n < 0)
	{
		written_bytes += write_e(fd, "-", 1, error);
		n = -n;
	}
	if (n > 9)
		written_bytes += putnbr_e(n / 10, fd, error);
	c = n % 10 + '0';
	written_bytes += write_e(fd, &c, 1, error);
	return (written_bytes);
}

int	putnbr_u_e(unsigned long u, char type, int fd, t_bool *error)
{
	const unsigned int	base = set_base(type);
	unsigned long		order_of_magnitude;
	int					size;
	char				c;
	int					written_bytes;

	size = int_length_ul(u, base);
	order_of_magnitude = ft_power(base, size - 1);
	written_bytes = 0;
	while (order_of_magnitude > 0)
	{
		c = u / order_of_magnitude;
		if (c < 10)
			c += '0';
		else if (type == 'X')
			c += 'A' - 10;
		else
			c += 'a' - 10;
		written_bytes += putchar_e(c, fd, error);
		u %= order_of_magnitude;
		order_of_magnitude /= base;
	}
	return (written_bytes);
}
