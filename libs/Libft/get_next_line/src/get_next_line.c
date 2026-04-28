/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:00:53 by pserre-s          #+#    #+#             */
/*   Updated: 2025/12/08 22:49:50 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free_all(char **stash, char *buffer)
{
	if (*stash)
		free(*stash);
	*stash = NULL;
	if (buffer)
		free(buffer);
	return (NULL);
}

char	*ft_extract_line_gnl(char **stash)
{
	size_t	len;
	char	*extracted_line;
	char	*remainder;

	len = 0;
	if (!*stash || !**stash)
		return (ft_free_all(stash, NULL));
	while ((*stash)[len] && (*stash)[len] != '\n')
		len++;
	if ((*stash)[len] == '\n')
		len++;
	extracted_line = malloc(len + 1);
	if (!extracted_line)
		return (ft_free_all(stash, NULL));
	ft_memcpy_gnl(extracted_line, *stash, len);
	extracted_line[len] = '\0';
	remainder = NULL;
	if ((*stash)[len])
		remainder = ft_strdup_gnl(*stash + len);
	if ((*stash)[len] && !remainder)
		return (free(extracted_line), ft_free_all(stash, NULL));
	free(*stash);
	*stash = remainder;
	return (extracted_line);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*buffer;
	ssize_t		r_byte;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	r_byte = 1;
	while (!ft_strchr_gnl(stash[fd], '\n') && r_byte > 0)
	{
		r_byte = read(fd, buffer, BUFFER_SIZE);
		if (r_byte < 0)
			return (ft_free_all(&stash[fd], buffer));
		if (r_byte == 0)
			break ;
		buffer[r_byte] = '\0';
		stash[fd] = ft_strjoin_gnl(stash[fd], buffer);
		if (!stash[fd])
			return (free(buffer), NULL);
	}
	free(buffer);
	return (ft_extract_line_gnl(&stash[fd]));
}
