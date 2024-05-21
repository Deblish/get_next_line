/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:06:36 by aapadill          #+#    #+#             */
/*   Updated: 2024/05/20 23:18:24 by aapadill         ###   ########.fr       */
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
	aux = read(fd, buffer, buffer_size);
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
	{
		*checker = aux;
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd, size_t buffer_size)
{
	static void	*buffer = NULL;
	void	*buffer_aux;
	void	*buffer_return;
	static ssize_t	checker = 0;
	static char	eof = 0;
	void	*nl_pos;
	static unsigned long	i = 0;

	//buffer = NULL;
	if (!buffer && !i)
	{
		//checker = 0;
		//eof = 0;
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
	while (!eof)
	{
		//printf("--->%s", (char *)buffer);
		if (checker > 0)
		{
			buffer_aux = malloc(checker + buffer_size);
			//check if null
			ft_memmove(buffer_aux, buffer, checker); //+buffer_size?
			free(buffer);
			buffer = buffer_aux;
			//buffer_aux = NULL;
		}
		eof = ft_read(fd, buffer + checker, buffer_size, &checker);
		printf("debug--->%s<---", (char *)buffer);
		if(ft_strchr(buffer, '\n'))
			break;
	}
	if (buffer)
	{
		nl_pos = ft_strchr(buffer, '\n');
		if (nl_pos)
		{
			//if (*((char *)nl_pos + 1))
			//{
				//printf("debug--->%i<---", (int)checker);
				//printf("about to malloc--->%li<---", (buffer + checker) - nl_pos);
				buffer_aux = malloc((buffer + checker) - nl_pos);
				//check null
				//printf("debug--->%s<---", (char *)nl_pos);
				if (*((char *)nl_pos + 1))
					ft_memmove(buffer_aux, nl_pos + 1, (buffer + checker) - nl_pos);
				else
					ft_memmove(buffer_aux, nl_pos, (buffer + checker) - nl_pos);
				//printf("about to malloc--->%li<---", nl_pos - buffer);
				buffer_return = malloc((nl_pos - buffer));
				//check null
				//printf("about to malloc--->%li<---", (nl_pos - buffer) + 1);
				ft_memmove(buffer_return, buffer, (nl_pos - buffer) + 1);
				free(buffer);
				//printf("left--->%s<---", (char *)buffer_aux);
				buffer = buffer_aux;
				return (buffer_return);
			//}
			//printf("buffer---->%s\n", (char *)buffer);
			//printf("nl_pos---->%s\n", (char *)nl_pos); //check nl_pos+1 is not null
		}
		//else //eof stopped the loop
		//{
		//	printf("buffer---->%s", (char *)buffer);
		//}
		buffer_return = malloc(checker);
		//check null
		ft_memmove(buffer_return, buffer, checker);
		free(buffer);
		buffer = NULL;
		i = 1;
		//printf("debug---->%s\n", (char *)buffer);
		return (buffer_return);
	}
	return(NULL);
}

int	ft_open(char *file)
{
	return (open(file, O_RDONLY));
}

int main(void)
{
	int fd;
	fd = ft_open("test.txt");
	printf("%s", get_next_line(fd, 8));
	printf("%s", get_next_line(fd, 8));
	return 0;
}
