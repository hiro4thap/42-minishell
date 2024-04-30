/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:26 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/08 23:53:59 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts string to an integer. Handles leading whitespace and single sign.
// Any trailing characters are ignored.
int	ft_atoi(const char *nptr)
{
	int	output;
	int	sign;
	int	index;

	index = 0;
	while (nptr[index] == ' ' || (nptr[index] >= '\t' && nptr[index] <= '\r'))
		index++;
	sign = 1;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			sign = -sign;
		index++;
	}
	output = 0;
	while (ft_isdigit(nptr[index]))
	{
		output = output * 10 + nptr[index] - '0';
		index++;
	}
	return (sign * output);
}
