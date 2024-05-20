/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_resize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:50:51 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/16 17:36:45 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarr_resize(char **arr, int size)
{
	char	**new_array;
	int		current_size;
	int		index;

	if (!arr)
		return (NULL);
	current_size = ft_strarr_len(arr);
	new_array = malloc(sizeof(char *) * (size + 1));
	if (!new_array)
		return (NULL);
	index = 0;
	while (index < current_size && index < size)
	{
		new_array[index] = ft_strdup(arr[index]);
		index++;
	}
	new_array[index] = NULL;
	ft_strarr_clear(arr);
	return (new_array);
}
