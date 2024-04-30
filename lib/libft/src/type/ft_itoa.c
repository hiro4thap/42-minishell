/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:16 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/08 23:56:38 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_length(int n)
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

static int	ft_power(int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	else if (power == 1)
		return (nb);
	else
		return (nb * ft_power(nb, power - 1));
}

static void	ensure_positive(int *n, size_t *size, char *output, int *index)
{
	if (*n < 0)
	{
		*n = -(*n);
		output[0] = '-';
		(*size)--;
		*index = 1;
	}
	else
		*index = 0;
}

// Converts an integer into a C string.
char	*ft_itoa(int n)
{
	size_t	size;
	char	*output;
	int		index;
	int		order_of_magnitude;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = int_length(n);
	output = malloc(sizeof(char) * (size + 1));
	if (!output)
		return (NULL);
	ensure_positive(&n, &size, output, &index);
	order_of_magnitude = ft_power(10, size - 1);
	while (order_of_magnitude > 0)
	{
		output[index++] = n / order_of_magnitude + '0';
		n %= order_of_magnitude;
		order_of_magnitude /= 10;
	}
	output[index] = '\0';
	return (output);
}
