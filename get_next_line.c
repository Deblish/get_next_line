/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:06:36 by aapadill          #+#    #+#             */
/*   Updated: 2024/06/09 16:36:25 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_update_buffer(char *buffer)
{
	char	*eol;
	char	*start;
	char	*new;

	eol = ft_strchr(buffer, '\n');
	start = buffer;
	if (eol)
		start = eol + 1;
	if (!*start)
	{
		free(buffer);
		return (NULL);
	}
	new = malloc(ft_strchr(start, '\0') - buffer + sizeof(char));
	if (!new)
	{
		free(buffer);
		return (NULL);
	}
	ft_strlcpy(new, start, ft_strchr(start, '\0') - buffer + sizeof(char));
	free(buffer);
	return (new);
}

static char	*ft_get_line(char *buffer)
{
	char	*line;
	char	*eol;
	size_t	len;

	eol = ft_strchr(buffer, '\n');
	if (!eol)
		len = ft_strchr(buffer, '\0') - buffer;
	if (eol)
		len = eol - buffer + 1;
	line = malloc(len + sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	ft_strlcpy(line, buffer, len + sizeof(char));
	return (line);
}

static int	ft_read_helper(ssize_t bytes_read, char **aux, char **buffer)
{
	char	*old;

	if (bytes_read < 0)
	{
		free(*aux);
		free(*buffer);
		return (-1);
	}
	if (bytes_read == 0)
		return (1);
	aux[0][bytes_read] = '\0';
	old = *buffer;
	*buffer = ft_strjoin(*buffer, *aux);
	free(old);
	if (!*buffer)
	{
		free(*aux);
		return (-1);
	}
	if (ft_strchr(*buffer, '\n'))
		return (1);
	return (0);
}

static char	*ft_read(int fd, char *buffer)
{
	char	*aux;
	ssize_t	bytes_read;
	int		stopper;

	aux = malloc(BUFFER_SIZE + sizeof(char));
	if (!aux)
	{
		free(buffer);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, aux, BUFFER_SIZE);
		stopper = ft_read_helper(bytes_read, &aux, &buffer);
		if (stopper < 0)
			return (NULL);
		if (stopper)
			break ;
	}
	free(aux);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || 0 > read(fd, 0, 0))
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	if (!line)
	{
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_update_buffer(buffer);
	if (!ft_strchr(line, '\n'))
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
