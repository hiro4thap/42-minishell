/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:15:57 by jhughes           #+#    #+#             */
/*   Updated: 2024/04/23 00:52:42 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns index of first 'c' in 'str', or -1 not found/error occurs
static int	ft_strfind(char *str, char c)
{
	int	index;

	if (!str || !c)
		return (-1);
	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

// Adds read_buffer to buffer and stores result in buffer, frees previous result
// Returns NULL if str_join fails. Expects read_buffer to not be NULL.
static char	*update_buffer(char **buffer, char *read_buffer)
{
	char	*output;

	if (!read_buffer)
	{
		free(*buffer);
		return (NULL);
	}
	if (!*buffer)
		output = ft_strjoin("", read_buffer);
	else
		output = ft_strjoin(*buffer, read_buffer);
	free(*buffer);
	return (output);
}

static char	*buffer_new_data(char **buffer, int fd)
{
	char	*read_buffer;
	int		bytes_read;

	while (ft_strfind(*buffer, '\n') == -1)
	{
		read_buffer = ft_calloc(BUFFER_SIZE +1, sizeof(char));
		if (!read_buffer)
			return (update_buffer(buffer, NULL));
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 1)
			break ;
		*buffer = update_buffer(buffer, read_buffer);
		free(read_buffer);
		if (bytes_read < BUFFER_SIZE)
			break ;
	}
	if (bytes_read < 1)
		free(read_buffer);
	if (bytes_read == -1)
		return (update_buffer(buffer, NULL));
	return (*buffer);
}

// Pops the next line from the provided buffer
static char	*get_line_from_buffer(char **buffer)
{
	const int	index = ft_strfind(*buffer, '\n');
	const int	size = ft_strlen(*buffer);
	char		*output;
	char		*new_buffer;

	new_buffer = NULL;
	if (index == -1 || index + 1 == size)
		output = ft_substr(*buffer, 0, size);
	else
	{
		output = ft_substr(*buffer, 0, index + 1);
		if (output)
		{
			new_buffer = ft_substr(*buffer, index + 1, size - (index + 1));
			if (!new_buffer)
			{
				free(output);
				output = NULL;
			}
		}
	}
	free(*buffer);
	*buffer = new_buffer;
	return (output);
}

// Get the next line from fd
// Return a malloced string, or NULL if nothing to be read or on error.
char	*get_next_line(int fd)
{
	static char	*buffer[FILES_LIMIT];
	char		*output;

	if (fd < 0 || fd >= FILES_LIMIT)
		return (NULL);
	if (ft_strfind(buffer[fd], '\n') == -1)
		buffer[fd] = buffer_new_data(&buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	output = get_line_from_buffer(&buffer[fd]);
	return (output);
}
