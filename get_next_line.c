/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:06:36 by aapadill          #+#    #+#             */
/*   Updated: 2024/05/21 16:49:14 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//remove
#include <fcntl.h>
#include <stdio.h>

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
	{
		*checker = -1;
		return (0);
	}
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

	printf("start--->%i", (int)i);
	if (!i)
	{
		//check if buffer_size
		buffer = malloc(buffer_size); //calloc?
		//check if null
		ft_bzero(buffer, buffer_size); //necessary?
	}
	while (!eof)
	{
		//printf("--->%s", (char *)buffer);
		if (checker > 0)
		{
			buffer_aux = malloc(checker + buffer_size);
			//check if null
			printf("\npointer--->%p<---", buffer_aux);
			if (buffer)
			{
				ft_memmove(buffer_aux, buffer, checker); //+buffer_size?
				free(buffer);
				buffer = buffer_aux;
				buffer_aux = NULL;
			}
		}
		eof = ft_read(fd, buffer, buffer_size, &checker);
		printf("debug--->%s<---", (char *)buffer);
		if(ft_strchr(buffer, '\n'))
			break;
	}
	if (buffer)
	{
		nl_pos = ft_strchr(buffer, '\n');
		if (nl_pos)
		{
			if (nl_pos < buffer + (checker - 1))
			{
				buffer_aux = malloc((buffer + checker) - nl_pos);
				//check null
				ft_memmove(buffer_aux, nl_pos + 1, (buffer + checker) - (nl_pos + 1));
				buffer_return = malloc((nl_pos + 1 - buffer));
				//check null
				ft_memmove(buffer_return, buffer, (nl_pos + 1 - buffer));
				free(buffer);
				buffer = buffer_aux;
				buffer_aux = NULL;
				return (buffer_return);
			}
			if (buffer + (checker - 1) == nl_pos)
			{
				printf("-->nl_pos is in the same place as buffer + checker<--");
				return (0);
			}
			else
			{
				printf("-->there's no new line in the buffer?<--");
			}
		}
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
	printf("%s", get_next_line(fd, 1));
	printf("%s", get_next_line(fd, 1));
	return 0;
}
