/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:06:36 by aapadill          #+#    #+#             */
/*   Updated: 2024/05/27 17:29:32 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 23
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

static char	*extract_line(char **buffer, int *buffer_length)
{
	int	i;
	char	*line;

	printf("buffer->%s<-", *buffer);
	i = ft_strchr(*buffer, '\n') - *buffer;
	//printf("i->%i\t", i);
	//printf("buffer_len->%i\t", *buffer_length);
	if (i < *buffer_length && (*buffer)[i] == '\n')
	{
		line = (char *)malloc(sizeof(char) * (i + 2));
		if (!line)
			return (NULL);
		ft_memmove(line, *buffer, i);
		line[i] = '\n';
		line[i + 1] = '\0';
		*buffer_length = *buffer_length - i - 1;
		if (!*buffer_length)
			*buffer[*buffer_length] = '\0';
		if (*buffer_length > 0)
			ft_memmove(*buffer, *buffer + i + 1, *buffer_length); //might be overflowing?
		return (line);
	}
	//printf("buffer_len->%i\t", i);
	//printf("buffer->%s", *buffer);
	(*buffer)[i] = '\0';
	//return (*buffer);
	return (NULL);
}

static char	*resize_and_read(int fd, char **buffer, int *buffer_length, int *eof)
{
	int	bytes_read;

	if (*buffer == NULL)
		if (!ft_resize(buffer, buffer_length)) //buffer_length here is zero
			return (NULL);
	bytes_read = 1;
	//you're assuming the buffer will be smaller eof position
	while (bytes_read > 0 && !ft_strchr(*buffer, '\n'))
	{
		if (*buffer_length >= BUFFER_SIZE)
			if(!ft_resize(buffer, buffer_length))
				return (NULL);
		bytes_read = read(fd, *buffer + *buffer_length, BUFFER_SIZE);
		printf("bytes_read->%i\t", (int)bytes_read);
		//printf("-->%s<--", *buffer);
		if (bytes_read > 0)
			*buffer_length += bytes_read;
	}
	if (ft_strchr(*buffer, '\n'))
		return (extract_line(buffer, buffer_length));
	//if (!bytes_read)
	//	return (*buffer); //this is just a guess, what is wrong?
	if (bytes_read < 1) //and eof?
	{
		*eof = 1;
		if (*buffer)
			free(*buffer);
		*buffer = NULL;
	}
	return (*buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	static int	buffer_length = 0;
	static int	eof = 0;
	char	*line;

	if (eof)
		return (NULL);
	line = resize_and_read(fd, &buffer, &buffer_length, &eof);
	while (!line && !eof)
		line = resize_and_read(fd, &buffer, &buffer_length, &eof);
	return (line);
	/*
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
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return 0;
}
