/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:10:18 by aapadill          #+#    #+#             */
/*   Updated: 2024/06/03 11:40:14 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dest;
	char	*result;

	len = ft_strlen(s1);
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	result = dest;
	while (*s1)
		*dest++ = *s1++;
	*dest = 0;
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	writable;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	writable = len;
	if (s_len - start < len)
		writable = s_len - start;
	sub = malloc(writable + sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, writable + 1);
	return (sub);
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

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	//clean possible '/n's
	if (!str)
		return (NULL); //free s1
	joined = str;
	while (s1 && *s1)
		*str++ = *s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = 0;
	if (s1)
		free(s1);
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
