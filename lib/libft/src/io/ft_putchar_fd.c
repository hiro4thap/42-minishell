/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:05 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:13:11 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Writes the value of 'c' to file descriptor 'fd'.
// fd = 1 corresponds to STDOUT, fd = 2 corresponds to STDERR.
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
