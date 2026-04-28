/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 02:51:47 by pserre-s          #+#    #+#             */
/*   Updated: 2026/01/23 03:16:36 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_first_word(char *str)
{
	int		i;
	int		start;
	int		len;
	char	*first_word;

	if (!str)
		return (NULL);
	i = 0;
	first_word = NULL;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	start = i;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	len = i - start;
	first_word = malloc(len + 1);
	if (!first_word)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		first_word[i] = str[start + i];
	}
	first_word[i] = '\0';
	return (first_word);
}
