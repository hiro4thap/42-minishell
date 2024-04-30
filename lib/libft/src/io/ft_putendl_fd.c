/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:04 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/30 15:18:34 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Writes the string 's' to file descriptor 'fd', followed by a newline.
// fd = 1 corresponds to STDOUT, fd = 2 corresponds to STDERR.
void	ft_putendl_fd(char *s, int fd)
{
	int	count;

	count = 0;
	while (s[count])
		count++;
	write(fd, s, count);
	write(fd, "\n", 1);
}
