/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:10:18 by aapadill          #+#    #+#             */
/*   Updated: 2024/06/03 18:23:46 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//remove
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (!dstsize)
		return (srclen);
	while (dstsize - 1 && *src)
	{
		*dst++ = *src++;
		dstsize--;
	}
	*dst = 0;
	return (srclen);
}

size_t	ft_strlen(const char *s)
{
	const char	*end;

	if (!s)
		return (0);
	end = s;
	while (*end)
		end++;
	return (end - s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*joined;
	char	*x;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + sizeof(char));
	//printf("\ts1->%zu", ft_strlen(s1));
	printf("\ts2->%zu\t", ft_strlen(s2));
	//clean possible '/n's
	if (!str)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	joined = str;
	//x = s1;
	while (s1 && *s1)
		*str++ = *s1++;
	//if (x)
	//	free(x);
	//x = s2;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = 0;
	//if (x)
	//	free(x);
	return (joined);
}

/*
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = 0;
}
*/

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
