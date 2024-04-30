/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:58 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/30 15:17:38 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Writes the string 's' to file descriptor 'fd'.
// fd = 1 corresponds to STDOUT, fd = 2 corresponds to STDERR.
void	ft_putstr_fd(char *s, int fd)
{
	int	count;

	count = 0;
	while (s[count])
		count++;
	write(fd, s, count);
}
