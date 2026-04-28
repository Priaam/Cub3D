/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:00:30 by pserre-s          #+#    #+#             */
/*   Updated: 2025/12/08 22:50:34 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr_gnl(char *str, char c)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*source;

	if (!dest && !src)
		return (NULL);
	i = 0;
	dst = (unsigned char *)dest;
	source = (unsigned char *)src;
	while (i < n)
	{
		dst[i] = source[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup_gnl(char *str)
{
	char	*dup;
	size_t	i;

	if (!str)
		return (NULL);
	dup = (char *)malloc((ft_strlen_gnl(str) + 1) * sizeof(char));
	i = 0;
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin_gnl(char *stash, char *buffer)
{
	char	*result;
	size_t	len_stash;
	size_t	len_buffer;

	len_stash = ft_strlen_gnl(stash);
	len_buffer = ft_strlen_gnl(buffer);
	result = malloc(len_stash + len_buffer + 1);
	if (!result)
	{
		free(stash);
		return (NULL);
	}
	if (stash)
	{
		ft_memcpy_gnl(result, stash, len_stash);
		free(stash);
	}
	if (buffer)
		ft_memcpy_gnl(result + len_stash, buffer, len_buffer);
	result[len_stash + len_buffer] = '\0';
	return (result);
}
