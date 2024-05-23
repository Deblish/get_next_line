/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:06:36 by aapadill          #+#    #+#             */
/*   Updated: 2024/05/23 15:13:15 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 6
//remove
#include <fcntl.h>
#include <stdio.h>

/*
char	ft_read(int fd, void *buffer, size_t buffer_size, ssize_t *checker)
{
	ssize_t	aux;

	aux = read(fd, buffer + *checker, buffer_size);
	if (aux == 0)
		return (1);
	if (aux < 0)
	{
		*checker = -1;
		return (0);
	}
	*checker += aux;
	if ((size_t)aux < buffer_size)
	{
		*checker = aux;
		return (1);
	}
	return (0);
}
*/

char	*ft_resize(char **buffer, int *buffer_length)
{
	char	*new_buffer;

	new_buffer = (char	*)malloc(sizeof(char) * (*buffer_length));
	if (!new_buffer)
		return (NULL);
	ft_memmove(new_buffer, *buffer, *buffer_length); //double check this
	free(*buffer);
	*buffer = new_buffer; 
	return (*buffer); //double check this
}

static char	*resize_and_read(int fd, char **buffer, int *buffer_length, int *eof)
{
	int	bytes_read;

	if (*buffer == NULL)
		if (!ft_resize(buffer, buffer_length)) //buffer_length here is zero
			return (NULL);
	//you gotta change this
	bytes_read = 1; 
	while (bytes_read > 0)
	{
		if (*buffer_length >= BUFFER_SIZE)
			if(!ft_resize(buffer, buffer_length))
				return (NULL);
		bytes_read = read(fd, *buffer + *buffer_length, BUFFER_SIZE);
		if (bytes_read < 0)
			break;
		*buffer_length += bytes_read;
		if (ft_strchr(*buffer, '\n'))
			break;
	}
	//buffer[*buffer_length] = 0;
	if (bytes_read == -1) //and eof?
	{
		free(buffer);
		return (NULL);
	}
	return (*buffer);
}

/*
static char	*extract_line(char **buffer, int *buffer_length)
{
	int	i;
	char	*line;

	i = 0;
	while (i < *buffer_length && (*buffer)[i] != '\n')
		i++;
	if (i < *buffer_length && (*buffer)[i] == '\n')
	{
		line = (char *)malloc(sizeof(char) * (i + 1));
		if (!line)
			return (NULL);
		ft_memmove(line, *buffer, i);
		line[i] = '\0';
		*buffer_length -= (i + 1);
		ft_memmove(*buffer, *buffer + i + 1, *buffer_length);
		return (line);
	}
	return (NULL);
}
*/

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	static int	buffer_length = 0;
	static int	eof = 0;
	char	*line;

	if (eof)
		return (NULL);
	if (!resize_and_read(fd, &buffer, &buffer_length, &eof))
		return (NULL);
	//if (!resize_and_read(fd, &buffer, &buffer_length, &eof))
	//	return (NULL);
	//if (!resize_and_read(fd, &buffer, &buffer_length, &eof))
	//	return (NULL);
	//if (!resize_and_read(fd, &buffer, &buffer_length, &eof))
	//	return (NULL);
	//printf("%s", buffer);
	/*line = extract_line(&buffer, &buffer_length);
	if (line)
		return (line);
	if (buffer_length > 0 && eof)
	{
		line = (char *)malloc(sizeof(char) * (buffer_length + 1));
		if (!line)
			return (NULL);
		ft_memmove(line, buffer, buffer_length);
		line[buffer_length] = '\0';
		buffer_length = 0;
		return (line);
	}
	*/
	return (buffer);
}

int	ft_open(char *file)
{
	return (open(file, O_RDONLY));
}

int main(void)
{
	int fd;
	fd = ft_open("test.txt");
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return 0;
}
