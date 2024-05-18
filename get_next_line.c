/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:06:36 by aapadill          #+#    #+#             */
/*   Updated: 2024/05/18 07:30:48 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//remove
#include <fcntl.h>
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	if (!*s)
		return (NULL);
	return ((char *)s);
}

char	ft_read(int fd, void *buffer, size_t buffer_size, ssize_t *checker)
{
	ssize_t	aux;

	//ft_bzero(buffer, buffer_size);
	aux = read(fd, buffer, buffer_size);
	//eof reached
	if (!aux)
		return (1);
	//error, u might check errno in the future
	if (aux < 0)
		*checker = -1;
	//bytes read and reached, double check it in case of terminal or pipe
	*checker += aux;
	if (aux < buffer_size)
		return (1);
	return (0);
}

char	*get_next_line(int fd, size_t buffer_size)
{
	void	*buffer;
	ssize_t	checker;
	char	eof;
	void	*nl_pos;
	unsigned long	i;

	checker = 0;
	eof = 0;
	buffer = malloc(buffer_size); //check if buffer_size //calloc?
	//check if null
	eof = ft_read(fd, buffer, buffer_size, &checker);
	nl_pos = ft_strchr(buffer, '\n');
	while (!eof && !nl_pos && checker != -1)
		eof = ft_read(fd, buffer, buffer_size, &checker);
	//what do i have to return?
	if (nl_pos)
	{
		i = nl_pos - buffer;
		//printf("nl found at char %i\n", (int)(nl_pos - buffer));
		//printf("%zd\n", checker);
		free(buffer);
		buffer = malloc(i + 1);
		ft_read(fd, buffer, i + 1, &checker);
	}
	printf("%s\n", (char *)buffer);
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
	//printf("%s", get_next_line(fd, 3));
	get_next_line(fd, 6);
	return 0;
}
