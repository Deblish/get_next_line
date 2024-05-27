/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:10:18 by aapadill          #+#    #+#             */
/*   Updated: 2024/05/27 11:25:51 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dst && !src)
		return (0);
	d = (char *)dst;
	s = (const char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

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
