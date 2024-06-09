/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:06:36 by aapadill          #+#    #+#             */
/*   Updated: 2024/06/09 03:05:26 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
//remove
#include <fcntl.h>
#include <stdio.h>
*/

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
	if (!eol) //technically you could erase this line
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

static char	*ft_read(int fd, char *buffer)
{
	char	*bytes_saved;
	char	*old;
	ssize_t	bytes_read;

	bytes_saved = malloc(BUFFER_SIZE + sizeof(char));
	if (!bytes_saved)
	{
		free(buffer);
		return (NULL);
	}
	//check for '\n' and erase them?
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, bytes_saved, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(bytes_saved);
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		bytes_saved[bytes_read] = '\0';
		old = buffer;
		buffer = ft_strjoin(buffer, bytes_saved);
		free(old);
		if (!buffer)
		{
			free(bytes_saved);
			return (NULL);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(bytes_saved);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	line = NULL;
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

/*
//remove
int	ft_open(char *file)
{
	return (open(file, O_RDONLY));
}

int main(void)
{
	int		fd;
	char	*line;

	fd = ft_open("test.txt");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
	//printf("%s", get_next_line(fd));
	return 0;
}
*/
