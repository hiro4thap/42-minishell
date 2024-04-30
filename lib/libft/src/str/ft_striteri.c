/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:16:23 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:21:46 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Applies 'f' to each character in 's', based on the index of the character.
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	index;

	index = 0;
	while (s[index])
	{
		(*f)(index, &s[index]);
		index++;
	}
}
