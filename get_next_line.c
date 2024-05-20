/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:06:36 by aapadill          #+#    #+#             */
/*   Updated: 2024/05/20 18:06:06 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//remove
#include <fcntl.h>
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*temp_dst;
	const char	*temp_src;

	if (!src && !dst)
		return (dst);
	temp_dst = (char *)dst;
	temp_src = (const char *)src;
	if ((const char *)src < (char *)dst)
		while (len--)
			*(temp_dst + len) = *(temp_src + len);
	else
		while (len--)
			*temp_dst++ = *temp_src++;
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = 0;
}

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
	aux = read(fd, buffer + *checker, buffer_size);
	//eof reached
	if (!aux)
		return (1);
	//error, u might check errno in the future
	if (aux < 0)
		*checker = -1;
	//bytes read and reached, double check it in case of terminal or pipe
	*checker += aux;
	//eof also reached
	if (aux < buffer_size)
		return (1);
	return (0);
}

char	*get_next_line(int fd, size_t buffer_size)
{
	void	*buffer;
	void	*buffer_aux;
	ssize_t	checker;
	char	eof;
	void	*nl_pos;
	unsigned long	i;

	buffer = NULL;
	if (!buffer)
	{
		checker = 0;
		eof = 0;
		//check if buffer_size
		buffer = malloc(buffer_size); //calloc?
		//check if null
		ft_bzero(buffer, buffer_size); //necessary?
	}
	//if (buffer)
	//{
	//	nl_pos = ft_strchr(buffer, '\n');
	//	if (nl_pos && *(nl_pos + 1))
			///////
	//}
	while (!eof && !ft_strchr(buffer, '\n'))
	{
		//printf("--->%s", (char *)buffer);
		if (checker > 0)
		{
			buffer_aux = malloc(checker + buffer_size);
			//check if null
			ft_memmove(buffer_aux, buffer, checker);
			free(buffer);
			buffer = buffer_aux;
			buffer_aux = NULL;
		}
		eof = ft_read(fd, buffer, buffer_size, &checker);
	}
	if (!eof) //next line stopped the loop
	{
		nl_pos = ft_strchr(buffer, '\n');
		//if (*(nl_pos + 1))
		//{
		//	buffer_aux =  
		//}
		printf("buffer---->%s\n", (char *)buffer);
		printf("nl_pos---->%s\n", (char *)nl_pos); //check nl_pos+1 is not null
	}
	else //eof stopped the loop
	{
		printf("buffer---->%s", (char *)buffer);
	}
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
	get_next_line(fd, 16);
	return 0;
}
